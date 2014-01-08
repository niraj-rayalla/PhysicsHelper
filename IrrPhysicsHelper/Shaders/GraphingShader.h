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

#ifndef _WX_IRR_GRAPHING_SHADER
#define _WX_IRR_GRAPHING_SHADER

#include "../IrrlichtInclude.h"
#include "../DefinitionsInclude.h"


class GraphingShaderCallBack : public IShaderConstantSetCallBack
{
public:
	IrrlichtDevice* device;
	bool hasLighting;
	bool hasSpecular;
	bool showGrid;

	GraphingShaderCallBack(IrrlichtDevice* dev)
	{
		device = dev;
		hasSpecular = true;
		hasLighting = true;
		showGrid = true;
	}
	
	void EnableLighting() { hasLighting = true; }
	void DisableLighting() { hasLighting = false; }
	void EnableSpecular() { hasSpecular = true; }
	void DisableSpecular() { hasSpecular = false; }
	void ShowGrid() { showGrid = true; }
	void HideGrid() { showGrid = false; }

	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);
};

GraphingShaderCallBack* SetupGraphingShader(IrrlichtDevice* device);

s32 GetGraphingShader();

#endif