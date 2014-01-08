/*	
Copyright (C) 2013  Niraj Rayalla

This file is part of 3-DPhysicsSim.    

3-DPhysicsSim is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

3-DPhysicsSim is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

///-----------------------------------------------------------------
///
/// @file      PendulumChangeAccelerationDialog.h
/// @author    niraj
/// Created:   7/2/2012 2:01:51 PM
/// @section   DESCRIPTION
///            PendulumChangeAccelerationDialog class declaration
///
///------------------------------------------------------------------

#ifndef _WX_IRR_PENDULUM_CHANGE_ACCELERATION_DIALOG
#define _WX_IRR_PENDULUM_CHANGE_ACCELERATION_DIALOG

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
////Header Include End

////Dialog Style Start
#undef PendulumChangeAccelerationDialog_STYLE
#define PendulumChangeAccelerationDialog_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class PendulumChangeAccelerationDialog : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		PendulumChangeAccelerationDialog(wxWindow *parent, wxString xString = _("0"), wxString yString = _("-9.8"), wxString zString = _("0"), wxWindowID id = 1, const wxString &title = wxT("PendulumChangeAccelerationDialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = PendulumChangeAccelerationDialog_STYLE);
		virtual ~PendulumChangeAccelerationDialog();
		void ChangeButtonClick(wxCommandEvent& event);
		void CancelButtonClick(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *CancelButton;
		wxButton *ChangeButton;
		wxTextCtrl *ZTextbox;
		wxStaticText *ZLabel;
		wxTextCtrl *YTextbox;
		wxStaticText *YLabel;
		wxTextCtrl *XTextbox;
		wxStaticText *XLabel;
		////GUI Control Declaration End

	public:		

		wxString GetXString() { return XTextbox->GetValue(); }
		wxString GetYString() { return YTextbox->GetValue(); }
		wxString GetZString() { return ZTextbox->GetValue(); }
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_CANCELBUTTON = 1036,
			ID_CHANGEBUTTON = 1035,
			ID_ZTEXTBOX = 1034,
			ID_ZLABEL = 1033,
			ID_YTEXTBOX = 1032,
			ID_YLABEL = 1031,
			ID_XTEXTBOX = 1030,
			ID_XLABEL = 1029,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
