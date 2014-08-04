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
    void OnOK(wxCommandEvent &evt);
    void OnOpenFile(wxCommandEvent &evt);

    wxString pic_fullname;

    wxImage *originalImg; // Original picture;
    wxImage *averageColorImg; // For average RGB display
    wxImage *custColorImg; // Show customised Color

    wxStaticBitmap *originalBitmap;
    wxStaticBitmap *averageColorBitmap; // For average RGB display
    wxStaticBitmap *custColorBitmap;

    DECLARE_EVENT_TABLE();
};
BEGIN_EVENT_TABLE(myWindow,wxFrame)
    EVT_CLOSE(myWindow::OnClose)
    EVT_MENU(wxID_OPEN,myWindow::OnOpenFile)
    EVT_MENU(wxID_EXIT,myWindow::OnExit)
    EVT_BUTTON(wxID_OK,myWindow::OnOK)
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
void myWindow::OnOK(wxCommandEvent &evt)
{
    int Red = this->spinCtrlRed->GetValue();
    int Green = this->spinCtrlGreen->GetValue();
    int Blue = this->spinCtrlBlue->GetValue();
    printf("Red-Green-Blue: %d-%d-%d\n",Red,Green,Blue);

    unsigned char *data = (unsigned char*)malloc(30000);
    for(int i = 0;i<30000;i+=3){
        data[i]=Red;
        data[i+1]=Green;
        data[i+2]=Blue;
    }
    this->custColorImg->SetData(data);
    //free(data);

    this->custColorBitmap->SetBitmap(wxBitmap(*this->custColorImg));
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
        dlg->Destroy();
    }else{
        dlg->Destroy();
        return;
    }

    wxImage::AddHandler(new wxJPEGHandler);

    int w,h;
    wxScreenDC dc;
    dc.GetSize(&w,&h); //  获取当前Screen 大小
    printf("Current Screen : %d x %d\n",w,h);

    this->originalImg->LoadFile(this->pic_fullname);
    w = this->originalImg->GetWidth();
    h = this->originalImg->GetHeight();

    DEBUG_PRINT_LINE();
    int data_size = w*h*3;
    int pixelNum = w*h;
    int scale = 1;
    unsigned char *data = (unsigned char *)malloc(data_size);

    printf("Pic size : %d x %d\n",w,h);
    const unsigned char *rgb_data = this->originalImg->GetData();
    memcpy(data,rgb_data,data_size);

    scale = w>400?w/400:1;

    w/=scale;
    h/=scale;

    printf("Pic size after scale(%d) : %d x %d\n",scale,w,h);
    this->originalBitmap->SetBitmap(wxBitmap(this->originalImg->Scale(w,h)));
    this->picSizer->SetItemMinSize(this->originalBitmap, w, h);
    //return ;
    unsigned int averageRed=0,averageGreen=0,averageBlue=0;
    int i = 0;
    for(i=0; i<data_size; i+=3){
        averageRed += (unsigned char)data[i];
        averageGreen += (unsigned char)data[i+1];
        averageBlue += (unsigned char)data[i+2];
    }
    //free(data);
    printf("i=%d,averageRed-averageGreen-averageBlue : %d-%d-%d\n",i,averageRed,averageGreen,averageBlue);
    averageRed/=pixelNum;
    averageGreen/=pixelNum;
    averageBlue/=pixelNum;
    printf("Average RGB: %d-%d-%d\n",averageRed,averageGreen,averageBlue);

    unsigned char *averageRgb = (unsigned char *)malloc(100*100*3);

    for(i=0; i<30000; i+=3){
        averageRgb[i]=averageRed;
        averageRgb[i+1]=averageGreen;
        averageRgb[i+2]=averageBlue;
    }
    this->averageColorImg->SetData(averageRgb);
    //free(averageRgb);
    this->averageColorBitmap->SetBitmap(wxBitmap(*this->averageColorImg));

    wxString value;
    value.Printf("%d",averageRed);
    this->overallRedValue->SetLabel(wxT("R: ") + value);
    value.Empty();
    value.Printf("%d",averageGreen);
    this->overallGreenValue->SetLabel(wxT("G: ") + value);
    value.Empty();
    value.Printf("%d",averageBlue);
    this->overallBlueValue->SetLabel(wxT("B: ") + value);

    wxWindow::SetClientSize(w+220,h+30);
}

myWindow::myWindow(const wxString &title)
    :mainWindow(NULL,wxID_ANY,title)
{
    DEBUG_PRINT_LINE();
    this->menuFile->Append(wxID_OPEN,wxT("&Open\tF2"),wxT("Open file"));
    this->menuFile->Append(wxID_EXIT,wxT("&Exit\tF4"),wxT("Exit"));

    this->originalImg = new wxImage(300,300,true);
    this->averageColorImg = new wxImage(100,100,false);
    this->custColorImg = new wxImage(100,100,false);

    this->originalBitmap = new wxStaticBitmap(this,wxID_ANY,wxBitmap(*this->originalImg),wxDefaultPosition,wxDefaultSize);
    this->averageColorBitmap = new wxStaticBitmap(this,wxID_ANY,wxBitmap(*this->averageColorImg),wxDefaultPosition,wxDefaultSize);
    this->custColorBitmap = new wxStaticBitmap(this,wxID_ANY,wxBitmap(*this->custColorImg),wxDefaultPosition,wxDefaultSize);

    this->colorSizer->Prepend(averageColorBitmap,wxSizerFlags().Center().FixedMinSize());

    this->picSizer->Add(originalBitmap,wxSizerFlags().Center());
    this->picSizer->SetItemMinSize(originalBitmap, 300, 300);
    this->custColorSizer->Prepend(custColorBitmap,wxSizerFlags().Center().FixedMinSize());
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
