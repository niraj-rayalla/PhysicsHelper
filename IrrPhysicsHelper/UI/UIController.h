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

#ifndef _PHYSICSHELPER_UI_CONTROLLER
#define _PHYSICSHELPER_UI_CONTROLLER

#include <wx/wx.h>
#include "wx/aui/aui.h"
#include "wx/artprov.h"
#include "./WxIrrMenuBar.h"
#include "./WxIrrToolbars.h"

class UIController
{
private:
	wxMenuBar* menuBar;
	PhysicsHelperMenuBar* menuBarManager;
	PhysicsHelperToolbars* toolBarsManager;

public:
	UIController(wxMenuBar* _menuBar, PhysicsHelperMenuBar* _menuBarManager, PhysicsHelperToolbars* _toolBarsManager);

	void DisableRemoveWindow();
	void EnableRemoveWindow();

	void SetXYGridVisibility(bool isVisibile);
	void SetXZGridVisibility(bool isVisibile);
	void SetYZGridVisibility(bool isVisibile);

	void SimulationRun();
	void SimulationPause();
};


#endif