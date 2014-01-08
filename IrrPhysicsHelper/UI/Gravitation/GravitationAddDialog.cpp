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
/// @file      GravitationAddDialog.cpp
/// @author    niraj
/// Created:   7/7/2012 12:31:35 PM
/// @section   DESCRIPTION
///            GravitationAddDialog class implementation
///
///------------------------------------------------------------------

#include "GravitationAddDialog.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// GravitationAddDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(GravitationAddDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(GravitationAddDialog::OnClose)
	EVT_CHECKBOX(ID_CUSTOMNAMECHECKBOX,GravitationAddDialog::CustomNameCheckBoxClick)
	EVT_BUTTON(ID_CANCELBUTTON,GravitationAddDialog::CancelButtonClick)
	EVT_BUTTON(ID_ADDBUTTON,GravitationAddDialog::AddButtonClick)
	EVT_COMBOBOX(ID_REFERENCEOBJECTCOMBOBOX,GravitationAddDialog::ReferenceObjectComboBoxSelected)
END_EVENT_TABLE()
////Event Table End

GravitationAddDialog::GravitationAddDialog(wxWindow *parent, wxArrayString (*getObjectNames)(void), wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();

	GetObjectNames = getObjectNames;

	isSingleObject = true;
	useCustomName = false;
}

GravitationAddDialog::~GravitationAddDialog()
{
} 

void GravitationAddDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	EnabledCheckbox = new wxCheckBox(this, ID_ENABLEDCHECKBOX, _("Enabled"), wxPoint(10, 13), wxSize(70, 17), 0, wxDefaultValidator, _("EnabledCheckbox"));
	EnabledCheckbox->SetHelpText(_("Should the object(s) being added be dynamic or static"));
	EnabledCheckbox->SetValue(true);

	MultiplicityNotebook = new wxNotebook(this, ID_MULTIPLICITYNOTEBOOK, wxPoint(10, 97), wxSize(304, 218), wxNB_DEFAULT);

	MultiplicitySingleNotebookPage = new wxPanel(MultiplicityNotebook, ID_MULTIPLICITYSINGLENOTEBOOKPAGE, wxPoint(4, 26), wxSize(296, 188));
	MultiplicityNotebook->AddPage(MultiplicitySingleNotebookPage, _("Single Object"));

	MultiplicityMultipleNotebookPage = new wxPanel(MultiplicityNotebook, ID_MULTIPLICITYMULTIPLENOTEBOOKPAGE, wxPoint(4, 26), wxSize(296, 188));
	MultiplicityNotebook->AddPage(MultiplicityMultipleNotebookPage, _("Multiple Objects"));

	wxArrayString arrayStringFor_ReferenceObjectComboBox;
	arrayStringFor_ReferenceObjectComboBox.Add(_("Absolute"));
	arrayStringFor_ReferenceObjectComboBox.Add(_("Relative to another object"));
	ReferenceObjectComboBox = new wxComboBox(this, ID_REFERENCEOBJECTCOMBOBOX, _(""), wxPoint(10, 63), wxSize(135, 23), arrayStringFor_ReferenceObjectComboBox, 0, wxDefaultValidator, _("ReferenceObjectComboBox"));
	ReferenceObjectComboBox->Select(0);

	ReferencePointLabel = new wxStaticText(this, ID_REFERENCEPOINTLABEL, _("Position and Velocity type:"), wxPoint(10, 43), wxDefaultSize, 0, _("ReferencePointLabel"));

	MassSingleLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_MASSSINGLELABEL, _("Mass(Kilogram):"), wxPoint(6, 6), wxDefaultSize, 0, _("MassSingleLabel"));

	MassSingleTextbox = new wxTextCtrl(MultiplicitySingleNotebookPage, ID_MASSSINGLETEXTBOX, _("1"), wxPoint(12, 24), wxSize(100, 19), 0, wxDefaultValidator, _("MassSingleTextbox"));

	PositionSingleLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_POSITIONSINGLELABEL, _("Position(Meters):"), wxPoint(6, 98), wxDefaultSize, 0, _("PositionSingleLabel"));

	PositionSingleXTextbox = new wxTextCtrl(MultiplicitySingleNotebookPage, ID_POSITIONSINGLEXTEXTBOX, _("0"), wxPoint(26, 116), wxSize(73, 19), 0, wxDefaultValidator, _("PositionSingleXTextbox"));

	PositionSingleXLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_POSITIONSINGLEXLABEL, _("X:"), wxPoint(12, 116), wxDefaultSize, 0, _("PositionSingleXLabel"));

	PositionSingleYTextbox = new wxTextCtrl(MultiplicitySingleNotebookPage, ID_POSITIONSINGLEYTEXTBOX, _("0"), wxPoint(119, 116), wxSize(73, 19), 0, wxDefaultValidator, _("PositionSingleYTextbox"));

	PositionSingleYLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_POSITIONSINGLEYLABEL, _("Y:"), wxPoint(105, 116), wxDefaultSize, 0, _("PositionSingleYLabel"));

	PositionSingleZTextbox = new wxTextCtrl(MultiplicitySingleNotebookPage, ID_POSITIONSINGLEZTEXTBOX, _("0"), wxPoint(214, 116), wxSize(73, 19), 0, wxDefaultValidator, _("PositionSingleZTextbox"));

	PositionSingleZLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_POSITIONSINGLEZLABEL, _("Z:"), wxPoint(200, 116), wxDefaultSize, 0, _("PositionSingleZLabel"));

	VelocitySingleLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_VELOCITYSINGLELABEL, _("Velocity(Meters / Second):"), wxPoint(6, 144), wxDefaultSize, 0, _("VelocitySingleLabel"));

	VelocitySingleXLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_VELOCITYSINGLEXLABEL, _("X:"), wxPoint(12, 162), wxDefaultSize, 0, _("VelocitySingleXLabel"));

	VelocitySingleXTexbox = new wxTextCtrl(MultiplicitySingleNotebookPage, ID_VELOCITYSINGLEXTEXBOX, _("0"), wxPoint(26, 162), wxSize(73, 19), 0, wxDefaultValidator, _("VelocitySingleXTexbox"));

	VelocitySingleYLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_VELOCITYSINGLEYLABEL, _("Y:"), wxPoint(105, 162), wxDefaultSize, 0, _("VelocitySingleYLabel"));

	VelocitySingleYTexbox = new wxTextCtrl(MultiplicitySingleNotebookPage, ID_VELOCITYSINGLEYTEXBOX, _("0"), wxPoint(119, 162), wxSize(73, 19), 0, wxDefaultValidator, _("VelocitySingleYTexbox"));

	VelocitySingleZLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_VELOCITYSINGLEZLABEL, _("Z:"), wxPoint(200, 162), wxDefaultSize, 0, _("VelocitySingleZLabel"));

	VelocitySingleZTexbox = new wxTextCtrl(MultiplicitySingleNotebookPage, ID_VELOCITYSINGLEZTEXBOX, _("0"), wxPoint(214, 162), wxSize(73, 19), 0, wxDefaultValidator, _("VelocitySingleZTexbox"));

	RadiusSingleLabel = new wxStaticText(MultiplicitySingleNotebookPage, ID_RADIUSSINGLELABEL, _("Raidus(Meters):"), wxPoint(6, 52), wxDefaultSize, 0, _("RadiusSingleLabel"));

	RadiusSingleTextbox = new wxTextCtrl(MultiplicitySingleNotebookPage, ID_RADIUSSINGLETEXTBOX, _("1"), wxPoint(12, 70), wxSize(100, 19), 0, wxDefaultValidator, _("RadiusSingleTextbox"));

	AddButton = new wxButton(this, ID_ADDBUTTON, _("Add"), wxPoint(33, 323), wxSize(101, 25), 0, wxDefaultValidator, _("AddButton"));

	CancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(188, 323), wxSize(101, 25), 0, wxDefaultValidator, _("CancelButton"));

	WxScrolledWindow1 = new wxScrolledWindow(MultiplicityMultipleNotebookPage, ID_WXSCROLLEDWINDOW1, wxPoint(0, 0), wxSize(296, 188), wxVSCROLL | wxHSCROLL);
	WxScrolledWindow1->SetScrollbars(10, 10, 50, 50);

	MultipleMassLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEMASSLABEL, _("Mass(Kilogram):"), wxPoint(6, 6), wxDefaultSize, 0, _("MultipleMassLabel"));

	MultipleMassTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEMASSTEXTBOX, _("1"), wxPoint(12, 24), wxSize(100, 19), 0, wxDefaultValidator, _("MultipleMassTextbox"));

	MultipleRadiusLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLERADIUSLABEL, _("Raidus(Meters):"), wxPoint(6, 52), wxDefaultSize, 0, _("MultipleRadiusLabel"));

	MultipleRadiusTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLERADIUSTEXTBOX, _("1"), wxPoint(12, 70), wxSize(100, 19), 0, wxDefaultValidator, _("MultipleRadiusTextbox"));

	MultiplePositionLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEPOSITIONLABEL, _("Position(Meters):"), wxPoint(6, 98), wxDefaultSize, 0, _("MultiplePositionLabel"));

	MultiplePositionXLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEPOSITIONXLABEL, _("X:"), wxPoint(12, 116), wxDefaultSize, 0, _("MultiplePositionXLabel"));

	MultiplePositionXTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEPOSITIONXTEXTBOX, _("x"), wxPoint(26, 116), wxSize(73, 19), 0, wxDefaultValidator, _("MultiplePositionXTextbox"));

	MultiplePositionYLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEPOSITIONYLABEL, _("Y:"), wxPoint(12, 140), wxDefaultSize, 0, _("MultiplePositionYLabel"));

	MultiplePositionYTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEPOSITIONYTEXTBOX, _("y"), wxPoint(26, 140), wxSize(73, 19), 0, wxDefaultValidator, _("MultiplePositionYTextbox"));

	MultiplePositionZLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEPOSITIONZLABEL, _("Z:"), wxPoint(12, 164), wxDefaultSize, 0, _("MultiplePositionZLabel"));

	MultiplePositionZTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEPOSITIONZTEXTBOX, _("z"), wxPoint(26, 164), wxSize(73, 19), 0, wxDefaultValidator, _("MultiplePositionZTextbox"));

	MultipleVelocityLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEVELOCITYLABEL, _("Velocity(Meters / Second):"), wxPoint(6, 192), wxDefaultSize, 0, _("MultipleVelocityLabel"));

	MultipleVelocityXLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEVELOCITYXLABEL, _("X:"), wxPoint(12, 210), wxDefaultSize, 0, _("MultipleVelocityXLabel"));

	MultipleVelocityXTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEVELOCITYXTEXTBOX, _("0"), wxPoint(26, 210), wxSize(73, 19), 0, wxDefaultValidator, _("MultipleVelocityXTextbox"));

	MultipleVelocityYLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEVELOCITYYLABEL, _("Y:"), wxPoint(105, 210), wxDefaultSize, 0, _("MultipleVelocityYLabel"));

	MultipleVelocityYTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEVELOCITYYTEXTBOX, _("0"), wxPoint(119, 210), wxSize(73, 19), 0, wxDefaultValidator, _("MultipleVelocityYTextbox"));

	MultipleVelocityZLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEVELOCITYZLABEL, _("Z:"), wxPoint(200, 210), wxDefaultSize, 0, _("MultipleVelocityZLabel"));

	MultipleVelocityZTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEVELOCITYZTEXTBOX, _("0"), wxPoint(214, 210), wxSize(73, 19), 0, wxDefaultValidator, _("MultipleVelocityZTextbox"));

	MultipleAxixRangeLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEAXIXRANGELABEL, _("Axis Range:"), wxPoint(105, 98), wxDefaultSize, 0, _("MultipleAxixRangeLabel"));

	MultipleAxisRangeXBegin = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEAXISRANGEXBEGIN, _("0"), wxPoint(110, 116), wxSize(50, 19), 0, wxDefaultValidator, _("MultipleAxisRangeXBegin"));

	MultipleAxisRangeYBegin = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEAXISRANGEYBEGIN, _("0"), wxPoint(110, 140), wxSize(50, 19), 0, wxDefaultValidator, _("MultipleAxisRangeYBegin"));

	MultipleAxisRangeZBegin = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEAXISRANGEZBEGIN, _("0"), wxPoint(110, 164), wxSize(50, 19), 0, wxDefaultValidator, _("MultipleAxisRangeZBegin"));

	WxStaticText11 = new wxStaticText(WxScrolledWindow1, ID_WXSTATICTEXT11, _("to"), wxPoint(164, 116), wxDefaultSize, 0, _("WxStaticText11"));

	WxStaticText12 = new wxStaticText(WxScrolledWindow1, ID_WXSTATICTEXT12, _("to"), wxPoint(164, 140), wxDefaultSize, 0, _("WxStaticText12"));

	WxStaticText13 = new wxStaticText(WxScrolledWindow1, ID_WXSTATICTEXT13, _("to"), wxPoint(164, 164), wxDefaultSize, 0, _("WxStaticText13"));

	MultipleAxisRangeXEnd = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEAXISRANGEXEND, _("10"), wxPoint(179, 117), wxSize(50, 19), 0, wxDefaultValidator, _("MultipleAxisRangeXEnd"));

	MultipleAxisRangeYEnd = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEAXISRANGEYEND, _("10"), wxPoint(179, 140), wxSize(50, 19), 0, wxDefaultValidator, _("MultipleAxisRangeYEnd"));

	MultipleAxisRangeZEnd = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEAXISRANGEZEND, _("10"), wxPoint(179, 164), wxSize(50, 19), 0, wxDefaultValidator, _("MultipleAxisRangeZEnd"));

	MultiplePositionResolutionLabel = new wxStaticText(WxScrolledWindow1, ID_MULTIPLEPOSITIONRESOLUTIONLABEL, _("Resolution:"), wxPoint(237, 98), wxDefaultSize, 0, _("MultiplePositionResolutionLabel"));

	MultiplePositionResolutionXTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEPOSITIONRESOLUTIONXTEXTBOX, _("10"), wxPoint(243, 116), wxSize(50, 19), 0, wxDefaultValidator, _("MultiplePositionResolutionXTextbox"));

	MultiplePositionResolutionYTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEPOSITIONRESOLUTIONYTEXTBOX, _("10"), wxPoint(243, 139), wxSize(50, 19), 0, wxDefaultValidator, _("MultiplePositionResolutionYTextbox"));

	MultiplePositionResolutionZTextbox = new wxTextCtrl(WxScrolledWindow1, ID_MULTIPLEPOSITIONRESOLUTIONZTEXTBOX, _("10"), wxPoint(243, 163), wxSize(50, 19), 0, wxDefaultValidator, _("MultiplePositionResolutionZTextbox"));

	ReferenceObjectLabel = new wxStaticText(this, ID_REFERENCEOBJECTLABEL, _("Reference Object:"), wxPoint(171, 43), wxDefaultSize, 0, _("ReferenceObjectLabel"));
	ReferenceObjectLabel->Show(false);

	wxArrayString arrayStringFor_ReferenceObjectSelectionComboBox;
	arrayStringFor_ReferenceObjectSelectionComboBox.Add(_("Absolute"));
	arrayStringFor_ReferenceObjectSelectionComboBox.Add(_("Relative to another object"));
	ReferenceObjectSelectionComboBox = new wxComboBox(this, ID_REFERENCEOBJECTSELECTIONCOMBOBOX, _(""), wxPoint(171, 63), wxSize(135, 23), arrayStringFor_ReferenceObjectSelectionComboBox, 0, wxDefaultValidator, _("ReferenceObjectSelectionComboBox"));
	ReferenceObjectSelectionComboBox->Show(false);

	CustomNameCheckBox = new wxCheckBox(this, ID_CUSTOMNAMECHECKBOX, _("Use custom name:"), wxPoint(90, 13), wxSize(119, 17), 0, wxDefaultValidator, _("CustomNameCheckBox"));
	CustomNameCheckBox->SetHelpText(_("If selected the name specified will be used. If it's not selected a name will be generated."));

	CustomNameTextbox = new wxTextCtrl(this, ID_CUSTOMNAMETEXTBOX, _("ObjectName"), wxPoint(216, 13), wxSize(90, 19), 0, wxDefaultValidator, _("CustomNameTextbox"));
	CustomNameTextbox->Enable(false);

	SetTitle(_("GravitationAddDialog"));
	SetIcon(wxNullIcon);
	SetSize(8,8,339,387);
	Center();
	
	////GUI Items Creation End
}

