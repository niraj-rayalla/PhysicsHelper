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
/// @file      PlaygroundPanel.cpp
/// @author    Niraj
/// Created:   8/2/2012 10:01:16 AM
/// @section   DESCRIPTION
///            PlaygroundPanel class implementation
///
///------------------------------------------------------------------

#include "PlaygroundSideControl.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// PlaygroundPanel
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(PlaygroundPanel,wxPanel)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(PlaygroundPanel::OnClose)
	EVT_BUTTON(ID_CLEAROBJECTSBUTTON,PlaygroundPanel::ClearObjectsButtonClick)
	EVT_BUTTON(ID_REMOVEOBJECTBUTTON,PlaygroundPanel::RemoveObjectsButtonClick)
	EVT_LISTBOX(ID_OBJECTLISTBOX,PlaygroundPanel::ObjectListBoxSelected)
	EVT_LISTBOX_DCLICK(ID_OBJECTLISTBOX,PlaygroundPanel::ObjectListBoxDoubleClicked)
	
	EVT_LIST_ITEM_SELECTED(ID_ADDOBJECTTYPELISTCONTROL,PlaygroundPanel::AddObjectTypeListControlSelected)
	EVT_LIST_ITEM_ACTIVATED(ID_ADDOBJECTTYPELISTCONTROL,PlaygroundPanel::AddObjectTypeListControlItemActivated)
END_EVENT_TABLE()
////Event Table End

enum
{
	ObjectAddType_Sphere,
	ObjectAddType_Cube,
	ObjectAddType_Cylinder,
	ObjectAddType_Cone,
	ObjectAddType_Capsule,
	ObjectAddType_Multiple,
	ObjectAddType_Spring,
	ObjectAddType_PointToPointJoint,
	ObjectAddType_HingeJoint,
	ObjectAddType_GeneralJoint
};

