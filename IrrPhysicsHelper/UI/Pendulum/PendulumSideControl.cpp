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

#include "PendulumSideControl.h"

PendulumPanel* globalPendulumPanel;

void AddPendulumFunction(double theta, double phi, double length, float mass)
{
	wxString name = _("Mass:") + wxString::Format(wxT("%f"), mass)
		+ _(" ") + "Theta: " + wxString::Format(wxT("%f"), theta)
		+ _(" ") + "Phi: " + wxString::Format(wxT("%f"), phi)
		+ _(" ") + "Length: " + wxString::Format(wxT("%f"), length);

	globalPendulumPanel->AddPendulumFunctionPointer(name, theta, phi, length, mass);
	globalPendulumPanel->AddToListBox(name);
}

void AddPendulumComponentsFunction(double X, double Y, double Z, float mass)
{
	wxString name = _("Mass:") + wxString::Format(wxT("%f"), mass)
		+ _(" ") + "X: " + wxString::Format(wxT("%f"), X)
		+ _(" ") + "Y: " + wxString::Format(wxT("%f"), Y)
		+ _(" ") + "Z: " + wxString::Format(wxT("%f"), Z);

	globalPendulumPanel->AddPendulumComponentsFunctionPointer(name, X, Y, Z, mass);
	globalPendulumPanel->AddToListBox(name);
}

BEGIN_EVENT_TABLE(PendulumPanel,wxPanel)
	////Manual Code Start
	////Manual Code End
	EVT_CLOSE(PendulumPanel::OnClose)
	EVT_BUTTON(ID_CHANGEACCELERTAIONEQUATIONBUTTON,PendulumPanel::ChangeAccelertaionEquationButtonClick)
	EVT_BUTTON(ID_REMOVEPENDULUM,PendulumPanel::RemovePendulumClick)
	EVT_BUTTON(ID_ADDPENDULUM,PendulumPanel::AddPendulumClick)
	EVT_LISTBOX(ID_PENDULUMLISTBOX,PendulumPanel::PendulumListBoxSelected)
END_EVENT_TABLE()
////Event Table End

PendulumPanel::PendulumPanel(wxWindow *parent, void (*addPendulumFunctionPointer)(wxString _name, double theta, double phi, double length, float mass),
			void (*addPendulumComponentsFunctionPointer)(wxString _name, double X, double Y, double Z, float mass),
			void (*removePendulumFunctionPointer)(int index),
			void (*changeSelectionFunctionPointer)(wxArrayInt indices),
			void (*changeAccelerationEquations)(std::string XString, std::string YString, std::string ZString),
			 wxWindowID id, const wxPoint &pos, const wxSize& size)
	 : TimedSimulationPanel( parent, id, pos, size )
{
	AddPendulumFunctionPointer = addPendulumFunctionPointer;
	AddPendulumComponentsFunctionPointer = addPendulumComponentsFunctionPointer;
	RemovePendulumFunctionPointer = removePendulumFunctionPointer;
	ChangeSelectionFunctionPointer = changeSelectionFunctionPointer;
	ChangeAccelerationEquations = changeAccelerationEquations;

	ChangeAccelertaionEquationButton = new wxButton(this, ID_CHANGEACCELERTAIONEQUATIONBUTTON, _("Change Accelertaion"), wxPoint(161, 53), wxSize(117, 25), 0, wxDefaultValidator, _("ChangeAccelertaionEquationButton"));
	ChangeAccelertaionEquationButton->SetHelpText(_("Change accelertaion equations as funtion of time(t)"));

	CurrentAcceleration = new wxStaticText(this, ID_CURRENTACCELERATION, _("{0, -9.8, 0}"), wxPoint(141, 138), wxDefaultSize, 0, _("CurrentAcceleration"));

	CurrentAccelerationLabel = new wxStaticText(this, ID_CURRENTACCELERATIONLABEL, _("Current Acceleration:"), wxPoint(16, 138), wxDefaultSize, 0, _("CurrentAccelerationLabel"));

	AccelerationZEquation = new wxStaticText(this, ID_ACCELERATIONZEQUATION, _("0"), wxPoint(56, 117), wxDefaultSize, 0, _("AccelerationZEquation"));

	AccelerationYEquation = new wxStaticText(this, ID_ACCELERATIONYEQUATION, _("-9.8"), wxPoint(55, 97), wxDefaultSize, 0, _("AccelerationYEquation"));

	AccelerationXEquation = new wxStaticText(this, ID_ACCELERATIONXEQUATION, _("0"), wxPoint(55, 76), wxDefaultSize, 0, _("AccelerationXEquation"));

	AccelerationZEquationLabel = new wxStaticText(this, ID_ACCELERATIONZEQUATIONLABEL, _("Z:"), wxPoint(32, 117), wxDefaultSize, 0, _("AccelerationZEquationLabel"));

	AccelerationYEquationLabel = new wxStaticText(this, ID_ACCELERATIONYEQUATIONLABEL, _("Y:"), wxPoint(32, 97), wxDefaultSize, 0, _("AccelerationYEquationLabel"));

	AccelerationXEquationLabel = new wxStaticText(this, ID_ACCELERATIONXEQUATIONLABEL, _("X:"), wxPoint(32, 76), wxDefaultSize, 0, _("AccelerationXEquationLabel"));

	AccelerationEquationLabel = new wxStaticText(this, ID_ACCELERATIONEQUATIONLABEL, _("Acceleration Equation:"), wxPoint(16, 55), wxDefaultSize, 0, _("AccelerationEquationLabel"));

	RemovePendulum = new wxButton(this, ID_REMOVEPENDULUM, _("Remove Pendulum"), wxPoint(156, 283), wxSize(120, 25), 0, wxDefaultValidator, _("RemovePendulum"));
	RemovePendulum->SetHelpText(_("Remove Pendulum"));

	AddPendulum = new wxButton(this, ID_ADDPENDULUM, _("Add Pendulum"), wxPoint(22, 283), wxSize(120, 25), 0, wxDefaultValidator, _("AddPendulum"));

	wxArrayString arrayStringFor_PendulumListBox;
	PendulumListBox = new wxListBox(this, ID_PENDULUMLISTBOX, wxPoint(16, 165), wxSize(269, 116), arrayStringFor_PendulumListBox, wxLB_EXTENDED);	

	SetInitialSize(size);

	pendulumListBoxCount = 0;
	globalPendulumPanel = this;
}

