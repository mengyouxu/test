/*
    MS Windows only;
    wx Version:	wxWidgets-3.0.1
    IDE:	Code::Blocks 13.12 + Mingw-TDM-GCC-481
*/

#include <stdio.h>
#include <stdlib.h>

#include <wx/wx.h>

#include "mainWindow.h"

#define DEBUG_PRINT_LINE() printf("%s()L%d\n",__func__,__LINE__)

class myWindow: public mainWindow
{
public:
    myWindow(const wxString &title);

private:
    void OnClose(wxCloseEvent &evt);
    void OnExit(wxCommandEvent &evt);
    void OnOpenFile(wxCommandEvent &evt);

    wxString pic_fullname;

    DECLARE_EVENT_TABLE();
};
BEGIN_EVENT_TABLE(myWindow,wxFrame)
    EVT_CLOSE(myWindow::OnClose)
    EVT_MENU(wxID_OPEN,myWindow::OnOpenFile)
    EVT_MENU(wxID_EXIT,myWindow::OnExit)
END_EVENT_TABLE()

void myWindow::OnClose(wxCloseEvent &evt)
{
    DEBUG_PRINT_LINE();
    this->Destroy();
}
void myWindow::OnExit(wxCommandEvent &evt)
{
    DEBUG_PRINT_LINE();
    this->Destroy();
}
void myWindow::OnOpenFile(wxCommandEvent &evt)
{
    wxFileDialog *dlg = new wxFileDialog(this,
									"Open a picture", "", "",
									"JPEG Files(*.jpg)|*.jpg;*.JPG\
                                         |PNG Files(*.png)|*.png\
                                         |All files(*.*)|*.*",
									wxFD_OPEN, wxDefaultPosition);
    //使用ShowModal显示对话框时,当用户按下OK时返回wxID_OK,其它情况返回wxID_CANCEL.
    if(dlg->ShowModal()==wxID_OK)
    {
        this->pic_fullname = dlg->GetPath();
        printf("file name : %s\n",(char *)this->pic_fullname.char_str());
    }
    dlg->Destroy();
    wxImage::AddHandler(new wxJPEGHandler);
    wxImage img;

    int w,h;

    wxScreenDC dc;
    dc.GetSize(&w,&h); //  获取当前Screen 大小
    printf("Current Screen : %d x %d\n",w,h);

    img.LoadFile(this->pic_fullname);
    w = img.GetWidth();
    h = img.GetHeight();
    if(w>800 || h>800){
        w/=(w/800);
        h/=(h/800);
    }
    wxWindow::SetClientSize(w,h);
    wxStaticBitmap *staticBitmap = new wxStaticBitmap(this,wxID_ANY,wxBitmap(img.Scale(w,h)),wxDefaultPosition,wxDefaultSize);
    this->topBoxSizer->Add(staticBitmap,wxSizerFlags().Center());

}

myWindow::myWindow(const wxString &title)
    :mainWindow(NULL,wxID_ANY,title)
{
    DEBUG_PRINT_LINE();
    this->menuFile->Append(wxID_OPEN,wxT("&Open\tF2"),wxT("Open file"));
    this->menuFile->Append(wxID_EXIT,wxT("&Exit\tF4"),wxT("Exit"));
}

class myApp : public wxApp{
public:
    virtual bool OnInit();
    virtual int OnExit();
private:

};

bool myApp::OnInit()
{
    myWindow *window = new myWindow(wxT("Picture viewer"));
    window->Show(true);
    DEBUG_PRINT_LINE();
    return true;
}

IMPLEMENT_APP(myApp);

int myApp::OnExit()
{
    DEBUG_PRINT_LINE();
    return true;
}
