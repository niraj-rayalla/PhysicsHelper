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

#include "WxIrrToolbars.h"

PhysicsHelperToolbars::PhysicsHelperToolbars(wxWindow* wnd, wxAuiManager& wxAuiMgr)
{
	basicToolbar = new wxAuiToolBar(wnd, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
	basicToolbar->SetToolBitmapSize(wxSize(16,16));
	basicToolbar->AddTool(TOOLBARID_New, wxT("New"), wxArtProvider::GetBitmap(wxART_NEW, wxART_OTHER, wxSize(16,16)), wxT("Reset Simulation"));
	basicToolbar->AddTool(TOOLBARID_SaveSimulation, wxT("Save"), wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_OTHER, wxSize(16,16)), wxT("Save Simulation"));
	basicToolbar->AddTool(TOOLBARID_LoadSimulation, wxT("Load"), wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_OTHER, wxSize(16,16)), wxT("Load Simulation"));
	basicToolbar->AddSeparator();
	basicToolbar->AddTool(TOOLBARID_SplitViewportHoriz, wxT("Split View Horizontally"), wxBitmap(wxImage(wxT("./Icons/Window_Split_Horizontally.bmp"))), wxT("Split View Horizontally"));
	basicToolbar->AddTool(TOOLBARID_SplitViewportVert, wxT("Split View Vertically"), wxBitmap(wxImage(wxT("./Icons/Window_Split_Vertically.bmp"))), wxT("Split View Vertically"));
	basicToolbar->AddTool(TOOLBARID_RemoveViewport, wxT("Remove View"), wxBitmap(wxImage(wxT("./Icons/Window_Remove.bmp"))), wxT("Remove View"));
	basicToolbar->Realize();

	simulationToolbar = new wxAuiToolBar(wnd, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
	simulationToolbar->SetToolBitmapSize(wxSize(16,16));
	simulationToolbar->AddTool(TOOLBARID_RunSimulation, wxT("Run"), wxBitmap(wxImage(wxT("./Icons/Simulation_Run.png"))), wxT("Run"), wxITEM_RADIO);
	simulationToolbar->AddTool(TOOLBARID_PauseSimulation, wxT("Pause"), wxBitmap(wxImage(wxT("./Icons/Simulation_Pause.bmp"))), wxT("Pause"), wxITEM_RADIO);
	simulationToolbar->AddSeparator();
	simulationToolbar->AddTool(TOOLBARID_SimulationChangeTimeScale, wxT("Change Time Scale"), wxArtProvider::GetBitmap(wxART_WARNING, wxART_OTHER, wxSize(16,16)), wxT("Change Time Scale"));
	simulationToolbar->AddTool(TOOLBARID_SimulationChangePositionScale, wxT("Change Position Scale"), wxArtProvider::GetBitmap(wxART_WARNING, wxART_OTHER, wxSize(16,16)), wxT("Change Position Scale"));
	simulationToolbar->AddSeparator();
	simulationToolbar->AddTool(TOOLBARID_SimulationSkipBack, wxT("Skip Back"), wxArtProvider::GetBitmap(wxART_WARNING, wxART_OTHER, wxSize(16,16)), wxT("Skip Back"));
	simulationToolbar->AddTool(TOOLBARID_SimulationSkipNext, wxT("Skip Next"), wxBitmap(wxImage(wxT("./Icons/Simulation_Skip.bmp"))), wxT("Skip Next"));
	simulationToolbar->AddTool(TOOLBARID_SimulationChangeSkipAmount, wxT("Change Skip Amount"), wxArtProvider::GetBitmap(wxART_WARNING, wxART_OTHER, wxSize(16,16)), wxT("Change Skip Amount"));
	/*simulationToolbar->AddSeparator();
	simulationToolbar->AddTool(TOOLBARID_SimulationBackward, wxT("Backwards"), wxArtProvider::GetBitmap(wxART_WARNING, wxART_OTHER, wxSize(16,16)), wxT("Backwards"), wxITEM_RADIO);
	simulationToolbar->AddTool(TOOLBARID_SimulationForward, wxT("Forwards"), wxArtProvider::GetBitmap(wxART_WARNING, wxART_OTHER, wxSize(16,16)), wxT("Forwards"), wxITEM_RADIO);*/
	simulationToolbar->Realize();
		
	recordingToolbar = new wxAuiToolBar(wnd, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
	recordingToolbar->SetToolBitmapSize(wxSize(16,16));
	recordingToolbar->AddTool(TOOLBARID_SimulationStartRecord, wxT("Start Recording"), wxBitmap(wxImage(wxT("./Icons/Simulation_Record.bmp"))), wxT("Start Recording"), wxITEM_RADIO);
	recordingToolbar->AddTool(TOOLBARID_SimulationStopRecord, wxT("Stop Recording"), wxBitmap(wxImage(wxT("./Icons/Simulation_StopRecord.bmp"))), wxT("Stop Recording"), wxITEM_RADIO);

	recordingToolbar->Realize();

	// add the toolbars to the manager
	wxAuiMgr.AddPane(basicToolbar, wxAuiPaneInfo().
		Name(wxT("basicToolbar")).Caption(wxT("Basic Toolbar")).
		ToolbarPane().Top());
	wxAuiMgr.AddPane(simulationToolbar, wxAuiPaneInfo().
		Name(wxT("simulationToolbar")).Caption(wxT("Simulation Toolbar")).
		ToolbarPane().Top());
	wxAuiMgr.AddPane(recordingToolbar, wxAuiPaneInfo().
		Name(wxT("recordingToolbar")).Caption(wxT("Recording Toolbar")).
		ToolbarPane().Top());
}

void PhysicsHelperToolbars::ShowRecordingToolbar()
{
	simulationToolbar->Show();
}

void PhysicsHelperToolbars::HideRecordingToolbar()
{
	simulationToolbar->Show(false);
}