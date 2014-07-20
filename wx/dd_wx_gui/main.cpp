
#include "dd_wx_gui_common.h"
#include "mainWindow.h"
#include "file_oprations.h"
class mainWindow : public MyDialog{
public:
    mainWindow(const wxString &title);
    void setProgressValue(int val);
private:
    void OnChooseInputFile( wxCommandEvent& event );
    void OnChooseOutputFile( wxCommandEvent& event );
    void OnRun( wxCommandEvent& event );
    void OnCancel( wxCommandEvent& event );
    void OnQuit( wxCommandEvent& event );
    void OnClose(wxCloseEvent& event);

    void OnProgressUpdate(wxCommandEvent &event);

    DECLARE_EVENT_TABLE()
};
BEGIN_EVENT_TABLE(mainWindow,wxDialog)
	EVT_CLOSE(mainWindow::OnClose)
END_EVENT_TABLE()

void mainWindow::OnQuit(wxCommandEvent &evt)
{
	printf("%s():L%d\n",__func__,__LINE__);
    this->Destroy();
}

void mainWindow::OnClose(wxCloseEvent& event)
{
	printf("%s():L%d\n",__func__,__LINE__);
	this->Destroy();
}

void mainWindow::setProgressValue(int val){
	this->gaugeProgress->SetValue(val);
}

void mainWindow::OnChooseInputFile(wxCommandEvent &evt)
{
    wxFileDialog *dlg = new wxFileDialog(this,
									"Open a text file", "", "",
									"All files(*.*)|*.*\
										|Text Files(*.txt)|*.txt\
										|TS(*.ts;*.m2ts)|*.ts;*.m2ts",
									wxFD_OPEN, wxDefaultPosition);
    //使用ShowModal显示对话框时,当用户按下OK时返回wxID_OK,其它情况返回wxID_CANCEL.
    if(dlg->ShowModal()==wxID_OK)
    {
        this->textCtrlInputFile->SetValue(dlg->GetPath());
        //printf("file name : %s\n",(char *)dlg->GetFilename().char_str());
    }
    dlg->Destroy();
}
void mainWindow::OnChooseOutputFile(wxCommandEvent &evt)
{
    wxFileDialog *dlg = new wxFileDialog(this,
									"Open a text file", "", "",
									"All files(*.*)|*.*",
									wxFD_SAVE, wxDefaultPosition);
    //使用ShowModal显示对话框时,当用户按下OK时返回wxID_OK,其它情况返回wxID_CANCEL.
    if(dlg->ShowModal()==wxID_OK)
    {
        this->textCtrlOutputFile->SetValue(dlg->GetPath());
        //printf("file name : %s\n",(char *)dlg->GetFilename().char_str());
    }
    dlg->Destroy();
}

void mainWindow::OnRun(wxCommandEvent &evt)
{
	long long begin_pos = this->spinCtrlBeginPos->GetValue();
	long long copy_size = this->spinCtrlCopySize->GetValue();
    switch(this->comboBoxUnit->GetSelection()){
	case 0:
		break;
	case 1:
		begin_pos *= 1024;
		copy_size *= 1024;
		break;
	case 2:
		begin_pos *= (1024*1024);
		copy_size *= (1024*1024);
		break;
	default:
		wxString msg;
		msg.Printf("Please select a unit!!!");

		return;

    }
	cut_file_thread *cutter = new cut_file_thread((char *)this->textCtrlInputFile->GetValue().char_str(),
												(char *)this->textCtrlOutputFile->GetValue().char_str(),
												begin_pos,copy_size);
	//void (wxGauge::*set_progress)(int) = &wxGauge::SetValue;
	cutter->setGauge(this->gaugeProgress);
	cutter->Run();
	printf("%s():L%d\n",__func__,__LINE__);
}

void mainWindow::OnCancel(wxCommandEvent &evt)
{


}
void mainWindow::OnProgressUpdate(wxCommandEvent &event)
{
	this->gaugeProgress->SetValue(50);

}

mainWindow::mainWindow(const wxString &title)
        :MyDialog(nullptr, wxID_ANY, title,
				wxDefaultPosition,  wxSize( 450,333 ),
				wxDEFAULT_DIALOG_STYLE)
{

}
class myApp : public wxApp{
public:
    virtual bool OnInit();
    virtual int OnExit();
private:

};

DECLARE_APP(myApp);
IMPLEMENT_APP(myApp);

bool myApp::OnInit()
{
    mainWindow *mWindow = new mainWindow(wxT("dd GUI"));
    mWindow->Show(true);
    return true;
}
int myApp::OnExit()
{
    printf("OnExit()\n");
}
