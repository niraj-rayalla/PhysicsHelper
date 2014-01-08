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

#include "PathDrawableObject.h"

SColor PathDrawableObject::color = SColor(255, 255, 255, 255);
int PathDrawableObject::numFrames = 3;
//int PathDrawableObject::maxNumLines = 0;

PathDrawableObject::PathDrawableObject(bool _drawPath)
{
	drawPath = _drawPath;

	pathVertices.set_used(0);
	pathIndicies.set_used(0);

	currentIndex = 0;
	currentFrame = 0;
}

void PathDrawableObject::ShowObjectPath()
{
	drawPath = true;
}

void PathDrawableObject::HideObjectPath()
{
	drawPath = false;

	//Reset
	currentIndex = 0;
	pathVertices.clear();
	pathIndicies.clear();
}

void PathDrawableObject::UpdatePath(Vector3 pos)
{
	if (drawPath)
	{
		if (currentFrame >= numFrames)
		{
			currentPosition = pos;
			
			S3DVertex tempVertex = S3DVertex(pos, Vector3_Zero, color, vector2d<float>(0.0f, 0.0f));
			pathVertices.push_back(tempVertex);

			if (currentIndex != 0)
			{
				pathIndicies.push_back(currentIndex - 1);
				pathIndicies.push_back(currentIndex);
			}

			currentIndex++;

			currentFrame = 0;
		}
		else
		{
			/*if (currentFrame >= numFrames)
			{
				currentFrame = 0;
			}
			else*/
			{
				currentFrame++;
			}
		}
	}
}

void PathDrawableObject::DrawPath(IVideoDriver* driver)
{
	if (drawPath)
	{
		driver->drawVertexPrimitiveList(pathVertices.pointer(), currentIndex, pathIndicies.pointer(), currentIndex - 1, EVT_STANDARD, EPT_LINES, EIT_32BIT);
	}
}