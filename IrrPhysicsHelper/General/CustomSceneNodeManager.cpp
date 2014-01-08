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

#include "CustomSceneNodeManager.h"

void CalculateNormals(irr::core::array<video::S3DVertex>& vertices,	irr::core::array<u16>& indices)
{
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices[i].Normal = Vector3_Zero;
	}

	u32 size = indices.size();
	for (unsigned int i = 0; i < size / 3; i++)
	{
		int index1 = indices[i * 3];
        int index2 = indices[i * 3 + 1];
        int index3 = indices[i * 3 + 2];

		Vector3 side1 = vertices[index2].Pos - vertices[index1].Pos;
        Vector3 side2 = vertices[index3].Pos - vertices[index1].Pos;
		Vector3 normal = side1.crossProduct(side2);

        vertices[index1].Normal += normal;
        vertices[index2].Normal += normal;
        vertices[index3].Normal += normal;
	}

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices[i].Normal.normalize();
	}
}

CustomSceneNodeManager::CustomSceneNodeManager()
{
	cylinderMesh = NULL;
}

IMeshSceneNode* CustomSceneNodeManager::CreateCylinderSceneNode(scene::ISceneManager* sceneManager, s32 id, SColor& color, unsigned int resolution, float radius, float height)
{
	/*if (!cylinderMesh)
	{*/
		if (resolution >= 4)
		{
			SMesh* newCylinderMesh = new SMesh();

			SMeshBuffer* buf = new SMeshBuffer();
		
			newCylinderMesh->addMeshBuffer(buf);
			buf->MappingHint_Vertex = EHM_STATIC;
			buf->MappingHint_Index = EHM_STATIC;
			buf->drop();

			int noWarningSignedResolution = resolution;

			float currentTheta = 0.0f;
			float skipAmount = 2.0f*PI / (float)resolution;
			float halfHeight = height / 2.0f;

			S3DVertex temp1 = S3DVertex(Vector3(0.0f, halfHeight, 0.0f), Vector3_Zero, color, vector2d<f32>(0.0f, 0.0f));
			S3DVertex temp2 = S3DVertex(Vector3(0.0f, -halfHeight, 0.0f), Vector3_Zero, color, vector2d<f32>(0.0f, 1.0f));
			for(int i = 0; i < noWarningSignedResolution; i++)
			{
				float x = cosf(currentTheta) * radius;
				float z = sinf(currentTheta) * radius;

				temp1.Pos.X = x;
				temp1.Pos.Z = z;
				temp1.TCoords.X = currentTheta / 2.0f*PI;
				temp2.Pos.X = x;
				temp2.Pos.Z = z;
				temp2.TCoords.X = currentTheta / 2.0f*PI;

				buf->Vertices.push_back(temp1);
				buf->Vertices.push_back(temp2);

				currentTheta += skipAmount;
			}

			temp1.Pos.X = 0.0f;
			temp1.Pos.Z = 0.0f;
			temp1.TCoords.X = 0.0f;
			temp2.Pos.X = 0.0f;
			temp2.Pos.Z = 0.0f;
			temp1.TCoords.X = 0.0f;
			buf->Vertices.push_back(temp1);
			buf->Vertices.push_back(temp2);

			//Get indices
			for(int i = 0; i < noWarningSignedResolution - 1; i++)
			{
				buf->Indices.push_back(i*2);
				buf->Indices.push_back(i*2+2);
				buf->Indices.push_back(i*2+1);

				buf->Indices.push_back(i*2+1);
				buf->Indices.push_back(i*2+2);
				buf->Indices.push_back(i*2+3);

				buf->Indices.push_back(i*2);
				buf->Indices.push_back(buf->Vertices.size()-2);
				buf->Indices.push_back(i*2+2);

				buf->Indices.push_back(i*2+1);
				buf->Indices.push_back(i*2+3);
				buf->Indices.push_back(buf->Vertices.size()-1);
			}

			buf->Indices.push_back(buf->Vertices.size()-4);
			buf->Indices.push_back(0);
			buf->Indices.push_back(buf->Vertices.size()-3);

			buf->Indices.push_back(buf->Vertices.size()-3);
			buf->Indices.push_back(0);
			buf->Indices.push_back(1);

			buf->Indices.push_back(buf->Vertices.size()-4);
			buf->Indices.push_back(buf->Vertices.size()-2);
			buf->Indices.push_back(0);

			buf->Indices.push_back(buf->Vertices.size()-3);
			buf->Indices.push_back(1);
			buf->Indices.push_back(buf->Vertices.size()-1);

			//Calculate normals
			CalculateNormals(buf->Vertices, buf->Indices);

			buf->recalculateBoundingBox();
			newCylinderMesh->recalculateBoundingBox();

			IMeshSceneNode* node = sceneManager->addMeshSceneNode(newCylinderMesh);

			newCylinderMesh->drop();

			return node;
		}

	/*	return NULL;
	}
	else
	{
		IMeshSceneNode* node = sceneManager->addMeshSceneNode(cylinderMesh);
		node->setScale(Vector3(radius, height, radius));

		return node;
	}*/

	return NULL;
}


