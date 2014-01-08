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

#include "SimulationSideControl.h"

SimulationPanel::SimulationPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
	: wxPanel( parent, id, pos, size )
{
}

SimulationPanel::~SimulationPanel()
{
}

void SimulationPanel::ChangeSimulationTime(float time)
{
}

void SimulationPanel::Reset()
{
}


TimedSimulationPanel::TimedSimulationPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
	: SimulationPanel( parent, id, pos, size )
{
	WxStaticLine1 = new wxStaticLine(this, ID_WXSTATICLINE1, wxPoint(5, 41), wxSize(292, -1), wxLI_HORIZONTAL);
	WxStaticLine1->SetForegroundColour(wxColour(_("BLACK")));
	WxStaticLine1->SetBackgroundColour(wxColour(000,000,000));

	SimulationTimeValue = new wxStaticText(this, ID_SIMULATIONTIMEVALUE, _(" "), wxPoint(60, 18), wxDefaultSize, 0, _("SimulationTimeValue"));

	SimulationTimeLabel = new wxStaticText(this, ID_, _("Time:"), wxPoint(11, 18), wxDefaultSize, 0, _("SimulationTimeLabel"));
	SimulationTimeLabel->SetHelpText(_("Total simulation time"));

	Reset();
}

TimedSimulationPanel::~TimedSimulationPanel()
{
}

void TimedSimulationPanel::ChangeSimulationTime(float time)
{
	SimulationTimeValue->SetLabel(wxString::Format("%f", time));
}

void TimedSimulationPanel::Reset()
{
	ChangeSimulationTime(0.0f);
}