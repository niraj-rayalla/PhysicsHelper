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
/// @file      PendulumAddDialog.cpp
/// @author    niraj
/// Created:   6/27/2012 7:32:38 PM
/// @section   DESCRIPTION
///            PendulumAddDialog class implementation
///
///------------------------------------------------------------------

#include "PendulumAddDialog.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// PendulumAddDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(PendulumAddDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(PendulumAddDialog::OnClose)
	EVT_BUTTON(ID_CANCELBUTTON,PendulumAddDialog::CancelButtonClick)
	EVT_BUTTON(ID_ADDBUTTON,PendulumAddDialog::AddButtonClick)
	EVT_COMBOBOX(ID_PENDULUMDESCRIPTIONTYPE,PendulumAddDialog::PendulumDescriptionTypeSelected)
END_EVENT_TABLE()
////Event Table End

PendulumAddDialog::PendulumAddDialog(wxWindow *parent, void (*addPendulumFunctionPointer)(double theta, double phi, double length, float mass),
			void (*addPendulumComponentsFunctionPointer)(double X, double Y, double Z, float mass), wxWindowID id, const wxString &title, 
			const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	AddPendulumFunctionPointer = addPendulumFunctionPointer;
	AddPendulumComponentsFunctionPointer = addPendulumComponentsFunctionPointer;

	CreateGUIControls();
}

PendulumAddDialog::~PendulumAddDialog()
{
} 

void PendulumAddDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	CancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(109, 168), wxSize(75, 25), 0, wxDefaultValidator, _("CancelButton"));

	AddButton = new wxButton(this, ID_ADDBUTTON, _("Add"), wxPoint(9, 168), wxSize(75, 25), 0, wxDefaultValidator, _("AddButton"));

	ZorLengthTextbox = new wxTextCtrl(this, ID_ZORLENGTHTEXTBOX, _("10"), wxPoint(58, 122), wxSize(63, 19), 0, wxDefaultValidator, _("ZorLengthTextbox"));

	ZorLengthLabel = new wxStaticText(this, ID_ZORLENGTHLABLE, _("Length:"), wxPoint(16, 122), wxDefaultSize, 0, _("ZorLengthLabel"));

	YorPhiTextbox = new wxTextCtrl(this, ID_YORPHITEXTBOX, _("0"), wxPoint(58, 99), wxSize(63, 19), 0, wxDefaultValidator, _("YorPhiTextbox"));

	YorPhiLabel = new wxStaticText(this, ID_YORPHILABEL, _("Phi:"), wxPoint(16, 99), wxDefaultSize, 0, _("YorPhiLabel"));

	XorThetaTextbox = new wxTextCtrl(this, ID_XORTHETATEXTBOX, _("0"), wxPoint(58, 76), wxSize(63, 19), 0, wxDefaultValidator, _("XorThetaTextbox"));

	XorThetaLabel = new wxStaticText(this, ID_XORTHETALABEL, _("Theta:"), wxPoint(16, 76), wxDefaultSize, 0, _("XorThetaLabel"));

	wxArrayString arrayStringFor_PendulumDescriptionType;
	arrayStringFor_PendulumDescriptionType.Add(_("Polar"));
	arrayStringFor_PendulumDescriptionType.Add(_("Vector"));
	PendulumDescriptionType = new wxComboBox(this, ID_PENDULUMDESCRIPTIONTYPE, _(""), wxPoint(16, 41), wxSize(145, 23), arrayStringFor_PendulumDescriptionType, 0, wxDefaultValidator, _("PendulumDescriptionType"));
	PendulumDescriptionType->Select(0);

	MassTextbox = new wxTextCtrl(this, ID_MASSTEXTBOX, _("1"), wxPoint(56, 11), wxSize(63, 19), 0, wxDefaultValidator, _("MassTextbox"));

	MassLabel = new wxStaticText(this, ID_MASSLABEL, _("Mass:"), wxPoint(16, 11), wxDefaultSize, 0, _("MassLabel"));

	SetTitle(_("Add Pendulum Node"));
	SetIcon(wxNullIcon);
	SetSize(8,8,207,232);
	Center();
	
	////GUI Items Creation End
}

void PendulumAddDialog::OnClose(wxCloseEvent& /*event*/)
{
	this->EndModal(0);
}

/*
 * PendulumDescriptionTypeSelected
 */
void PendulumAddDialog::PendulumDescriptionTypeSelected(wxCommandEvent& event )
{
    if(PendulumDescriptionType->GetCurrentSelection() == 0)
    {
        //Polar
        XorThetaLabel->SetLabel(_("Theta:"));
        YorPhiLabel->SetLabel(_("Phi:"));
        ZorLengthLabel->SetLabel( _("Length:"));
    }
    else
    {
        //Vector
        XorThetaLabel->SetLabel(_("X:"));
        YorPhiLabel->SetLabel(_("Y:"));
        ZorLengthLabel->SetLabel( _("Z:"));
    }
}

/*
 * AddButtonClick
 */
void PendulumAddDialog::AddButtonClick(wxCommandEvent& event)
{
	double mass = 1.0;
	double theta = 0.0;
	double phi = 0.0;
	double length = 1.0;

	if (MassTextbox->GetValue().ToDouble(&mass) &&
		XorThetaTextbox->GetValue().ToDouble(&theta) &&
		YorPhiTextbox->GetValue().ToDouble(&phi) &&
		ZorLengthTextbox->GetValue().ToDouble(&length))
	{
		if(PendulumDescriptionType->GetCurrentSelection() == 0)
		{
			//Polar
			AddPendulumFunctionPointer(theta, phi, length, (float)mass);
		}
		else
		{
			//Vector
			AddPendulumComponentsFunctionPointer(theta, phi, length, (float)mass);
		}

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
void PendulumAddDialog::CancelButtonClick(wxCommandEvent& event)
{
	this->EndModal(0);
}
