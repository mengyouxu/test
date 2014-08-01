///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "mainWindow.h"

///////////////////////////////////////////////////////////////////////////

mainWindow::mainWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	menuBar = new wxMenuBar( 0 );
	menuFile = new wxMenu();
	menuBar->Append( menuFile, wxT("File") ); 
	
	menuHelp = new wxMenu();
	menuBar->Append( menuHelp, wxT("Help") ); 
	
	this->SetMenuBar( menuBar );
	
	topBoxSizer = new wxBoxSizer( wxVERTICAL );
	
	
	this->SetSizer( topBoxSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

mainWindow::~mainWindow()
{
}
