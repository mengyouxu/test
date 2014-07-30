
#include "wx/wx.h"

class DemoFrame : public wxFrame{
public:
    DemoFrame(const wxString &title,wxSize &_size);
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

DemoFrame::DemoFrame(const wxString &title,wxSize &_size)
    :wxFrame(NULL, wxID_ANY, title,wxDefaultPosition,_size,wxDEFAULT_FRAME_STYLE)
{
    //wxFRAME_NO_TASKBAR添加这个style可以隐藏标题栏
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);
    wxButton *button= new wxButton(this,wxID_CLOSE,"OK");
    sizer->Add(5,5);
    sizer->Add(button,0,wxALL,5);
}

class DemoApp : public wxApp{
public:
        virtual bool OnInit();
};

bool DemoApp::OnInit(){
    wxSize _size(200,100);
    DemoFrame *frame = new DemoFrame("Hello world",_size);
    frame->Show(true);
    return true;
}

DECLARE_APP(DemoApp);
IMPLEMENT_APP(DemoApp);
