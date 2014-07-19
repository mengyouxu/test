///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/gauge.h>
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog
///////////////////////////////////////////////////////////////////////////////
class MyDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* textCtrlInputFile;
		wxButton* buttonGetInputFile;
		wxStaticText* m_staticText2;
		wxTextCtrl* textCtrlOutputFile;
		wxButton* buttonGetOutputFile;
		wxGauge* gaugeProgress;
		wxStaticText* m_staticText6;
		wxSpinCtrl* spinCtrlBeginPos;
		wxStaticText* m_staticText7;
		wxSpinCtrl* spinCtrlCopySize;
		wxComboBox* comboBoxUnit;
		wxButton* m_button6;
		wxButton* m_button5;
		wxButton* m_button7;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChooseInputFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChooseOutputFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRun( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 403,355 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~MyDialog();
	
};

#endif //__MAINWINDOW_H__
