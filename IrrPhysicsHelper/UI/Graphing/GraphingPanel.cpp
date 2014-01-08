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
/// @file      GraphingPanel.cpp
/// @author    niraj
/// Created:   7/12/2012 11:38:39 AM
/// @section   DESCRIPTION
///            GraphingPanel class implementation
///
///------------------------------------------------------------------

#include "GraphingPanel.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// GraphingPanel
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(GraphingPanel,wxPanel)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(GraphingPanel::OnClose)
	EVT_BUTTON(ID_CLEARGRAPHSBUTTON,GraphingPanel::ClearGraphsButtonClick)
	EVT_BUTTON(ID_REMOVEGRAPHBUTTON,GraphingPanel::RemoveGraphButtonClick)
	EVT_CHECKLISTBOX(ID_GRAPHSLISTBOX,GraphingPanel::GraphsListBoxCheckListBox)
	EVT_BUTTON(ID_SPHERICALADDGRAPHBUTTON,GraphingPanel::SphericalAddGraphButtonClick)
	EVT_BUTTON(ID_SPHERICALCOLORSWITCHBUTTON,GraphingPanel::SphericalColorSwitchButtonClick)
	EVT_COMBOBOX(ID_RECTANGULARAXISPICKERCOMBOBOX,GraphingPanel::RectangularAxisPickerComboBoxSelected)
	EVT_BUTTON(ID_RECTANGULARADDGRAPHBUTTON,GraphingPanel::RectangularAddGraphButtonClick)
	EVT_BUTTON(ID_RECTANGULARSWITCHBUTTON,GraphingPanel::RectangularSwitchButtonClick)
	EVT_BUTTON(ID_PARAMETRICADDGRAPHBUTTON,GraphingPanel::ParametricAddGraphButtonClick)
	EVT_BUTTON(ID_PARAMETRICSWITCHBUTTON,GraphingPanel::ParametricSwitchButtonClick)
	EVT_BUTTON(ID_CYLINDRICALSWITCHCOLORSBUTTON,GraphingPanel::CylindricalSwitchColorsButtonClick)
	EVT_BUTTON(ID_CYLINDRICALADDGRAPHBUTTON,GraphingPanel::CylindricalAddGraphButtonClick)
END_EVENT_TABLE()
////Event Table End

GraphingPanel::GraphingPanel(wxWindow *parent, void (*graphingSimulationAddCylindrical)(wxString _name, const char* equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid),
		void (*graphingSimulationAddParametric)(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
		int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid),
		void (*graphingSimulationAddRectangular)(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis, int equationAxis, 
		int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid),
		void (*graphingSimulationAddSpherical)(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid),
		void (*graphingSimulationRemove)(int index),
		void (*graphingSimulationClear)(void),
		void (*graphingChangeSelections)(wxArrayInt intArray),
		void (*graphingChangeEnabledState)(int index),
		wxWindowID id, const wxPoint &position, const wxSize& size)
: SimulationPanel(parent, id, position, size)
{
	CreateGUIControls();

	GraphingSimulationAddCylindrical = graphingSimulationAddCylindrical;
	GraphingSimulationAddParametric = graphingSimulationAddParametric;
	GraphingSimulationAddRectangular = graphingSimulationAddRectangular;
	GraphingSimulationAddSpherical = graphingSimulationAddSpherical;
	GraphingSimulationRemove = graphingSimulationRemove;
	GraphingSimulationClear = graphingSimulationClear;
	GraphingChangeSelections = graphingChangeSelections;
	GraphingChangeEnabledState = graphingChangeEnabledState;

	objectCounter = 1;
	graphingListBoxCount = 0;

	CylindricalAxisAlongComboBox->SetSelection(0);
	ParametricAxisAlongComboBox->SetSelection(0);
	RectangularAxisPickerComboBox->SetSelection(2);
	RectangularAxisAlongCombobox->SetSelection(0);
	SphericalAxisAlongCombobox->SetSelection(0);
}

GraphingPanel::~GraphingPanel()
{
}

