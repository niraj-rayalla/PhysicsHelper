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

#include "LightSimulation.h"

LightSimulation::LightSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*AddObjectToListBox)(wxString str, bool enabled))
	: GraphingSimulation(dev, _driver, _physicsEngine, AddObjectToListBox)
{
	showReflection = true;
	showRefraction = true;
	maxReflections = 4;

	lightRays = new List<LightRay*>();
	lightMediumSplitterObjects = new List<LightMediumSplitterObject*>();
}

LightSimulation::~LightSimulation()
{
	delete lightRays;
	delete lightMediumSplitterObjects;
}

void LightSimulation::AddLightRay(Vector3 _start, Vector3 _direction)
{
	lightRays->Add(new LightRay(_start, _direction));

	RecalculateRay(lightRays->GetSize() - 1);
}

void LightSimulation::AddRectangularMedium(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, RectangularAxis _colorAxis, RectangularAxis _axis, 
	int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid, bool _enabled , float IoR)
{
	GraphingSimulation::AddRectangularGraph(_name, _equationString, Scale, _lowColor, _highColor, _colorAxis, _axis, _graphWidthResolution, _widthStart,
		_widthEnd, _graphHeightResolution, _heightStart, _heightEnd, _solid, _enabled);

	lightMediumSplitterObjects->Add(new LightMediumSplitterObject(IoR, graphList->GetTail()->GetData()));
	graphList->GetTail()->GetData()->node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	RecalculateRays();
}

void LightSimulation::AddSphericalMedium(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, SphericalAxis _colorAxis,
	int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid, bool _enabled, float IoR)
{
	GraphingSimulation::AddSphericalGraph(_name, _equationString, Scale, _lowColor, _highColor, _colorAxis, _thetaResolution, _thetaStart,
		_thetaEnd, _phiResolution, _phiStart, _phiEnd, _solid, _enabled);

	lightMediumSplitterObjects->Add(new LightMediumSplitterObject(IoR, graphList->GetTail()->GetData()));
	graphList->GetTail()->GetData()->node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	RecalculateRays();
}

void LightSimulation::AddCylindricalMedium(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, CylindricalAxis _colorAxis,
	int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid , bool _enabled, float IoR)
{
	GraphingSimulation::AddCylindricalGraph(_name, _equationString, Scale, _lowColor, _highColor, _colorAxis, _thetaResolution, _thetaStart,
		_thetaEnd, _radiusResolution, _radiusStart, _radiusEnd, _solid, _enabled);

	lightMediumSplitterObjects->Add(new LightMediumSplitterObject(IoR, graphList->GetTail()->GetData()));
	graphList->GetTail()->GetData()->node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	RecalculateRays();
}

void LightSimulation::AddParametricMedium(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, SColor _lowColor, SColor _highColor, ParametricAxis _colorAxis,
	int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid, bool _enabled, float IoR)
{
	GraphingSimulation::AddParametricGraph(_name, _xEquationString, _yEquationString, _zEquationString, Scale, _lowColor, _highColor, _colorAxis, _uResolution, _uStart,
		_uEnd, _vResolution, _vStart, _vEnd, _solid, _enabled);

	lightMediumSplitterObjects->Add(new LightMediumSplitterObject(IoR, graphList->GetTail()->GetData()));
	graphList->GetTail()->GetData()->node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	RecalculateRays();
}

void LightSimulation::ChangeSelections(wxArrayInt intArray)
{
	GraphingSimulation::ChangeSelections(intArray);
}

void LightSimulation::ChangeEnabled(int index)
{
	GraphingSimulation::ChangeEnabled(index);

	RecalculateRays();
}

void LightSimulation::RemoveMedium(int index)
{
	GraphingSimulation::RemoveGraph(index);
	lightMediumSplitterObjects->Remove(index);

	RecalculateRays();
}

