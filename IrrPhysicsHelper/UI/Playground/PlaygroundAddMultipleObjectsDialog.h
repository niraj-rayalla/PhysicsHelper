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
/// @file      PlaygroundAddMultipleObjectsDialog.h
/// @author    niraj
/// Created:   8/15/2012 12:14:35 PM
/// @section   DESCRIPTION
///            PlaygroundAddMultipleObjectsDialog class declaration
///
///------------------------------------------------------------------

#ifndef __PLAYGROUNDADDMULTIPLEOBJECTSDIALOG_H__
#define __PLAYGROUNDADDMULTIPLEOBJECTSDIALOG_H__

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
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/notebook.h>
////Header Include End

////Dialog Style Start
#undef PlaygroundAddMultipleObjectsDialog_STYLE
#define PlaygroundAddMultipleObjectsDialog_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class PlaygroundAddMultipleObjectsDialog : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		PlaygroundAddMultipleObjectsDialog(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Add Multiple Objects"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = PlaygroundAddMultipleObjectsDialog_STYLE);
		virtual ~PlaygroundAddMultipleObjectsDialog();
		void SphericalAddObjectsButtonClick(wxCommandEvent& event);
		void CylindricalAddObjectsButtonClick(wxCommandEvent& event);
		void ParametricAddObjectsButtonClick(wxCommandEvent& event);
		void RectangularAddObjectsButtonClick(wxCommandEvent& event);
		void AddObjectsButtonClick(wxCommandEvent& event);
		void CancelButtonClick(wxCommandEvent& event);
		void AddAsSingleSurfaceCheckboxClick(wxCommandEvent& event);
		void RectangularAxisPickerComboBoxSelected(wxCommandEvent& event);

		bool singleSurface;
		
		double firstRes, secondRes, minFirst, maxFirst,	minSecond, maxSecond;

		wxString xEquation, yEquation, zEquation;

		wxString massEquation, xRotEquation, yRotEquation, zRotEquation;
		//Cylindrical variables

		//Parametric variables

		//Rectangular variables
		int axisIndex;
		wxString equation;

		//Spherical variables
		wxString rEquation;
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *CancelButton;
		wxButton *AddObjectsButton;
		wxTextCtrl *SphericalRotationZTextbox;
		wxStaticText *SphericalRotationZLabel;
		wxTextCtrl *SphericalRotationYTextbox;
		wxStaticText *SphericalRotationYLabel;
		wxTextCtrl *SphericalRotationXTextbox;
		wxStaticText *SphericalRotationXLabel;
		wxStaticText *SphericalRotationLabel;
		wxTextCtrl *SphericalMassTextbox;
		wxStaticText *SphericalMassLabel;
		wxTextCtrl *RectangularRotationZTextbox;
		wxStaticText *RectangularRotationZLabel;
		wxTextCtrl *RectangularRotationYTextbox;
		wxStaticText *RectangularRotationYLabel;
		wxTextCtrl *RectangularRotationXTextbox;
		wxStaticText *RectangularRotationXLabel;
		wxStaticText *RectangularRotationLabel;
		wxTextCtrl *RectangularMassTextbox;
		wxStaticText *RectangularMassLabel;
		wxTextCtrl *ParametricRotationZTextbox;
		wxStaticText *ParametricRotationZLabel;
		wxTextCtrl *ParametricRotationYTextbox;
		wxStaticText *ParametricRotationYLabel;
		wxTextCtrl *ParametricRotationXTextbox;
		wxStaticText *ParametricRotationXLabel;
		wxStaticText *ParametricRotationLabel;
		wxTextCtrl *ParametricMassTextbox;
		wxStaticText *ParametricMassLabel;
		wxTextCtrl *CylindricalRotationZTextbox;
		wxStaticText *CylindricalRotationZLabel;
		wxTextCtrl *CylindricalRotationYTextbox;
		wxStaticText *CylindricalRotationYLabel;
		wxTextCtrl *CylindricalRotationXTextbox;
		wxStaticText *CylindricalRotationXLabel;
		wxStaticText *CylindricalRotationLabel;
		wxTextCtrl *CylindricalMassTextbox;
		wxStaticText *CylindricalMassLabel;
		wxCheckBox *AddAsSingleSurfaceCheckbox;
		wxTextCtrl *SphericalMaxPhiTextbox;
		wxStaticText *SphericalMaxPhiLabel;
		wxTextCtrl *SphericalMinPhiTextbox;
		wxStaticText *SphericalMinPhiLabel;
		wxTextCtrl *SphericalMaxThetaTextbox;
		wxStaticText *SphericalMaxThetaLabel;
		wxTextCtrl *SphericalMinThetaTextbox;
		wxStaticText *SphericalMinThetaLabel;
		wxStaticText *SphericalBoundsLabel;
		wxTextCtrl *SphericalPhiResolutionTextbox;
		wxStaticText *SphericalPhiResolutionLabel;
		wxTextCtrl *SphericalThetaResolutionTextbox;
		wxStaticText *SphericalThetaResolutionLabel;
		wxStaticText *SphericalResolutionLabel;
		wxTextCtrl *SphericalREquationTextbox;
		wxStaticText *SphericalREquationLabel;
		wxStaticText *SphericalEquationLabel;
		wxPanel *SphericalTab;
		wxTextCtrl *RectangularMaxSecondAxisTextbox;
		wxStaticText *RectangularMaxSecondAxisLabel;
		wxTextCtrl *RectangularMinSecondAxisTextbox;
		wxStaticText *RectangularMinSecondAxisLabel;
		wxTextCtrl *RectangularMaxFirstAxisTextbox;
		wxStaticText *RectangularMaxFirstAxisLabel;
		wxTextCtrl *RectangularMinFirstAxisTextbox;
		wxStaticText *RectangularMinFirstAxisLabel;
		wxStaticText *RectangularBoundsLabel;
		wxTextCtrl *RectangularSecondAxisResolutionTextbox;
		wxStaticText *RectangularSecondAxisResolutionLabel;
		wxTextCtrl *RectangularFirstAxisResolutionTextbox;
		wxStaticText *RectangularFirstAxisResolutionLabel;
		wxStaticText *RectangularResolutionLabel;
		wxTextCtrl *RectangularEquationTextbox;
		wxStaticText *WxStaticText2;
		wxComboBox *RectangularAxisPickerComboBox;
		wxStaticText *RectangularEquationLabel;
		wxPanel *RectangularTab;
		wxTextCtrl *ParametricMaxVTextbox;
		wxStaticText *ParametricMaxVLabel;
		wxTextCtrl *ParametricMinVTextbox;
		wxStaticText *ParametricMinVLabel;
		wxTextCtrl *ParametricMaxUTextbox;
		wxStaticText *ParametricMaxULabel;
		wxTextCtrl *ParametricMinUTextbox;
		wxStaticText *ParametricMinULabel;
		wxStaticText *ParametricBoundsLabel;
		wxTextCtrl *ParametricVTextbox;
		wxStaticText *ParametricVResolutionLabel;
		wxTextCtrl *ParametricUTextbox;
		wxStaticText *ParametricUResolutionLabel;
		wxStaticText *ParametricResolutionLabel;
		wxTextCtrl *ParametricZTextbox;
		wxStaticText *ParametricZLabel;
		wxTextCtrl *ParametricYTextbox;
		wxStaticText *ParametricYLabel;
		wxTextCtrl *ParametricXTextbox;
		wxStaticText *ParametricXLabel;
		wxStaticText *ParametricEquationLabel;
		wxPanel *ParametricTab;
		wxTextCtrl *CylindricalMaxRTextbox;
		wxStaticText *CylindricalMaxRLabel;
		wxTextCtrl *CylindricalMinRTextbox;
		wxStaticText *CylindricalMinRLabel;
		wxTextCtrl *CylindricalMaxThetaTextbox;
		wxStaticText *CylindricalMaxThetaLabel;
		wxTextCtrl *CylindricalMinThetaTextbox;
		wxStaticText *CylindricalMinThetaLabel;
		wxStaticText *CylindricalBoundsLabel;
		wxTextCtrl *CylindricalRResolutionTextbox;
		wxStaticText *CylindricalRResolutionLabel;
		wxTextCtrl *CylindricalThetaResolutionTextbox;
		wxStaticText *CylindricalThetaResolutionLabel;
		wxStaticText *CylindricalResolutionLabel;
		wxTextCtrl *CylindricalZEquationTextbox;
		wxStaticText *CylindricalEquationZLabel;
		wxStaticText *CylindricalEquationLabel;
		wxPanel *CylindricalTab;
		wxNotebook *GraphTypesTabs;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_CANCELBUTTON = 3664,
			ID_ADDOBJECTSBUTTON = 3663,
			ID_SPHERICALROTATIONZTEXTBOX = 3662,
			ID_SPHERICALROTATIONZLABEL = 3661,
			ID_SPHERICALROTATIONYTEXTBOX = 3660,
			ID_SPHERICALROTATIONYLABEL = 3659,
			ID_SPHERICALROTATIONXTEXTBOX = 3658,
			ID_SPHERICALXROTATIONLABEL = 3657,
			ID_SPHERICALROTATIONLABEL = 3656,
			ID_SPHERICALMASSTEXTBOX = 3655,
			ID_SPHERICALMASSLABEL = 3654,
			ID_RECTANGULARROTATIONZTEXTBOX = 3617,
			ID_RECTANGULARROTATIONZLABEL = 3616,
			ID_RECTANGULARROTATIONYTEXTBOX = 3615,
			ID_RECTANGULARROTATIONYLABEL = 3614,
			ID_RECTANGULARROTATIONXTEXTBOX = 3613,
			ID_RECTANGULARROTATIONXLABEL = 3612,
			ID_RECTANGULARROTATIONLAVEL = 3611,
			ID_RECTANGULARMASSTEXTBOX = 3610,
			ID_RECTANGULARMASSLABEL = 3609,
			ID_PARAMETRICROTATIONZTEXTBOX = 3572,
			ID_PARAMETRICROTATIONZLABEL = 3571,
			ID_PARAMETRICROTATIONYTEXTBOX = 3570,
			ID_PARAMETRICROTATIONYLABEL = 3569,
			ID_PARAMETRICROTATIONXTEXTBOX = 3568,
			ID_PARAMETRICROTATIONXLABEL = 3567,
			ID_PARAMETRICROTATIONLABEL = 3566,
			ID_PARAMETRICMASSTEXTBOX = 3565,
			ID_PARAMETRICMASSLABEL = 3564,
			ID_CYLINDRICALROTATIONZTEXTBOX = 3527,
			ID_CYLINDRICALROTATIONZLABEL = 3526,
			ID_CYLINDRICALROTATIONYTEXTBOX = 3524,
			ID_ = 3523,
			ID_CYLINDRICALROTATIONXTEXTBOX = 3519,
			ID_CYLINDRICALROTATIONXLABEL = 3518,
			ID_CYLINDRICALROTATIONLABEL = 3517,
			ID_CYLINDRICALMASSTEXTBOX = 3505,
			ID_CYLINDRICALMASSLABEL = 3503,
			ID_ADDASSINGLESURFACECHECKBOX = 3499,
			ID_SPHERICALMAXPHITEXTBOX = 3489,
			ID_SPHERICALMAXPHILABEL = 3488,
			ID_SPHERICALMINPHITEXTBOX = 3487,
			ID_SPHERICALMINPHILABEL = 3486,
			ID_SPHERICALMAXTHETATEXTBOX = 3485,
			ID_SPHERICALMAXTHETALABEL = 3484,
			ID_SPHERICALMINTHETATEXTBOX = 3483,
			ID_SPHERICALMINTHETALABEL = 3482,
			ID_SPHERICALBOUNDSLABEL = 3481,
			ID_SPHERICALPHIRESOLUTIONTEXTBOX = 3480,
			ID_SPHERICALPHIRESOLUTIONLABEL = 3479,
			ID_SPHERICALTHETARESOLUTIONTEXTBOX = 3478,
			ID_SPHERICALTHETARESOLUTIONLABEL = 3477,
			ID_SPHERICALRESOLUTIONLABEL = 3476,
			ID_SPHERICALREQUATIONTEXTBOX = 3475,
			ID_SPHERICALREQUATIONLABEL = 3474,
			ID_SPHERICALEQUATIONLABEL = 3473,
			ID_SPHERICALTAB = 2061,
			ID_RECTANGULARMAXSECONDAXISTEXTBOX = 3164,
			ID_RECTANGULARMAXSECONDAXISLABEL = 3163,
			ID_RECTANGULARMINSECONDAXISTEXTBOX = 3162,
			ID_RECTANGULARMINSECONDAXISLABEL = 3161,
			ID_RECTANGULARMAXFIRSTAXISTEXTBOX = 3160,
			ID_RECTANGULARMAXFIRSTAXISLABEL = 3159,
			ID_RECTANGULARMINFIRSTAXISTEXTBOX = 3158,
			ID_RECTANGULARMINFIRSTAXISLABEL = 3157,
			ID_RECTANGULARBOUNDSLABEL = 3156,
			ID_RECTANGULARSECONDAXISRESOLUTIONTEXTBOX = 3155,
			ID_RECTANGULARSECONDAXISRESOLUTIONLABEL = 3154,
			ID_RECTANGULARFIRSTAXISRESOLUTIONTEXTBOX = 3153,
			ID_RECTANGULARFIRSTAXISRESOLUTIONLABEL = 3152,
			ID_RECTANGULARRESOLUTIONLABEL = 3151,
			ID_RECTANGULAREQUATIONTEXTBOX = 3150,
			ID_WXSTATICTEXT2 = 3149,
			ID_RECTANGULARAXISPICKERCOMBOBOX = 3148,
			ID_RECTANGULAREQUATIONLABEL = 3147,
			ID_RECTANGULARTAB = 2060,
			ID_PARAMETRICMAXVTEXTBOX = 2813,
			ID_PARAMETRICMAXVLABEL = 2812,
			ID_PARAMETRICMINVTEXTBOX = 2811,
			ID_PARAMETRICMINVLABEL = 2810,
			ID_PARAMETRICMAXUTEXTBOX = 2809,
			ID_PARAMETRICMAXULABEL = 2808,
			ID_PARAMETRICMINUTEXTBOX = 2807,
			ID_PARAMETRICMINULABEL = 2806,
			ID_PARAMETRICBOUNDSLABEL = 2805,
			ID_PARAMETRICVTEXTBOX = 2804,
			ID_PARAMETRICVRESOLUTIONLABEL = 2803,
			ID_PARAMETRICUTEXTBOX = 2802,
			ID_PARAMETRICURESOLUTIONLABEL = 2801,
			ID_PARAMETRICRESOLUTIONLABEL = 2800,
			ID_PARAMETRICZTEXTBOX = 2799,
			ID_PARAMETRICZLABEL = 2798,
			ID_PARAMETRICYTEXTBOX = 2797,
			ID_PARAMETRICYLABEL = 2796,
			ID_PARAMETRICXTEXTBOX = 2795,
			ID_PARAMETRICXLABEL = 2794,
			ID_PARAMETRICEQUATIONLABEL = 2793,
			ID_PARAMETRICTAB = 2059,
			ID_CYLINDRICALMAXRTEXTBOX = 2378,
			ID_CYLINDRICALMAXRLABEL = 2377,
			ID_CYLINDRICALMINRTEXTBOX = 2376,
			ID_CYLINDRICALMINRLABEL = 2375,
			ID_CYLINDRICALMAXTHETATEXTBOX = 2374,
			ID_CYLINDRICALMAXTHETALABEL = 2373,
			ID_CYLINDRICALMINTHETATEXTBOX = 2372,
			ID_CYLINDRICALMINTHETALABEL = 2371,
			ID_CYLINDRICALBOUNDSLABEL = 2370,
			ID_CYLINDRICALRRESOLUTIONTEXTBOX = 2369,
			ID_CYLINDRICALRRESOLUTIONLABEL = 2368,
			ID_CYLINDRICALTHETARESOLUTIONTEXTBOX = 2367,
			ID_CYLINDRICALTHETARESOLUTIONLABEL = 2366,
			ID_CYLINDRICALRESOLUTIONLABEL = 2365,
			ID_CYLINDRICALZEQUATIONTEXTBOX = 2364,
			ID_CYLINDRICALEQUATIONZLABEL = 2363,
			ID_CYLINDRICALEQUATIONLABEL = 2362,
			ID_CYLINDRICALTAB = 2058,
			ID_GRAPHTYPESTABS = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
