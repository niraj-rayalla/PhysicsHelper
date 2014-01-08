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

#ifndef PHYSICS_HELPER_GUI_ENVIORNMENT
#define PHYSICS_HELPER_GUI_ENVIORNMENT

#include "../IrrlichtInclude.h"
#include "../General/GeneralClasses.h"

#include "BasicDynamicObjectIrrlichtGUI.h"

enum
{
	PHYSICSHELPER_GUI_WINDOW_ID = 1
};

class PhysicsHelperGUIEnviornment
{
private:
	IGUIEnvironment* guiEnv;

	List<IGUIElement*> guiElements;

	CGUITTFont* customFont;

public:
	static IGUIElement* focusedGUIElement;

	PhysicsHelperGUIEnviornment(IGUIEnvironment* _guiEnv);
	~PhysicsHelperGUIEnviornment();

	IGUIWindow* AddWindow();
	BasicDynamicObjectIrrlichtGUI* AddBasicDynamicObjectWindow(wxString title, float mass, const Vector3& pos, const Vector3& vel, const Vector3& frc);
	//true if removed. false if elem doesnt exist in list.
	bool RemoveGUIElement(IGUIElement* elem);
};

#endif