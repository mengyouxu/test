#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DEBUG_PRINT_LINE() printf("%s()L%d\n",__func__,__LINE__)
#define BUFFER_SIZE 1024

using namespace std;

class SerialPort{
public:
    SerialPort(LPCSTR com,int bautRate);
    ~SerialPort();

    int SendData(char *data,int size);
    //virtual void NotifyDataRecv(unsigned char*buff, int size) = 0;
private:
    HANDLE hCom;  //���ھ��
    HANDLE hThreadRecvData;
    HANDLE hThreadCtrlHaneler;
    HWND hConsole;
    OVERLAPPED m_osWrite;
    DCB dcb;

    static DWORD WINAPI threadReadSerialPort(void *pM);
    static DWORD WINAPI threadCtrlHandler(void *pM);
    BOOL CtrlHandler(DWORD fdwCtrlType);
};
SerialPort::SerialPort(LPCSTR com,int bautRate)
{
    //��COM4,���������첽��ʽ��(FILE_FLAG_OVERLAPPED)
    hCom = CreateFile(com,
					GENERIC_READ|GENERIC_WRITE,
					0, //��ռ��ʽ
					NULL,
					OPEN_EXISTING, //�򿪶����Ǵ���
					FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //�첽
					NULL);
	if(hCom == INVALID_HANDLE_VALUE){
		DEBUG_PRINT_LINE();
		printf("open COM5 fail, err:%d\n",GetLastError());
		return;
	}else{
        SetupComm(hCom,1024,1024);
	}
    m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    /*
       BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE HandlerRoutine,BOOL Add);
       ����Console ���źŴ�������Add==TRUE-->��ӣ�Add==FALSE-->�Ƴ�

       HandlerRoutine() :���䷵��TRUE,��ǰ�յ�����Ϣ�����ݸ�����CtrlHandler��
       ������FALSE,��ǰsignal�����������ǰconsole ������CtrlHandler����
    */
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)&SerialPort::CtrlHandler,TRUE);//��Ա����ָ����÷�!!!

	GetCommState(hCom,&dcb);
    dcb.BaudRate=bautRate;
    dcb.ByteSize=8;
	dcb.Parity=NOPARITY; //����żУ��λ
	dcb.StopBits=TWOSTOPBITS; //����ֹͣλ
	SetCommState(hCom,&dcb);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//�ڶ�д����֮ǰ����Ҫ��PurgeComm()������ջ�����
    hConsole = GetActiveWindow();
	this->hThreadRecvData = CreateThread(NULL, 0, this->threadReadSerialPort, &hCom, 0, NULL);
	this->hThreadCtrlHaneler = CreateThread(NULL, 0, this->threadCtrlHandler, &hConsole, 0, NULL);
}