PlaygroundPanel::PlaygroundPanel(wxWindow *parent, 
			void (*addSphereUsingMouse)(void), void (*addCubeUsingMouse)(void), void (*addCylinderUsingMouse)(void), void (*addConeUsingMouse)(void),
			void (*addCapsuleUsingMouse)(void), void (*addSpringUsingMouse)(void), void (*addFromFileUsingMouse)(wxString filename),
			void (*addPointToPointJointUsingMouse)(void), void (*addHingeJointUsingMouse)(void), void (*addGeneralJointUsingMouse)(void),
			void (*addSphere)(wxString name, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ),
			void (*addCube)(wxString name, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ),
			void (*addFromFile)(wxString name, wxString filename, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ),
			void (*addMultipleObjectsCylindrical)(bool singleSurface, wxString zEquation, double thetaRes, double rRes, double minTheta, double maxTheta, double minR, double maxR,
				wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*addMultipleObjectsParametric)(bool singleSurface, wxString xEquation, wxString yEquation, wxString zEquation, double uRes, double vRes, double minU, double maxU, 
				double minV, double maxV, wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*addMultipleObjectsRectangular)(bool singleSurface, int axisIndex, wxString equation, double firstRes, double secondRes, double minFirst, double maxFirst,
				double minSecond, double maxSecond,	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*addMultipleObjectsSpherical)(bool singleSurface, wxString rEquation, double thetaRes, double phiRes, double minTheta, double maxTheta, double minPhi, double maxPhi,
				wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*removeObjectFunction)(int index), void (*clearObjectsFunction)(void), void (*changeSelection)(wxArrayInt intArray), void (*objectListDoubleClick)(int index),
			wxWindowID id, const wxPoint& pos, const wxSize& size)
	: TimedSimulationPanel( parent, id, pos, size )
{
	ClearObjectsButton = new wxButton(this, ID_CLEAROBJECTSBUTTON, _("Clear Objects"), wxPoint(168, 299), wxSize(112, 25), 0, wxDefaultValidator, _("ClearObjectsButton"));

	RemoveObjectsButton = new wxButton(this, ID_REMOVEOBJECTBUTTON, _("Remove Objects"), wxPoint(24, 299), wxSize(112, 25), 0, wxDefaultValidator, _("RemoveObjectsButton"));

	wxArrayString arrayStringFor_ObjectListBox;
	ObjectListBox = new wxListBox(this, ID_OBJECTLISTBOX, wxPoint(16, 160), wxSize(272, 134), arrayStringFor_ObjectListBox, wxLB_SINGLE);

	objectAddTypeImageList = new wxImageList(32, 32, true);
	objectAddTypeImageList->Add(wxIcon(playgroundsphereadd));
	objectAddTypeImageList->Add(wxIcon(playgroundcubeadd));
	objectAddTypeImageList->Add(wxIcon(playgroundcylinderadd));
	objectAddTypeImageList->Add(wxIcon(playgroundconeadd));
	objectAddTypeImageList->Add(wxIcon(playgroundcapsuleadd));
	objectAddTypeImageList->Add(wxIcon(playgroundmultipleadd));
	objectAddTypeImageList->Add(wxIcon(playgroundspringadd));
	objectAddTypeImageList->Add(wxIcon(playgroundpointtopointjointadd));
	objectAddTypeImageList->Add(wxIcon(playgroundhingeadd));	

	AddObjectTypeListControl = new wxListView(this, ID_ADDOBJECTTYPELISTCONTROL, wxPoint(16, 55), wxSize(272, 90), wxLC_ICON | wxLC_NO_HEADER | wxLC_SINGLE_SEL, wxDefaultValidator, _("AddObjectTypeListControl"));
	AddObjectTypeListControl->SetImageList(objectAddTypeImageList, wxIMAGE_LIST_NORMAL);
	AddObjectTypeListControl->InsertItem(0, 0);
	AddObjectTypeListControl->InsertItem(1, 1);
	AddObjectTypeListControl->InsertItem(2, 2);
	AddObjectTypeListControl->InsertItem(3, 3);
	AddObjectTypeListControl->InsertItem(4, 4);
	AddObjectTypeListControl->InsertItem(5, 5);
	AddObjectTypeListControl->InsertItem(6, 6);
	AddObjectTypeListControl->InsertItem(7, 7);
	AddObjectTypeListControl->InsertItem(8, 8);

	AddSphereUsingMouse = addSphereUsingMouse;
	AddCubeUsingMouse = addCubeUsingMouse;
	AddCylinderUsingMouse = addCylinderUsingMouse;
	AddConeUsingMouse = addConeUsingMouse;
	AddCapsuleUsingMouse = addCapsuleUsingMouse;
	AddFromFileUsingMouse = addFromFileUsingMouse;
	AddSpringUsingMouse = addSpringUsingMouse;
	AddPointToPointJointUsingMouse = addPointToPointJointUsingMouse;
	AddHingeJointUsingMouse = addHingeJointUsingMouse;
	AddGeneralJointUsingMouse = addGeneralJointUsingMouse;
	AddSphere = addSphere;
	AddCube = addCube;
	AddFromFile = addFromFile;

	AddMultipleObjectsCylindrical = addMultipleObjectsCylindrical;
	AddMultipleObjectsParametric = addMultipleObjectsParametric;
	AddMultipleObjectsRectangular = addMultipleObjectsRectangular;
	AddMultipleObjectsSpherical = addMultipleObjectsSpherical;

	RemoveObjectFunction = removeObjectFunction;
	ClearObjectsFunction = clearObjectsFunction;
	ChangeSelection = changeSelection;
	ObjectListDoubleClick = objectListDoubleClick;

	selectedIndex = 0;
	selected = false;
}

PlaygroundPanel::~PlaygroundPanel()
{
	delete objectAddTypeImageList;
}

void PlaygroundPanel::OnClose(wxCloseEvent& event)
{
	Destroy();
}

void PlaygroundPanel::Reset()
{
	
}

void PlaygroundPanel::RemoveObjectsButtonClick(wxCommandEvent& event)
{
	int index = ObjectListBox->GetSelection();
	ObjectListBox->Delete(index);
	RemoveObjectFunction(index);
}

