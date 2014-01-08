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
/// @file      VectorPanel.cpp
/// @author    niraj
/// Created:   7/5/2012 10:11:22 PM
/// @section   DESCRIPTION
///            VectorPanel class implementation
///
///------------------------------------------------------------------

#include "VectorSideControl.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// VectorPanel
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(VectorPanel,wxPanel)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(VectorPanel::OnClose)
	EVT_LISTBOX(ID_VECTORLISTBOX,VectorPanel::VectorListBoxSelected)
	EVT_CHECKBOX(ID_LINEUPVECTORS,VectorPanel::LineUpVectorsClick)
	EVT_BUTTON(ID_CLEARVECTORS,VectorPanel::ClearVectorsClick)
	EVT_BUTTON(ID_REMOVEVECTOR,VectorPanel::RemoveVectorClick)
	EVT_BUTTON(ID_ADDVECTOR,VectorPanel::AddVectorClick)
END_EVENT_TABLE()
////Event Table End

VectorPanel::VectorPanel(wxWindow *parent, void (*addPolarVector)(float length, float theta, float phi),
			void (*addRectangularVector)(float X, float Y, float Z),
			void (*removeVector)(int index),
			void (*clearVectors)(void),
			void (*changeLineUpOrientation)(void),
			void (*changeSelection)(wxArrayInt intArray),
			wxWindowID id, const wxPoint& position, const wxSize& size)
	: SimulationPanel( parent, id, position, size )
{
	AddPolarVector = addPolarVector;
	AddRectangularVector = addRectangularVector;
	RemoveVectorFunction = removeVector;
	ClearVectorsFunction = clearVectors;
	ChangeLineUpOrientation = changeLineUpOrientation;
	ChangeSelection = changeSelection;

	wxArrayString arrayStringFor_VectorListBox;
	VectorListBox = new wxListBox(this, ID_VECTORLISTBOX, wxPoint(16, 75), wxSize(268, 150), arrayStringFor_VectorListBox, wxLB_EXTENDED);

	LineUpVectors = new wxCheckBox(this, ID_LINEUPVECTORS, _("Line Up Vectors"), wxPoint(16, 55), wxSize(98, 17), 0, wxDefaultValidator, _("LineUpVectors"));
	LineUpVectors->SetHelpText(_("Line up all vectors from first to last"));
	LineUpVectors->SetValue(true);

	ClearVectors = new wxButton(this, ID_CLEARVECTORS, _("Clear Vectors"), wxPoint(22, 256), wxSize(252, 25), 0, wxDefaultValidator, _("ClearVectors"));
	ClearVectors->SetHelpText(_("Clear all vectors"));

	RemoveVector = new wxButton(this, ID_REMOVEVECTOR, _("Remove Vector(s)"), wxPoint(156, 228), wxSize(120, 25), 0, wxDefaultValidator, _("RemoveVector"));
	RemoveVector->SetHelpText(_("Remove selected vector(s)"));

	AddVector = new wxButton(this, ID_ADDVECTOR, _("Add Vector"), wxPoint(22, 228), wxSize(120, 25), 0, wxDefaultValidator, _("AddVector"));
	AddVector->SetHelpText(_("Add a vector"));

	vectorListBoxCount = 0;
}

VectorPanel::~VectorPanel()
{
}

void VectorPanel::OnClose(wxCloseEvent& event)
{
	Destroy();
}

void VectorPanel::Reset()
{
	SimulationPanel::Reset();

	wxCommandEvent evt = wxCommandEvent();
	ClearVectorsClick(evt);
}

void VectorPanel::AddObjectToListBox(wxString str)
{
	VectorListBox->Append(str);
}

/*
 * AddVectorClick
 */
void VectorPanel::AddVectorClick(wxCommandEvent& event)
{
	static VectorAddDialog* diag = NULL;
	if (!diag)
	{
		diag = new VectorAddDialog(this);
	}
	
	int result = diag->ShowModal();

	float first = (float)diag->theta;
	float second = (float)diag->phi;
	float third = (float)diag->length;

	if(result == 1)
	{
		//Polar
		AddPolarVector(first, second, third);
		VectorListBox->Append(_("Spherical: {") + wxString::Format("%f", first) + _(", ") + wxString::Format("%f", second) + _(", ") + wxString::Format("%f", third) + _("}"));
	}
	else if(result == 2)
	{
		//Vector
		AddRectangularVector(first, second, third);
		VectorListBox->Append(_("Cartesian: {") + wxString::Format("%f", first) + _(", ") + wxString::Format("%f", second) + _(", ") + wxString::Format("%f", third) + _("}"));
	}
	vectorListBoxCount++;
}

/*
 * RemoveVectorClick
 */
void VectorPanel::RemoveVectorClick(wxCommandEvent& event)
{
	wxArrayInt intArray;
	VectorListBox->GetSelections(intArray);

	for (int i = intArray.size() - 1; i >= 0; i--)
	{
		VectorListBox->Delete(intArray[i]);
		RemoveVectorFunction(intArray[i]);
		vectorListBoxCount--;
	}
}

/*
 * ClearVectorsClick
 */
void VectorPanel::ClearVectorsClick(wxCommandEvent& event)
{
	ClearVectorsFunction();
	VectorListBox->Clear();
}

/*
 * LineUpVectorsClick
 */
void VectorPanel::LineUpVectorsClick(wxCommandEvent& event)
{
	ChangeLineUpOrientation();
}

/*
 * VectorListBoxSelected
 */
void VectorPanel::VectorListBoxSelected(wxCommandEvent& event)
{
	wxArrayInt selections;
	VectorListBox->GetSelections(selections);
	ChangeSelection(selections);
}

