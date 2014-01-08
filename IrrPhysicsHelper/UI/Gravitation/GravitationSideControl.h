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
///            GravitationPanel class declaration
///
///------------------------------------------------------------------

#ifndef WX_IRR_GRAVITATION_PANEL
#define WX_IRR_GRAVITATION_PANEL

#include <wx/wx.h>
#include "../SimulationSideControl.h"
#include "GravitationAddDialog.h"



class GravitationPanel : public TimedSimulationPanel
{
	private:
		void OnClose(wxCloseEvent& event);

		DECLARE_EVENT_TABLE();
		
	public:
		GravitationPanel(wxWindow *parent, void (*addObjectSingle)(wxString _name, bool enabled, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ, bool isRelative, int relativeIndex),
			void (*AddObjectMultiple)(wxString _name, bool enabled, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			std::string velX, std::string velY, std::string velZ, bool isRelative, int relativeIndex ),
			void (*RemoveObjectFunction)(int index), void (*ClearObjectsFunction)(void),
			void (*ChangeSelection)(wxArrayInt intArray), void (*ChangeEnabledState)(int index),
			wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 305,357 ));
		virtual ~GravitationPanel();
		void AddObjectClick(wxCommandEvent& event);
		void RemoveObjectClick(wxCommandEvent& event);
		void ClearObjectsClick(wxCommandEvent& event);
		void ObjectListboxCheckListBox(wxCommandEvent& event);
		void ObjectListboxSelected(wxCommandEvent& event);

		void (*AddObjectSingle)(wxString _name, bool enabled, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ, bool isRelative, int relativeIndex);
		void (*AddObjectMultiple)(wxString _name, bool enabled, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			std::string velX, std::string velY, std::string velZ, bool isRelative, int relativeIndex );
		void (*RemoveObjectFunction)(int index);
		void (*ClearObjectsFunction)(void);
		void (*ChangeSelection)(wxArrayInt intArray);
		void (*ChangeEnabledState)(int index);

		void Reset();

		void AddObjectToListBox(wxString str, bool enabled);

		wxCheckListBox *ObjectListbox;
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *ClearObjects;
		wxButton *RemoveObject;
		wxButton *AddObject;
		////GUI Control Declaration End

		int gravitationListBoxCount;
		int objectCounter;

		enum
		{
			////GUI Enum Control ID Start
			ID_CLEAROBJECTS = 1141,
			ID_OBJECTLISTBOX = 1140,
			ID_REMOVEOBJECT = 1126,
			ID_ADDOBJECT = 1125
		};

};

#endif
