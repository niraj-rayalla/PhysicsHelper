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
/// @file      PlaygroundPanel.h
/// @author    Niraj
/// Created:   8/2/2012 10:01:16 AM
/// @section   DESCRIPTION
///            PlaygroundPanel class declaration
///
///------------------------------------------------------------------

#ifndef WX_IRR_PLAYGROUND_PANEL
#define WX_IRR_PLAYGROUND_PANEL

#include <wx/wx.h>
#include "../SimulationSideControl.h"

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/listctrl.h>
#include <wx/stattext.h>
////Header Include End

#include "PlaygroundAddMultipleObjectsDialog.h"

//Icons include
#include "../../Icons/playgroundsphereadd.xpm"
#include "../../Icons/playgroundcubeadd.xpm"
#include "../../Icons/playgroundcylinderadd.xpm"
#include "../../Icons/playgroundspringadd.xpm"
#include "../../Icons/playgroundpointtopointjointadd.xpm"
#include "../../Icons/playgroundconeadd.xpm"
#include "../../Icons/playgroundcapsuleadd.xpm"
#include "../../Icons/playgroundmultipleadd.xpm"
#include "../../Icons/playgroundhingeadd.xpm"


class PlaygroundPanel : public TimedSimulationPanel
{
	private:
		DECLARE_EVENT_TABLE();

		wxImageList* objectAddTypeImageList;
		
	public:
		PlaygroundPanel(wxWindow *parent, 
			void (*AddSphereUsingMouse)(void), void (*AddCubeUsingMouse)(void), void (*addCylinderUsingMouse)(void), void (*AddConeUsingMouse)(void),
			void (*AddCapsuleUsingMouse)(void), void (*addSpringUsingMouse)(void), void (*AddFromFileUsingMouse)(wxString filename),
			void (*AddPointToPointJointUsingMouse)(void), void (*AddHingeJointUsingMouse)(void), void (*AddGeneralJointUsingMouse)(void),
			void (*AddSphere)(wxString name, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ),
			void (*AddCube)(wxString name, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ),
			void (*AddFromFile)(wxString name, wxString filename, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ),
			void (*AddMultipleObjectsCylindrical)(bool singleSurface, wxString zEquation, double thetaRes, double rRes, double minTheta, double maxTheta, double minR, double maxR,
				wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*AddMultipleObjectsParametric)(bool singleSurface, wxString xEquation, wxString yEquation, wxString zEquation, double uRes, double vRes, double minU, double maxU, 
				double minV, double maxV, wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*AddMultipleObjectsRectangular)(bool singleSurface, int axisIndex, wxString equation, double firstRes, double secondRes, double minFirst, double maxFirst,
				double minSecond, double maxSecond,	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*AddMultipleObjectsSpherical)(bool singleSurface, wxString rEquation, double thetaRes, double phiRes, double minTheta, double maxTheta, double minPhi, double maxPhi,
				wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*RemoveObjectFunction)(int index), void (*ClearObjectsFunction)(void), void (*ChangeSelection)(wxArrayInt intArray), void (*ObjectListDoubleClick)(int index),
			wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 305,357 ));
		virtual ~PlaygroundPanel();

		void Reset();

		void RemoveObjectsButtonClick(wxCommandEvent& event);
		void ClearObjectsButtonClick(wxCommandEvent& event);
		void ObjectListBoxSelected(wxCommandEvent& event);
		void ObjectListBoxDoubleClicked(wxCommandEvent& event);
		void AddObjectTypeListControlSelected(wxListEvent& event);
		void AddObjectTypeListControlItemActivated(wxListEvent& event);

		void AddObjectToListBox(wxString str);

		void (*RemoveObjectFunction)(int index);
		void (*ClearObjectsFunction)(void);
		void (*ChangeSelection)(wxArrayInt intArray);
		void (*ObjectListDoubleClick)(int index);

		void (*AddSphereUsingMouse)(void);
		void (*AddCubeUsingMouse)(void);
		void (*AddCylinderUsingMouse)(void);
		void (*AddConeUsingMouse)(void);
		void (*AddCapsuleUsingMouse)(void);
		void (*AddFromFileUsingMouse)(wxString filename);
		void (*AddSpringUsingMouse)(void);
		void (*AddPointToPointJointUsingMouse)(void);
		void (*AddHingeJointUsingMouse)(void);
		void (*AddGeneralJointUsingMouse)(void);

		void (*AddSphere)(wxString name, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ);
		void (*AddCube)(wxString name, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ);
		void (*AddFromFile)(wxString name, wxString filename, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ);

		void (*AddMultipleObjectsCylindrical)(bool singleSurface, wxString zEquation, double thetaRes, double rRes, double minTheta, double maxTheta, double minR, double maxR,
			wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation);
		void (*AddMultipleObjectsParametric)(bool singleSurface, wxString xEquation, wxString yEquation, wxString zEquation, double uRes, double vRes, double minU, double maxU, 
			double minV, double maxV, wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation);
		void (*AddMultipleObjectsRectangular)(bool singleSurface, int axisIndex, wxString equation, double firstRes, double secondRes, double minFirst, double maxFirst,
			double minSecond, double maxSecond,	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation);
		void (*AddMultipleObjectsSpherical)(bool singleSurface, wxString rEquation, double thetaRes, double phiRes, double minTheta, double maxTheta, double minPhi, double maxPhi,
			wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation);

		void DeselectSelectedItem();

		void AddObjectToListBox(wxString str, bool enabled);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *ClearObjectsButton;
		wxButton *RemoveObjectsButton;
		wxListBox *ObjectListBox;
		wxListView *AddObjectTypeListControl;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_CLEAROBJECTSBUTTON = 1009,
			ID_REMOVEOBJECTBUTTON = 1008,
			ID_OBJECTLISTBOX = 1007,
			ID_ADDOBJECTTYPELISTCONTROL = 1006,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		int selectedIndex;
		bool selected;
};

#endif
