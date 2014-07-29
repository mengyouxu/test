
#include "wx/wx.h"

class DemoFrame : public wxFrame{
public:
    DemoFrame(const wxString &title);
    void OnButtonPress(wxCommandEvent &event);
private:
    DECLARE_EVENT_TABLE();
};

void DemoFrame::OnButtonPress(wxCommandEvent &event){
    Close(true);
}

BEGIN_EVENT_TABLE(DemoFrame,wxFrame)
    EVT_BUTTON(wxID_CLOSE,DemoFrame::OnButtonPress)
END_EVENT_TABLE()

DemoFrame::DemoFrame(const wxString &title)
:wxFrame(NULL, wxID_ANY, title)
{
    //setWindowStyleFlag(wxFRAME_NO_TASKBAR);//这句可以隐藏标题栏
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);
    wxButton *button= new wxButton(this,wxID_CLOSE,"OK");
    sizer->Add(50,50);
    sizer->Add(button,0,wxALL,50);
}

class DemoApp : public wxApp{
public:
        virtual bool OnInit();
};

bool DemoApp::OnInit(){
    DemoFrame *frame = new DemoFrame("Hello world");
    frame->Show(true);
    return true;
}

DECLARE_APP(DemoApp);
IMPLEMENT_APP(DemoApp);