void GravitationAddDialog::OnClose(wxCloseEvent& /*event*/)
{
	//Destroy();
	this->EndModal(0);
}

void GravitationAddDialog::BeforeShowing()
{
	wxCommandEvent evt = wxCommandEvent();
	ReferenceObjectComboBoxSelected(evt);
}

/*
 * AddButtonClick
 */
void GravitationAddDialog::AddButtonClick(wxCommandEvent& event)
{
	objEnabled = EnabledCheckbox->IsChecked();
	if(ReferenceObjectComboBox->GetValue() == _("Absolute"))
	{
		//Absolute
		refObjType = ReferenceObjectType_Absolute;
	}
	else
	{
		//Relative
		refObjType = ReferenceObjectType_Relative;
		selectedReferenceObjectIndex = ReferenceObjectSelectionComboBox->GetCurrentSelection();
	}

	useCustomName = CustomNameCheckBox->IsChecked();
	if (useCustomName)
	{
		customName = CustomNameTextbox->GetValue();
	}

	bool hasNoError = false;

	if(MultiplicityNotebook->GetSelection() == 0)
	{
		//Single object
		isSingleObject = true;

		hasNoError = (MassSingleTextbox->GetValue().ToDouble(&singleMass) &&
			RadiusSingleTextbox->GetValue().ToDouble(&singleRadius) &&
			PositionSingleXTextbox->GetValue().ToDouble(&singlePositionX) && PositionSingleYTextbox->GetValue().ToDouble(&singlePositionY) && PositionSingleZTextbox->GetValue().ToDouble(&singlePositionZ) &&
			VelocitySingleXTexbox->GetValue().ToDouble(&singleVelocityX) && VelocitySingleYTexbox->GetValue().ToDouble(&singleVelocityY) && VelocitySingleZTexbox->GetValue().ToDouble(&singleVelocityZ));
	}
	else
	{
		//Multiple objects using equation
		isSingleObject = false;

		hasNoError = (MultipleAxisRangeXBegin->GetValue().ToDouble(&multiplePositionXAxisRangeBegin) &&
			MultipleAxisRangeYBegin->GetValue().ToDouble(&multiplePositionYAxisRangeBegin) &&
			MultipleAxisRangeZBegin->GetValue().ToDouble(&multiplePositionZAxisRangeBegin) &&
			MultipleAxisRangeXEnd->GetValue().ToDouble(&multiplePositionXAxisRangeEnd) &&
			MultipleAxisRangeYEnd->GetValue().ToDouble(&multiplePositionYAxisRangeEnd) &&
			MultipleAxisRangeZEnd->GetValue().ToDouble(&multiplePositionZAxisRangeEnd) &&
			MultiplePositionResolutionXTextbox->GetValue().ToDouble(&multiplePositionXAxisRangeResolution) &&
			MultiplePositionResolutionYTextbox->GetValue().ToDouble(&multiplePositionYAxisRangeResolution) &&
			MultiplePositionResolutionZTextbox->GetValue().ToDouble(&multiplePositionZAxisRangeResolution));

		if (hasNoError)
		{
			multiplePositionXAxisRangeResolution = (double)((int)multiplePositionXAxisRangeResolution);
			multiplePositionYAxisRangeResolution = (double)((int)multiplePositionYAxisRangeResolution);
			multiplePositionZAxisRangeResolution = (double)((int)multiplePositionZAxisRangeResolution);

			multipleMass = MultipleMassTextbox->GetValue();
			multipleRadius = MultipleRadiusTextbox->GetValue();
			multiplePositionX = MultiplePositionXTextbox->GetValue();
			multiplePositionY = MultiplePositionYTextbox->GetValue();
			multiplePositionZ = MultiplePositionZTextbox->GetValue();
			multipleVelocityX = MultipleVelocityXTextbox->GetValue();
			multipleVelocityY = MultipleVelocityYTextbox->GetValue();
			multipleVelocityZ = MultipleVelocityZTextbox->GetValue();
		}
	}

	if(hasNoError)
	{
		this->EndModal(1);
	}
	else
	{
		this->EndModal(0);
	}

}

