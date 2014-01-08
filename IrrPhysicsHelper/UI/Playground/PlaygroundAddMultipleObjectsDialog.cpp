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
/// @file      PlaygroundAddMultipleObjectsDialog.cpp
/// @author    niraj
/// Created:   8/15/2012 12:14:35 PM
/// @section   DESCRIPTION
///            PlaygroundAddMultipleObjectsDialog class implementation
///
///------------------------------------------------------------------

#include "PlaygroundAddMultipleObjectsDialog.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// PlaygroundAddMultipleObjectsDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(PlaygroundAddMultipleObjectsDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(PlaygroundAddMultipleObjectsDialog::OnClose)
	EVT_BUTTON(ID_CANCELBUTTON,PlaygroundAddMultipleObjectsDialog::CancelButtonClick)
	EVT_BUTTON(ID_ADDOBJECTSBUTTON,PlaygroundAddMultipleObjectsDialog::AddObjectsButtonClick)
	EVT_CHECKBOX(ID_ADDASSINGLESURFACECHECKBOX,PlaygroundAddMultipleObjectsDialog::AddAsSingleSurfaceCheckboxClick)
	EVT_COMBOBOX(ID_RECTANGULARAXISPICKERCOMBOBOX,PlaygroundAddMultipleObjectsDialog::RectangularAxisPickerComboBoxSelected)
END_EVENT_TABLE()
////Event Table End

PlaygroundAddMultipleObjectsDialog::PlaygroundAddMultipleObjectsDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();

	RectangularAxisPickerComboBox->SetSelection(2);
}

PlaygroundAddMultipleObjectsDialog::~PlaygroundAddMultipleObjectsDialog()
{
} 

void PlaygroundAddMultipleObjectsDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	GraphTypesTabs = new wxNotebook(this, ID_GRAPHTYPESTABS, wxPoint(0, 23), wxSize(288, 296), wxNB_DEFAULT);

	CylindricalTab = new wxPanel(GraphTypesTabs, ID_CYLINDRICALTAB, wxPoint(4, 26), wxSize(280, 266));
	GraphTypesTabs->AddPage(CylindricalTab, _("Cylindrical"));

	CylindricalEquationLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALEQUATIONLABEL, _("Equation:"), wxPoint(4, 5), wxDefaultSize, 0, _("CylindricalEquationLabel"));

	CylindricalEquationZLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALEQUATIONZLABEL, _("Z="), wxPoint(63, 5), wxDefaultSize, 0, _("CylindricalEquationZLabel"));

	CylindricalZEquationTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALZEQUATIONTEXTBOX, _("theta*r"), wxPoint(83, 5), wxSize(121, 19), 0, wxDefaultValidator, _("CylindricalZEquationTextbox"));
	CylindricalZEquationTextbox->SetHelpText(_("Function of theta and r(radius)."));

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

	ParametricTab = new wxPanel(GraphTypesTabs, ID_PARAMETRICTAB, wxPoint(4, 26), wxSize(280, 266));
	GraphTypesTabs->AddPage(ParametricTab, _("Parametric"));

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

	RectangularTab = new wxPanel(GraphTypesTabs, ID_RECTANGULARTAB, wxPoint(4, 26), wxSize(280, 266));
	GraphTypesTabs->AddPage(RectangularTab, _("Rectangular"));

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

	SphericalTab = new wxPanel(GraphTypesTabs, ID_SPHERICALTAB, wxPoint(4, 26), wxSize(280, 266));
	GraphTypesTabs->AddPage(SphericalTab, _("Spherical"));

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

	AddAsSingleSurfaceCheckbox = new wxCheckBox(this, ID_ADDASSINGLESURFACECHECKBOX, _("Add as a single surface"), wxPoint(0, 1), wxSize(144, 17), 0, wxDefaultValidator, _("AddAsSingleSurfaceCheckbox"));

	CylindricalMassLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALMASSLABEL, _("Mass:"), wxPoint(4, 152), wxDefaultSize, 0, _("CylindricalMassLabel"));

	CylindricalMassTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALMASSTEXTBOX, _("1"), wxPoint(45, 151), wxSize(85, 19), 0, wxDefaultValidator, _("CylindricalMassTextbox"));
	CylindricalMassTextbox->SetHelpText(_("Mass of less than or equal to zero equates to a immovable object. Function of theta and r(radius)."));

	CylindricalRotationLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALROTATIONLABEL, _("Rotation:"), wxPoint(4, 178), wxDefaultSize, 0, _("CylindricalRotationLabel"));

	CylindricalRotationXLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALROTATIONXLABEL, _("X:"), wxPoint(16, 197), wxDefaultSize, 0, _("CylindricalRotationXLabel"));

	CylindricalRotationXTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALROTATIONXTEXTBOX, _("0"), wxPoint(36, 197), wxSize(43, 19), 0, wxDefaultValidator, _("CylindricalRotationXTextbox"));
	CylindricalRotationXTextbox->SetHelpText(_("Rotation around the X axis in radians. Function of theta and r(radius)."));

	CylindricalRotationYLabel = new wxStaticText(CylindricalTab, ID_, _("Y:"), wxPoint(91, 197), wxDefaultSize, 0, _("CylindricalRotationYLabel"));

	CylindricalRotationYTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALROTATIONYTEXTBOX, _("0"), wxPoint(111, 197), wxSize(43, 19), 0, wxDefaultValidator, _("CylindricalRotationYTextbox"));
	CylindricalRotationYTextbox->SetHelpText(_("Rotation around the Y axis in radians. Function of theta and r(radius)."));

	CylindricalRotationZLabel = new wxStaticText(CylindricalTab, ID_CYLINDRICALROTATIONZLABEL, _("Z:"), wxPoint(167, 197), wxDefaultSize, 0, _("CylindricalRotationZLabel"));

	CylindricalRotationZTextbox = new wxTextCtrl(CylindricalTab, ID_CYLINDRICALROTATIONZTEXTBOX, _("0"), wxPoint(187, 197), wxSize(43, 19), 0, wxDefaultValidator, _("CylindricalRotationZTextbox"));
	CylindricalRotationZTextbox->SetHelpText(_("Rotation around the Z axis in radians. Function of theta and r(radius)."));

	ParametricMassLabel = new wxStaticText(ParametricTab, ID_PARAMETRICMASSLABEL, _("Mass:"), wxPoint(4, 198), wxDefaultSize, 0, _("ParametricMassLabel"));

	ParametricMassTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICMASSTEXTBOX, _("1"), wxPoint(45, 198), wxSize(85, 19), 0, wxDefaultValidator, _("ParametricMassTextbox"));
	ParametricMassTextbox->SetHelpText(_("Mass of less than or equal to zero equates to a immovable object. Function of theta and r(radius)."));

	ParametricRotationLabel = new wxStaticText(ParametricTab, ID_PARAMETRICROTATIONLABEL, _("Rotation:"), wxPoint(4, 223), wxDefaultSize, 0, _("ParametricRotationLabel"));

	ParametricRotationXLabel = new wxStaticText(ParametricTab, ID_PARAMETRICROTATIONXLABEL, _("X:"), wxPoint(16, 243), wxDefaultSize, 0, _("ParametricRotationXLabel"));

	ParametricRotationXTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICROTATIONXTEXTBOX, _("0"), wxPoint(36, 243), wxSize(43, 19), 0, wxDefaultValidator, _("ParametricRotationXTextbox"));
	ParametricRotationXTextbox->SetHelpText(_("Rotation around the X axis in radians. Function of theta and r(radius)."));

	ParametricRotationYLabel = new wxStaticText(ParametricTab, ID_PARAMETRICROTATIONYLABEL, _("Y:"), wxPoint(91, 243), wxDefaultSize, 0, _("ParametricRotationYLabel"));

	ParametricRotationYTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICROTATIONYTEXTBOX, _("0"), wxPoint(111, 243), wxSize(43, 19), 0, wxDefaultValidator, _("ParametricRotationYTextbox"));
	ParametricRotationYTextbox->SetHelpText(_("Rotation around the Y axis in radians. Function of theta and r(radius)."));

	ParametricRotationZLabel = new wxStaticText(ParametricTab, ID_PARAMETRICROTATIONZLABEL, _("Z:"), wxPoint(167, 243), wxDefaultSize, 0, _("ParametricRotationZLabel"));

	ParametricRotationZTextbox = new wxTextCtrl(ParametricTab, ID_PARAMETRICROTATIONZTEXTBOX, _("0"), wxPoint(187, 243), wxSize(43, 19), 0, wxDefaultValidator, _("ParametricRotationZTextbox"));
	ParametricRotationZTextbox->SetHelpText(_("Rotation around the Z axis in radians. Function of theta and r(radius)."));

	RectangularMassLabel = new wxStaticText(RectangularTab, ID_RECTANGULARMASSLABEL, _("Mass:"), wxPoint(4, 152), wxDefaultSize, 0, _("RectangularMassLabel"));

	RectangularMassTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARMASSTEXTBOX, _("1"), wxPoint(45, 152), wxSize(85, 19), 0, wxDefaultValidator, _("RectangularMassTextbox"));
	RectangularMassTextbox->SetHelpText(_("Mass of less than or equal to zero equates to a immovable object. Function of theta and r(radius)."));

	RectangularRotationLabel = new wxStaticText(RectangularTab, ID_RECTANGULARROTATIONLAVEL, _("Rotation:"), wxPoint(4, 178), wxDefaultSize, 0, _("RectangularRotationLabel"));

	RectangularRotationXLabel = new wxStaticText(RectangularTab, ID_RECTANGULARROTATIONXLABEL, _("X:"), wxPoint(16, 197), wxDefaultSize, 0, _("RectangularRotationXLabel"));

	RectangularRotationXTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARROTATIONXTEXTBOX, _("0"), wxPoint(36, 197), wxSize(43, 19), 0, wxDefaultValidator, _("RectangularRotationXTextbox"));
	RectangularRotationXTextbox->SetHelpText(_("Rotation around the X axis in radians. Function of theta and r(radius)."));

	RectangularRotationYLabel = new wxStaticText(RectangularTab, ID_RECTANGULARROTATIONYLABEL, _("Y:"), wxPoint(91, 197), wxDefaultSize, 0, _("RectangularRotationYLabel"));

	RectangularRotationYTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARROTATIONYTEXTBOX, _("0"), wxPoint(111, 197), wxSize(43, 19), 0, wxDefaultValidator, _("RectangularRotationYTextbox"));
	RectangularRotationYTextbox->SetHelpText(_("Rotation around the Y axis in radians. Function of theta and r(radius)."));

	RectangularRotationZLabel = new wxStaticText(RectangularTab, ID_RECTANGULARROTATIONZLABEL, _("Z:"), wxPoint(167, 197), wxDefaultSize, 0, _("RectangularRotationZLabel"));

	RectangularRotationZTextbox = new wxTextCtrl(RectangularTab, ID_RECTANGULARROTATIONZTEXTBOX, _("0"), wxPoint(187, 197), wxSize(43, 19), 0, wxDefaultValidator, _("RectangularRotationZTextbox"));
	RectangularRotationZTextbox->SetHelpText(_("Rotation around the Z axis in radians. Function of theta and r(radius)."));

	SphericalMassLabel = new wxStaticText(SphericalTab, ID_SPHERICALMASSLABEL, _("Mass:"), wxPoint(4, 152), wxDefaultSize, 0, _("SphericalMassLabel"));

	SphericalMassTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALMASSTEXTBOX, _("1"), wxPoint(45, 152), wxSize(85, 19), 0, wxDefaultValidator, _("SphericalMassTextbox"));
	SphericalMassTextbox->SetHelpText(_("Mass of less than or equal to zero equates to a immovable object. Function of theta and r(radius)."));

	SphericalRotationLabel = new wxStaticText(SphericalTab, ID_SPHERICALROTATIONLABEL, _("Rotation:"), wxPoint(4, 178), wxDefaultSize, 0, _("SphericalRotationLabel"));

	SphericalRotationXLabel = new wxStaticText(SphericalTab, ID_SPHERICALXROTATIONLABEL, _("X:"), wxPoint(16, 197), wxDefaultSize, 0, _("SphericalRotationXLabel"));

	SphericalRotationXTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALROTATIONXTEXTBOX, _("0"), wxPoint(36, 197), wxSize(43, 19), 0, wxDefaultValidator, _("SphericalRotationXTextbox"));
	SphericalRotationXTextbox->SetHelpText(_("Rotation around the X axis in radians. Function of theta and r(radius)."));

	SphericalRotationYLabel = new wxStaticText(SphericalTab, ID_SPHERICALROTATIONYLABEL, _("Y:"), wxPoint(91, 197), wxDefaultSize, 0, _("SphericalRotationYLabel"));

	SphericalRotationYTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALROTATIONYTEXTBOX, _("0"), wxPoint(111, 197), wxSize(43, 19), 0, wxDefaultValidator, _("SphericalRotationYTextbox"));
	SphericalRotationYTextbox->SetHelpText(_("Rotation around the Y axis in radians. Function of theta and r(radius)."));

	SphericalRotationZLabel = new wxStaticText(SphericalTab, ID_SPHERICALROTATIONZLABEL, _("Z:"), wxPoint(167, 197), wxDefaultSize, 0, _("SphericalRotationZLabel"));

	SphericalRotationZTextbox = new wxTextCtrl(SphericalTab, ID_SPHERICALROTATIONZTEXTBOX, _("0"), wxPoint(187, 197), wxSize(43, 19), 0, wxDefaultValidator, _("SphericalRotationZTextbox"));
	SphericalRotationZTextbox->SetHelpText(_("Rotation around the Z axis in radians. Function of theta and r(radius)."));

	AddObjectsButton = new wxButton(this, ID_ADDOBJECTSBUTTON, _("Add Objects"), wxPoint(23, 324), wxSize(89, 25), 0, wxDefaultValidator, _("AddObjectsButton"));

	CancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(175, 324), wxSize(89, 25), 0, wxDefaultValidator, _("CancelButton"));

	SetTitle(_("Add Multiple objects"));
	SetIcon(wxNullIcon);
	SetSize(8,8,304,392);
	Center();
	
	////GUI Items Creation End
}

