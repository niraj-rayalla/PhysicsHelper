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
/// @file      GraphingPanel.h
/// @author    niraj
/// Created:   7/12/2012 11:38:39 AM
/// @section   DESCRIPTION
///            GraphingPanel class declaration
///
///------------------------------------------------------------------

#ifndef __GRAPHINGPANEL_H__
#define __GRAPHINGPANEL_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/checklst.h>
#include <wx/combobox.h>
#include <wx/clrpicker.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/aui/auibook.h>
////Header Include End

#include "../SimulationSideControl.h"

class GraphingPanel : public SimulationPanel
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		GraphingPanel(wxWindow *parent, void (*GraphingSimulationAddCylindrical)(wxString _name, const char* equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid),
		void (*GraphingSimulationAddParametric)(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
		int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid),
		void (*GraphingSimulationAddRectangular)(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis, int equationAxis, 
		int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid),
		void (*GraphingSimulationAddSpherical)(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid),
		void (*GraphingSimulationRemove)(int index),
		void (*GraphingSimulationClear)(void),
		void (*GraphingChangeSelections)(wxArrayInt intArray),
		void (*GraphingChangeEnabledState)(int index),
		wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
		virtual ~GraphingPanel();
		void RemoveGraphButtonClick(wxCommandEvent& event);
		void ClearGraphsButtonClick(wxCommandEvent& event);
		void CylindricalAddGraphButtonClick(wxCommandEvent& event);
		void ParametricAddGraphButtonClick(wxCommandEvent& event);
		void RectangularAddGraphButtonClick(wxCommandEvent& event);
		void SphericalAddGraphButtonClick(wxCommandEvent& event);
		void CylindricalSwitchColorsButtonClick(wxCommandEvent& event);
		void ParametricSwitchButtonClick(wxCommandEvent& event);
		void RectangularSwitchButtonClick(wxCommandEvent& event);
		void SphericalColorSwitchButtonClick(wxCommandEvent& event);
		void RectangularAxisPickerComboBoxSelected(wxCommandEvent& event );
		void GraphsListBoxCheckListBox(wxCommandEvent& event);

		void AddObjectToListBox(wxString name, bool enabled);

		void Reset();

		void (*GraphingSimulationAddCylindrical)(wxString _name, const char* equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
			int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid);
		void (*GraphingSimulationAddParametric)(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
			int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid);
		void (*GraphingSimulationAddRectangular)(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis, int equationAxis, 
			int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid);
		void (*GraphingSimulationAddSpherical)(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int _colorAxis,
			int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid);
		void (*GraphingSimulationRemove)(int index);
		void (*GraphingSimulationClear)(void);
		void (*GraphingChangeSelections)(wxArrayInt intArray);
		void (*GraphingChangeEnabledState)(int index);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *ClearGraphsButton;
		wxButton *RemoveGraphButton;
		wxCheckListBox *GraphsListBox;
		wxButton *SphericalAddGraphButton;
		wxComboBox *SphericalAxisAlongCombobox;
		wxStaticText *SphericalAlongLabel;
		wxColourPickerCtrl *SphericalEndColorPicker;
		wxButton *SphericalColorSwitchButton;
		wxColourPickerCtrl *SphericalBeginColorPicker;
		wxCheckBox *SphericalSolidCheckbox;
		wxStaticText *SphericalColorLabel;
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
		wxStaticText *WxStaticText2;
		wxComboBox *RectangularAxisPickerComboBox;
		wxButton *RectangularAddGraphButton;
		wxComboBox *RectangularAxisAlongCombobox;
		wxColourPickerCtrl *RectangularColorEndPicker;
		wxButton *RectangularSwitchButton;
		wxColourPickerCtrl *RectangularColorBeginPicker;
		wxStaticText *RectangularAlongLabel;
		wxCheckBox *RectangularSolidCheckbox;
		wxStaticText *RectangularColorLabel;
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
		wxStaticText *RectangularEquationLabel;
		wxPanel *RectangularTab;
		wxTextCtrl *ParametricZTextbox;
		wxStaticText *ParametricZLabel;
		wxStaticText *ParametricYLabel;
		wxTextCtrl *ParametricYTextbox;
		wxButton *ParametricAddGraphButton;
		wxStaticText *ParametricAlongLabel;
		wxComboBox *ParametricAxisAlongComboBox;
		wxColourPickerCtrl *ParametricEndColorPicker;
		wxButton *ParametricSwitchButton;
		wxColourPickerCtrl *ParametricColorBeginPicker;
		wxCheckBox *ParametricSolidCheckbox;
		wxStaticText *ParametricColorLabel;
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
		wxTextCtrl *ParametricXTextbox;
		wxStaticText *ParametricXLabel;
		wxStaticText *ParametricEquationLabel;
		wxPanel *ParametricTab;
		wxComboBox *CylindricalAxisAlongComboBox;
		wxColourPickerCtrl *CylindricalColorEndPicker;
		wxButton *CylindricalSwitchColorsButton;
		wxColourPickerCtrl *CylindricalColorBeginPicker;
		wxStaticText *CylindricalAxisAlongLabel;
		wxCheckBox *CylindricalSolidCheckbox;
		wxStaticText *CylindricalColorLabel;
		wxButton *CylindricalAddGraphButton;
		wxStaticText *CylindricalMaxRLabel;
		wxTextCtrl *CylindricalMaxRTextbox;
		wxStaticText *CylindricalMaxThetaLabel;
		wxTextCtrl *CylindricalMaxThetaTextbox;
		wxTextCtrl *CylindricalMinRTextbox;
		wxStaticText *CylindricalMinRLabel;
		wxTextCtrl *CylindricalMinThetaTextbox;
		wxStaticText *CylindricalMinThetaLabel;
		wxStaticText *CylindricalBoundsLabel;
		wxStaticText *CylindricalRResolutionLabel;
		wxTextCtrl *CylindricalRResolutionTextbox;
		wxTextCtrl *CylindricalThetaResolutionTextbox;
		wxStaticText *CylindricalThetaResolutionLabel;
		wxStaticText *CylindricalResolutionLabel;
		wxTextCtrl *CylindricalZEquationTextbox;
		wxStaticText *CylindricalEquationZLabel;
		wxStaticText *CylindricalEquationLabel;
		wxPanel *CylindricalTab;
		wxNotebook *GraphTypesTabs;
		////GUI Control Declaration End

		int objectCounter;
		int graphingListBoxCount;
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_SPHERICALADDGRAPHBUTTON = 3497,
			ID_SPHERICALAXISALONGCOMBOBOX = 3496,
			ID_SPHERICALENDCOLORPICKER = 3495,
			ID_SPHERICALCOLORSWITCHBUTTON = 3494,
			ID_SPHERICALBEGINCOLORPICKER = 3493,
			ID_SPHERICALALONGLABEL = 3492,
			ID_SPHERICALSOLIDCHECKBOX = 3491,
			ID_SPHERICALCOLORLABEL = 3490,
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
			ID_RECTANGULARADDGRAPHBUTTON = 3172,
			ID_RECTANGULARAXISALONGCOMBOBOX = 3171,
			ID_RECTANGULARALONGLABEL = 3170,
			ID_RECTANGULARCOLORENDPICKER = 3169,
			ID_RECTANGULARSWITCHBUTTON = 3168,
			ID_RECTANGULARCOLORBEGINPICKER = 3167,
			ID_RECTANGULARSOLIDCHECKBOX = 3166,
			ID_RECTANGULARCOLORLABEL = 3165,
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
			ID_PARAMETRICADDGRAPHBUTTON = 2821,
			ID_PARAMETRICAXISALONGCOMBOBOX = 2820,
			ID_PARAMETRICENDCOLORPICKER = 2819,
			ID_PARAMETRICSWITCHBUTTON = 2818,
			ID_PARAMETRICCOLORBEGINPICKER = 2817,
			ID_PARAMETRICALONGLABEL = 2816,
			ID_PARAMETRICSOLIDCHECKBOX = 2815,
			ID_PARAMETRICCOLORLABEL = 2814,
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
			ID_CYLINDRICALADDGRAPHBUTTON = 2386,
			ID_CYLINDRICALAXISALONGCOMBOBOX = 2385,
			ID_CYLINDRICALCOLORENDPICKER = 2384,
			ID_CYLINDRICALSWITCHCOLORSBUTTON = 2383,
			ID_CYLINDRICALCOLORBEGINPICKER = 2382,
			ID_CYLINDRICALAXISALONGLABEL = 2381,
			ID_CYLINDRICALSOLIDCHECKBOX = 2380,
			ID_CYLINDRICALCOLORLABEL = 2379,
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
			ID_SPHERICALTAB = 2061,
			ID_RECTANGULARTAB = 2060,
			ID_PARAMETRICTAB = 2059,
			ID_CYLINDRICALTAB = 2058,
			ID_GRAPHTYPESTABS = 2057,
			ID_CLEARGRAPHSBUTTON = 1044,
			ID_REMOVEGRAPHBUTTON = 1043,
			ID_GRAPHSLISTBOX = 1011,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();

		wxString AddObjectToListBox();
};

#endif
