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
/// @file      PendulumChangeAccelerationDialog.cpp
/// @author    niraj
/// Created:   7/2/2012 2:01:51 PM
/// @section   DESCRIPTION
///            PendulumChangeAccelerationDialog class implementation
///
///------------------------------------------------------------------

#include "PendulumChangeAccelerationDialog.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// PendulumChangeAccelerationDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(PendulumChangeAccelerationDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(PendulumChangeAccelerationDialog::OnClose)
	EVT_BUTTON(ID_CANCELBUTTON,PendulumChangeAccelerationDialog::CancelButtonClick)
	EVT_BUTTON(ID_CHANGEBUTTON,PendulumChangeAccelerationDialog::ChangeButtonClick)
END_EVENT_TABLE()
////Event Table End

PendulumChangeAccelerationDialog::PendulumChangeAccelerationDialog(wxWindow *parent, wxString xString, wxString yString, wxString zString, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();

	XTextbox->SetLabel(xString);
	YTextbox->SetLabel(yString);
	ZTextbox->SetLabel(zString);
}

PendulumChangeAccelerationDialog::~PendulumChangeAccelerationDialog()
{
} 

void PendulumChangeAccelerationDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	CancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(109, 101), wxSize(75, 25), 0, wxDefaultValidator, _("CancelButton"));

	ChangeButton = new wxButton(this, ID_CHANGEBUTTON, _("Change"), wxPoint(9, 101), wxSize(75, 25), 0, wxDefaultValidator, _("ChangeButton"));

	ZTextbox = new wxTextCtrl(this, ID_ZTEXTBOX, _("0"), wxPoint(40, 55), wxSize(63, 19), 0, wxDefaultValidator, _("ZTextbox"));
	ZTextbox->SetHelpText(_("Z Equation(function dependant on time)"));

	ZLabel = new wxStaticText(this, ID_ZLABEL, _("Z:"), wxPoint(16, 55), wxDefaultSize, 0, _("ZLabel"));

	YTextbox = new wxTextCtrl(this, ID_YTEXTBOX, _("-9.8"), wxPoint(40, 32), wxSize(63, 19), 0, wxDefaultValidator, _("YTextbox"));
	YTextbox->SetHelpText(_("Y Equation"));

	YLabel = new wxStaticText(this, ID_YLABEL, _("Y:"), wxPoint(16, 32), wxDefaultSize, 0, _("YLabel"));

	XTextbox = new wxTextCtrl(this, ID_XTEXTBOX, _("0"), wxPoint(40, 9), wxSize(63, 19), 0, wxDefaultValidator, _("XTextbox"));
	XTextbox->SetHelpText(_("X Equation(function dependant on time)"));

	XLabel = new wxStaticText(this, ID_XLABEL, _("X:"), wxPoint(16, 9), wxDefaultSize, 0, _("XLabel"));

	SetTitle(_("PendulumChangeAccelerationDialog"));
	SetIcon(wxNullIcon);
	SetSize(8,8,207,171);
	Center();
	
	////GUI Items Creation End
}

void PendulumChangeAccelerationDialog::OnClose(wxCloseEvent& /*event*/)
{
	this->EndModal(0);
}

void PendulumChangeAccelerationDialog::ChangeButtonClick(wxCommandEvent& event)
{
	// insert your code here
	this->EndModal(1);
}

/*
 * CancelButtonClick
 */
void PendulumChangeAccelerationDialog::CancelButtonClick(wxCommandEvent& event)
{
	this->EndModal(0);
}