IMeshSceneNode* CustomSceneNodeManager::CreateConeSceneNode(scene::ISceneManager* sceneManager, s32 id, SColor& color, unsigned int resolution, float radius, float height)
{
	if (resolution >= 4)
	{
		/*IMesh* newConeMesh = sceneManager->getGeometryCreator()->createConeMesh(radius, height, resolution, color, color);

		IMeshSceneNode* node = sceneManager->addMeshSceneNode(newConeMesh);

		sceneManager->getMeshCache()->addMesh(irr::io::path("ConeMesh"), (irr::scene::IAnimatedMesh*)newConeMesh);
		newConeMesh->drop();*/

		SMesh* newConeMesh = new SMesh();

		SMeshBuffer* buf = new SMeshBuffer();
	
		newConeMesh->addMeshBuffer(buf);
		buf->MappingHint_Vertex = EHM_STATIC;
		buf->MappingHint_Index = EHM_STATIC;
		buf->drop();

		int noWarningSignedResolution = resolution;

		float currentTheta = 0.0f;
		float skipAmount = 2.0f*PI / (float)resolution;
		float halfHeight = height / 2.0f;

		S3DVertex temp1 = S3DVertex(Vector3(0.0f, halfHeight, 0.0f), Vector3_Zero, color, vector2d<f32>(0.0f, 0.0f));
		S3DVertex temp2 = S3DVertex(Vector3(0.0f, -halfHeight, 0.0f), Vector3_Zero, color, vector2d<f32>(0.0f, 1.0f));
		for(int i = 0; i < noWarningSignedResolution; i++)
		{
			float x = cosf(currentTheta) * radius;
			float z = sinf(currentTheta) * radius;

			temp2.Pos.X = x;
			temp2.Pos.Z = z;
			temp2.TCoords.X = currentTheta / 2.0f*PI;

			buf->Vertices.push_back(temp2);

			currentTheta += skipAmount;
		}
		
		buf->Vertices.push_back(temp1);

		//Get side indices
		for(int i = 0; i < noWarningSignedResolution - 1; i++)
		{
			buf->Indices.push_back(i);
			buf->Indices.push_back(buf->Vertices.size()-1);
			buf->Indices.push_back(i+1);
		}

		buf->Indices.push_back(buf->Vertices.size()-2);
		buf->Indices.push_back(buf->Vertices.size()-1);
		buf->Indices.push_back(0);

		temp2.Pos.X = 0.0f;
		temp2.Pos.Z = 0.0f;
		buf->Vertices.push_back(temp2);

		//Get bottom indices
		for(int i = 0; i < noWarningSignedResolution - 1; i++)
		{
			buf->Indices.push_back(i);
			buf->Indices.push_back(i+1);
			buf->Indices.push_back(buf->Vertices.size()-1);
		}

		buf->Indices.push_back(buf->Vertices.size()-1);
		buf->Indices.push_back(buf->Vertices.size()-3);
		buf->Indices.push_back(0);

		//Calculate normals
		CalculateNormals(buf->Vertices, buf->Indices);

		buf->recalculateBoundingBox();
		newConeMesh->recalculateBoundingBox();

		IMeshSceneNode* node = sceneManager->addMeshSceneNode(newConeMesh);

		newConeMesh->drop();

		return node;
	}

	return NULL;
}

