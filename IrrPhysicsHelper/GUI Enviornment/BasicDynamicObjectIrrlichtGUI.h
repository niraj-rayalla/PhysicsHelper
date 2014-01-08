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

#ifndef BASIC_DYNAMIC_OBJECT_IRRLICHT_GUI
#define BASIC_DYNAMIC_OBJECT_IRRLICHT_GUI

#include "../IrrlichtInclude.h"

class BasicDynamicObjectIrrlichtGUI
{
private:
	IGUIStaticText* massLabel;
	IGUIStaticText* massValue;

	IGUIStaticText* posLabel;
	IGUIStaticText* posXLabel;
	IGUIStaticText* posXValue;
	IGUIStaticText* posYLabel;
	IGUIStaticText* posYValue;
	IGUIStaticText* posZLabel;
	IGUIStaticText* posZValue;

	IGUIStaticText* velLabel;
	IGUIStaticText* velXLabel;
	IGUIStaticText* velXValue;
	IGUIStaticText* velYLabel;
	IGUIStaticText* velYValue;
	IGUIStaticText* velZLabel;
	IGUIStaticText* velZValue;

	IGUIStaticText* frcLabel;
	IGUIStaticText* frcXLabel;
	IGUIStaticText* frcXValue;
	IGUIStaticText* frcYLabel;
	IGUIStaticText* frcYValue;
	IGUIStaticText* frcZLabel;
	IGUIStaticText* frcZValue;
public:
	IGUIWindow* window;
	BasicDynamicObjectIrrlichtGUI(IGUIEnvironment* guiEnv, const wchar_t* title, float mass, const Vector3& pos, const Vector3& vel, const Vector3& frc);
	~BasicDynamicObjectIrrlichtGUI();

	void UpdatePosition(Vector3& pos);
	void UpdateVelocity(Vector3& vel);
	void UpdateForce(Vector3& frc);
};

#endif