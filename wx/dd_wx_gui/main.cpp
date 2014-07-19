
#include "dd_wx_gui_common.h"
#include "mainWindow.h"
#include "file_oprations.h"
class mainWindow : public MyDialog{
public:
    mainWindow();
    mainWindow(const wxString &title);
    void setProgressValue(int val);
private:
    void OnChooseInputFile( wxCommandEvent& event );
    void OnChooseOutputFile( wxCommandEvent& event );
    void OnRun( wxCommandEvent& event );
    void OnCancel( wxCommandEvent& event );
    void OnQuit( wxCommandEvent& event );

    void OnProgressUpdate(wxCommandEvent &event);

};
void mainWindow::OnQuit(wxCommandEvent &evt){
    this->Close();
}
void mainWindow::setProgressValue(int val){
	this->gaugeProgress->SetValue(val);
}

void mainWindow::OnChooseInputFile(wxCommandEvent &evt)
{

    wxFileDialog *dlg = new wxFileDialog(this, "Open a text file", "", "",
                                       "All files(*.*)|*.*|Text Files(*.txt)|*.txt",
                                        wxFD_OPEN, wxDefaultPosition);
    if(dlg->ShowModal()==wxID_OK)//使用ShowModal显示对话框时,当用户按下OK时返回wxID_OK,其它情况返回wxID_CANCEL.
    {
        this->textCtrlInputFile->SetValue(dlg->GetPath());
        //printf("file name : %s\n",(char *)dlg->GetFilename().char_str());
    }
    dlg->Destroy();
}
void mainWindow::OnChooseOutputFile(wxCommandEvent &evt)
{

    wxFileDialog *dlg = new wxFileDialog(this, "Open a text file", "", "",
                                       "All files(*.*)|*.*|Text Files(*.txt)|*.txt",
                                        wxFD_SAVE, wxDefaultPosition);
    if(dlg->ShowModal()==wxID_OK)//使用ShowModal显示对话框时,当用户按下OK时返回wxID_OK,其它情况返回wxID_CANCEL.
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
	printf("%s():L%d\n",__func__,__LINE__);
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
    printf("input file : %s \n",(char *)this->textCtrlInputFile->GetValue().char_str());
    printf("output file : %s \n",(char *)this->textCtrlOutputFile->GetValue().char_str());
	cut_file_thread *cutter = new cut_file_thread((char *)this->textCtrlInputFile->GetValue().char_str(),
												(char *)this->textCtrlOutputFile->GetValue().char_str(),
												begin_pos,copy_size);
	//void (wxGauge::*set_progress)(int) = &wxGauge::SetValue;
	cutter->setGauge(this->gaugeProgress);
	cutter->Run();

}

void mainWindow::OnCancel(wxCommandEvent &evt)
{


}
void mainWindow::OnProgressUpdate(wxCommandEvent &event)
{
	this->gaugeProgress->SetValue(50);

}
mainWindow::mainWindow()
        :MyDialog(nullptr, wxID_ANY, wxT("Hello World"), wxDefaultPosition,  wxSize( 450,333 ), wxDEFAULT_DIALOG_STYLE ){
}
mainWindow::mainWindow(const wxString &title)
        :MyDialog(nullptr, wxID_ANY, title, wxDefaultPosition,  wxSize( 450,333 ), wxDEFAULT_DIALOG_STYLE ){

}
class myApp : public wxApp{
public:
    virtual bool OnInit();
private:

};


DECLARE_APP(myApp);
IMPLEMENT_APP(myApp);

bool myApp::OnInit()
{
    //mainFrame *mframe = new mainFrame(nullptr,wxID_ANY,wxT("Hello World"),wxDefaultPosition, wxSize( 241,114 ),wxDEFAULT_FRAME_STYLE|wxFRAME_TOOL_WINDOW|wxTAB_TRAVERSAL );
    //mframe->Show(true);
    //MyDialog *dialog = new MyDialog(nullptr, wxID_ANY, wxT("Hello"), wxDefaultPosition,  wxSize( 450,333 ), wxDEFAULT_DIALOG_STYLE );
    //dialog->Show(true);

    mainWindow *mWindow = new mainWindow(wxT("h"));
    mWindow->Show(true);
    return true;
}
