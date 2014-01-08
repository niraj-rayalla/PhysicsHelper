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

#include "VectorSimulation.h"

VectorSimulation::VectorSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine,
								   void (*addObjectToListBox)(wxString str)) : Simulation(dev, _driver, _physicsEngine, SimulationType_VectorAddition)
{
	sumVector = Vector3(0.0f, 0.0f, 0.0f);
	lineUpVectors = true;
	numArrows = 0;

	vectorColor = SColor(255, 255, 255, 255);
	sumVectorColor = SColor(255, 255, 0, 0);

	sumArrow = new ThreeDArrow(sumVectorColor);

	arrowVertices.set_used(0);
	arrowIndicies.set_used(0);

	selectedVectorsIndexes = new List<int>();

	nameList = new List<VectorNameStorage>();

	AddObjectToListBox = addObjectToListBox;
}

VectorSimulation::~VectorSimulation()
{
	delete sumArrow;
	delete selectedVectorsIndexes;
	delete nameList;
}

void VectorSimulation::AddToSumVector(Vector3 vec)
{
	sumVector += vec;
	sumArrow->Update(Vector3(0.0f, 0.0f, 0.0f), sumVector);

	SetUnSaved();
}

void VectorSimulation::Clear()
{
	arrowVertices.clear();
	arrowIndicies.clear();

	sumArrow->Update(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

	numArrows = 0;
	sumVector = Vector3_Zero;

	delete selectedVectorsIndexes;
	selectedVectorsIndexes = new List<int>();

	delete nameList;
	nameList = new List<VectorNameStorage>();
}

void VectorSimulation::Draw(WxIrrViewport* currentViewport)
{
	Simulation::Draw(currentViewport);

	//driver->setTransform(video::ETS_WORLD, ThreeDArrow::mat);
	driver->drawVertexPrimitiveList(arrowVertices.pointer(), numArrows*4, arrowIndicies.pointer(), numArrows*3, EVT_STANDARD, EPT_LINES, EIT_16BIT);

	sumArrow->Draw(driver);
}

void VectorSimulation::AddVectorFunction(Vector3 vec)
{
	Vector3 tail;
	Vector3 head;
	Vector3 arrowHead1;
	Vector3 arrowHead2;

	if(lineUpVectors)
	{
		tail = sumVector;
	}
	else
	{
		tail = Vector3(0.0f, 0.0f, 0.0f);
	}
	Get3DArrowPositions(tail, vec, head, arrowHead1, arrowHead2);

	S3DVertex tempVertex = S3DVertex(tail, Vector3(0.0f, 0.0f, 0.0f), vectorColor, vector2d<float>(0.0f, 0.0f));
	arrowVertices.push_back(tempVertex);
	tempVertex.Pos = head;
	arrowVertices.push_back(tempVertex);
	tempVertex.Pos = arrowHead1;
	arrowVertices.push_back(tempVertex);
	tempVertex.Pos = arrowHead2;
	arrowVertices.push_back(tempVertex);
	
	arrowIndicies.push_back(numArrows*4 + 0);
	arrowIndicies.push_back(numArrows*4 + 1);
	arrowIndicies.push_back(numArrows*4 + 1);
	arrowIndicies.push_back(numArrows*4 + 2);
	arrowIndicies.push_back(numArrows*4 + 1);
	arrowIndicies.push_back(numArrows*4 + 3);

	numArrows++;	

	AddToSumVector(vec);
}

void VectorSimulation::AddVector(Vector3 vec)
{
	AddVectorFunction(vec);

	nameList->Add(VectorNameStorage(VectorType_Cartesian, vec.X, vec.Y, vec.Z));
}

void VectorSimulation::AddVector(float magnitude, float theta, float phi)
{
	Vector3 vec = magnitude * Vector3(sinf(phi)*cosf(theta), sinf(phi)*sinf(theta), cosf(phi));

	AddVectorFunction(vec);

	nameList->Add(VectorNameStorage(VectorType_Spherical, theta, phi, magnitude));
}

void VectorSimulation::RemoveVector(int arrowNumberIndex)
{
	//The arrow's vector.
	Vector3 deletedDirection = arrowVertices[arrowNumberIndex*4 + 1].Pos - arrowVertices[arrowNumberIndex*4].Pos;

	//First remove all the vertices and indices corresponding to arrowNumber.
	arrowVertices.erase(arrowNumberIndex*4, 4);
	arrowIndicies.erase(arrowNumberIndex*6, 6);

	numArrows--;

	if (lineUpVectors)
	{
		//Update all the indices after the indices deleted since the index values have changed by 4.
		for (int i = arrowNumberIndex*6; i < numArrows*6; i++)
		{
			arrowIndicies[i] -= 4;
		}

		//Update all the vertices after the deleted vertices.
		for (int i = arrowNumberIndex*4; i < numArrows*4; i++)
		{
			arrowVertices[i].Pos -= deletedDirection;
		}
	}
	

	AddToSumVector(-deletedDirection);

	selectedVectorsIndexes->Clear();

	nameList->Remove(arrowNumberIndex);
}

void VectorSimulation::ChangeVectorLineUp()
{
	if (lineUpVectors)
	{
		//Change all vertex positions according to the vector displacement of each vectors tail to the origin.
		for (int i = 0; i < numArrows*4; i+=4)
		{
			Vector3 displacement = arrowVertices[i].Pos;
			arrowVertices[i].Pos = Vector3(0.0f, 0.0f, 0.0f);
			arrowVertices[i+1].Pos -= displacement;
			arrowVertices[i+2].Pos -= displacement;
			arrowVertices[i+3].Pos -= displacement;
		}

		lineUpVectors = false;
	}
	else
	{
		if (numArrows > 0)
		{
			Vector3 tailStart = arrowVertices[1].Pos;

			for (int i = 4; i < numArrows*4; i+=4)
			{
				arrowVertices[i].Pos += tailStart;
				arrowVertices[i+1].Pos += tailStart;
				arrowVertices[i+2].Pos += tailStart;
				arrowVertices[i+3].Pos += tailStart;

				tailStart = arrowVertices[i+1].Pos;
			}
		}

		lineUpVectors = true;
	}

	SetUnSaved();
}

void VectorSimulation::ChangeSelectedVectors(wxArrayInt vectorIndexes)
{
	//Deselect currently selected arrows
	foreach(int, selectedIt, selectedVectorsIndexes)
	{
		arrowVertices[selectedIt->GetData()*4].Color = vectorColor;
		arrowVertices[selectedIt->GetData()*4 + 1].Color = vectorColor;
		arrowVertices[selectedIt->GetData()*4 + 2].Color = vectorColor;
		arrowVertices[selectedIt->GetData()*4 + 3].Color = vectorColor;
	}
	selectedVectorsIndexes->Clear();

	SColor newColor = SColor(255, 255, 255, 0);

	for(unsigned int i = 0; i < vectorIndexes.size(); i++)
	{
		arrowVertices[vectorIndexes[i]*4].Color = newColor;
		arrowVertices[vectorIndexes[i]*4 + 1].Color = newColor;
		arrowVertices[vectorIndexes[i]*4 + 2].Color = newColor;
		arrowVertices[vectorIndexes[i]*4 + 3].Color = newColor;

		selectedVectorsIndexes->Add(vectorIndexes[i]);
	}
}

Vector3 VectorSimulation::GetUnitVector(int arrowNumber)
{
	Vector3 direction = arrowVertices[arrowNumber*4+1].Pos - arrowVertices[arrowNumber*4].Pos;
	direction.normalize();

	return direction;
}

float VectorSimulation::GetDotProduct(int arrowNumber1, int arrowNumber2)
{
	Vector3 vec1 = arrowVertices[arrowNumber1*4+1].Pos - arrowVertices[arrowNumber1*4].Pos;
	Vector3 vec2 = arrowVertices[arrowNumber2*4+1].Pos - arrowVertices[arrowNumber2*4].Pos;

	return vec1.dotProduct(vec2);
}

Vector3 VectorSimulation::GetCrossVector(int arrowNumber1, int arrowNumber2)
{
	Vector3 vec1 = arrowVertices[arrowNumber1*4+1].Pos - arrowVertices[arrowNumber1*4].Pos;
	Vector3 vec2 = arrowVertices[arrowNumber2*4+1].Pos - arrowVertices[arrowNumber2*4].Pos;

	return vec1.crossProduct(vec2);	
}

void VectorSimulation::SerializeIn(istream &is)
{
	is >> lineUpVectors;

	vectorColor = SerializeInSColor(is);
	sumVectorColor = SerializeInSColor(is);

	int tempNumArrows = 0;
	is >> tempNumArrows;

	for(int i = 0; i < tempNumArrows; i++)
	{
		Vector3 vec = SerializeInVector3(is);//os, arrowVertices[i*4 + 1].Pos - arrowVertices[i*4].Pos);
		AddVector(vec);
	}

	nameList = SerializeInList<VectorNameStorage>(is);

	foreach(VectorNameStorage, nameIt, nameList)
	{
		VectorNameStorage nameStorage = nameIt->GetData();

		wxString str = nameStorage.vectorType == VectorType_Cartesian ? _("Cartesian: {") : _("Spherical: {");

		str += wxString::Format("%f", nameStorage.first) + _(", ");
		str += wxString::Format("%f", nameStorage.second) + _(", ");
		str += wxString::Format("%f", nameStorage.third) + _("}");

		AddObjectToListBox(str);
	}

	sumVector = SerializeInVector3(is);
}
void VectorSimulation::SerializeOut(ostream &os)
{
	os << lineUpVectors << endl;

	SerializeOutSColor(os, vectorColor);
	SerializeOutSColor(os, sumVectorColor);

	os << numArrows << endl;

	for(int i = 0; i < numArrows; i++)
	{
		Vector3 outVector = arrowVertices[i*4 + 1].Pos - arrowVertices[i*4].Pos;
		SerializeOutVector3(os, outVector);
	}

	SerializeOutList(os, nameList);

	SerializeOutVector3(os, sumVector);
}
