#include "file_oprations.h"

cut_file_thread::cut_file_thread(const char *inputFile,const char *outputFile,long long begin_pos,long long size)
	:wxThread(wxTHREAD_DETACHED)
{
	this->can_run = 1;
	printf("%s():L%d\n",__func__,__LINE__);
	printf("input file : %s \n",inputFile);
    printf("output file : %s \n",outputFile);
	this->inputFile = new wxFile(inputFile,wxFile::read);
	if(this->inputFile == nullptr){
			printf("%s():L%d\n",__func__,__LINE__);
			this->can_run = 0;
	}
	this->outputFile = new wxFile(outputFile,wxFile::write);
	if(this->outputFile == nullptr){
			printf("%s():L%d\n",__func__,__LINE__);
			this->can_run = 0;
	}
	this->begin_pos = begin_pos;
	printf("begin position : %I64d\n",begin_pos);  // For long long int, %I64d->Win / %lld->Linux
	this->copy_size = size;
	printf("copy size: %I64d\n",copy_size);

}

void cut_file_thread::setGauge(wxGauge *gauge)
{
    this->gaugeProgress = gauge;
}

void *cut_file_thread::Entry(){
	long long ret = 0;
	int get_eof = 0;
	long long size = 0;
	int progress = 0;
    char *buff;
    buff = (char *)malloc(BUFF_SIZE);
    if(this->can_run == 0) return NULL;
	if(this->inputFile->IsOpened()==false){
		printf("%s():L%d\n",__func__,__LINE__);
		return NULL;
	}
	if(this->inputFile->IsOpened()==false){
		printf("%s():L%d\n",__func__,__LINE__);
		return NULL;
	}
	while(1){
		ret = this->inputFile->Read(buff,BUFF_SIZE);
		size += ret;
		if(ret < BUFF_SIZE){
			printf("%s():L%d\n",__func__,__LINE__);
			get_eof = 1;
		}
		if(ret == 0){
				printf("%s():L%d\n",__func__,__LINE__);
				break;
		}
		//printf("%s():L%d\n",__func__,__LINE__);
		if(size > this->copy_size){
            ret = ret - (size - this->copy_size);
            printf("%s():L%d\n",__func__,__LINE__);
            get_eof = 1;
		}
		//printf("%s():L%d\n",__func__,__LINE__);
		if(this->outputFile->Write(buff,ret) < ret)break;
		progress = 100 * size / this->copy_size;
		//printf("%s():L%d\n",__func__,__LINE__);
		gaugeProgress->SetValue(progress);
		if(get_eof == 1)break;
	}
	printf("%s():L%d\n",__func__,__LINE__);
	return nullptr;
}
