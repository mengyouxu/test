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
        //PurgeComm(*hCom,PURGE_RXCLEAR);//打开该行会导致一些数据丢失，why???
        bReadStatus = ReadFile(*hCom,lpInBuffer,dwBytesRead,&dwBytesRead,&m_osRead);
        err = GetLastError();
        if(bReadStatus == FALSE){
            if(err==ERROR_IO_PENDING){
                GetOverlappedResult(*hCom,&m_osRead,&dwBytesRead,TRUE);
                // GetOverlappedResult函数的最后一个参数设为TRUE，
                //函数会一直等待，直到读操作完成或由于错误而返回。
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
    //打开COM4,下面是以异步方式打开(FILE_FLAG_OVERLAPPED)
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

    //初始化overlaooped结构！！//否则WriteFile(hCom,...)会GetLastError()==6，无效句柄
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
        PurgeComm(hCom,PURGE_TXCLEAR);//在读写串口之前，还要用PurgeComm()函数清空缓冲区
        /*
		PURGE_TXABORT     中断所有写操作并立即返回，即使写操作还没有完成。
		PURGE_RXABORT     中断所有读操作并立即返回，即使读操作还没有完成。
		PURGE_TXCLEAR     清除输出缓冲区
		PURGE_RXCLEAR     清除输入缓冲区
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
