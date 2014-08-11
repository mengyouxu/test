#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DEBUG_PRINT_LINE() printf("%s()L%d\n",__func__,__LINE__)
#define BUFFER_SIZE 1024
static int current_status;
using namespace std;
typedef struct{
    HANDLE *hCom;
}ARG_READ;

DWORD WINAPI ThreadReadSerialPort(void *pM){
    HANDLE *hCom;
    //get serial port input
    char lpInBuffer[BUFFER_SIZE];
    DWORD dwBytesRead=BUFFER_SIZE;
    BOOL bReadStatus;
    DWORD dwErrorFlags;
    COMSTAT ComStat;
    OVERLAPPED m_osRead;
    hCom = ((ARG_READ*)pM)->hCom;
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
            }
        }else{
            printf("%s",lpInBuffer);
        }
    }
}

int main()
{
    HANDLE hCom;
    //��COM4,���������첽��ʽ��(FILE_FLAG_OVERLAPPED)
    hCom = CreateFile("COM4",
					GENERIC_READ|GENERIC_WRITE,
					0, //��ռ��ʽ
					NULL,
					OPEN_EXISTING, //�򿪶����Ǵ���
					FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //�첽
					NULL);
	if(hCom == INVALID_HANDLE_VALUE){
		DEBUG_PRINT_LINE();
		printf("open COM5 fail, err:%d\n",GetLastError());
		return 0;
	}
	SetupComm(hCom,1024,1024);

	DCB dcb;
	GetCommState(hCom,&dcb);
    dcb.BaudRate=115200;
    dcb.ByteSize=8;
	dcb.Parity=NOPARITY; //����żУ��λ
	dcb.StopBits=TWOSTOPBITS; //����ֹͣλ
	SetCommState(hCom,&dcb);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//�ڶ�д����֮ǰ����Ҫ��PurgeComm()������ջ�����

    current_status=1;
    ARG_READ arg;
    arg.hCom=&hCom;
    HANDLE handle = CreateThread(NULL, 0, ThreadReadSerialPort, &arg, 0, NULL);

    char lpOutBuffer[BUFFER_SIZE];
    DWORD dwBytesWrite=0;
    COMSTAT ComStat;
    DWORD dwErrorFlags;
    BOOL bWriteStat;
    OVERLAPPED m_osWrite;
    int err = 0;

    //��ʼ��overlaooped�ṹ����//����WriteFile(hCom,...)��GetLastError()==6����Ч���
    m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    m_osWrite.Offset =  0;
    m_osWrite.OffsetHigh =  0;

    while(1){
        memset(lpOutBuffer,'\0',BUFFER_SIZE);
        //printf("[%d]Waiting for ...\n",__LINE__);
        fgets(lpOutBuffer,BUFFER_SIZE,stdin);
        dwBytesWrite = strlen(lpOutBuffer);
        //printf("input[%d]: %s\n",dwBytesWrite,lpOutBuffer);
        ClearCommError(hCom,&dwErrorFlags,&ComStat);
        PurgeComm(hCom,PURGE_TXCLEAR);//�ڶ�д����֮ǰ����Ҫ��PurgeComm()������ջ�����
        /*
		PURGE_TXABORT     �ж�����д�������������أ���ʹд������û����ɡ�
		PURGE_RXABORT     �ж����ж��������������أ���ʹ��������û����ɡ�
		PURGE_TXCLEAR     ������������
		PURGE_RXCLEAR     ������뻺����
        */
        bWriteStat = WriteFile(hCom,lpOutBuffer,dwBytesWrite,&dwBytesWrite,&m_osWrite);
        err = GetLastError();
        //printf("Last err: %d \n",err);
        if(bWriteStat==FALSE)
        {
            if(err==ERROR_IO_PENDING)
            {
                WaitForSingleObject(m_osWrite.hEvent,1000);
            }
        }

        if(strncmp(lpOutBuffer,"exit",4) == 0) {
            TerminateThread(handle,0);
            break;
        }
    }
    WaitForSingleObject(handle, INFINITE);

    CloseHandle(hCom);
    return 0;
}
