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

#include "UIController.h"

UIController::UIController(wxMenuBar* _menuBar, PhysicsHelperMenuBar* _menuBarManager, PhysicsHelperToolbars* _toolBarsManager)
{
	menuBar = _menuBar;
	menuBarManager = _menuBarManager;
	toolBarsManager = _toolBarsManager;
}

void UIController::DisableRemoveWindow()
{
	menuBarManager->windowsMenu->Enable(ID_RemoveViewport, false);
	toolBarsManager->basicToolbar->EnableTool(TOOLBARID_RemoveViewport, false);
	toolBarsManager->basicToolbar->Refresh();
}
void UIController::EnableRemoveWindow()
{
	menuBarManager->windowsMenu->Enable(ID_RemoveViewport, true);
	toolBarsManager->basicToolbar->EnableTool(TOOLBARID_RemoveViewport, true);
	toolBarsManager->basicToolbar->Refresh();
}

void UIController::SetXYGridVisibility(bool isVisibile)
{
	if (isVisibile)
	{
		menuBarManager->showGridsMenu->Check(MENUBAR_SimulationVisibilityXYGrid, true);
	}
	else
	{
		menuBarManager->showGridsMenu->Check(MENUBAR_SimulationVisibilityXYGrid, false);
	}
}
void UIController::SetXZGridVisibility(bool isVisibile)
{
	if (isVisibile)
	{
		menuBarManager->showGridsMenu->Check(MENUBAR_SimulationVisibilityXZGrid, true);
	}
	else
	{
		menuBarManager->showGridsMenu->Check(MENUBAR_SimulationVisibilityXZGrid, false);
	}
}
void UIController::SetYZGridVisibility(bool isVisibile)
{
	if (isVisibile)
	{
		menuBarManager->showGridsMenu->Check(MENUBAR_SimulationVisibilityYZGrid, true);
	}
	else
	{
		menuBarManager->showGridsMenu->Check(MENUBAR_SimulationVisibilityYZGrid, false);
	}
}

void UIController::SimulationRun()
{
	toolBarsManager->simulationToolbar->SetToolSticky(TOOLBARID_RunSimulation, true);
	toolBarsManager->simulationToolbar->SetToolSticky(TOOLBARID_PauseSimulation, false);
}
void UIController::SimulationPause()
{
	toolBarsManager->simulationToolbar->SetToolSticky(TOOLBARID_RunSimulation, false);
	toolBarsManager->simulationToolbar->SetToolSticky(TOOLBARID_PauseSimulation, true);
}