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

#ifndef _WX_IRR_PENDULUM_PANEL
#define _WX_IRR_PENDULUM_PANEL

#include <wx/wx.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include "../SimulationSideControl.h"
#include "PendulumAddDialog.h"
#include "PendulumChangeAccelerationDialog.h"

enum
{
	////GUI Enum Control ID Start
	ID_CHANGEACCELERTAIONEQUATIONBUTTON = 1022,
	ID_CURRENTACCELERATION = 1021,
	ID_CURRENTACCELERATIONLABEL = 1020,
	ID_ACCELERATIONZEQUATION = 1019,
	ID_ACCELERATIONYEQUATION = 1018,
	ID_ACCELERATIONXEQUATION = 1017,
	ID_ACCELERATIONZEQUATIONLABEL = 1013,
	ID_ACCELERATIONYEQUATIONLABEL = 1012,
	ID_ACCELERATIONXEQUATIONLABEL = 1011,
	ID_ACCELERATIONEQUATIONLABEL = 1010,
	ID_REMOVEPENDULUM = 1009,
	ID_ADDPENDULUM = 1008,
	ID_PENDULUMLISTBOX = 1007
};

class PendulumPanel : public TimedSimulationPanel
{
	private:
		wxButton *ChangeAccelertaionEquationButton;
		wxStaticText *CurrentAcceleration;
		wxStaticText *CurrentAccelerationLabel;
		wxStaticText *AccelerationZEquation;
		wxStaticText *AccelerationYEquation;
		wxStaticText *AccelerationXEquation;
		wxStaticText *AccelerationZEquationLabel;
		wxStaticText *AccelerationYEquationLabel;
		wxStaticText *AccelerationXEquationLabel;
		wxStaticText *AccelerationEquationLabel;
		wxButton *RemovePendulum;
		wxButton *AddPendulum;
		wxListBox *PendulumListBox;

		int pendulumListBoxCount;

		void OnClose(wxCloseEvent& event);

		DECLARE_EVENT_TABLE();
	protected:
	
	public:
		
		PendulumPanel( wxWindow* parent, void (*addPendulumFunctionPointer)(wxString _name, double theta, double phi, double length, float mass),
			void (*addPendulumComponentsFunctionPointer)(wxString _name, double X, double Y, double Z, float mass),
			void (*removePendulumFunctionPointer)(int index),
			void (*changeSelectionFunctionPointer)(wxArrayInt indices),
			void (*changeAccelerationEquations)(std::string XString, std::string YString, std::string ZString),
			wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 305,357 ) ); 
		~PendulumPanel();
		void AddPendulumClick(wxCommandEvent& event);
		void RemovePendulumClick(wxCommandEvent& event);
		void PendulumListBoxSelected(wxCommandEvent& event);
		void ChangeAccelertaionEquationButtonClick(wxCommandEvent& event);
		void AddToListBox(wxString str);
		void ChangeCurrentAcceleration(float X, float Y, float Z);

		void (*AddPendulumFunctionPointer)(wxString _name, double theta, double phi, double length, float mass);
		void (*AddPendulumComponentsFunctionPointer)(wxString _name, double X, double Y, double Z, float mass);
		void (*RemovePendulumFunctionPointer)(int index);
		void (*ChangeSelectionFunctionPointer)(wxArrayInt indices);
		void (*ChangeAccelerationEquations)(std::string XString, std::string YString, std::string ZString);

		void Reset();
};

#endif