/*
 * ClearObjectsButtonClick
 */
void PlaygroundPanel::ClearObjectsButtonClick(wxCommandEvent& event)
{
	ObjectListBox->Clear();
	ClearObjectsFunction();
}

/*
 * AddObjectTypeListControlSelected
 */
void PlaygroundPanel::AddObjectTypeListControlSelected(wxListEvent& event)
{
		selectedIndex = event.GetIndex();

		switch(event.GetIndex())
		{
		case ObjectAddType_Sphere:
			AddSphereUsingMouse();
			break;
		case ObjectAddType_Cube:
			AddCubeUsingMouse();
			break;
		case ObjectAddType_Cylinder:
			AddCylinderUsingMouse();
			break;
		case ObjectAddType_Cone:
			AddConeUsingMouse();
			break;
		case ObjectAddType_Capsule:
			AddCapsuleUsingMouse();
			break;
		case ObjectAddType_Multiple:
			{
				static PlaygroundAddMultipleObjectsDialog* diag = NULL;

				if(!diag)
				{
					diag = new PlaygroundAddMultipleObjectsDialog(this);
				}

				int retValue = diag->ShowModal();
				if (retValue)
				{
					switch(retValue)
					{
					case 1:
						AddMultipleObjectsCylindrical(diag->singleSurface, diag->zEquation, diag->firstRes, diag->secondRes, diag->minFirst, diag->maxFirst,
							diag->minSecond, diag->maxSecond, diag->massEquation, diag->xRotEquation, diag->yRotEquation, diag->zRotEquation);

						break;
					case 2:
						AddMultipleObjectsParametric(diag->singleSurface, diag->xEquation, diag->yEquation, diag->zEquation, diag->firstRes, diag->secondRes,
							diag->minFirst, diag->maxFirst,	diag->minSecond, diag->maxSecond, diag->massEquation, diag->xRotEquation, diag->yRotEquation, diag->zRotEquation);
						break;
					case 3:
						AddMultipleObjectsRectangular(diag->singleSurface, diag->axisIndex, diag->equation, diag->firstRes, diag->secondRes, diag->minFirst, diag->maxFirst,
							diag->minSecond, diag->maxSecond, diag->massEquation, diag->xRotEquation, diag->yRotEquation, diag->zRotEquation);
						break;
					case 4:
						AddMultipleObjectsSpherical(diag->singleSurface, diag->rEquation, diag->firstRes, diag->secondRes, diag->minFirst, diag->maxFirst,
							diag->minSecond, diag->maxSecond, diag->massEquation, diag->xRotEquation, diag->yRotEquation, diag->zRotEquation);					
						break;
					}
				}
				break;
			}
		case ObjectAddType_Spring:
			AddSpringUsingMouse();
			break;
		case ObjectAddType_PointToPointJoint:
			AddPointToPointJointUsingMouse();
			break;
		case ObjectAddType_HingeJoint:
			AddHingeJointUsingMouse();
			break;
		case ObjectAddType_GeneralJoint:
			AddGeneralJointUsingMouse();
			break;
		}
		
		selected = !selected;
		
}

void PlaygroundPanel::DeselectSelectedItem()
{
	AddObjectTypeListControl->Select(selectedIndex, false);
}

void PlaygroundPanel::AddObjectToListBox(wxString str)
{
	ObjectListBox->Append(str);
}


/*
 * AddObjectTypeListControlItemActivated
 */
void PlaygroundPanel::AddObjectTypeListControlItemActivated(wxListEvent& event)
{
	// insert your code here
}

/*
 * ObjectListBoxSelected
 */
void PlaygroundPanel::ObjectListBoxSelected(wxCommandEvent& event)
{
	wxArrayInt indices;
	indices.Add(ObjectListBox->GetSelection());
	ChangeSelection(indices);
}

/*
 * ObjectListBoxDoubleClicked
 */
void PlaygroundPanel::ObjectListBoxDoubleClicked(wxCommandEvent& event)
{
	ObjectListDoubleClick(ObjectListBox->GetSelection());
}