
#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>

#include "mainWindow.h"

#define PRINT_LINE() printf("%s()L%d\n",__func__,__LINE__)

class MyWindow : public mainWindow{
public:
    MyWindow();

private:
    void OnClose(wxCloseEvent &evt);
    DECLARE_EVENT_TABLE();
};
BEGIN_EVENT_TABLE(MyWindow,wxFrame)
    EVT_CLOSE(MyWindow::OnClose)
END_EVENT_TABLE()

MyWindow::MyWindow():mainWindow(NULL,wxID_ANY)
{
    PRINT_LINE();
}

void MyWindow::OnClose(wxCloseEvent &evt)
{
    PRINT_LINE();
    this->Close(true);//
    this->Destroy();
}
class MyApp:public wxApp{
public:
    virtual bool OnInit();
};
DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyWindow * window = new MyWindow();
    window->Show(true);
    PRINT_LINE();
    return true;
}

