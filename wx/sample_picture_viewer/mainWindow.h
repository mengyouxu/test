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
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class mainWindow
///////////////////////////////////////////////////////////////////////////////
class mainWindow : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* menuBar;
		wxMenu* menuFile;
		wxMenu* menuHelp;
		wxFlexGridSizer* topSizer;
		wxStaticBoxSizer* picSizer;
		wxStaticBoxSizer* colorSizer;
	
	public:
		
		mainWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 472,365 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~mainWindow();
	
};

#endif //__MAINWINDOW_H__
