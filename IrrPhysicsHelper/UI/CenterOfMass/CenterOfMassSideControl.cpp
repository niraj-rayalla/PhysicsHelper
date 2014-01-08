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
/// @file      CenterOfMassPanel.cpp
/// @author    niraj
/// Created:   7/11/2012 10:05:21 AM
/// @section   DESCRIPTION
///            CenterOfMassPanel class implementation
///
///------------------------------------------------------------------

#include "CenterOfMassSideControl.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

CenterOfMassPanel* globalCenterOfMassPanelPointer;

wxArrayString CenterOfMassGetObjectNames()
{
	return globalCenterOfMassPanelPointer->ObjectListbox->GetStrings();
}

//----------------------------------------------------------------------------
// CenterOfMassPanel
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(CenterOfMassPanel,wxPanel)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(CenterOfMassPanel::OnClose)
	EVT_BUTTON(ID_CLEAROBJECTS,CenterOfMassPanel::ClearObjectsClick)
	EVT_BUTTON(ID_REMOVEOBJECT,CenterOfMassPanel::RemoveObjectClick)
	EVT_BUTTON(ID_ADDOBJECT,CenterOfMassPanel::AddObjectClick)
	EVT_CHECKLISTBOX(ID_OBJECTLISTBOX,CenterOfMassPanel::ObjectListboxCheckListBox)
	EVT_LISTBOX(ID_OBJECTLISTBOX,CenterOfMassPanel::ObjectListboxSelected)
END_EVENT_TABLE()
////Event Table End

CenterOfMassPanel::CenterOfMassPanel(wxWindow *parent, wxString* (*addObjectSingle)(wxString _name, float mass, float radius, float posX, float posY, float posZ, bool isRelative, int relativeIndex),
			wxString* (*addObjectMultiple)(wxString _name, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			bool isRelative, int relativeIndex ),
			wxString* (*removeObjectFunction)(int index), wxString* (*clearObjectsFunction)(void),
			void (*changeSelection)(wxArrayInt intArray), wxString* (*changeEnabledState)(int index),
			wxWindowID id, const wxPoint &position, const wxSize& size)
: SimulationPanel(parent, id, position, size)
{
	AddObjectSingle = addObjectSingle;
	AddObjectMultiple = addObjectMultiple;
	RemoveObjectFunction = removeObjectFunction;
	ClearObjectsFunction = clearObjectsFunction;
	ChangeSelection = changeSelection;
	ChangeEnabledState = changeEnabledState;


	NumberOfObjectsValue = new wxStaticText(this, ID_NUMBEROFOBJECTSVALUE, _("0"), wxPoint(135, 290), wxDefaultSize, 0, _("NumberOfObjectsValue"));

	NumberOfObjectsLabel = new wxStaticText(this, ID_NUMBEROFOBJECTSLABEL, _("Number of Objects:"), wxPoint(22, 290), wxDefaultSize, 0, _("NumberOfObjectsLabel"));

	TotalMassValue = new wxStaticText(this, ID_TOTALMASSVALUE, _("0"), wxPoint(112, 267), wxDefaultSize, 0, _("TotalMassValue"));

	TotalMassLabel = new wxStaticText(this, ID_TOTALMASSLABEL, _("Total Mass(Kg):"), wxPoint(22, 267), wxDefaultSize, 0, _("TotalMassLabel"));
	TotalMassLabel->SetHelpText(_("The total mass of all the objects being used for the calculation."));

	CenterOfMassValue = new wxStaticText(this, ID_CENTEROFMASSVALUE, _("{0, 0, 0}"), wxPoint(116, 244), wxDefaultSize, 0, _("CenterOfMassValue"));

	CenterOfMassLabel = new wxStaticText(this, ID_CENTEROFMASSLABEL, _("Center Of Mass:"), wxPoint(22, 244), wxDefaultSize, 0, _("CenterOfMassLabel"));

	ClearObjects = new wxButton(this, ID_CLEAROBJECTS, _("Clear Objects"), wxPoint(22, 200), wxSize(252, 25), 0, wxDefaultValidator, _("ClearObjects"));
	ClearObjects->SetHelpText(_("Clear all objects"));

	RemoveObject = new wxButton(this, ID_REMOVEOBJECT, _("Remove Object(s)"), wxPoint(156, 172), wxSize(120, 25), 0, wxDefaultValidator, _("RemoveObject"));
	RemoveObject->SetHelpText(_("Remove selected object(s)"));

	AddObject = new wxButton(this, ID_ADDOBJECT, _("Add Object"), wxPoint(22, 172), wxSize(120, 25), 0, wxDefaultValidator, _("AddObject"));

	wxArrayString arrayStringFor_ObjectListbox;
	ObjectListbox = new wxCheckListBox(this, ID_OBJECTLISTBOX, wxPoint(16, 18), wxSize(268, 150), arrayStringFor_ObjectListbox, wxLB_EXTENDED, wxDefaultValidator, _("ObjectListbox"));

	centerOfMassListBoxCount = 0;
	objectCounter = 1;

	globalCenterOfMassPanelPointer = this;
}

