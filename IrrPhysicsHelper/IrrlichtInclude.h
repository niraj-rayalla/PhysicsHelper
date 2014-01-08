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

#ifndef _WX_IRR_IRRLICHT_INCLUDE
#define _WX_IRR_IRRLICHT_INCLUDE
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//Irrlicht redefinitions
typedef vector3df Vector3;
typedef vector2df Vector2;

const Vector3 Vector3_Zero = Vector3(0, 0, 0);

//Include Irrlicht classes/scene nodes

#include "General/GridSceneNode.h"
#include "General/CustomSceneNodeManager.h"

#include "GUI Enviornment\Fonts\CGUITTFont.h"

//Functions
SColor operator/(SColor& color, int num);

void DrawTextOnScreenFrom3DPos(Vector3& point, int currentViewportWidth, int currentViewportHeight, rect<s32>& viewportClientArea,
	ISceneManager* customSmgr, IGUIEnvironment* guiEnv, ICameraSceneNode* camera, stringw& text, SColor& color);

#endif _WX_IRR_IRRLICHT_INCLUDE