SerialPort::~SerialPort()
{
    TerminateThread(this->hThreadRecvData,0);
    TerminateThread(this->hThreadCtrlHaneler,0);
    CloseHandle(hCom);
}
int SerialPort::SendData(char *data,int size)
{

    char lpOutBuffer[BUFFER_SIZE];
    DWORD dwBytesWrite=0;
    COMSTAT ComStat;
    DWORD dwErrorFlags;
    BOOL bWriteStat;

    int err = 0;

    //��ʼ��overlaooped�ṹ����//����WriteFile(hCom,...)��GetLastError()==6����Ч���

    m_osWrite.Offset =  0;
    m_osWrite.OffsetHigh =  0;

    //printf("input[%d]: %s\n",dwBytesWrite,lpOutBuffer);
    ClearCommError(hCom,&dwErrorFlags,&ComStat);
    PurgeComm(hCom,PURGE_TXCLEAR);//�ڶ�д����֮ǰ����Ҫ��PurgeComm()������ջ�����
    /*
    PURGE_TXABORT     �ж�����д�������������أ���ʹд������û����ɡ�
    PURGE_RXABORT     �ж����ж��������������أ���ʹ��������û����ɡ�
    PURGE_TXCLEAR     ������������
    PURGE_RXCLEAR     ������뻺����
    */
    bWriteStat = WriteFile(hCom,data,size,&dwBytesWrite,&m_osWrite);
    err = GetLastError();
    //printf("Last err: %d \n",err);
    if(bWriteStat==FALSE)
    {
        if(err==ERROR_IO_PENDING)
        {
            //WaitForSingleObject(m_osWrite.hEvent,1000);
        }
    }

    return dwBytesWrite;
    //WaitForSingleObject(handle, INFINITE);
}
DWORD WINAPI SerialPort::threadReadSerialPort(void *pM){
    HANDLE *hCom;
    //get serial port input
    char lpInBuffer[BUFFER_SIZE];
    DWORD dwBytesRead=BUFFER_SIZE;
    BOOL bReadStatus;
    DWORD dwErrorFlags;
    COMSTAT ComStat;
    OVERLAPPED m_osRead;

    hCom = (HANDLE*)pM;
    int err = 0;
    while(1){
        memset(lpInBuffer,'\0',BUFFER_SIZE);
        //printf("[%d]Waiting for ...\n",__LINE__);
        ClearCommError(*hCom,&dwErrorFlags,&ComStat);
        dwBytesRead = BUFFER_SIZE;
        //PurgeComm(*hCom,PURGE_RXCLEAR);//�򿪸��лᵼ��һЩ���ݶ�ʧ��why???
        bReadStatus = ReadFile(*hCom,lpInBuffer,dwBytesRead,&dwBytesRead,&m_osRead);
        err = GetLastError();
        if(bReadStatus == FALSE){
            if(err==ERROR_IO_PENDING){
                GetOverlappedResult(*hCom,&m_osRead,&dwBytesRead,TRUE);
                // GetOverlappedResult���������һ��������ΪTRUE��
                //������һֱ�ȴ���ֱ����������ɻ����ڴ�������ء�
                printf("%s",lpInBuffer);
                //NotifyDataRecv(lpInBuffer,dwBytesRead);
            }
        }else{
            //NotifyDataRecv(lpInBuffer,dwBytesRead);
            printf("%s",lpInBuffer);
        }
    }
    return 0;
}
/*
    CtrlHandler() ��������Console�յ����ź�:
    CTRL_C_EVENT
    CTRL_BREAK_EVENT
    CTRL_CLOSE_EVENT
    CTRL_LOGOFF_EVENT
    CTRL_SHUTDOWN_EVENT

    See: SetConsoleCtrlHandler()
*/
BOOL SerialPort::CtrlHandler(DWORD fdwCtrlType)
{
  switch( fdwCtrlType )
  {
    // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
      printf( "Ctrl-C event\n\n" );
      Beep( 750, 300 );
      return( TRUE );

    // CTRL-CLOSE: confirm that the user wants to exit.
    case CTRL_CLOSE_EVENT:
      Beep( 600, 200 );
      printf( "Ctrl-Close event\n\n" );
      return( TRUE );

    // Pass other signals to the next handler.
    case CTRL_BREAK_EVENT:
      Beep( 900, 200 );
      printf( "Ctrl-Break event\n\n" );
      return FALSE;

    case CTRL_LOGOFF_EVENT:
      Beep( 1000, 200 );
      printf( "Ctrl-Logoff event\n\n" );
      return FALSE;

    case CTRL_SHUTDOWN_EVENT:
      Beep( 750, 500 );
      printf( "Ctrl-Shutdown event\n\n" );
      return FALSE;

    default:
      return FALSE;
  }
}

DWORD WINAPI SerialPort::threadCtrlHandler(void *pM)
{
    //HWND *hConsole = (HWND *)pM;
    MSG msg = {0};
    //MOD_NOREPEAT --> From win7
    //RegisterHotKey(*hConsole,1,MOD_CONTROL,0x42);//'b',��ͬSDK�ж�����ַ�ֵ���ܲ�ͬ,��������ֱ������ֵ��ʾ�ַ�
    //RegisterHotKey(*hConsole,2,MOD_CONTROL,0x43);//'c'
    /*
        RegisterHotKey() Defines a system-wide hot key
        �ú�����ע��ȫ��hot key��������Ҳ���ǻ����������������ڵ�hot key
        ���ԣ������Ƚ�Ctrl + c���� CtrlHandler() ����.
    */

    printf("Enter threadHotKey\n");
    printf("\'a\'=%#x\n",'a');
    while(GetMessage(&msg,NULL,0,0)!=0){
        printf("Get message:%d,wParam:%d\n ",msg.message,msg.wParam);
        if(msg.message == WM_HOTKEY){
            switch(msg.wParam){
            default:
                printf("wParam:%#x\n",msg.wParam);
            }
        }
    }
    return 0;
}
int main()
{
    SerialPort *com = new SerialPort("COM4",115200);
    char *lpOutBuffer = (char*)malloc(BUFFER_SIZE);

    while(1){
        memset(lpOutBuffer,'\0',BUFFER_SIZE);
        //printf("[%d]Waiting for ...\n",__LINE__);
        fgets(lpOutBuffer,BUFFER_SIZE,stdin);

        com->SendData(lpOutBuffer,strlen(lpOutBuffer));
        if(strncmp(lpOutBuffer,"exit",4) == 0) {
            //TerminateThread(handle,0);
            break;
        }
    }
    delete com;
    free(lpOutBuffer);
    return 0;
}