void GraphingPanel::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	wxArrayString arrayStringFor_GraphsListBox;
	GraphsListBox = new wxCheckListBox(this, ID_GRAPHSLISTBOX, wxPoint(16, 14), wxSize(288, 144), arrayStringFor_GraphsListBox, wxLB_SINGLE, wxDefaultValidator, _("GraphsListBox"));

	RemoveGraphButton = new wxButton(this, ID_REMOVEGRAPHBUTTON, _("Remove Graph"), wxPoint(22, 162), wxSize(127, 25), 0, wxDefaultValidator, _("RemoveGraphButton"));

	ClearGraphsButton = new wxButton(this, ID_CLEARGRAPHSBUTTON, _("Clear Graphs"), wxPoint(165, 161), wxSize(132, 25), 0, wxDefaultValidator, _("ClearGraphsButton"));

	GraphTypesTabs = new wxNotebook(this, ID_GRAPHTYPESTABS, wxPoint(16, 200), wxSize(288, 319), wxNB_DEFAULT);

	CylindricalTab = new wxPanel(GraphTypesTabs, ID_CYLINDRICALTAB, wxPoint(4, 26), wxSize(280, 289));
	GraphTypesTabs->AddPage(CylindricalTab, _("Cylindrical"));

	ParametricTab = new wxPanel(GraphTypesTabs, ID_PARAMETRICTAB, wxPoint(4, 26), wxSize(280, 289));
	GraphTypesTabs->AddPage(ParametricTab, _("Parametric"));

	RectangularTab = new wxPanel(GraphTypesTabs, ID_RECTANGULARTAB, wxPoint(4, 26), wxSize(280, 289));
	GraphTypesTabs->AddPage(RectangularTab, _("Rectangular"));

	SphericalTab = new wxPanel(GraphTypesTabs, ID_SPHERICALTAB, wxPoint(4, 26), wxSize(280, 289));
	GraphTypesTabs->AddPage(SphericalTab, _("Spherical"));

	CylindricalEquationLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALEQUATIONLABEL, _("Equation:"), wxPoint(4, 5), wxDefaultSize, 0, _("CylindricalEquationLabel"));

	CylindricalEquationZLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALEQUATIONZLABEL, _("Z="), wxPoint(63, 5), wxDefaultSize, 0, _("CylindricalEquationZLabel"));

	CylindricalZEquationTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALZEQUATIONTEXTBOX, _("theta*r"), wxPoint(83, 5), wxSize(121, 19), 0, wxDefaultValidator, _("CylindricalZEquationTextbox"));

	CylindricalResolutionLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALRESOLUTIONLABEL, _("Resolution:"), wxPoint(4, 31), wxDefaultSize, 0, _("CylindricalResolutionLabel"));

	CylindricalThetaResolutionLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALTHETARESOLUTIONLABEL, _("Theta:"), wxPoint(16, 50), wxDefaultSize, 0, _("CylindricalThetaResolutionLabel"));

	CylindricalThetaResolutionTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALTHETARESOLUTIONTEXTBOX, _("10"), wxPoint(58, 50), wxSize(40, 19), 0, wxDefaultValidator, _("CylindricalThetaResolutionTextbox"));

	CylindricalRResolutionLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALRRESOLUTIONLABEL, _("r:"), wxPoint(112, 50), wxDefaultSize, 0, _("CylindricalRResolutionLabel"));

	CylindricalRResolutionTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALRRESOLUTIONTEXTBOX, _("10"), wxPoint(128, 50), wxSize(40, 19), 0, wxDefaultValidator, _("CylindricalRResolutionTextbox"));

	CylindricalBoundsLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALBOUNDSLABEL, _("Bounds:"), wxPoint(4, 78), wxDefaultSize, 0, _("CylindricalBoundsLabel"));

	CylindricalMinThetaLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALMINTHETALABEL, _("Min Theta:"), wxPoint(16, 97), wxDefaultSize, 0, _("CylindricalMinThetaLabel"));

	CylindricalMinThetaTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALMINTHETATEXTBOX, _("0"), wxPoint(76, 99), wxSize(40, 19), 0, wxDefaultValidator, _("CylindricalMinThetaTextbox"));

	CylindricalMaxThetaLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALMAXTHETALABEL, _("Max Theta:"), wxPoint(131, 97), wxDefaultSize, 0, _("CylindricalMaxThetaLabel"));

	CylindricalMaxThetaTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALMAXTHETATEXTBOX, _("10"), wxPoint(193, 97), wxSize(40, 19), 0, wxDefaultValidator, _("CylindricalMaxThetaTextbox"));

	CylindricalMinRLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALMINRLABEL, _("Min r:"), wxPoint(16, 120), wxDefaultSize, 0, _("CylindricalMinRLabel"));

	CylindricalMinRTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALMINRTEXTBOX, _("0"), wxPoint(51, 120), wxSize(40, 19), 0, wxDefaultValidator, _("CylindricalMinRTextbox"));

	CylindricalMaxRLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALMAXRLABEL, _("Max r:"), wxPoint(100, 120), wxDefaultSize, 0, _("CylindricalMaxRLabel"));

	CylindricalMaxRTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALMAXRTEXTBOX, _("10"), wxPoint(138, 120), wxSize(40, 19), 0, wxDefaultValidator, _("CylindricalMaxRTextbox"));

	CylindricalColorLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALCOLORLABEL, _("Color:"), wxPoint(4, 154), wxDefaultSize, 0, _("CylindricalColorLabel"));

	CylindricalSolidCheckbox = new wxCheckBox(CylindricalTab, ID_CYLINDRICALSOLIDCHECKBOX, _("Solid"), wxPoint(44, 153), wxSize(52, 17), 0, wxDefaultValidator, _("CylindricalSolidCheckbox"));
	CylindricalSolidCheckbox->SetHelpText(_("If checked the graph will be one solid color. If this is not checked the color will be a gradient along a variable."));

	CylindricalAxisAlongLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALAXISALONGLABEL, _("Along:"), wxPoint(137, 154), wxDefaultSize, 0, _("CylindricalAxisAlongLabel"));

	CylindricalColorBeginPicker = new wxColourPickerCtrl(CylindricalTab, ID_CYLINDRICALCOLORBEGINPICKER, wxColour(0,0,255), wxPoint(14, 174), wxSize(22, 24), wxCLRP_DEFAULT_STYLE, wxDefaultValidator, _("CylindricalColorBeginPicker"));

	CylindricalSwitchColorsButton = new wxButton(CylindricalTab, ID_CYLINDRICALSWITCHCOLORSBUTTON, _("Switch"), wxPoint(44, 174), wxSize(50, 25), 0, wxDefaultValidator, _("CylindricalSwitchColorsButton"));

	CylindricalColorEndPicker = new wxColourPickerCtrl(CylindricalTab, ID_CYLINDRICALCOLORENDPICKER, wxColour(255,0,0), wxPoint(102, 174), wxSize(22, 24), wxCLRP_DEFAULT_STYLE, wxDefaultValidator, _("CylindricalColorEndPicker"));

	wxArrayString arrayStringFor_CylindricalAxisAlongComboBox;
	arrayStringFor_CylindricalAxisAlongComboBox.Add(_("r"));
	arrayStringFor_CylindricalAxisAlongComboBox.Add(_("theta"));
	arrayStringFor_CylindricalAxisAlongComboBox.Add(_("z"));
	CylindricalAxisAlongComboBox = new wxComboBox(CylindricalTab, ID_CYLINDRICALAXISALONGCOMBOBOX, _(""), wxPoint(147, 174), wxSize(74, 23), arrayStringFor_CylindricalAxisAlongComboBox, 0, wxDefaultValidator, _("CylindricalAxisAlongComboBox"));

	CylindricalAddGraphButton = new wxButton(CylindricalTab, ID_CYLINDRICALADDGRAPHBUTTON, _("Add Graph"), wxPoint(91, 210), wxSize(89, 25), 0, wxDefaultValidator, _("CylindricalAddGraphButton"));

	ParametricEquationLabel = new wxStaticText(ParametricTab, ID_PARAMETRICEQUATIONLABEL, _("Equation:"), wxPoint(4, 5), wxDefaultSize, 0, _("ParametricEquationLabel"));

	ParametricXLabel = new wxStaticText(ParametricTab, ID_PARAMETRICXLABEL, _("x(u,v)="), wxPoint(16, 25), wxDefaultSize, 0, _("ParametricXLabel"));

	ParametricXTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICXTEXTBOX, _("u*v"), wxPoint(55, 25), wxSize(63, 19), 0, wxDefaultValidator, _("ParametricXTextbox"));

	ParametricYLabel = new wxStaticText(ParametricTab, ID_PARAMETRICYLABEL, _("y(u,v)="), wxPoint(122, 25), wxDefaultSize, 0, _("ParametricYLabel"));

	ParametricYTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICYTEXTBOX, _("u*v"), wxPoint(161, 25), wxSize(63, 19), 0, wxDefaultValidator, _("ParametricYTextbox"));

	ParametricZLabel = new wxStaticText(ParametricTab, ID_PARAMETRICZLABEL, _("z(u,v)="), wxPoint(16, 48), wxDefaultSize, 0, _("ParametricZLabel"));

	ParametricZTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICZTEXTBOX, _("u*v"), wxPoint(55, 48), wxSize(63, 19), 0, wxDefaultValidator, _("ParametricZTextbox"));

	ParametricResolutionLabel = new wxStaticText(ParametricTab, ID_PARAMETRICRESOLUTIONLABEL, _("Resolution:"), wxPoint(4, 79), wxDefaultSize, 0, _("ParametricResolutionLabel"));

	ParametricUResolutionLabel = new wxStaticText(ParametricTab, ID_PARAMETRICURESOLUTIONLABEL, _("U:"), wxPoint(16, 98), wxDefaultSize, 0, _("ParametricUResolutionLabel"));

	ParametricUTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICUTEXTBOX, _("10"), wxPoint(33, 98), wxSize(40, 19), 0, wxDefaultValidator, _("ParametricUTextbox"));

	ParametricVResolutionLabel = new wxStaticText(ParametricTab, ID_PARAMETRICVRESOLUTIONLABEL, _("V:"), wxPoint(88, 98), wxDefaultSize, 0, _("ParametricVResolutionLabel"));

	ParametricVTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICVTEXTBOX, _("10"), wxPoint(105, 98), wxSize(40, 19), 0, wxDefaultValidator, _("ParametricVTextbox"));

	ParametricBoundsLabel = new wxStaticText(ParametricTab, ID_PARAMETRICBOUNDSLABEL, _("Bounds:"), wxPoint(4, 126), wxDefaultSize, 0, _("ParametricBoundsLabel"));

	ParametricMinULabel = new wxStaticText(ParametricTab, ID_PARAMETRICMINULABEL, _("Min U:"), wxPoint(16, 145), wxDefaultSize, 0, _("ParametricMinULabel"));

	ParametricMinUTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICMINUTEXTBOX, _("0"), wxPoint(53, 145), wxSize(40, 19), 0, wxDefaultValidator, _("ParametricMinUTextbox"));

	ParametricMaxULabel = new wxStaticText(ParametricTab, ID_PARAMETRICMAXULABEL, _("Max U:"), wxPoint(99, 145), wxDefaultSize, 0, _("ParametricMaxULabel"));

	ParametricMaxUTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICMAXUTEXTBOX, _("10"), wxPoint(140, 145), wxSize(40, 19), 0, wxDefaultValidator, _("ParametricMaxUTextbox"));

	ParametricMinVLabel = new wxStaticText(ParametricTab, ID_PARAMETRICMINVLABEL, _("Min V:"), wxPoint(16, 168), wxDefaultSize, 0, _("ParametricMinVLabel"));

	ParametricMinVTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICMINVTEXTBOX, _("0"), wxPoint(53, 168), wxSize(40, 19), 0, wxDefaultValidator, _("ParametricMinVTextbox"));

	ParametricMaxVLabel = new wxStaticText(ParametricTab, ID_PARAMETRICMAXVLABEL, _("Max V:"), wxPoint(100, 168), wxDefaultSize, 0, _("ParametricMaxVLabel"));

	ParametricMaxVTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICMAXVTEXTBOX, _("10"), wxPoint(140, 168), wxSize(40, 19), 0, wxDefaultValidator, _("ParametricMaxVTextbox"));

	ParametricColorLabel = new wxStaticText(ParametricTab, ID_PARAMETRICCOLORLABEL, _("Color:"), wxPoint(4, 202), wxDefaultSize, 0, _("ParametricColorLabel"));

	ParametricSolidCheckbox = new wxCheckBox(ParametricTab, ID_PARAMETRICSOLIDCHECKBOX, _("Solid"), wxPoint(44, 202), wxSize(52, 17), 0, wxDefaultValidator, _("ParametricSolidCheckbox"));
	ParametricSolidCheckbox->SetHelpText(_("If checked the graph will be one solid color. If this is not checked the color will be a gradient along a variable."));

	ParametricAlongLabel = new wxStaticText(ParametricTab, ID_PARAMETRICALONGLABEL, _("Along:"), wxPoint(137, 202), wxDefaultSize, 0, _("ParametricAlongLabel"));

	ParametricColorBeginPicker = new wxColourPickerCtrl(ParametricTab, ID_PARAMETRICCOLORBEGINPICKER, wxColour(0,0,255), wxPoint(14, 222), wxSize(22, 24), wxCLRP_DEFAULT_STYLE, wxDefaultValidator, _("ParametricColorBeginPicker"));

	ParametricSwitchButton = new wxButton(ParametricTab, ID_PARAMETRICSWITCHBUTTON, _("Switch"), wxPoint(44, 222), wxSize(50, 25), 0, wxDefaultValidator, _("ParametricSwitchButton"));

	ParametricEndColorPicker = new wxColourPickerCtrl(ParametricTab, ID_PARAMETRICENDCOLORPICKER, wxColour(255,0,0), wxPoint(102, 222), wxSize(22, 24), wxCLRP_DEFAULT_STYLE, wxDefaultValidator, _("ParametricEndColorPicker"));

	wxArrayString arrayStringFor_ParametricAxisAlongComboBox;
	arrayStringFor_ParametricAxisAlongComboBox.Add(_("u"));
	arrayStringFor_ParametricAxisAlongComboBox.Add(_("v"));
	arrayStringFor_ParametricAxisAlongComboBox.Add(_("x"));
	arrayStringFor_ParametricAxisAlongComboBox.Add(_("y"));
	arrayStringFor_ParametricAxisAlongComboBox.Add(_("z"));
	ParametricAxisAlongComboBox = new wxComboBox(ParametricTab, ID_PARAMETRICAXISALONGCOMBOBOX, _(""), wxPoint(147, 222), wxSize(74, 23), arrayStringFor_ParametricAxisAlongComboBox, 0, wxDefaultValidator, _("ParametricAxisAlongComboBox"));

	ParametricAddGraphButton = new wxButton(ParametricTab, ID_PARAMETRICADDGRAPHBUTTON, _("Add Graph"), wxPoint(91, 258), wxSize(89, 25), 0, wxDefaultValidator, _("ParametricAddGraphButton"));

	RectangularEquationLabel = new wxStaticText(RectangularTab, ID_RECTANGULAREQUATIONLABEL, _("Equation:"), wxPoint(4, 5), wxDefaultSize, 0, _("RectangularEquationLabel"));

	wxArrayString arrayStringFor_RectangularAxisPickerComboBox;
	arrayStringFor_RectangularAxisPickerComboBox.Add(_("X"));
	arrayStringFor_RectangularAxisPickerComboBox.Add(_("Y"));
	arrayStringFor_RectangularAxisPickerComboBox.Add(_("Z"));
	RectangularAxisPickerComboBox = new wxComboBox(RectangularTab, ID_RECTANGULARAXISPICKERCOMBOBOX, _(""), wxPoint(58, 5), wxSize(38, 23), arrayStringFor_RectangularAxisPickerComboBox, 0, wxDefaultValidator, _("RectangularAxisPickerComboBox"));

	WxStaticText2 = new wxStaticText(RectangularTab, ID_WXSTATICTEXT2, _("="), wxPoint(101, 5), wxDefaultSize, 0, _("WxStaticText2"));

	RectangularEquationTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULAREQUATIONTEXTBOX, _("x*y"), wxPoint(113, 5), wxSize(121, 19), 0, wxDefaultValidator, _("RectangularEquationTextbox"));

	RectangularResolutionLabel = new wxStaticText(RectangularTab, ID_RECTANGULARRESOLUTIONLABEL, _("Resolution:"), wxPoint(4, 31), wxDefaultSize, 0, _("RectangularResolutionLabel"));

	RectangularFirstAxisResolutionLabel = new wxStaticText(RectangularTab, ID_RECTANGULARFIRSTAXISRESOLUTIONLABEL, _("X:"), wxPoint(16, 50), wxDefaultSize, 0, _("RectangularFirstAxisResolutionLabel"));

	RectangularFirstAxisResolutionTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARFIRSTAXISRESOLUTIONTEXTBOX, _("10"), wxPoint(29, 50), wxSize(40, 19), 0, wxDefaultValidator, _("RectangularFirstAxisResolutionTextbox"));

	RectangularSecondAxisResolutionLabel = new wxStaticText(RectangularTab, ID_RECTANGULARSECONDAXISRESOLUTIONLABEL, _("Y:"), wxPoint(85, 50), wxDefaultSize, 0, _("RectangularSecondAxisResolutionLabel"));

	RectangularSecondAxisResolutionTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARSECONDAXISRESOLUTIONTEXTBOX, _("10"), wxPoint(101, 50), wxSize(40, 19), 0, wxDefaultValidator, _("RectangularSecondAxisResolutionTextbox"));

	RectangularBoundsLabel = new wxStaticText(RectangularTab, ID_RECTANGULARBOUNDSLABEL, _("Bounds:"), wxPoint(4, 78), wxDefaultSize, 0, _("RectangularBoundsLabel"));

	RectangularMinFirstAxisLabel = new wxStaticText(RectangularTab, ID_RECTANGULARMINFIRSTAXISLABEL, _("Min X:"), wxPoint(16, 97), wxDefaultSize, 0, _("RectangularMinFirstAxisLabel"));

	RectangularMinFirstAxisTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARMINFIRSTAXISTEXTBOX, _("0"), wxPoint(53, 97), wxSize(40, 19), 0, wxDefaultValidator, _("RectangularMinFirstAxisTextbox"));

	RectangularMaxFirstAxisLabel = new wxStaticText(RectangularTab, ID_RECTANGULARMAXFIRSTAXISLABEL, _("Max X:"), wxPoint(102, 97), wxDefaultSize, 0, _("RectangularMaxFirstAxisLabel"));

	RectangularMaxFirstAxisTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARMAXFIRSTAXISTEXTBOX, _("10"), wxPoint(140, 97), wxSize(40, 19), 0, wxDefaultValidator, _("RectangularMaxFirstAxisTextbox"));

	RectangularMinSecondAxisLabel = new wxStaticText(RectangularTab, ID_RECTANGULARMINSECONDAXISLABEL, _("Min Y:"), wxPoint(16, 120), wxDefaultSize, 0, _("RectangularMinSecondAxisLabel"));

	RectangularMinSecondAxisTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARMINSECONDAXISTEXTBOX, _("0"), wxPoint(53, 120), wxSize(40, 19), 0, wxDefaultValidator, _("RectangularMinSecondAxisTextbox"));

	RectangularMaxSecondAxisLabel = new wxStaticText(RectangularTab, ID_RECTANGULARMAXSECONDAXISLABEL, _("Max Y:"), wxPoint(102, 120), wxDefaultSize, 0, _("RectangularMaxSecondAxisLabel"));

	RectangularMaxSecondAxisTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARMAXSECONDAXISTEXTBOX, _("10"), wxPoint(140, 120), wxSize(40, 19), 0, wxDefaultValidator, _("RectangularMaxSecondAxisTextbox"));

	RectangularColorLabel = new wxStaticText(RectangularTab, ID_RECTANGULARCOLORLABEL, _("Color:"), wxPoint(4, 154), wxDefaultSize, 0, _("RectangularColorLabel"));

	RectangularSolidCheckbox = new wxCheckBox(RectangularTab, ID_RECTANGULARSOLIDCHECKBOX, _("Solid"), wxPoint(44, 154), wxSize(52, 17), 0, wxDefaultValidator, _("RectangularSolidCheckbox"));
	RectangularSolidCheckbox->SetHelpText(_("If checked the graph will be one solid color. If this is not checked the color will be a gradient along a variable."));

	RectangularColorBeginPicker = new wxColourPickerCtrl(RectangularTab, ID_RECTANGULARCOLORBEGINPICKER, wxColour(0,0,255), wxPoint(14, 174), wxSize(22, 24), wxCLRP_DEFAULT_STYLE, wxDefaultValidator, _("RectangularColorBeginPicker"));

	RectangularSwitchButton = new wxButton(RectangularTab, ID_RECTANGULARSWITCHBUTTON, _("Switch"), wxPoint(44, 174), wxSize(50, 25), 0, wxDefaultValidator, _("RectangularSwitchButton"));

	RectangularColorEndPicker = new wxColourPickerCtrl(RectangularTab, ID_RECTANGULARCOLORENDPICKER, wxColour(255,0,0), wxPoint(102, 174), wxSize(22, 24), wxCLRP_DEFAULT_STYLE, wxDefaultValidator, _("RectangularColorEndPicker"));

	RectangularAlongLabel = new wxStaticText(RectangularTab, ID_RECTANGULARALONGLABEL, _("Along:"), wxPoint(137, 154), wxDefaultSize, 0, _("RectangularAlongLabel"));

	wxArrayString arrayStringFor_RectangularAxisAlongCombobox;
	arrayStringFor_RectangularAxisAlongCombobox.Add(_("x"));
	arrayStringFor_RectangularAxisAlongCombobox.Add(_("y"));
	arrayStringFor_RectangularAxisAlongCombobox.Add(_("z"));
	RectangularAxisAlongCombobox = new wxComboBox(RectangularTab, ID_RECTANGULARAXISALONGCOMBOBOX, _(""), wxPoint(147, 174), wxSize(74, 23), arrayStringFor_RectangularAxisAlongCombobox, 0, wxDefaultValidator, _("RectangularAxisAlongCombobox"));

	RectangularAddGraphButton = new wxButton(RectangularTab, ID_RECTANGULARADDGRAPHBUTTON, _("Add Graph"), wxPoint(91, 210), wxSize(89, 25), 0, wxDefaultValidator, _("RectangularAddGraphButton"));

	SphericalEquationLabel = new wxStaticText(SphericalTab, ID_SPHERICALEQUATIONLABEL, _("Equation:"), wxPoint(4, 5), wxDefaultSize, 0, _("SphericalEquationLabel"));

	SphericalREquationLabel = new wxStaticText(SphericalTab, ID_SPHERICALREQUATIONLABEL, _("r="), wxPoint(63, 5), wxDefaultSize, 0, _("SphericalREquationLabel"));

	SphericalREquationTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALREQUATIONTEXTBOX, _("theta*phi"), wxPoint(83, 5), wxSize(121, 19), 0, wxDefaultValidator, _("SphericalREquationTextbox"));

	SphericalResolutionLabel = new wxStaticText(SphericalTab, ID_SPHERICALRESOLUTIONLABEL, _("Resolution:"), wxPoint(4, 31), wxDefaultSize, 0, _("SphericalResolutionLabel"));

	SphericalThetaResolutionLabel = new wxStaticText(SphericalTab, ID_SPHERICALTHETARESOLUTIONLABEL, _("Theta:"), wxPoint(16, 50), wxDefaultSize, 0, _("SphericalThetaResolutionLabel"));

	SphericalThetaResolutionTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALTHETARESOLUTIONTEXTBOX, _("10"), wxPoint(58, 50), wxSize(40, 19), 0, wxDefaultValidator, _("SphericalThetaResolutionTextbox"));

	SphericalPhiResolutionLabel = new wxStaticText(SphericalTab, ID_SPHERICALPHIRESOLUTIONLABEL, _("Phi:"), wxPoint(111, 51), wxDefaultSize, 0, _("SphericalPhiResolutionLabel"));

	SphericalPhiResolutionTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALPHIRESOLUTIONTEXTBOX, _("10"), wxPoint(138, 50), wxSize(40, 19), 0, wxDefaultValidator, _("SphericalPhiResolutionTextbox"));

	SphericalBoundsLabel = new wxStaticText(SphericalTab, ID_SPHERICALBOUNDSLABEL, _("Bounds:"), wxPoint(4, 78), wxDefaultSize, 0, _("SphericalBoundsLabel"));

	SphericalMinThetaLabel = new wxStaticText(SphericalTab, ID_SPHERICALMINTHETALABEL, _("Min Theta:"), wxPoint(16, 97), wxDefaultSize, 0, _("SphericalMinThetaLabel"));

	SphericalMinThetaTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALMINTHETATEXTBOX, _("0"), wxPoint(78, 97), wxSize(40, 19), 0, wxDefaultValidator, _("SphericalMinThetaTextbox"));

	SphericalMaxThetaLabel = new wxStaticText(SphericalTab, ID_SPHERICALMAXTHETALABEL, _("Max Theta:"), wxPoint(131, 97), wxDefaultSize, 0, _("SphericalMaxThetaLabel"));

	SphericalMaxThetaTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALMAXTHETATEXTBOX, _("10"), wxPoint(193, 97), wxSize(40, 19), 0, wxDefaultValidator, _("SphericalMaxThetaTextbox"));

	SphericalMinPhiLabel = new wxStaticText(SphericalTab, ID_SPHERICALMINPHILABEL, _("Min Phi:"), wxPoint(16, 120), wxDefaultSize, 0, _("SphericalMinPhiLabel"));

	SphericalMinPhiTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALMINPHITEXTBOX, _("0"), wxPoint(65, 120), wxSize(40, 19), 0, wxDefaultValidator, _("SphericalMinPhiTextbox"));

	SphericalMaxPhiLabel = new wxStaticText(SphericalTab, ID_SPHERICALMAXPHILABEL, _("Max Phi:"), wxPoint(114, 120), wxDefaultSize, 0, _("SphericalMaxPhiLabel"));

	SphericalMaxPhiTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALMAXPHITEXTBOX, _("10"), wxPoint(164, 120), wxSize(40, 19), 0, wxDefaultValidator, _("SphericalMaxPhiTextbox"));

	SphericalColorLabel = new wxStaticText(SphericalTab, ID_SPHERICALCOLORLABEL, _("Color:"), wxPoint(4, 154), wxDefaultSize, 0, _("SphericalColorLabel"));

	SphericalSolidCheckbox = new wxCheckBox(SphericalTab, ID_SPHERICALSOLIDCHECKBOX, _("Solid"), wxPoint(44, 154), wxSize(52, 17), 0, wxDefaultValidator, _("SphericalSolidCheckbox"));
	SphericalSolidCheckbox->SetHelpText(_("If checked the graph will be one solid color. If this is not checked the color will be a gradient along a variable."));

	SphericalAlongLabel = new wxStaticText(SphericalTab, ID_SPHERICALALONGLABEL, _("Along:"), wxPoint(137, 154), wxDefaultSize, 0, _("SphericalAlongLabel"));

	SphericalBeginColorPicker = new wxColourPickerCtrl(SphericalTab, ID_SPHERICALBEGINCOLORPICKER, wxColour(0,0,255), wxPoint(14, 174), wxSize(22, 24), wxCLRP_DEFAULT_STYLE, wxDefaultValidator, _("SphericalBeginColorPicker"));

	SphericalColorSwitchButton = new wxButton(SphericalTab, ID_SPHERICALCOLORSWITCHBUTTON, _("Switch"), wxPoint(44, 174), wxSize(50, 25), 0, wxDefaultValidator, _("SphericalColorSwitchButton"));

	SphericalEndColorPicker = new wxColourPickerCtrl(SphericalTab, ID_SPHERICALENDCOLORPICKER, wxColour(255,0,0), wxPoint(102, 174), wxSize(22, 24), wxCLRP_DEFAULT_STYLE, wxDefaultValidator, _("SphericalEndColorPicker"));

	wxArrayString arrayStringFor_SphericalAxisAlongCombobox;
	arrayStringFor_SphericalAxisAlongCombobox.Add(_("phi"));
	arrayStringFor_SphericalAxisAlongCombobox.Add(_("r"));
	arrayStringFor_SphericalAxisAlongCombobox.Add(_("theta"));
	SphericalAxisAlongCombobox = new wxComboBox(SphericalTab, ID_SPHERICALAXISALONGCOMBOBOX, _(""), wxPoint(147, 174), wxSize(74, 23), arrayStringFor_SphericalAxisAlongCombobox, 0, wxDefaultValidator, _("SphericalAxisAlongCombobox"));

	SphericalAddGraphButton = new wxButton(SphericalTab, ID_SPHERICALADDGRAPHBUTTON, _("Add Graph"), wxPoint(91, 210), wxSize(89, 25), 0, wxDefaultValidator, _("SphericalAddGraphButton"));

	SetSize(328,571);
	
	////GUI Items Creation End
}