void PlaygroundAddMultipleObjectsDialog::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * AddAsSingleSurfaceCheckboxClick
 */
void PlaygroundAddMultipleObjectsDialog::AddAsSingleSurfaceCheckboxClick(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
        AddObjectsButton->SetLabel(_("Add Surface"));
    }
    else
    {
        AddObjectsButton->SetLabel(_("Add Objects"));
    }
}

/*
 * AddObjectsButtonClick
 */
void PlaygroundAddMultipleObjectsDialog::AddObjectsButtonClick(wxCommandEvent& event)
{
	bool hasNoError = false;

	singleSurface = AddAsSingleSurfaceCheckbox->IsChecked();

	switch(GraphTypesTabs->GetSelection())
	{
	case 0:
		hasNoError = (CylindricalThetaResolutionTextbox->GetValue().ToDouble(&firstRes) &&
			CylindricalRResolutionTextbox->GetValue().ToDouble(&secondRes) &&
			CylindricalMinThetaTextbox->GetValue().ToDouble(&minFirst) &&
			CylindricalMaxThetaTextbox->GetValue().ToDouble(&maxFirst) &&
			CylindricalMinRTextbox->GetValue().ToDouble(&minSecond) &&
			CylindricalMaxRTextbox->GetValue().ToDouble(&maxSecond));

		zEquation = CylindricalZEquationTextbox->GetValue();
		massEquation = CylindricalMassTextbox->GetValue();
		xRotEquation = CylindricalRotationXTextbox->GetValue();
		yRotEquation = CylindricalRotationYTextbox->GetValue();
		zRotEquation = CylindricalRotationZTextbox->GetValue();

		if (!hasNoError)
			wxMessageBox(_("One of the numeric fields does not have a valid number"), _("Error in numeric field"));

		if (hasNoError)
			this->EndModal(1);
		break;

	case 1:
		hasNoError = (ParametricUTextbox->GetValue().ToDouble(&firstRes) &&
			ParametricVTextbox->GetValue().ToDouble(&secondRes) &&
			ParametricMinUTextbox->GetValue().ToDouble(&minFirst) &&
			ParametricMaxUTextbox->GetValue().ToDouble(&maxFirst) &&
			ParametricMinVTextbox->GetValue().ToDouble(&minSecond) &&
			ParametricMaxVTextbox->GetValue().ToDouble(&maxSecond));

		xEquation = ParametricXTextbox->GetValue();
		yEquation = ParametricYTextbox->GetValue();
		zEquation = ParametricZTextbox->GetValue();
		massEquation = ParametricMassTextbox->GetValue();
		xRotEquation = ParametricRotationXTextbox->GetValue();
		yRotEquation = ParametricRotationYTextbox->GetValue();
		zRotEquation = ParametricRotationZTextbox->GetValue();

		if (!hasNoError)
			wxMessageBox(_("One of the numeric fields does not have a valid number"), _("Error in numeric field"));

		if (hasNoError)
			this->EndModal(2);
		break;

	case 2:
		hasNoError = (RectangularFirstAxisResolutionTextbox->GetValue().ToDouble(&firstRes) &&
			RectangularSecondAxisResolutionTextbox->GetValue().ToDouble(&secondRes) &&
			RectangularMinFirstAxisTextbox->GetValue().ToDouble(&minFirst) &&
			RectangularMaxFirstAxisTextbox->GetValue().ToDouble(&maxFirst) &&
			RectangularMinSecondAxisTextbox->GetValue().ToDouble(&minSecond) &&
			RectangularMaxSecondAxisTextbox->GetValue().ToDouble(&maxSecond));

		axisIndex = RectangularAxisPickerComboBox->GetCurrentSelection();
		equation = RectangularEquationTextbox->GetValue();
		massEquation = RectangularMassTextbox->GetValue();
		xRotEquation = RectangularRotationXTextbox->GetValue();
		yRotEquation = RectangularRotationYTextbox->GetValue();
		zRotEquation = RectangularRotationZTextbox->GetValue();

		if (!hasNoError)
			wxMessageBox(_("One of the numeric fields does not have a valid number"), _("Error in numeric field"));

		if (hasNoError)
			this->EndModal(3);
		break;

	case 3:
		hasNoError = (SphericalThetaResolutionTextbox->GetValue().ToDouble(&firstRes) &&
			SphericalPhiResolutionTextbox->GetValue().ToDouble(&secondRes) &&
			SphericalMinThetaTextbox->GetValue().ToDouble(&minFirst) &&
			SphericalMaxThetaTextbox->GetValue().ToDouble(&maxFirst) &&
			SphericalMinPhiTextbox->GetValue().ToDouble(&minSecond) &&
			SphericalMaxPhiTextbox->GetValue().ToDouble(&maxSecond));

		rEquation = SphericalREquationTextbox->GetValue();
		massEquation = SphericalMassTextbox->GetValue();
		xRotEquation = SphericalRotationXTextbox->GetValue();
		yRotEquation = SphericalRotationYTextbox->GetValue();
		zRotEquation = SphericalRotationZTextbox->GetValue();

		if (!hasNoError)
			wxMessageBox(_("One of the numeric fields does not have a valid number"), _("Error in numeric field"));

		if (hasNoError)
			this->EndModal(4);
		break;
	}
}

/*
 * CancelButtonClick
 */
void PlaygroundAddMultipleObjectsDialog::CancelButtonClick(wxCommandEvent& event)
{
	this->EndModal(0);
}

/*
 * RectangularAxisPickerComboBoxSelected
 */
void PlaygroundAddMultipleObjectsDialog::RectangularAxisPickerComboBoxSelected(wxCommandEvent& event )
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