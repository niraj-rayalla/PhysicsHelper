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
/// @file      VectorAddDialog.h
/// @author    niraj
/// Created:   7/5/2012 11:52:16 PM
/// @section   DESCRIPTION
///            VectorAddDialog class declaration
///
///------------------------------------------------------------------

#ifndef WX_VECTOR_ADD_DIALOG
#define WX_VECTOR_ADD_DIALOG

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
#include <wx/combobox.h>
////Header Include End

////Dialog Style Start
#undef VectorAddDialog_STYLE
#define VectorAddDialog_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class VectorAddDialog : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();

		void ChangeVectorDescriptionSelection();
		
	public:
		VectorAddDialog(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("VectorAddDialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = VectorAddDialog_STYLE);
		virtual ~VectorAddDialog();
		void VectorDescriptionTypeSelected(wxCommandEvent& event );
		void AddButtonClick(wxCommandEvent& event);
		void CancelButtonClick(wxCommandEvent& event);

		double theta;
		double phi;
		double length;
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *CancelButton;
		wxButton *AddButton;
		wxTextCtrl *ZorLengthTextbox;
		wxStaticText *ZorLengthLabel;
		wxTextCtrl *YorPhiTextbox;
		wxStaticText *YorPhiLabel;
		wxTextCtrl *XorThetaTextbox;
		wxStaticText *XorThetaLabel;
		wxComboBox *VectorDescriptionType;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_CANCELBUTTON = 1045,
			ID_ADDBUTTON = 1044,
			ID_ZORLENGTHTEXTBOX = 1043,
			ID_ZORLENGTHLABEL = 1042,
			ID_YORPHITEXTBOX = 1041,
			ID_YORPHILABEL = 1040,
			ID_XORTHETATEXTBOX = 1039,
			ID_XORTHETALABEL = 1038,
			ID_VECTORDESCRIPTIONTYPE = 1037,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
