#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define LINE() printf("[Debug]----> %s() L:%d\n",__func__,__LINE__)

typedef enum{
    ENUM_NORMAL_FILE,
    ENUM_DIRECTORY

}M_FILE_TYPE;

typedef struct{
    char *file_name;
    char *parent_dir;
    M_FILE_TYPE file_type;

}M_FILE_INFO;
void get_current_dir(TCHAR *Buffer)
{
	//TCHAR Buffer[MAX_PATH];
	DWORD dwRet;
	
	dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
	if( dwRet == 0 )
	{
		printf("GetCurrentDirectory failed (%d)\n", GetLastError());
		return;
	}
	if(dwRet > MAX_PATH)
	{
		printf("Buffer too small; need %d characters\n", dwRet);
		return;
	}
}

int print_file_info(TCHAR *Buffer)
{
	SYSTEMTIME ct, lat,lwt; // create_time, last_access_time, last_write_time
	int ret = 0;
	WIN32_FILE_ATTRIBUTE_DATA FileInformation;
	
	ret = GetFileAttributesEx(Buffer,GetFileExInfoStandard,&FileInformation);
	
	FileTimeToSystemTime(&FileInformation.ftCreationTime,&ct);
	FileTimeToSystemTime(&FileInformation.ftLastAccessTime,&lat);
	FileTimeToSystemTime(&FileInformation.ftLastWriteTime,&lwt);

	printf("F	%.4d%.2d%.2d-%.2d%.2d%.2d	%.4d%.2d%.2d-%.2d%.2d%.2d	%.4d%.2d%.2d-%.2d%.2d%.2d	%s\n",
		ct.wYear,ct.wMonth,ct.wDay,ct.wHour,ct.wMinute,ct.wSecond,
		lat.wYear,lat.wMonth,lat.wDay,lat.wHour,lat.wMinute,lat.wSecond,
		lwt.wYear,lwt.wMonth,lwt.wDay,lwt.wHour,lwt.wMinute,lwt.wSecond,
		Buffer);
	return 0;
}
int list_dir(char *path){
  // List dir with WIN32 API
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;
	TCHAR Buffer[MAX_PATH];
    WIN32_FIND_DATA ffd;
	SYSTEMTIME ct, lat,lwt; // create_time, last_access_time, last_write_time
    //M_FILE_INFO *p_file_info;
	int file_num=0;

    int path_length = strlen(path);
	if(path_length>MAX_PATH){ 
		return 0;
	}
	
	strcpy(Buffer,path);
	strcat(Buffer,"\\*");

    hFind = FindFirstFile(Buffer,&ffd);
    if(INVALID_HANDLE_VALUE == hFind){
        LINE();
        dwError = GetLastError();
        printf("GetLastError = %d\n",dwError);
        return dwError;
    }

    //printf("size of M_FILE_INFO : %d\n",sizeof(M_FILE_INFO));
	
    do{
        //p_file_info = (M_FILE_INFO *)malloc(sizeof(M_FILE_INFO));
		FileTimeToSystemTime(&ffd.ftCreationTime,&ct);
		FileTimeToSystemTime(&ffd.ftLastAccessTime,&lat);
		FileTimeToSystemTime(&ffd.ftLastWriteTime,&lwt);
        if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
            //p_file_info->file_type=ENUM_DIRECTORY;
			printf("D	%.4d%.2d%.2d-%.2d%.2d%.2d	%.4d%.2d%.2d-%.2d%.2d%.2d	%.4d%.2d%.2d-%.2d%.2d%.2d	%s\n",
				ct.wYear,ct.wMonth,ct.wDay,ct.wHour,ct.wMinute,ct.wSecond,
				lat.wYear,lat.wMonth,lat.wDay,lat.wHour,lat.wMinute,lat.wSecond,
				lwt.wYear,lwt.wMonth,lwt.wDay,lwt.wHour,lwt.wMinute,lwt.wSecond,
				ffd.cFileName);
        }else{
            //p_file_info->file_type=ENUM_NORMAL_FILE;
			printf("F	%.4d%.2d%.2d-%.2d%.2d%.2d	%.4d%.2d%.2d-%.2d%.2d%.2d	%.4d%.2d%.2d-%.2d%.2d%.2d	%s\n",
				ct.wYear,ct.wMonth,ct.wDay,ct.wHour,ct.wMinute,ct.wSecond,
				lat.wYear,lat.wMonth,lat.wDay,lat.wHour,lat.wMinute,lat.wSecond,
				lwt.wYear,lwt.wMonth,lwt.wDay,lwt.wHour,lwt.wMinute,lwt.wSecond,
				ffd.cFileName);
        }

        //p_file_info->file_name = (char *)malloc(strlen(ffd.cFileName)+1);
        //p_file_info->parent_dir = (char *)malloc(path_length+1);
        //strcpy(p_file_info->parent_dir, path);
        //strcpy(p_file_info->file_name, ffd.cFileName);

    }while(FindNextFile(hFind,&ffd)!=0);
    //LINE();
    dwError = GetLastError();
    FindClose(hFind);
    return file_num;
}

int main(int argc, char *argv[])
{
	TCHAR Buffer[MAX_PATH];
	DWORD fileAttributes;
	WIN32_FILE_ATTRIBUTE_DATA FileInformation;

	int ret = 0;
	
	if(argc > 2){
		printf("Usage: \nList files in dir PATH:\t%s PATH\nList files in current dir:\t%s",
			argv[0],argv[0]);
		return 0;
	}
	if(argc==1){
		get_current_dir(Buffer);
	
	}else if(argc == 2){
		strcpy(Buffer,argv[1]);
	}
	printf("ATTR\tCREATE-TIME\tLAST-ACCESS\tLAST-WRITE\tFILENAME\n");
	
	fileAttributes = GetFileAttributes(Buffer);
	if(fileAttributes == INVALID_FILE_ATTRIBUTES){
		printf("GetFileAttributes(%s) fail,err : %d\n", argv[1],GetLastError());
		return 0;
	}else if(fileAttributes & FILE_ATTRIBUTE_DIRECTORY){
		list_dir(Buffer);
	}else if(fileAttributes & FILE_ATTRIBUTE_ARCHIVE){
		/*
		A file or directory that is an archive file or directory. 
		Applications typically use this attribute to mark files 
		for backup or removal . 
		*/
		print_file_info(Buffer);
	}else{
		
		printf("unknow file type %#x !!!!!\n",fileAttributes);
	}
	
	return 0;
}
