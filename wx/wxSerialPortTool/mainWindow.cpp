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
	this->SetMenuBar( menuBar );
	
	topSizer = new wxBoxSizer( wxVERTICAL );
	
	textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_LEFT|wxTE_MULTILINE );
	topSizer->Add( textCtrl, 0, wxALIGN_CENTER|wxALIGN_LEFT|wxEXPAND, 5 );
	
	
	this->SetSizer( topSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

mainWindow::~mainWindow()
{
}