void GraphingPanel::OnClose(wxCloseEvent& event)
{
	Destroy();
}

/*
 * RemoveGraphButtonClick
 */
void GraphingPanel::RemoveGraphButtonClick(wxCommandEvent& event)
{
	// insert your code here
	wxArrayInt intArray;
	GraphsListBox->GetSelections(intArray);

	for (int i = intArray.size() - 1; i >= 0; i--)
	{		
		GraphsListBox->Delete(intArray[i]);
		GraphingSimulationRemove(intArray[i]);
		graphingListBoxCount--;
	}
}

/*
 * ClearGraphsButtonClick
 */
void GraphingPanel::ClearGraphsButtonClick(wxCommandEvent& event)
{
	// insert your code here
	GraphsListBox->Clear();
	GraphingSimulationClear();

	graphingListBoxCount = 0;
}

void GraphingPanel::Reset()
{
	SimulationPanel::Reset();

	wxCommandEvent evt = wxCommandEvent();
	ClearGraphsButtonClick(evt);
	objectCounter = 1;
}

wxString GraphingPanel::AddObjectToListBox()
{
	wxString temp = _("Graph") + wxString::Format("%i", objectCounter++);
	GraphsListBox->Append(temp);
	GraphsListBox->Check(graphingListBoxCount++);

	return temp;
}


