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

#ifndef _WX_IRR_3DArrow
#define _WX_IRR_3DArrow

#include "../IrrlichtInclude.h"
#include "GeneralFunctions.h"

class ThreeDArrow
{
private:
	//Index 0 and 1 are for arrow shaft(tail and head).
	S3DVertex vertices[4];
	u16 indices[6];

public:
	static matrix4 mat;
	ThreeDArrow(SColor& color)
	{
		vertices[0] = S3DVertex(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), color, vector2d<f32>(0.0f, 0.0f));
		vertices[1] = S3DVertex(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), color, vector2d<f32>(0.0f, 0.0f));
		vertices[2] = S3DVertex(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), color, vector2d<f32>(0.0f, 0.0f));
		vertices[3] = S3DVertex(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), color, vector2d<f32>(0.0f, 0.0f));

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 1;
		indices[3] = 2;
		indices[4] = 1;
		indices[5] = 3;
	}

	~ThreeDArrow()
	{
	}

	void ChangeColor(SColor& color)
	{
		vertices[0].Color = color;
		vertices[1].Color = color;
		vertices[2].Color = color;
		vertices[3].Color = color;
	}

	void Update(Vector3& tail, Vector3& dirWithLength)
	{
		vertices[0].Pos = tail;
		vertices[1].Pos = tail + dirWithLength;

		Vector3 backwards = tail - vertices[1].Pos;
		Vector3 normBackwards = backwards;
		float length = normBackwards.getLength();
		normBackwards /= length;

		Vector3 arrowHeadDir = length * 0.2f * Vector3(Ceiling(1.0f-abs_(normBackwards.X), 1.0f), Ceiling(1.0f-abs_(normBackwards.Y), 1.0f), Ceiling(1.0f-abs_(normBackwards.Z), 1.0f));
		vertices[2].Pos = vertices[1].Pos + arrowHeadDir + backwards * 0.2f;
		vertices[3].Pos = vertices[1].Pos - arrowHeadDir + backwards * 0.2f;
	}

	void Draw(IVideoDriver* driver)
	{		
		driver->setTransform(video::ETS_WORLD, mat);
		driver->drawVertexPrimitiveList(vertices, 6, indices, 3, EVT_STANDARD, EPT_LINES, EIT_16BIT);
		//driver->draw3DLine(vertices[0].Pos, vertices[1].Pos, vertices[0].Color);
	}

	S3DVertex* GetVerticesPointer()
	{
		return vertices;
	}

	u16* GetIndicesPointer()
	{
		return indices;
	}
};

void Get3DArrowPositions(Vector3 tail, Vector3 dirWithLength, Vector3& head, Vector3& arrowHead1, Vector3& arrowHead2);

#endif