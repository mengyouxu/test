#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DEBUG_PRINT_LINE() printf("%s()L%d\n",__func__,__LINE__)

static int current_status;
using namespace std;
typedef struct{
    HANDLE *hCom;
}ARG_READ;

DWORD WINAPI ThreadReadSerialPort(void *pM){
    HANDLE *hCom;
    //get serial port input
    char lpInBuffer[1024];
    DWORD dwBytesRead=1024;
    BOOL bReadStatus;
    DWORD dwErrorFlags;
    COMSTAT ComStat;
    OVERLAPPED m_osRead;
    hCom = ((ARG_READ*)pM)->hCom;
    int err = 0;
    while(current_status == 1){
        memset(lpInBuffer,'\0',1024);
        //printf("[%d]Waiting for ...\n",__LINE__);
        ClearCommError(*hCom,&dwErrorFlags,&ComStat);
        dwBytesRead = 1024;
        dwBytesRead = ReadFile(*hCom,lpInBuffer,dwBytesRead,&dwBytesRead,&m_osRead);
        err = GetLastError();
        if(bReadStatus == FALSE){
            printf("LastError:%d\n",err);
            if(err==ERROR_IO_PENDING){
                GetOverlappedResult(*hCom,&m_osRead,&dwBytesRead,TRUE);
                // GetOverlappedResult函数的最后一个参数设为TRUE，
                //函数会一直等待，直到读操作完成或由于错误而返回。
                printf("------> %s",lpInBuffer);
                printf("Read %d\n",dwBytesRead);
            }
        }
    }
}

int main()
{
    HANDLE hCom;

    cout << "Hello world!" << endl;

    hCom = CreateFile("COM4",
					GENERIC_READ|GENERIC_WRITE,
					0, //独占方式
					NULL,
					OPEN_EXISTING, //打开而不是创建
					FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //异步
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
	dcb.Parity=NOPARITY; //无奇偶校验位
	dcb.StopBits=TWOSTOPBITS; //两个停止位
	SetCommState(hCom,&dcb);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//在读写串口之前，还要用PurgeComm()函数清空缓冲区
/*  // 写数据到串口
	char lpOutBuffer[100];
	memset(lpOutBuffer,'0',100);
	memcpy(lpOutBuffer,"hello world\n",12);
	DWORD dwBytesWrite=100;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom,lpOutBuffer,12,&dwBytesWrite,NULL);
	if(!bWriteStat)
	{
	   	DEBUG_PRINT_LINE();
	   	printf("WriteFile ERR:%d\n",GetLastError());
	}
*/
    current_status=1;
    ARG_READ arg;
    arg.hCom=&hCom;
    HANDLE handle = CreateThread(NULL, 0, ThreadReadSerialPort, &arg, 0, NULL);

    while(1){
        printf("[%d]Waiting for ...\n",__LINE__);
        scanf("%d",&current_status);
        if(current_status == 0) break;

    }
    WaitForSingleObject(handle, INFINITE);

	PurgeComm(hCom, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	/*
		PURGE_TXABORT     中断所有写操作并立即返回，即使写操作还没有完成。
		PURGE_RXABORT     中断所有读操作并立即返回，即使读操作还没有完成。
		PURGE_TXCLEAR     清除输出缓冲区
		PURGE_RXCLEAR     清除输入缓冲区
	*/

    CloseHandle(hCom);
    return 0;
}