IMeshSceneNode* CustomSceneNodeManager::CreateCapsuleSceneNode(scene::ISceneManager* sceneManager, s32 id, SColor& color, unsigned int resolution, float radius, float heightFromSphereCenters)
{
	if (resolution >= 4)
	{
		SMesh* newCapsuleMesh = new SMesh();

		SMeshBuffer* buf = new SMeshBuffer();
	
		newCapsuleMesh->addMeshBuffer(buf);
		buf->MappingHint_Vertex = EHM_STATIC;
		buf->MappingHint_Index = EHM_STATIC;
		buf->drop();

		int noWarningSignedResolution = resolution;

		float thetaSkipAmount = 2.0f*PI / (float)resolution;
		float halfHeight = heightFromSphereCenters / 2.0f;
		float phiSkipAmount = PI*0.5f / (float)resolution;
		
		S3DVertex temp1 = S3DVertex(Vector3(0.0f, halfHeight, 0.0f), Vector3_Zero, color, vector2d<f32>(0.0f, 0.0f));
		S3DVertex temp2 = S3DVertex(Vector3(0.0f, -halfHeight, 0.0f), Vector3_Zero, color, vector2d<f32>(0.0f, 1.0f));

		float currentTheta = 0.0f;		
		float currentPhi = phiSkipAmount;
		temp1.Pos.Y = halfHeight + radius;
		buf->Vertices.push_back(temp1);

		//Semi-sphere Tips
		for(unsigned int i = 1; i < resolution; i++)
		{
			for(unsigned int j = 0; j < resolution; j++)
			{
				float x = sinf(currentPhi) * cosf(currentTheta) * radius;
				float y = cosf(currentPhi) * radius;
				float z = sinf(currentPhi) * sinf(currentTheta) * radius;

				temp1.Pos.X = x;
				temp1.Pos.Y = y + halfHeight;
				temp1.Pos.Z = z;
				temp1.TCoords.X = currentTheta / 2.0f*PI;
				temp1.TCoords.Y = currentPhi / PI;

				buf->Vertices.push_back(temp1);

				currentTheta += thetaSkipAmount;
			}

			currentTheta = 0.0f;
			currentPhi += phiSkipAmount;
		}

		currentTheta = 0.0f;		
		currentPhi = PI/2.0f;

		//Semi-sphere Tips
		for(unsigned int i = 1; i < resolution; i++)
		{
			for(unsigned int j = 0; j < resolution; j++)
			{
				float x = sinf(currentPhi) * cosf(currentTheta) * radius;
				float y = cosf(currentPhi) * radius;
				float z = sinf(currentPhi) * sinf(currentTheta) * radius;

				temp1.Pos.X = x;
				temp1.Pos.Y = y - halfHeight;
				temp1.Pos.Z = z;
				temp1.TCoords.X = currentTheta / 2.0f*PI;
				temp1.TCoords.Y = currentPhi / PI;

				buf->Vertices.push_back(temp1);

				currentTheta += thetaSkipAmount;
			}

			currentTheta = 0.0f;
			currentPhi += phiSkipAmount;
		}
		temp1.Pos.X = 0.0f;
		temp1.Pos.Y = -(halfHeight + radius);
		temp1.Pos.Z = 0.0f;
		buf->Vertices.push_back(temp1);

		//Top vertex indices
		for(unsigned int i = 1; i <= resolution; i++)
		{
			if (i == resolution)
			{
				buf->Indices.push_back(i);
				buf->Indices.push_back(0);
				buf->Indices.push_back(1);
			}
			else
			{
				buf->Indices.push_back(i);
				buf->Indices.push_back(0);
				buf->Indices.push_back(i + 1);
			}
		}

		//Get indices
		int i  = 1 + resolution;

		while(i < buf->Vertices.size() - 1)
		{
			for(unsigned int j = 1; j < resolution; j++)
			{
				buf->Indices.push_back(i);
				buf->Indices.push_back(i - noWarningSignedResolution);
				buf->Indices.push_back(i - noWarningSignedResolution + 1);

				buf->Indices.push_back(i);
				buf->Indices.push_back(i - noWarningSignedResolution + 1);
				buf->Indices.push_back(i + 1);

				i++;
			}

			buf->Indices.push_back(i);
			buf->Indices.push_back(i - noWarningSignedResolution);
			buf->Indices.push_back(i - noWarningSignedResolution + 1 - resolution);

			buf->Indices.push_back(i);
			buf->Indices.push_back(i - noWarningSignedResolution + 1 - resolution);
			buf->Indices.push_back(i + 1 - resolution);

			i++;
		}

		//Bottom vertex indices
		for(int i = resolution; i >= 1 ; i--)
		{
			if (i == 1)
			{
				/*buf->Indices.push_back(i);
				buf->Indices.push_back(0);
				buf->Indices.push_back(1);*/

				buf->Indices.push_back(buf->Vertices.size() -1);
				buf->Indices.push_back(buf->Vertices.size() -1 - i);
				buf->Indices.push_back(buf->Vertices.size() - 1 - resolution);
			}
			else
			{
				buf->Indices.push_back(buf->Vertices.size() -1);
				buf->Indices.push_back(buf->Vertices.size() -1 - i);
				buf->Indices.push_back(buf->Vertices.size() - i);
			}
		}




		//Calculate normals
		CalculateNormals(buf->Vertices, buf->Indices);

		buf->recalculateBoundingBox();
		newCapsuleMesh->recalculateBoundingBox();

		IMeshSceneNode* node = sceneManager->addMeshSceneNode(newCapsuleMesh);

		newCapsuleMesh->drop();

		return node;
	}

	return NULL;
}