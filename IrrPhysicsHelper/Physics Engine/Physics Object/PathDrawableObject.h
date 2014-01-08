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

#ifndef _WX_IRR_PATH_DRAWABLE_OBJECT
#define _WX_IRR_PATH_DRAWABLE_OBJECT

#include "../../IrrlichtInclude.h"

class PathDrawableObject
{
private:
	bool drawPath;
	int currentFrame;
	Vector3 currentPosition;

	irr::core::array<S3DVertex> pathVertices;
	irr::core::array<u32> pathIndicies;

	int currentIndex;
	//int maxNumLines;

public:
	static int numFrames;
	static SColor color;

	PathDrawableObject(bool _drawPath = false);

	void ShowObjectPath();
	void HideObjectPath();

	void UpdatePath(Vector3 pos);

	void DrawPath(IVideoDriver* driver);

	/*void ChangeMaxNumberOfLines(int _maxNumLines)
	{ 
		maxNumLines = _maxNumLines;

		pathVertices.set_used(
	}*/

	static void ChangeFrameWaitCount(int cnt) { PathDrawableObject::numFrames = cnt; }
	static void ChangeColor(SColor& _color) { color = _color; }

};

#endif