CenterOfMassPanel::~CenterOfMassPanel()
{
}

void CenterOfMassPanel::OnClose(wxCloseEvent& event)
{
	Destroy();
}

void CenterOfMassPanel::Reset()
{
	SimulationPanel::Reset();

	wxCommandEvent evt = wxCommandEvent();
	ClearObjectsClick(evt);
}

void CenterOfMassPanel::ChangeCenterOfMassStrings(wxString* strings)
{
	CenterOfMassValue->SetLabel(strings[0]);
	TotalMassValue->SetLabel(strings[1]);
	NumberOfObjectsValue->SetLabel(strings[2]);

	delete [] strings;
}

/*
 * AddObjectClick
 */
void CenterOfMassPanel::AddObjectClick(wxCommandEvent& event)
{
	static CenterOfMassAddDialog* diag = NULL;

	if(!diag)
	{
		diag = new CenterOfMassAddDialog(this, CenterOfMassGetObjectNames);
	}

	diag->BeforeShowing();
	
	if (diag->ShowModal() == 1)
	{
		wxString tempName = _("");

		if (diag->useCustomName)
		{
			tempName = diag->customName;
		}
		else
		{
			tempName = _("Object");
		}

		bool isRelative = diag->refObjType == CenterOfMassReferenceObjectType_Relative;

		if (diag->isSingleObject)
		{
			wxString name = tempName + wxString::Format(wxT("%i"), objectCounter++);
			ObjectListbox->Append(name);
			ObjectListbox->Check(centerOfMassListBoxCount, diag->objEnabled);

			ChangeCenterOfMassStrings(AddObjectSingle(name, (float)diag->singleMass, (float)diag->singleRadius, (float)diag->singlePositionX, (float)diag->singlePositionY, (float)diag->singlePositionZ,
				isRelative, isRelative ? diag->selectedReferenceObjectIndex : -1));

			centerOfMassListBoxCount++;
		}
		else
		{
			if (diag->multiplePositionXAxisRangeResolution >= 1.0 && diag->multiplePositionYAxisRangeResolution >= 1.0 && diag->multiplePositionZAxisRangeResolution >= 1.0)
			{
				bool onceXInterval = false;
				bool onceYInterval = false;
				bool onceZInterval = false;

				double posXInterval = 0.0;
				if(diag->multiplePositionXAxisRangeResolution == 1.0)
				{
					posXInterval = 1.0;
					onceXInterval = true;
				}
				else
				{
					posXInterval = (diag->multiplePositionXAxisRangeEnd- diag->multiplePositionXAxisRangeBegin)/ (diag->multiplePositionXAxisRangeResolution - 1.0);
				}			
				
				double posYInterval = 0.0;
				if(diag->multiplePositionYAxisRangeResolution == 1.0)
				{
					posYInterval = 1.0;
					onceYInterval = true;
				}
				else
				{
					posYInterval = (diag->multiplePositionYAxisRangeEnd - diag->multiplePositionYAxisRangeBegin)/ (diag->multiplePositionYAxisRangeResolution - 1.0);
				}

				double posZInterval = 0.0;
				if(diag->multiplePositionZAxisRangeResolution == 1.0)
				{
					posZInterval = 1.0;
					onceZInterval = true;
				}
				else
				{
					posZInterval = (diag->multiplePositionZAxisRangeEnd - diag->multiplePositionZAxisRangeBegin)/ (diag->multiplePositionZAxisRangeResolution - 1.0);
				}

				int counter = 1;

				for (double currentX = diag->multiplePositionXAxisRangeBegin; currentX <= diag->multiplePositionXAxisRangeEnd; currentX += posXInterval)
				{
					for (double currentY = diag->multiplePositionYAxisRangeBegin; currentY <= diag->multiplePositionYAxisRangeEnd; currentY += posYInterval)
					{
						for (double currentZ = diag->multiplePositionZAxisRangeBegin; currentZ <= diag->multiplePositionZAxisRangeEnd; currentZ += posZInterval)
						{
							ObjectListbox->Append(tempName + wxString::Format(wxT("%i"), counter++));
							ObjectListbox->Check(centerOfMassListBoxCount, diag->objEnabled);
							centerOfMassListBoxCount++;

							if (onceZInterval)
								break;
						}

						if (onceYInterval)
							break;
					}

					if (onceXInterval)
						break;
				}

				ChangeCenterOfMassStrings(AddObjectMultiple(tempName, diag->multipleMass.ToStdString(), diag->multipleRadius.ToStdString(), 
					diag->multiplePositionX.ToStdString(), (float)diag->multiplePositionXAxisRangeBegin, (float)diag->multiplePositionXAxisRangeEnd, (float)diag->multiplePositionXAxisRangeResolution,
					diag->multiplePositionY.ToStdString(), (float)diag->multiplePositionYAxisRangeBegin, (float)diag->multiplePositionYAxisRangeEnd, (float)diag->multiplePositionYAxisRangeResolution,
					diag->multiplePositionZ.ToStdString(), (float)diag->multiplePositionZAxisRangeBegin, (float)diag->multiplePositionZAxisRangeEnd, (float)diag->multiplePositionZAxisRangeResolution,
					isRelative, isRelative ? diag->selectedReferenceObjectIndex : -1));
			}
		}
	}
}

