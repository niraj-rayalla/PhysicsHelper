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

#ifndef _WX_IRR_SIMULATION_SIDE_CONTROL
#define _WX_IRR_SIMULATION_SIDE_CONTROL

#include <wx/wx.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>

enum
{
	ID_WXSTATICLINE1 = 1005,
	ID_SIMULATIONTIMEVALUE = 1004,
	ID_ = 1002,
	////GUI Enum Control ID End
	ID_DUMMY_VALUE_
};

class SimulationPanel : public wxPanel
{		
	public:
		
		SimulationPanel(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size); 
		~SimulationPanel();

		virtual void ChangeSimulationTime(float time);
		virtual void Reset();	
};

class TimedSimulationPanel : public SimulationPanel
{
	protected:
		wxStaticLine *WxStaticLine1;
		wxStaticText *SimulationTimeValue;
		wxStaticText *SimulationTimeLabel;
	
	public:
		
		TimedSimulationPanel(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size); 
		~TimedSimulationPanel();

		virtual void ChangeSimulationTime(float time);
		virtual void Reset();
};

#endif