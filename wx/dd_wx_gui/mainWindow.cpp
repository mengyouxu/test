///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "mainWindow.h"

///////////////////////////////////////////////////////////////////////////

MyDialog::MyDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	bSizer1->SetMinSize( wxSize( -1,3 ) ); 
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Input File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALIGN_CENTER|wxBOTTOM|wxFIXED_MINSIZE|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	textCtrlInputFile = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_LEFT );
	bSizer2->Add( textCtrlInputFile, 0, wxALIGN_CENTER|wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT|wxSHAPED|wxTOP, 5 );
	
	buttonGetInputFile = new wxButton( this, wxID_ANY, wxT("Choose File"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( buttonGetInputFile, 0, wxALIGN_CENTER|wxALIGN_RIGHT|wxEXPAND|wxSHAPED, 5 );
	
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Output file"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALIGN_CENTER|wxALIGN_LEFT|wxBOTTOM|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	textCtrlOutputFile = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_LEFT );
	bSizer3->Add( textCtrlOutputFile, 0, wxALIGN_CENTER|wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT|wxSHAPED|wxTOP, 5 );
	
	buttonGetOutputFile = new wxButton( this, wxID_ANY, wxT("Choose File"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( buttonGetOutputFile, 0, wxALIGN_CENTER|wxALIGN_RIGHT|wxEXPAND|wxSHAPED, 5 );
	
	
	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_gauge1 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_SMOOTH );
	m_gauge1->SetValue( 0 ); 
	bSizer4->Add( m_gauge1, 0, wxALIGN_CENTER|wxEXPAND|wxLEFT|wxRIGHT|wxSHAPED, 5 );
	
	
	bSizer1->Add( bSizer4, 1, wxEXPAND, 5 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 3, 0, 0 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Begin position:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gSizer1->Add( m_staticText6, 0, wxALL, 5 );
	
	m_spinCtrl5 = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	gSizer1->Add( m_spinCtrl5, 0, wxALL, 5 );
	
	m_comboBox1 = new wxComboBox( this, wxID_ANY, wxT("kByte"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBox1->Append( wxT("Byte") );
	m_comboBox1->Append( wxT("kByte") );
	m_comboBox1->Append( wxT("MByte") );
	m_comboBox1->SetSelection( 1 );
	gSizer1->Add( m_comboBox1, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Copy size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gSizer1->Add( m_staticText7, 0, wxALL, 5 );
	
	m_spinCtrl6 = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	gSizer1->Add( m_spinCtrl6, 0, wxALL, 5 );
	
	m_comboBox2 = new wxComboBox( this, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBox2->Append( wxT("Byte") );
	m_comboBox2->Append( wxT("kByte") );
	m_comboBox2->Append( wxT("MByte") );
	m_comboBox2->SetSelection( 1 );
	gSizer1->Add( m_comboBox2, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 5 );
	
	
	bSizer1->Add( gSizer1, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button6 = new wxButton( this, wxID_ANY, wxT("Run"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_button6, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_button7 = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_button7, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer1->Add( bSizer6, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	buttonGetInputFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog::OnChooseInputFile ), NULL, this );
	buttonGetOutputFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog::OnChooseOutputFile ), NULL, this );
	m_button6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog::OnRun ), NULL, this );
	m_button7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog::OnQuit ), NULL, this );
}

MyDialog::~MyDialog()
{
	// Disconnect Events
	buttonGetInputFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog::OnChooseInputFile ), NULL, this );
	buttonGetOutputFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog::OnChooseOutputFile ), NULL, this );
	m_button6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog::OnRun ), NULL, this );
	m_button7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog::OnQuit ), NULL, this );
	
}