void GraphingPanel::AddObjectToListBox(wxString name, bool enabled)
{
	GraphsListBox->Append(name);
	GraphsListBox->Check(graphingListBoxCount++, enabled);
}
/*
 * CylindricalAddGraphButtonClick
 */
void GraphingPanel::CylindricalAddGraphButtonClick(wxCommandEvent& event)
{
	
	int beginRed = CylindricalColorBeginPicker->GetColour().Red();
	int beginGreen = CylindricalColorBeginPicker->GetColour().Green();
	int beginBlue = CylindricalColorBeginPicker->GetColour().Blue();

	int endRed = CylindricalColorEndPicker->GetColour().Red();
	int endGreen = CylindricalColorEndPicker->GetColour().Green();
	int endBlue = CylindricalColorEndPicker->GetColour().Blue();

	GraphingSimulationAddCylindrical(AddObjectToListBox(), CylindricalZEquationTextbox->GetValue().ToAscii(), 1.0f, beginRed, beginGreen, beginBlue, endRed, endGreen, endBlue, CylindricalAxisAlongComboBox->GetCurrentSelection(),
		wxAtoi(CylindricalThetaResolutionTextbox->GetValue()), wxAtof(CylindricalMinThetaTextbox->GetValue()), wxAtof(CylindricalMaxThetaTextbox->GetValue()),
		wxAtoi(CylindricalRResolutionTextbox->GetValue()), wxAtof(CylindricalMinRTextbox->GetValue()), wxAtof(CylindricalMaxRTextbox->GetValue()), CylindricalSolidCheckbox->IsChecked());
}

