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
/// @file      GravirationPanel.cpp
/// @author    niraj
/// Created:   7/4/2012 11:24:17 AM
/// @section   DESCRIPTION
///            GravitationPanel class implementation
///
///------------------------------------------------------------------

#include "GravitationSideControl.h"
#include <wx/clrpicker.h>
#include "wx/colour.h"

GravitationPanel* globalGravitationPanelPointer;

wxArrayString GetObjectNames()
{
	return globalGravitationPanelPointer->ObjectListbox->GetStrings();
}

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// GravitationPanel
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(GravitationPanel,wxPanel)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(GravitationPanel::OnClose)
	EVT_BUTTON(ID_CLEAROBJECTS,GravitationPanel::ClearObjectsClick)
	EVT_LISTBOX(ID_OBJECTLISTBOX,GravitationPanel::ObjectListboxSelected)
	EVT_CHECKLISTBOX(ID_OBJECTLISTBOX,GravitationPanel::ObjectListboxCheckListBox)
	EVT_BUTTON(ID_REMOVEOBJECT,GravitationPanel::RemoveObjectClick)
	EVT_BUTTON(ID_ADDOBJECT,GravitationPanel::AddObjectClick)
END_EVENT_TABLE()
////Event Table End

GravitationPanel::GravitationPanel(wxWindow *parent, void (*addObjectSingle)(wxString _name, bool enabled, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ, bool isRelative, int relativeIndex),
			void (*addObjectMultiple)(wxString _name, bool enabled, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			std::string velX, std::string velY, std::string velZ, bool isRelative, int relativeIndex ),
			void (*removeObjectFunction)(int index), void (*clearObjectsFunction)(void),
			void (*changeSelection)(wxArrayInt intArray), void (*changeEnabledState)(int index),
			wxWindowID id, const wxPoint &position, const wxSize& size)
	: TimedSimulationPanel( parent, id, position, size )
{
	AddObjectSingle = addObjectSingle;
	AddObjectMultiple = addObjectMultiple;
	RemoveObjectFunction = removeObjectFunction;
	ClearObjectsFunction = clearObjectsFunction;
	ChangeSelection = changeSelection;
	ChangeEnabledState = changeEnabledState;	

	ClearObjects = new wxButton(this, ID_CLEAROBJECTS, _("Clear Objects"), wxPoint(22, 236), wxSize(252, 25), 0, wxDefaultValidator, _("ClearObjects"));
	ClearObjects->SetHelpText(_("Clear all objects"));

	wxArrayString arrayStringFor_ObjectListbox;
	ObjectListbox = new wxCheckListBox(this, ID_OBJECTLISTBOX, wxPoint(16, 55), wxSize(268, 150), arrayStringFor_ObjectListbox, wxLB_EXTENDED, wxDefaultValidator, _("ObjectListbox"));

	RemoveObject = new wxButton(this, ID_REMOVEOBJECT, _("Remove Object(s)"), wxPoint(156, 208), wxSize(120, 25), 0, wxDefaultValidator, _("RemoveObject"));
	RemoveObject->SetHelpText(_("Remove selected object(s)"));

	AddObject = new wxButton(this, ID_ADDOBJECT, _("Add Object"), wxPoint(22, 208), wxSize(120, 25), 0, wxDefaultValidator, _("AddObject"));

	gravitationListBoxCount = 0;
	objectCounter = 1;
	globalGravitationPanelPointer = this;
}

GravitationPanel::~GravitationPanel()
{
}

void GravitationPanel::OnClose(wxCloseEvent& event)
{
	Destroy();
}

void GravitationPanel::Reset()
{
	TimedSimulationPanel::Reset();

	wxCommandEvent evt = wxCommandEvent();
	ClearObjectsClick(evt);
}

void GravitationPanel::AddObjectToListBox(wxString str, bool enabled)
{
	ObjectListbox->Append(str);
	ObjectListbox->Check(gravitationListBoxCount++, enabled);
}

/*
 * AddObjectClick
 */
void GravitationPanel::AddObjectClick(wxCommandEvent& event)
{
	static GravitationAddDialog* diag = NULL;

	if(!diag)
	{
		diag = new GravitationAddDialog(this, GetObjectNames);
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

		bool isRelative = diag->refObjType == ReferenceObjectType_Relative;

		if (diag->isSingleObject)
		{
			wxString name = tempName + wxString::Format(wxT("%i"), objectCounter++);
			ObjectListbox->Append(name);
			ObjectListbox->Check(gravitationListBoxCount, diag->objEnabled);

			AddObjectSingle(name, diag->objEnabled, (float)diag->singleMass, (float)diag->singleRadius, (float)diag->singlePositionX, (float)diag->singlePositionY, (float)diag->singlePositionZ,
				(float)diag->singleVelocityX, (float)diag->singleVelocityY, (float)diag->singleVelocityZ, isRelative, isRelative ? diag->selectedReferenceObjectIndex : -1);

			gravitationListBoxCount++;
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
							ObjectListbox->Check(gravitationListBoxCount, diag->objEnabled);
							gravitationListBoxCount++;

							if (onceZInterval)
								break;
						}

						if (onceYInterval)
							break;
					}

					if (onceXInterval)
						break;
				}

				AddObjectMultiple(tempName, diag->objEnabled, diag->multipleMass.ToStdString(), diag->multipleRadius.ToStdString(), 
					diag->multiplePositionX.ToStdString(), (float)diag->multiplePositionXAxisRangeBegin, (float)diag->multiplePositionXAxisRangeEnd, (float)diag->multiplePositionXAxisRangeResolution,
					diag->multiplePositionY.ToStdString(), (float)diag->multiplePositionYAxisRangeBegin, (float)diag->multiplePositionYAxisRangeEnd, (float)diag->multiplePositionYAxisRangeResolution,
					diag->multiplePositionZ.ToStdString(), (float)diag->multiplePositionZAxisRangeBegin, (float)diag->multiplePositionZAxisRangeEnd, (float)diag->multiplePositionZAxisRangeResolution,
					diag->multipleVelocityX.ToStdString(), diag->multipleVelocityY.ToStdString(), diag->multipleVelocityZ.ToStdString(), isRelative, isRelative ? diag->selectedReferenceObjectIndex : -1);
			}
		}
	}
}

/*
 * RemoveObjectClick
 */
void GravitationPanel::RemoveObjectClick(wxCommandEvent& event)
{
	wxArrayInt intArray;
	ObjectListbox->GetSelections(intArray);

	for (int i = intArray.size() - 1; i >= 0; i--)
	{
		
		ObjectListbox->Delete(intArray[i]);
		RemoveObjectFunction(intArray[i]);
		gravitationListBoxCount--;
	}
}

/*
 * ClearObjectsClick
 */
void GravitationPanel::ClearObjectsClick(wxCommandEvent& event)
{
	ObjectListbox->Clear();
	ClearObjectsFunction();
	gravitationListBoxCount = 0;
	objectCounter = 1;
}

void GravitationPanel::ObjectListboxSelected(wxCommandEvent& event)
{
	wxArrayInt intArray;
	ObjectListbox->GetSelections(intArray);
	ChangeSelection(intArray);
}

/*
 * ObjectListboxCheckListBox
 */
void GravitationPanel::ObjectListboxCheckListBox(wxCommandEvent& event)
{
	int index = event.GetInt();
	ChangeEnabledState(index);
}
