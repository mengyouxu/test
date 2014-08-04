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
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxVERTICAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	colorSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Overall Color") ), wxHORIZONTAL );
	
	colorSizer->SetMinSize( wxSize( 200,100 ) ); 
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	overallRedValue = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	overallRedValue->Wrap( -1 );
	bSizer2->Add( overallRedValue, 0, wxALIGN_RIGHT, 5 );
	
	overallGreenValue = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	overallGreenValue->Wrap( -1 );
	bSizer2->Add( overallGreenValue, 0, wxALIGN_RIGHT, 5 );
	
	overallBlueValue = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	overallBlueValue->Wrap( -1 );
	bSizer2->Add( overallBlueValue, 0, wxALIGN_RIGHT, 5 );
	
	
	colorSizer->Add( bSizer2, 1, wxALIGN_RIGHT, 5 );
	
	
	fgSizer2->Add( colorSizer, 1, wxALIGN_CENTER|wxFIXED_MINSIZE, 5 );
	
	
	fgSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Test Color") ), wxVERTICAL );
	
	sbSizer4->SetMinSize( wxSize( -1,200 ) ); 
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	custColorSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	spinCtrlRed = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0 );
	bSizer5->Add( spinCtrlRed, 0, wxALIGN_RIGHT, 5 );
	
	spinCtrlGreen = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0 );
	bSizer5->Add( spinCtrlGreen, 0, wxALIGN_RIGHT, 5 );
	
	spinCtrlBlue = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0 );
	bSizer5->Add( spinCtrlBlue, 0, wxALIGN_RIGHT, 5 );
	
	
	custColorSizer->Add( bSizer5, 1, wxALIGN_RIGHT|wxFIXED_MINSIZE, 5 );
	
	
	fgSizer5->Add( custColorSizer, 1, wxEXPAND, 5 );
	
	
	fgSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer4->SetMinSize( wxSize( -1,50 ) ); 
	buttonOk = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( buttonOk, 0, wxALL, 5 );
	
	
	fgSizer5->Add( bSizer4, 1, wxALIGN_CENTER|wxFIXED_MINSIZE, 5 );
	
	
	sbSizer4->Add( fgSizer5, 1, wxALIGN_CENTER|wxEXPAND, 5 );
	
	
	fgSizer2->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	
	topSizer->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( topSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

mainWindow::~mainWindow()
{
}