/*
 * ParametricAddGraphButtonClick
 */
void GraphingPanel::ParametricAddGraphButtonClick(wxCommandEvent& event)
{
	int beginRed = ParametricColorBeginPicker->GetColour().Red();
	int beginGreen = ParametricColorBeginPicker->GetColour().Green();
	int beginBlue = ParametricColorBeginPicker->GetColour().Blue();

	int endRed = ParametricEndColorPicker->GetColour().Red();
	int endGreen = ParametricEndColorPicker->GetColour().Green();
	int endBlue = ParametricEndColorPicker->GetColour().Blue();

	GraphingSimulationAddParametric(AddObjectToListBox(), ParametricXTextbox->GetValue().ToAscii(), ParametricYTextbox->GetValue().ToAscii(), ParametricZTextbox->GetValue().ToAscii(), 1.0f,
		beginRed, beginGreen, beginBlue, endRed, endGreen, endBlue, ParametricAxisAlongComboBox->GetCurrentSelection(), wxAtoi(ParametricUTextbox->GetValue()), wxAtof(ParametricMinUTextbox->GetValue()), wxAtof(ParametricMaxUTextbox->GetValue()),
		wxAtoi(ParametricVTextbox->GetValue()), wxAtof(ParametricMinVTextbox->GetValue()), wxAtof(ParametricMaxVTextbox->GetValue()), ParametricSolidCheckbox->IsChecked());
}

