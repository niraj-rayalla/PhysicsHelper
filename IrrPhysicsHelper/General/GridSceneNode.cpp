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

#include "GridSceneNode.h"

GridSceneNode::GridSceneNode(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id, SColor& _color, unsigned int widthResolution, unsigned int heightResolution,
	float widthSpacing, float heightSpacing)
	: scene::ISceneNode(parent, smgr, id)
{
	material.Wireframe = false;
	material.Lighting = false;

	color = _color;

	int noWarningSignedWidthResolution = widthResolution;
	int noWarningSignedHeightResolution = heightResolution;

	bool isWidthOdd = (widthResolution % 2) == 1;
	bool isHeightOdd = (heightResolution % 2) == 1;
	float widthStart = isWidthOdd ? -(noWarningSignedWidthResolution - 1) / 2 * widthSpacing : -noWarningSignedWidthResolution / 2 * widthSpacing - widthSpacing / 2.0f;
	float widthEnd = -widthStart;
	float heightStart = isHeightOdd ? -(noWarningSignedHeightResolution - 1) / 2 * heightSpacing : -noWarningSignedHeightResolution / 2 * heightSpacing - heightSpacing / 2.0f;
	float heightEnd = -heightStart;

	int counter = 0;
	int DarkLineWidthCount = widthResolution / 20;
	int DarkLineHeightCount = heightResolution / 20;
	bool widthHasDarkLine = DarkLineWidthCount > 0;
	bool heightHasDarkLine = DarkLineHeightCount > 0;
	SColor DarkLineColor = color;
	DarkLineColor.setAlpha(255);
	DarkLineColor.setRed(255 - DarkLineColor.getRed());
	DarkLineColor.setGreen(255 - DarkLineColor.getGreen());
	DarkLineColor.setBlue(255 - DarkLineColor.getBlue());

	int DarkLineWidthCounter = DarkLineWidthCount;
	int DarkLineHeightCounter = DarkLineHeightCount;

	float x = widthStart;
	for(unsigned int i = 0; i < widthResolution; i++)
	{
		S3DVertex tempVertex = S3DVertex(Vector3(x, 0.0f, heightStart), Vector3(0.0f, 0.0f, 0.0f), (widthHasDarkLine && DarkLineWidthCounter == 0) ? DarkLineColor : color,
			vector2d<float>(0.0f, 0.0f));
		vertices.push_back(tempVertex);
		tempVertex.Pos.Z = heightEnd;
		vertices.push_back(tempVertex);

		indices.push_back(counter*2);
		indices.push_back(counter*2 + 1);

		x += widthSpacing;
		
		if (DarkLineWidthCounter == 0)
		{
			DarkLineWidthCounter = DarkLineWidthCount;
		}
		else
		{
			DarkLineWidthCounter--;
		}
		counter++;
	}

	float y = heightStart;
	for(unsigned int i = 0; i < heightResolution; i++)
	{
		S3DVertex tempVertex = S3DVertex(Vector3(widthStart, 0.0f, y), Vector3(0.0f, 0.0f, 0.0f), (heightHasDarkLine && DarkLineHeightCounter == 0) ? DarkLineColor : color,
			vector2d<float>(0.0f, 0.0f));
		vertices.push_back(tempVertex);
		tempVertex.Pos.X = widthEnd;
		vertices.push_back(tempVertex);

		indices.push_back(counter*2);
		indices.push_back(counter*2 + 1);

		y += heightSpacing;

		if (DarkLineHeightCounter == 0)
		{
			DarkLineHeightCounter = DarkLineHeightCount;
		}
		else
		{
			DarkLineHeightCounter--;
		}
		counter++;
	}

	setAutomaticCulling(EAC_OFF);
}