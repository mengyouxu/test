
#include <wx/wx.h>
#include "mainWindow.h"

class mainWindow : public MyDialog{
public:
    mainWindow();
    mainWindow(const wxString &title);
private:
    void OnChooseInputFile( wxCommandEvent& event );
    void OnChooseOutputFile( wxCommandEvent& event );
    void OnRun( wxCommandEvent& event );
    void OnQuit( wxCommandEvent& event );

};
void mainWindow::OnQuit(wxCommandEvent &evt){
    this->Close();
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
    wxFile *inputFile = new wxFile((char *)this->textCtrlInputFile->GetValue().char_str(),wxFile::read);
    if(inputFile ==  nullptr){
        //wxMessageBox(wxT("Cannot open input file: ")+this->textCtrlInputFile->GetValue(),wxT("Error open input"),wxOK,this);
        //return;
    }
    wxFile *outputFile = new wxFile((char *)this->textCtrlOutputFile->GetValue().char_str(),wxFile::write);
    if(outputFile == nullptr){
        //wxMessageBox(wxT("Cannot open output file: ")+this->textCtrlOutputFile->GetValue()+wxT(" cannot open"),wxT("Error open output"),wxOK,this);
        //return;
    }
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
