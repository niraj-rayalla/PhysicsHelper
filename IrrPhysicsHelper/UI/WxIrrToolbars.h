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

#ifndef _PHYSICSHELPER_TOOL_BARS
#define _PHYSICSHELPER_TOOL_BARS

#include <wx/wx.h>
#include "wx/aui/aui.h"
#include "wx/artprov.h"

const int TOOLBAR_IDSTART = 500;

enum
{
	TOOLBARID_New = TOOLBAR_IDSTART,
	TOOLBARID_SaveSimulation,
	TOOLBARID_LoadSimulation,
	TOOLBARID_RunSimulation,
	TOOLBARID_PauseSimulation,
	TOOLBARID_SplitViewportHoriz,
	TOOLBARID_SplitViewportVert,
	TOOLBARID_RemoveViewport,
	TOOLBARID_SimulationChangeTimeScale,
	TOOLBARID_SimulationChangePositionScale,
	TOOLBARID_SimulationSkipBack,
	TOOLBARID_SimulationSkipNext,
	TOOLBARID_SimulationChangeSkipAmount,
	TOOLBARID_SimulationBackward,
	TOOLBARID_SimulationForward,
	TOOLBARID_SimulationStartRecord,
	TOOLBARID_SimulationStopRecord
};

class PhysicsHelperToolbars
{
public:
	wxAuiToolBar* basicToolbar;
	wxAuiToolBar* simulationToolbar;
	wxAuiToolBar* recordingToolbar;

	PhysicsHelperToolbars(wxWindow* wnd, wxAuiManager& wxAuiMgr);

	void ShowRecordingToolbar();

	void HideRecordingToolbar();
};

#endif