/*
 * RectangularAddGraphButtonClick
 */
void GraphingPanel::RectangularAddGraphButtonClick(wxCommandEvent& event)
{
	int beginRed = RectangularColorBeginPicker->GetColour().Red();
	int beginGreen = RectangularColorBeginPicker->GetColour().Green();
	int beginBlue = RectangularColorBeginPicker->GetColour().Blue();

	int endRed = RectangularColorEndPicker->GetColour().Red();
	int endGreen = RectangularColorEndPicker->GetColour().Green();
	int endBlue = RectangularColorEndPicker->GetColour().Blue();

	GraphingSimulationAddRectangular(AddObjectToListBox(), RectangularEquationTextbox->GetValue().ToAscii(), 1.0f, beginRed, beginGreen, beginBlue, endRed, endGreen, endBlue, RectangularAxisAlongCombobox->GetCurrentSelection(),
		RectangularAxisPickerComboBox->GetCurrentSelection(), wxAtoi(RectangularFirstAxisResolutionTextbox->GetValue()), wxAtof(RectangularMinFirstAxisTextbox->GetValue()), wxAtof(RectangularMaxFirstAxisTextbox->GetValue()),
		wxAtoi(RectangularSecondAxisResolutionTextbox->GetValue()), wxAtof(RectangularMinSecondAxisTextbox->GetValue()), wxAtof(RectangularMaxSecondAxisTextbox->GetValue()), RectangularSolidCheckbox->IsChecked());
}

