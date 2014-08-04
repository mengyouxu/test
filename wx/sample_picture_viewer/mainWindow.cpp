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
	
	topSizer = new wxFlexGridSizer( 0, 2, 0, 0 );
	topSizer->SetFlexibleDirection( wxHORIZONTAL );
	topSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	picSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Original Picture") ), wxVERTICAL );
	
	picSizer->SetMinSize( wxSize( 300,300 ) ); 
	
	topSizer->Add( picSizer, 1, wxEXPAND, 5 );
	
	colorSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Overall Color") ), wxVERTICAL );
	
	colorSizer->SetMinSize( wxSize( 100,100 ) ); 
	
	topSizer->Add( colorSizer, 1, wxALIGN_RIGHT|wxALIGN_TOP|wxFIXED_MINSIZE, 5 );
	
	
	this->SetSizer( topSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

mainWindow::~mainWindow()
{
}
