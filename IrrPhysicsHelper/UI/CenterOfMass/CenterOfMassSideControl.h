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
/// @file      GravirationPanel.h
/// @author    niraj
/// Created:   7/4/2012 11:24:17 AM
/// @section   DESCRIPTION
///            CoulombPanel class declaration
///
///------------------------------------------------------------------

#ifndef WX_IRR_CENTER_OF_MASS_PANEL
#define WX_IRR_CENTER_OF_MASS_PANEL

#include <wx/wx.h>
#include "../SimulationSideControl.h"
#include "CenterOfMassAddDialog.h"

class CenterOfMassPanel : public SimulationPanel
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		CenterOfMassPanel(wxWindow *parent, wxString* (*AddObjectSingle)(wxString _name, float mass, float radius, float posX, float posY, float posZ, bool isRelative, int relativeIndex),
			wxString* (*AddObjectMultiple)(wxString _name, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			bool isRelative, int relativeIndex ),
			wxString* (*RemoveObjectFunction)(int index), wxString* (*ClearObjectsFunction)(void),
			void (*ChangeSelection)(wxArrayInt intArray), wxString* (*ChangeEnabledState)(int index),
			wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
		virtual ~CenterOfMassPanel();
		void AddObjectClick(wxCommandEvent& event);
		void RemoveObjectClick(wxCommandEvent& event);
		void ClearObjectsClick(wxCommandEvent& event);
		void ObjectListboxCheckListBox(wxCommandEvent& event);
		void ObjectListboxSelected(wxCommandEvent& event);

		//Funtions that the simulation will do and for most cause changes to the center of mass values and so returns the strings
		//that shows the new center of mass, total mass and number of objects.
		wxString* (*AddObjectSingle)(wxString _name, float mass, float radius, float posX, float posY, float posZ, bool isRelative, int relativeIndex);
		wxString* (*AddObjectMultiple)(wxString _name, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			bool isRelative, int relativeIndex );
		wxString* (*RemoveObjectFunction)(int index);
		wxString* (*ClearObjectsFunction)(void);
		void (*ChangeSelection)(wxArrayInt intArray);
		wxString* (*ChangeEnabledState)(int index);

		void Reset();

		void AddObjectToListBox(wxString str, bool enabled);
		void ChangeCOMLabels(float COMX, float COMY, float COMZ,	float totalMass, int numObjects);

		void ChangeCenterOfMassStrings(wxString* strings);

		wxCheckListBox *ObjectListbox;
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxStaticText *NumberOfObjectsValue;
		wxStaticText *NumberOfObjectsLabel;
		wxStaticText *TotalMassValue;
		wxStaticText *TotalMassLabel;
		wxStaticText *CenterOfMassValue;
		wxStaticText *CenterOfMassLabel;
		wxButton *ClearObjects;
		wxButton *RemoveObject;
		wxButton *AddObject;
		////GUI Control Declaration End

		int centerOfMassListBoxCount;
		int objectCounter;
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_NUMBEROFOBJECTSVALUE = 1017,
			ID_NUMBEROFOBJECTSLABEL = 1016,
			ID_TOTALMASSVALUE = 1014,
			ID_TOTALMASSLABEL = 1013,
			ID_CENTEROFMASSVALUE = 1012,
			ID_CENTEROFMASSLABEL = 1011,
			ID_CLEAROBJECTS = 1010,
			ID_REMOVEOBJECT = 1009,
			ID_ADDOBJECT = 1008,
			ID_OBJECTLISTBOX = 1007,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
};

#endif