/*
 * RemoveObjectClick
 */
void CenterOfMassPanel::RemoveObjectClick(wxCommandEvent& event)
{
	wxArrayInt intArray;
	ObjectListbox->GetSelections(intArray);

	for (int i = intArray.size() - 1; i >= 0; i--)
	{		
		ObjectListbox->Delete(intArray[i]);
		ChangeCenterOfMassStrings(RemoveObjectFunction(intArray[i]));
		centerOfMassListBoxCount--;
	}
}

/*
 * ClearObjectsClick
 */
void CenterOfMassPanel::ClearObjectsClick(wxCommandEvent& event)
{
	ObjectListbox->Clear();
	ChangeCenterOfMassStrings(ClearObjectsFunction());
	centerOfMassListBoxCount = 0;
	objectCounter = 1;
}

/*
 * ObjectListboxCheckListBox
 */
void CenterOfMassPanel::ObjectListboxCheckListBox(wxCommandEvent& event)
{
	int index = event.GetInt();
	ChangeCenterOfMassStrings(ChangeEnabledState(index));
}

void CenterOfMassPanel::ObjectListboxSelected(wxCommandEvent& event)
{
	wxArrayInt intArray;
	ObjectListbox->GetSelections(intArray);
	ChangeSelection(intArray);
}

void CenterOfMassPanel::AddObjectToListBox(wxString name, bool enabled)
{
	ObjectListbox->Append(name);
	ObjectListbox->Check(centerOfMassListBoxCount++, enabled);
}

void CenterOfMassPanel::ChangeCOMLabels(float COMX, float COMY, float COMZ,	float totalMass, int numObjects)
{
	CenterOfMassValue->SetLabel(_("{") + wxString::Format("%f", COMX) + _(", ")
		+ wxString::Format("%f", COMY) + _(", ")
		+ wxString::Format("%f", COMZ) + _("}"));
	TotalMassValue->SetLabel(wxString::Format("%f", totalMass));
	NumberOfObjectsValue->SetLabel(wxString::Format("%i", numObjects));
}
