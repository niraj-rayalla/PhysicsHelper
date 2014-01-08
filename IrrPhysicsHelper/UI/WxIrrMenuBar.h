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

#ifndef _PHYSICSHELPER_MENU_BAR
#define _PHYSICSHELPER_MENU_BAR

#include "../Include.h"

enum
{
    ID_Exit = 1,
    ID_About,
	ID_Help,
	ID_New,
	ID_SaveSimulation,
	ID_LoadSimulation,
	ID_SplitViewportHoriz,
	ID_SplitViewportVert,
	ID_RemoveViewport,
	ID_ForceSimulation,
	ID_CalculateCOM,
	MENUBAR_SimulationAtwoodMachine,
	MENUBAR_CenterOfMass,
	MENUBAR_SimulationCoulombLaw,
	MENUBAR_SimulationForceWithoutRamp,
	MENUBAR_SimulationForceWithRamp,
	MENUBAR_SimulationGraphing,
	MENUBAR_SimulationGravitation,
	MENUBAR_SimulationLight,
	MENUBAR_SimulationMotion,
	MENUBAR_SimulationPendulum,
	MENUBAR_SimulationPlayground,
	MENUBAR_SimulationSpring,
	MENUBAR_SimulationVectorAddition,
	MENUBAR_SimulationWaves,
	MENUBAR_SimulationShowAxes,
	MENUBAR_SimulationXAxisChangeColor,
	MENUBAR_SimulationYAxisChangeColor,
	MENUBAR_SimulationZAxisChangeColor,
	MENUBAR_SimulationShowObjectNames,
	MENUBAR_SimulationVisibilityXYGrid,
	MENUBAR_SimulationVisibilityXZGrid,
	MENUBAR_SimulationVisibilityYZGrid
};

class PhysicsHelperMenuBar
{	
public:
	//Main menus
	wxMenu* fileMenu;
	wxMenu* windowsMenu;
	wxMenu* simulationsMenu;
	wxMenu* calculateMenu;
	wxMenu* unitsMenu;
	wxMenu* mathMenu;
	wxMenu* helpMenu;

	wxMenu* conversionsMenu;
	wxMenu* forcesMenu;
	wxMenu* simulationOptionsMenu;
	wxMenu* simulationAxesMenu;
	wxMenu* showGridsMenu;

	//Simulation menu elements.
	wxMenuItem* playgroundMenuItem;
	wxMenuItem* atwoodMachineMenuItem;
	wxMenuItem* coulombsLawMenuItem;
	wxMenuItem* withoutRampForceMenuItem;
	wxMenuItem* withRampMenuItem;
	wxMenuItem* gravitationMenuItem;
	wxMenuItem* lightMenuItem;
	wxMenuItem* motionMenuItem;
	wxMenuItem* pendulumMenuItem;
	wxMenuItem* springMenuItem;
	wxMenuItem* vectorAdditionMenuItem;
	wxMenuItem* wavesMenuItem;
	wxMenuItem* centerOfMassMenuItem;
	wxMenuItem* graphingMenuItem;

	void ClearMenuSimulationSelection();

	PhysicsHelperMenuBar(wxMenuBar* menuBar);
	
	void ChangeMenuSimulationSelection(int menuId);

};

#endif
