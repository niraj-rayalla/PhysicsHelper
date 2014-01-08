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

#ifndef _WX_IRR_VECTOR_SIMULATION
#define _WX_IRR_VECTOR_SIMULATION

#include "Simulation.h"
#include "../General/ThreeDArrow.h"

enum VectorType
{
	VectorType_Cartesian,
	VectorType_Spherical
};

class VectorNameStorage
{
public:
	VectorType vectorType;
	float first;
	float second;
	float third;

	VectorNameStorage(){}

	VectorNameStorage(VectorType _vectorType, float _first, float _second, float _third)
	{
		vectorType = _vectorType;
		first = _first;
		second = _second;
		third = _third;
	}

	friend ostream& operator<<(ostream& os, VectorNameStorage& nameStorage)
	{
		os << nameStorage.vectorType << endl;
		os << nameStorage.first << endl;
		os << nameStorage.second << endl;
		os << nameStorage.third << endl;

		return os;
	}

	friend istream& operator>>(istream& is, VectorNameStorage& nameStorage)
	{
		int tempVectorType = 0;
		is >> tempVectorType;
	
		if (tempVectorType == VectorType_Cartesian)
		{
			nameStorage.vectorType = VectorType_Cartesian;
		}
		else if (tempVectorType == VectorType_Spherical)
		{
			nameStorage.vectorType = VectorType_Spherical;
		}

		is >> nameStorage.first;
		is >> nameStorage.second;
		is >> nameStorage.third;

		return is;
	}
};

class VectorSimulation : public Simulation
{
private:
	Vector3 sumVector;
	ThreeDArrow* sumArrow;

	bool lineUpVectors;
	int numArrows;

	SColor vectorColor;
	SColor sumVectorColor;

	irr::core::array<S3DVertex> arrowVertices;
	irr::core::array<u16> arrowIndicies;

	List<int>* selectedVectorsIndexes;

	List<VectorNameStorage>* nameList;

	void AddToSumVector(Vector3 vec);

	void (*AddObjectToListBox)(wxString str);

public:
	VectorSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*addObjectToListBox)(wxString str));
	~VectorSimulation();

	void Clear();

	void Draw(WxIrrViewport* currentViewport = 0);

	void AddVectorFunction(Vector3 vec);
	void AddVector(Vector3 vec);
	void AddVector(float magnitude, float theta, float phi);
	void RemoveVector(int arrowNumberIndex);

	Vector3 GetUnitVector(int arrowNumber);
	float GetDotProduct(int arrowNumber1, int arrowNumber2);
	Vector3 GetCrossVector(int arrowNumber1, int arrowNumber2);

	void ChangeVectorLineUp();
	void ChangeSelectedVectors(wxArrayInt vectorIndexes);

	void SerializeIn(istream &is);
	void SerializeOut(ostream &os);
};

#endif
