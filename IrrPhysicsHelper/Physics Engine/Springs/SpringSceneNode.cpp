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

#include "SpringSceneNode.h"

SpringSceneNode::SpringSceneNode(irr::scene::ISceneNode *parent, irr::scene::ISceneManager *smgr, irr::s32 id, ISceneNode *_obj1, ISceneNode *_obj2)
	: scene::ISceneNode(parent, smgr, id)
{
	material.Wireframe = false;
	material.Lighting = false;

	obj1 = _obj1;
	obj2 = _obj2;

	color = SColor(255, 0, 0, 0);

	vertices.set_used(0);
	indices.set_used(22);

	for(int i = 0; i < 12; i++)
	{
		vertices.push_back(S3DVertex(Vector3_Zero, Vector3_Zero, color, vector2d<f32>(0.0f, 0.0f)));
	}

	for(int i = 0; i < 11; i++)
	{
		indices[i*2] = i;
		indices[i*2 + 1] = i + 1;
	}

	pos1 = Vector3_Zero;
	pos2 = Vector3_Zero;

	setAutomaticCulling(EAC_OFF);
}

void SpringSceneNode::UpdatePositions(Vector3& _pos1, Vector3& _pos2)
{
	pos1 = _pos1;
	pos2 = _pos2;

	Vector3 dirVec = pos2 - pos1;
	Vector3 startVec = dirVec * 0.1f;
	float length = dirVec.getLength();
	dirVec /= length;

	float scale = Floor<float>(squareroot(length)*0.3f, length / 10.0f);
	Vector3 sideVec = scale * Vector3(Ceiling(1.0f-abs_(dirVec.X), 1.0f), Ceiling(1.0f-abs_(dirVec.Y), 1.0f), Ceiling(1.0f-abs_(dirVec.Z), 1.0f));

	vertices[0].Pos = pos1;
	vertices[1].Pos = pos1 + startVec;

	vertices[2].Pos = vertices[1].Pos + (sideVec + startVec) / 2.0f;

	for (int i = 3; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			vertices[i].Pos = vertices[i-1].Pos + sideVec + startVec;
		}
		else
		{
			vertices[i].Pos = vertices[i-1].Pos - sideVec + startVec;
		}
	}

	vertices[10].Pos = vertices[9].Pos + (sideVec + startVec) / 2.0f;
	vertices[11].Pos = pos2;
}

void SpringSceneNode::SetObjects(ISceneNode* _obj1, ISceneNode* _obj2)
{
	obj1 = _obj1;
	obj2 = _obj2;
}