void PendulumPanel::OnClose(wxCloseEvent& event)
{
	Destroy();
}

PendulumPanel::~PendulumPanel()
{
}


/*
 * AddPendulumClick
 */
void PendulumPanel::AddPendulumClick(wxCommandEvent& event)
{
	static PendulumAddDialog* diag = NULL;
	if (!diag)
	{
		diag = new PendulumAddDialog(this, AddPendulumFunction, AddPendulumComponentsFunction);
	}
	diag->ShowModal();
}
/*
 * RemovePendulumClick
 */
void PendulumPanel::RemovePendulumClick(wxCommandEvent& event)
{
	wxArrayInt intArray;
	PendulumListBox->GetSelections(intArray);

	for (int i = intArray.size() - 1; i >= 0; i--)
	{
		RemovePendulumFunctionPointer(intArray[i]);
		PendulumListBox->Delete(intArray[i]);
		pendulumListBoxCount--;
	}	
}

/*
 * WxListBox1Selected
 */
void PendulumPanel::PendulumListBoxSelected(wxCommandEvent& event)
{
	wxArrayInt intArray;
	PendulumListBox->GetSelections(intArray);
	ChangeSelectionFunctionPointer(intArray);
}

void PendulumPanel::AddToListBox(wxString str)
{
	PendulumListBox->Insert(str, pendulumListBoxCount);
	pendulumListBoxCount++;
}

void PendulumPanel::ChangeCurrentAcceleration(float X, float Y, float Z)
{
	wxString accString = _("{") + wxString::Format(wxT("%f"), X) + _(", ") + wxString::Format(wxT("%f"), Y) + _(", ") + wxString::Format(wxT("%f"), Z) + _("}");

	CurrentAcceleration->SetLabel(accString);
}

void PendulumPanel::Reset()
{
	TimedSimulationPanel::Reset();

	PendulumListBox->Clear();
	pendulumListBoxCount = 0;
}

void PendulumPanel::ChangeAccelertaionEquationButtonClick(wxCommandEvent& event)
{
    static PendulumChangeAccelerationDialog* diag = NULL;
    
    if (!diag)
    {
		diag = new PendulumChangeAccelerationDialog(this, AccelerationXEquation->GetLabel(), AccelerationYEquation->GetLabel(), AccelerationZEquation->GetLabel());
    }
	if (diag->ShowModal() == 1)
	{
		ChangeAccelerationEquations(diag->GetXString().ToStdString(), diag->GetYString().ToStdString(), diag->GetZString().ToStdString());

		AccelerationXEquation->SetLabel(diag->GetXString());
		AccelerationYEquation->SetLabel(diag->GetYString());
		AccelerationZEquation->SetLabel(diag->GetZString());
	}
}
