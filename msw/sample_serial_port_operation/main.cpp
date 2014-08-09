#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DEBUG_PRINT_LINE() printf("%s()L%d\n",__func__,__LINE__)

using namespace std;

int main()
{
    HANDLE hCom;

    cout << "Hello world!" << endl;

    hCom = CreateFile("COM5",
					GENERIC_READ|GENERIC_WRITE,
					0, //独占方式
					NULL,
					OPEN_EXISTING, //打开而不是创建
					0,//FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //异步
					NULL);
	if(hCom == INVALID_HANDLE_VALUE){
		DEBUG_PRINT_LINE();
		printf("open COM5 fail, err:%d\n",GetLastError());
		return 0;
	}
	SetupComm(hCom,1024,1024);

	DCB dcb;
	GetCommState(hCom,&dcb);
    dcb.BaudRate=9600;
    dcb.ByteSize=8;
	dcb.Parity=NOPARITY; //无奇偶校验位
	dcb.StopBits=TWOSTOPBITS; //两个停止位
	SetCommState(hCom,&dcb);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//在读写串口之前，还要用PurgeComm()函数清空缓冲区

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
