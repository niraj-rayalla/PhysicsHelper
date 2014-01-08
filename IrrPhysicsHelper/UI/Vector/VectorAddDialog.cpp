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
/// @file      VectorAddDialog.cpp
/// @author    niraj
/// Created:   7/5/2012 11:52:16 PM
/// @section   DESCRIPTION
///            VectorAddDialog class implementation
///
///------------------------------------------------------------------

#include "VectorAddDialog.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// VectorAddDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(VectorAddDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(VectorAddDialog::OnClose)
	EVT_BUTTON(ID_CANCELBUTTON,VectorAddDialog::CancelButtonClick)
	EVT_BUTTON(ID_ADDBUTTON,VectorAddDialog::AddButtonClick)
	EVT_COMBOBOX(ID_VECTORDESCRIPTIONTYPE,VectorAddDialog::VectorDescriptionTypeSelected)
END_EVENT_TABLE()
////Event Table End

VectorAddDialog::VectorAddDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();

	theta = 0.0;
	phi = 0.0;
	length = 0.0;
}

VectorAddDialog::~VectorAddDialog()
{
} 

void VectorAddDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	CancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(109, 138), wxSize(75, 25), 0, wxDefaultValidator, _("CancelButton"));

	AddButton = new wxButton(this, ID_ADDBUTTON, _("Add"), wxPoint(9, 138), wxSize(75, 25), 0, wxDefaultValidator, _("AddButton"));

	ZorLengthTextbox = new wxTextCtrl(this, ID_ZORLENGTHTEXTBOX, _("10"), wxPoint(58, 92), wxSize(63, 19), 0, wxDefaultValidator, _("ZorLengthTextbox"));

	ZorLengthLabel = new wxStaticText(this, ID_ZORLENGTHLABEL, _("Length:"), wxPoint(16, 92), wxDefaultSize, 0, _("ZorLengthLabel"));

	YorPhiTextbox = new wxTextCtrl(this, ID_YORPHITEXTBOX, _("0"), wxPoint(58, 69), wxSize(63, 19), 0, wxDefaultValidator, _("YorPhiTextbox"));

	YorPhiLabel = new wxStaticText(this, ID_YORPHILABEL, _("Phi:"), wxPoint(16, 69), wxDefaultSize, 0, _("YorPhiLabel"));

	XorThetaTextbox = new wxTextCtrl(this, ID_XORTHETATEXTBOX, _("0"), wxPoint(58, 46), wxSize(63, 19), 0, wxDefaultValidator, _("XorThetaTextbox"));

	XorThetaLabel = new wxStaticText(this, ID_XORTHETALABEL, _("Theta:"), wxPoint(16, 46), wxDefaultSize, 0, _("XorThetaLabel"));

	wxArrayString arrayStringFor_VectorDescriptionType;
	arrayStringFor_VectorDescriptionType.Add(_("Polar"));
	arrayStringFor_VectorDescriptionType.Add(_("Vector"));
	VectorDescriptionType = new wxComboBox(this, ID_VECTORDESCRIPTIONTYPE, _(""), wxPoint(16, 11), wxSize(145, 23), arrayStringFor_VectorDescriptionType, 0, wxDefaultValidator, _("VectorDescriptionType"));
	VectorDescriptionType->SetSelection(1);
	ChangeVectorDescriptionSelection();

	SetTitle(_("Add Vector"));
	SetIcon(wxNullIcon);
	SetSize(8,8,207,202);
	Center();
	
	////GUI Items Creation End
}

void VectorAddDialog::OnClose(wxCloseEvent& /*event*/)
{
	this->EndModal(0);
}

void VectorAddDialog::ChangeVectorDescriptionSelection()
{
    if(VectorDescriptionType->GetCurrentSelection() == 0)
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
 * VectorDescriptionTypeSelected
 */
void VectorAddDialog::VectorDescriptionTypeSelected(wxCommandEvent& event )
{
	ChangeVectorDescriptionSelection();
}

/*
 * AddButtonClick
 */
void VectorAddDialog::AddButtonClick(wxCommandEvent& event)
{
	if (XorThetaTextbox->GetValue().ToDouble(&theta) &&
		YorPhiTextbox->GetValue().ToDouble(&phi) &&
		ZorLengthTextbox->GetValue().ToDouble(&length))
	{
		if(VectorDescriptionType->GetCurrentSelection() == 0)
		{
			//Polar
			this->EndModal(1);
		}
		else
		{
			//Vector
			this->EndModal(2);
		}		
	}
	else
	{
		this->EndModal(0);
	}  
}

/*
 * CancelButtonClick
 */
void VectorAddDialog::CancelButtonClick(wxCommandEvent& event)
{
	this->EndModal(0);
}
