
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
    wxWindow::SetBackgroundColour(*wxBLUE);// 设置背景颜色
    //wxWindow::SetWindowStyleFlag(wxFRAME_NO_TASKBAR); //无标题栏
    wxWindow::SetClientSize(500,500);  //改变窗口大小

    //{// load a jpeg picture here use wxStaticBitmap
        wxImage::AddHandler(new wxJPEGHandler);
        wxImage img;
        img.LoadFile(_T("d:\\sun.jpg"),wxBITMAP_TYPE_JPEG);
        wxStaticBitmap *static_bitmap = new wxStaticBitmap(this,wxID_ANY,wxBitmap(img),wxDefaultPosition,wxDefaultSize);
    //}

    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);
    wxButton *button= new wxButton(this,wxID_CLOSE,"OK");
    sizer->Add(5,5);
    sizer->Add(button,0,wxALL,5);
    sizer->Add(static_bitmap,0,wxALL,5);
}

class DemoApp : public wxApp{
public:
        virtual bool OnInit();
};

bool DemoApp::OnInit(){
    wxSize _size(200,100); //使用这个size 来设置Frame的初始大小
    DemoFrame *frame = new DemoFrame("Hello world",_size);
    frame->Show(true);
    return true;
}

DECLARE_APP(DemoApp);
IMPLEMENT_APP(DemoApp);