void LightSimulation::CalculateSingleRayReflection(LightRay* currentRay, int* mediumNumReflected)
{
	bool foundIntersection = false;

	do
	{
		foundIntersection = false;

		float closestDistance = HUGE_VAL;
		Vector3 closestIntersection = Vector3_Zero;
		Vector3 intersectionNormal = Vector3_Zero;
		int intersectionMediumIndex = -1;

		LightRay* currentReflectionRay = currentRay->reflectionRays->GetSize() == 0 ? currentRay : currentRay->reflectionRays->GetTail()->GetData();

		int mediumIndex = 0;
		foreach(LightMediumSplitterObject*, mediumIt, lightMediumSplitterObjects)
		{
			if (mediumNumReflected[mediumIndex] < maxReflections)
			{
				//If an intersection is found make sure its closer than the one already found.
				IntersectionReturnType* intersectionValues = mediumIt->GetData()->IntersectWithLightRay(currentReflectionRay);
				if (intersectionValues)
				{
					float tempDist = intersectionValues->IntersectionPoint.getDistanceFrom(currentReflectionRay->start);
					if (tempDist < closestDistance)
					{
						foundIntersection = true;

						closestDistance = tempDist;
						closestIntersection = intersectionValues->IntersectionPoint;
						intersectionNormal = intersectionValues->IntersectionNormal;
						intersectionMediumIndex = mediumIndex;
					}

					delete intersectionValues;
					intersectionValues = NULL;	
				}
			}

			mediumIndex++;
		}

		if(closestDistance != HUGE_VAL)
		{
			mediumNumReflected[intersectionMediumIndex] = mediumNumReflected[intersectionMediumIndex] + 1; 

			Vector3 correctionVector = -2.0f * currentReflectionRay->direction.dotProduct(intersectionNormal) * intersectionNormal;
			LightRay* addedRay = currentRay->AddReflectionRay(closestIntersection, currentReflectionRay->direction + correctionVector);

			CalculateSingleRayRefraction(addedRay);
		}

	} while(foundIntersection);
}

void LightSimulation::CalculateSingleRayRefraction(LightRay* currentRay)
{
	float currentIOR = 1.0f;
    float nextIOR = 1.0f;

	bool foundIntersection = false;

	do
	{
		foundIntersection = false;

		float closestDistance = HUGE_VAL;
		Vector3 closestIntersection = Vector3_Zero;
		Vector3 intersectionNormal = Vector3_Zero;

		LightRay* currentRefractionRay = currentRay->refractionRays->GetSize() == 0 ? currentRay : currentRay->refractionRays->GetTail()->GetData();

		int mediumIndex = 0;
		foreach(LightMediumSplitterObject*, mediumIt, lightMediumSplitterObjects)
		{
			LightMediumSplitterObject* medium = mediumIt->GetData();
			//If an intersection is found make sure its closer than the one already found.
			IntersectionReturnType* intersectionValues = medium->IntersectWithLightRay(currentRefractionRay);
			if (intersectionValues)
			{
				float tempDist = intersectionValues->IntersectionPoint.getDistanceFrom(currentRefractionRay->start);
				if (tempDist < closestDistance)
				{
					foundIntersection = true;

					closestDistance = tempDist;
					closestIntersection = intersectionValues->IntersectionPoint;
					intersectionNormal = intersectionValues->IntersectionNormal;
					nextIOR = medium->IoR;
				}

				delete intersectionValues;
				intersectionValues = NULL;
			}

			mediumIndex++;
		}

		if(closestDistance != HUGE_VAL)
		{
			float dotNormal = currentRefractionRay->direction.dotProduct(intersectionNormal);

			float currentAngle = cosf(dotNormal);
			float newAngle = asinf(currentIOR*sinf(currentAngle)/nextIOR);

			Vector3 correctionVector = -1.0f * dotNormal * intersectionNormal;
			correctionVector += currentRefractionRay->direction;
			correctionVector.normalize();
			
			Vector3 perpNormal = correctionVector * sinf(newAngle);
			Vector3 parallelNormal = -intersectionNormal * cosf(newAngle);

			LightRay* addedRay = currentRay->AddRefractionRay(closestIntersection, perpNormal + parallelNormal);

			CalculateSingleRayRefraction(addedRay);
		}

	} while(foundIntersection);
}

void LightSimulation::RecalculateRay(int index)
{
	LightRay* currentRay =  lightRays->GetAt(index)->GetData();

	currentRay->Reset();

	int size = lightMediumSplitterObjects->GetSize();
	int* numberOfTimesReflected =  new int[size];
	for(int i = 0; i < lightMediumSplitterObjects->GetSize(); i++)
	{
		numberOfTimesReflected[i] = 0;
	}

	if (showReflection)
	{
		CalculateSingleRayReflection(currentRay, numberOfTimesReflected);
	}

	if (showRefraction)
	{
		CalculateSingleRayRefraction(currentRay);
	}

	delete numberOfTimesReflected;
}

void LightSimulation::RecalculateRays()
{
	for(int i = 0; i < lightRays->GetSize(); i++)
	{
		RecalculateRay(i);
	}
}

void LightSimulation::Reset()
{
	GraphingSimulation::Reset();
	lightRays->Clear();
	lightMediumSplitterObjects->Clear();
}

void LightSimulation::Draw(WxIrrViewport* currentViewport)
{
	GraphingSimulation::Draw(currentViewport);

	foreach(LightRay*, lightRayIt, lightRays)
	{
		lightRayIt->GetData()->Draw(driver);
	}
}

void LightSimulation::SerializeIn(istream& is)
{
	GraphingSimulation::SerializeIn(is);
}
void LightSimulation::SerializeOut(ostream& os)
{
	GraphingSimulation::SerializeOut(os);
}