/*
 * CancelButtonClick
 */
void GravitationAddDialog::CancelButtonClick(wxCommandEvent& event)
{
	this->EndModal(0);
}

/*
 * ReferenceObjectComboBoxSelected
 */
void GravitationAddDialog::ReferenceObjectComboBoxSelected(wxCommandEvent& event )
{
	if (ReferenceObjectComboBox->GetCurrentSelection() == 1)
	{
		wxArrayString names = GetObjectNames();
		if (names.size() > 0)
		{
			ReferenceObjectSelectionComboBox->Clear();

			ReferenceObjectSelectionComboBox->Set(names);
			ReferenceObjectLabel->Show();
			ReferenceObjectSelectionComboBox->Show();
			ReferenceObjectSelectionComboBox->SetSelection(0);

			refObjType = ReferenceObjectType_Relative;
		}
		else
		{
			ReferenceObjectComboBox->SetSelection(0);
			ReferenceObjectLabel->Hide();
			ReferenceObjectSelectionComboBox->Hide();

			refObjType = ReferenceObjectType_Absolute;
		}
	}
	else
	{
		ReferenceObjectLabel->Hide();
		ReferenceObjectSelectionComboBox->Hide();

		refObjType = ReferenceObjectType_Absolute;
	}
}

/*
 * CustomNameCheckBoxClick
 */
void GravitationAddDialog::CustomNameCheckBoxClick(wxCommandEvent& event)
{
	useCustomName = event.IsChecked();

	if (useCustomName)
	{
		CustomNameTextbox->Enable();
	}
	else
	{
		CustomNameTextbox->Enable(false);
	}
}