/*
 * SphericalAddGraphButtonClick
 */
void GraphingPanel::SphericalAddGraphButtonClick(wxCommandEvent& event)
{
	int beginRed = SphericalBeginColorPicker->GetColour().Red();
	int beginGreen = SphericalBeginColorPicker->GetColour().Green();
	int beginBlue = SphericalBeginColorPicker->GetColour().Blue();

	int endRed = SphericalEndColorPicker->GetColour().Red();
	int endGreen = SphericalEndColorPicker->GetColour().Green();
	int endBlue = SphericalEndColorPicker->GetColour().Blue();

	GraphingSimulationAddSpherical(AddObjectToListBox(), SphericalREquationTextbox->GetValue(), 1.0f, beginRed, beginGreen, beginBlue, endRed, endGreen, endBlue, SphericalAxisAlongCombobox->GetCurrentSelection(),
	wxAtoi(SphericalThetaResolutionTextbox->GetValue()), wxAtof(SphericalMinThetaTextbox->GetValue()), wxAtof(SphericalMaxThetaTextbox->GetValue()),
	wxAtoi(SphericalPhiResolutionTextbox->GetValue()), wxAtof(SphericalMinPhiTextbox->GetValue()), wxAtof(SphericalMaxPhiTextbox->GetValue()), SphericalSolidCheckbox->IsChecked());
}

