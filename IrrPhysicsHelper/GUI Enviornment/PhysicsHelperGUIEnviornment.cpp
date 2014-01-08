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

#include "PhysicsHelperGUIEnviornment.h"

IGUIElement* PhysicsHelperGUIEnviornment::focusedGUIElement = NULL;

PhysicsHelperGUIEnviornment::PhysicsHelperGUIEnviornment(IGUIEnvironment* _guiEnv)
{
	guiEnv = _guiEnv;

	c8 tmp[512];
	GetWindowsDirectoryA(tmp,511);
	strcat(tmp,"\\fonts\\arial.ttf");
	customFont = gui::CGUITTFont::createTTFont(guiEnv, tmp, 10);
	guiEnv->getSkin()->setFont(customFont);

	guiEnv->getSkin()->setColor ( EGDC_BUTTON_TEXT, video::SColor(255,0xCC,0xCC,0xCC) );
	guiEnv->getSkin()->setColor ( EGDC_3D_HIGH_LIGHT, video::SColor(200,0x44,0x44,0x44) );
	guiEnv->getSkin()->setColor ( EGDC_3D_FACE, video::SColor(200,0x44,0x44,0x44) );
	guiEnv->getSkin()->setColor ( EGDC_WINDOW, video::SColor(200,0x44,0x44,0x44) );
	guiEnv->getSkin()->setColor ( EGDC_3D_SHADOW, video::SColor(200,0x44,0x44,0x44) );

	customFont->drop();
}

PhysicsHelperGUIEnviornment::~PhysicsHelperGUIEnviornment()
{
	customFont->drop();
}

IGUIWindow* PhysicsHelperGUIEnviornment::AddWindow()
{
	IGUIWindow* newWindow = guiEnv->addWindow(irr::core::rect<s32>(0, 0, 100, 100), false, L"Test", 0, PHYSICSHELPER_GUI_WINDOW_ID);

	guiElements.Add(newWindow, false);

	return newWindow;
}

BasicDynamicObjectIrrlichtGUI* PhysicsHelperGUIEnviornment::AddBasicDynamicObjectWindow(wxString title, float mass, const Vector3& pos, const Vector3& vel, const Vector3& frc)
{
	wxCStrData titleData = title.c_str();

	BasicDynamicObjectIrrlichtGUI* newWindow = new BasicDynamicObjectIrrlichtGUI(guiEnv, titleData.AsWChar(), mass, pos, vel, frc);
	
	guiElements.Add(newWindow->window, false);

	return newWindow;
}

bool PhysicsHelperGUIEnviornment::RemoveGUIElement(IGUIElement* elem)
{
	if (elem)
	{
		List<IGUIElement*>* guiElementsPointer = &guiElements;
		foreach(IGUIElement*, elemIt, guiElementsPointer)
		{
			if (elem == elemIt->GetData())
			{
				guiElements.Remove(elemIt);
				return true;
			}
		}
	}

	return false;
}