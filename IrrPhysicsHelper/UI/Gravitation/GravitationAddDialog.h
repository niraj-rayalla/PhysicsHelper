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
/// @file      GravitationAddDialog.h
/// @author    niraj
/// Created:   7/7/2012 12:31:35 PM
/// @section   DESCRIPTION
///            GravitationAddDialog class declaration
///
///------------------------------------------------------------------

#ifndef WX_IRR_GRAVITATION_ADD_DIALOG
#define WX_IRR_GRAVITATION_ADD_DIALOG

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
#include <wx/scrolwin.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/checkbox.h>
////Header Include End

////Dialog Style Start
#undef GravitationAddDialog_STYLE
#define GravitationAddDialog_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

enum ReferenceObjectType
{
    ReferenceObjectType_Absolute,
    ReferenceObjectType_Relative
};

class GravitationAddDialog : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		GravitationAddDialog(wxWindow *parent, wxArrayString (*getObjectNames)(void), wxWindowID id = 1, const wxString &title = wxT("GravitationAddDialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = GravitationAddDialog_STYLE);
		virtual ~GravitationAddDialog();
		void AddButtonClick(wxCommandEvent& event);
		void CancelButtonClick(wxCommandEvent& event);
		void ReferenceObjectComboBoxSelected(wxCommandEvent& event );
		void CustomNameCheckBoxClick(wxCommandEvent& event);
		
		bool objEnabled;
		bool useCustomName;
		wxString customName;
		ReferenceObjectType refObjType;
		bool isSingleObject;
		int selectedReferenceObjectIndex;
		
		double singleMass;
		double singleRadius;
		double singlePositionX;
		double singlePositionY;
		double singlePositionZ;
		double singleVelocityX;
		double singleVelocityY;
		double singleVelocityZ;
		
		wxString multipleMass;
		wxString multipleRadius;
		wxString multiplePositionX;
		double multiplePositionXAxisRangeBegin;
		double multiplePositionXAxisRangeEnd;
		double multiplePositionXAxisRangeResolution;
		wxString multiplePositionY;
		double multiplePositionYAxisRangeBegin;
		double multiplePositionYAxisRangeEnd;
		double multiplePositionYAxisRangeResolution;
		wxString multiplePositionZ;
		double multiplePositionZAxisRangeBegin;
		double multiplePositionZAxisRangeEnd;
		double multiplePositionZAxisRangeResolution;
		wxString multipleVelocityX;
		wxString multipleVelocityY;
		wxString multipleVelocityZ;

		wxArrayString (*GetObjectNames)(void);

		void BeforeShowing();
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTextCtrl *CustomNameTextbox;
		wxCheckBox *CustomNameCheckBox;
		wxComboBox *ReferenceObjectSelectionComboBox;
		wxStaticText *ReferenceObjectLabel;
		wxTextCtrl *MultiplePositionResolutionZTextbox;
		wxTextCtrl *MultiplePositionResolutionYTextbox;
		wxTextCtrl *MultiplePositionResolutionXTextbox;
		wxStaticText *MultiplePositionResolutionLabel;
		wxTextCtrl *MultipleAxisRangeZEnd;
		wxTextCtrl *MultipleAxisRangeYEnd;
		wxTextCtrl *MultipleAxisRangeXEnd;
		wxStaticText *WxStaticText13;
		wxStaticText *WxStaticText12;
		wxStaticText *WxStaticText11;
		wxTextCtrl *MultipleAxisRangeZBegin;
		wxTextCtrl *MultipleAxisRangeYBegin;
		wxTextCtrl *MultipleAxisRangeXBegin;
		wxStaticText *MultipleAxixRangeLabel;
		wxTextCtrl *MultipleVelocityZTextbox;
		wxStaticText *MultipleVelocityZLabel;
		wxTextCtrl *MultipleVelocityYTextbox;
		wxStaticText *MultipleVelocityYLabel;
		wxTextCtrl *MultipleVelocityXTextbox;
		wxStaticText *MultipleVelocityXLabel;
		wxStaticText *MultipleVelocityLabel;
		wxTextCtrl *MultiplePositionZTextbox;
		wxStaticText *MultiplePositionZLabel;
		wxTextCtrl *MultiplePositionYTextbox;
		wxStaticText *MultiplePositionYLabel;
		wxTextCtrl *MultiplePositionXTextbox;
		wxStaticText *MultiplePositionXLabel;
		wxStaticText *MultiplePositionLabel;
		wxTextCtrl *MultipleRadiusTextbox;
		wxStaticText *MultipleRadiusLabel;
		wxTextCtrl *MultipleMassTextbox;
		wxStaticText *MultipleMassLabel;
		wxScrolledWindow *WxScrolledWindow1;
		wxButton *CancelButton;
		wxButton *AddButton;
		wxTextCtrl *RadiusSingleTextbox;
		wxStaticText *RadiusSingleLabel;
		wxTextCtrl *VelocitySingleZTexbox;
		wxStaticText *VelocitySingleZLabel;
		wxTextCtrl *VelocitySingleYTexbox;
		wxStaticText *VelocitySingleYLabel;
		wxTextCtrl *VelocitySingleXTexbox;
		wxStaticText *VelocitySingleXLabel;
		wxStaticText *VelocitySingleLabel;
		wxStaticText *PositionSingleZLabel;
		wxTextCtrl *PositionSingleZTextbox;
		wxStaticText *PositionSingleYLabel;
		wxTextCtrl *PositionSingleYTextbox;
		wxStaticText *PositionSingleXLabel;
		wxTextCtrl *PositionSingleXTextbox;
		wxStaticText *PositionSingleLabel;
		wxTextCtrl *MassSingleTextbox;
		wxStaticText *MassSingleLabel;
		wxStaticText *ReferencePointLabel;
		wxComboBox *ReferenceObjectComboBox;
		wxPanel *MultiplicityMultipleNotebookPage;
		wxPanel *MultiplicitySingleNotebookPage;
		wxNotebook *MultiplicityNotebook;
		wxCheckBox *EnabledCheckbox;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_CUSTOMNAMETEXTBOX = 1452,
			ID_CUSTOMNAMECHECKBOX = 1451,
			ID_REFERENCEOBJECTSELECTIONCOMBOBOX = 1450,
			ID_REFERENCEOBJECTLABEL = 1449,
			ID_MULTIPLEPOSITIONRESOLUTIONZTEXTBOX = 1447,
			ID_MULTIPLEPOSITIONRESOLUTIONYTEXTBOX = 1446,
			ID_MULTIPLEPOSITIONRESOLUTIONXTEXTBOX = 1445,
			ID_MULTIPLEPOSITIONRESOLUTIONLABEL = 1435,
			ID_MULTIPLEAXISRANGEZEND = 1434,
			ID_MULTIPLEAXISRANGEYEND = 1433,
			ID_MULTIPLEAXISRANGEXEND = 1432,
			ID_WXSTATICTEXT13 = 1428,
			ID_WXSTATICTEXT12 = 1427,
			ID_WXSTATICTEXT11 = 1426,
			ID_MULTIPLEAXISRANGEZBEGIN = 1422,
			ID_MULTIPLEAXISRANGEYBEGIN = 1421,
			ID_MULTIPLEAXISRANGEXBEGIN = 1420,
			ID_MULTIPLEAXIXRANGELABEL = 1416,
			ID_MULTIPLEVELOCITYZTEXTBOX = 1415,
			ID_MULTIPLEVELOCITYZLABEL = 1414,
			ID_MULTIPLEVELOCITYYTEXTBOX = 1413,
			ID_MULTIPLEVELOCITYYLABEL = 1412,
			ID_MULTIPLEVELOCITYXTEXTBOX = 1411,
			ID_MULTIPLEVELOCITYXLABEL = 1410,
			ID_MULTIPLEVELOCITYLABEL = 1409,
			ID_MULTIPLEPOSITIONZTEXTBOX = 1408,
			ID_MULTIPLEPOSITIONZLABEL = 1407,
			ID_MULTIPLEPOSITIONYTEXTBOX = 1406,
			ID_MULTIPLEPOSITIONYLABEL = 1405,
			ID_MULTIPLEPOSITIONXTEXTBOX = 1404,
			ID_MULTIPLEPOSITIONXLABEL = 1403,
			ID_MULTIPLEPOSITIONLABEL = 1402,
			ID_MULTIPLERADIUSTEXTBOX = 1401,
			ID_MULTIPLERADIUSLABEL = 1400,
			ID_MULTIPLEMASSTEXTBOX = 1399,
			ID_MULTIPLEMASSLABEL = 1398,
			ID_WXSCROLLEDWINDOW1 = 1240,
			ID_CANCELBUTTON = 1068,
			ID_ADDBUTTON = 1067,
			ID_RADIUSSINGLETEXTBOX = 1066,
			ID_RADIUSSINGLELABEL = 1065,
			ID_VELOCITYSINGLEZTEXBOX = 1063,
			ID_VELOCITYSINGLEZLABEL = 1062,
			ID_VELOCITYSINGLEYTEXBOX = 1061,
			ID_VELOCITYSINGLEYLABEL = 1060,
			ID_VELOCITYSINGLEXTEXBOX = 1059,
			ID_VELOCITYSINGLEXLABEL = 1058,
			ID_VELOCITYSINGLELABEL = 1057,
			ID_POSITIONSINGLEZLABEL = 1035,
			ID_POSITIONSINGLEZTEXTBOX = 1034,
			ID_POSITIONSINGLEYLABEL = 1032,
			ID_POSITIONSINGLEYTEXTBOX = 1031,
			ID_POSITIONSINGLEXLABEL = 1029,
			ID_POSITIONSINGLEXTEXTBOX = 1028,
			ID_POSITIONSINGLELABEL = 1027,
			ID_MASSSINGLETEXTBOX = 1019,
			ID_MASSSINGLELABEL = 1018,
			ID_REFERENCEPOINTLABEL = 1017,
			ID_REFERENCEOBJECTCOMBOBOX = 1016,
			ID_MULTIPLICITYMULTIPLENOTEBOOKPAGE = 1011,
			ID_MULTIPLICITYSINGLENOTEBOOKPAGE = 1010,
			ID_MULTIPLICITYNOTEBOOK = 1005,
			ID_ENABLEDCHECKBOX = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
