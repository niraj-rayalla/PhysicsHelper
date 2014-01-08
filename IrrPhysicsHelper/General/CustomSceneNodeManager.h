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

#ifndef WX_CUSTOM_SCENE_NODE_MANAGER
#define WX_CUSTOM_SCENE_NODE_MANAGER

#include "../IrrlichtInclude.h"

void CalculateNormals(irr::core::array<video::S3DVertex>& vertices,	irr::core::array<u16>& indices);

class CustomSceneNodeManager
{
public:
	SMesh* cylinderMesh;

	CustomSceneNodeManager();

	IMeshSceneNode* CreateCylinderSceneNode(scene::ISceneManager* smgr, s32 id, SColor& color, unsigned int resolution = 10, float radius = 1.0f, float height = 1.0f);
	IMeshSceneNode* CreateConeSceneNode(scene::ISceneManager* smgr, s32 id, SColor& color, unsigned int resolution = 10, float radius = 1.0f, float height = 1.0f);
	IMeshSceneNode* CreateCapsuleSceneNode(scene::ISceneManager* smgr, s32 id, SColor& color, unsigned int resolution = 10, float radius = 1.0f, float heightFromSphereCenters = 1.0f);
};

#endif