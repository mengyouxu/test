#include <stdlib.h>
#include <wx/Thread.h>
#include <wx/file.h>

#include "dd_wx_gui_common.h"

#define BUFF_SIZE (1024*1024)

class cut_file_thread: public wxThread{
public:
	cut_file_thread(const char *inputFile,const char *outputFile,long long begin_pos,long long asize);
	virtual void *Entry();
	void setGauge(wxGauge *gauge);
private:
	wxGauge *gaugeProgress;
	wxFile *inputFile;
	wxFile *outputFile;
	long long begin_pos;
	long long copy_size;
	bool can_run;
};