/*
 * CylindricalSwitchColorsButtonClick
 */
void GraphingPanel::CylindricalSwitchColorsButtonClick(wxCommandEvent& event)
{
	wxColour colorBegin = CylindricalColorBeginPicker->GetColour();
	wxColour colorEnd = CylindricalColorEndPicker->GetColour();

	CylindricalColorBeginPicker->SetColour(colorEnd);
	CylindricalColorEndPicker->SetColour(colorBegin);
}

/*
 * ParametricSwitchButtonClick
 */
void GraphingPanel::ParametricSwitchButtonClick(wxCommandEvent& event)
{
	wxColour colorBegin = ParametricColorBeginPicker->GetColour();
	wxColour colorEnd = ParametricEndColorPicker->GetColour();

	ParametricColorBeginPicker->SetColour(colorEnd);
	ParametricEndColorPicker->SetColour(colorBegin);
}

/*
 * RectangularSwitchButtonClick
 */
void GraphingPanel::RectangularSwitchButtonClick(wxCommandEvent& event)
{
	wxColour colorBegin = RectangularColorBeginPicker->GetColour();
	wxColour colorEnd = RectangularColorEndPicker->GetColour();

	RectangularColorBeginPicker->SetColour(colorEnd);
	RectangularColorEndPicker->SetColour(colorBegin);
}

/*
 * SphericalColorSwitchButtonClick
 */
void GraphingPanel::SphericalColorSwitchButtonClick(wxCommandEvent& event)
{
	wxColour colorBegin = SphericalBeginColorPicker->GetColour();
	wxColour colorEnd = SphericalEndColorPicker->GetColour();

	SphericalBeginColorPicker->SetColour(colorEnd);
	SphericalEndColorPicker->SetColour(colorBegin);
}

/*
 * RectangularAxisPickerComboBoxSelected
 */
void GraphingPanel::RectangularAxisPickerComboBoxSelected(wxCommandEvent& event )
{
	switch(RectangularAxisPickerComboBox->GetCurrentSelection())
	{
	case 0:
		RectangularFirstAxisResolutionLabel->SetLabel(_("Y:"));
		RectangularSecondAxisResolutionLabel->SetLabel(_("Z:"));

		RectangularMinFirstAxisLabel->SetLabel(_("Min Y:"));
		RectangularMaxFirstAxisLabel->SetLabel(_("Max Y:"));
		RectangularMinSecondAxisLabel->SetLabel(_("Min Z:"));
		RectangularMaxSecondAxisLabel->SetLabel(_("Max Z:"));
		break;
	case 1:
		RectangularFirstAxisResolutionLabel->SetLabel(_("X:"));
		RectangularSecondAxisResolutionLabel->SetLabel(_("Z:"));

		RectangularMinFirstAxisLabel->SetLabel(_("Min X:"));
		RectangularMaxFirstAxisLabel->SetLabel(_("Max X:"));
		RectangularMinSecondAxisLabel->SetLabel(_("Min Z:"));
		RectangularMaxSecondAxisLabel->SetLabel(_("Max Z:"));
		break;
	case 2:
		RectangularFirstAxisResolutionLabel->SetLabel(_("X:"));
		RectangularSecondAxisResolutionLabel->SetLabel(_("Y:"));

		RectangularMinFirstAxisLabel->SetLabel(_("Min X:"));
		RectangularMaxFirstAxisLabel->SetLabel(_("Max X:"));
		RectangularMinSecondAxisLabel->SetLabel(_("Min Y:"));
		RectangularMaxSecondAxisLabel->SetLabel(_("Max Y:"));
		break;
	}
}

/*
 * GraphsListBoxCheckListBox
 */
void GraphingPanel::GraphsListBoxCheckListBox(wxCommandEvent& event)
{
	GraphingChangeEnabledState(event.GetInt());
}
