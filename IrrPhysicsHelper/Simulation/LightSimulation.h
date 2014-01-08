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

#ifndef _WX_IRR_LIGHT_SIMULATION
#define _WX_IRR_LIGHT_SIMULATION

#include "GraphingSimulation.h"

const float RoundUpAccuracy = 0.0001f;

class LightRay
{
public:
	Vector3 start;
	Vector3 direction;

	List<LightRay*>* reflectionRays;
	List<LightRay*>* refractionRays;

	LightRay(Vector3 _start, Vector3 _direction)
	{
		start = _start;
		direction = _direction;
		direction.normalize();

		reflectionRays = new List<LightRay*>();
		refractionRays = new List<LightRay*>();
	}

	~LightRay()
	{
		delete refractionRays;
		delete reflectionRays;
	}

	LightRay* AddReflectionRay(Vector3 point, Vector3 dir)
	{
		LightRay* ray = new LightRay(point, dir);
		reflectionRays->Add(ray);

		return ray;
	}

	LightRay* AddRefractionRay(Vector3 point, Vector3 dir)
	{
		LightRay* ray = new LightRay(point, dir);
		refractionRays->Add(ray);

		return ray;
	}

	void Reset()
	{
		reflectionRays->Clear();
		refractionRays->Clear();
	}

	void Draw(IVideoDriver* driver)
	{
		Vector3 point1 = start;
		Vector3 point2 = Vector3_Zero;

		if (reflectionRays->GetSize() == 0 && refractionRays->GetSize() == 0)
		{
			driver->draw3DLine(point1, point1 + direction * 1000.0f);

			return;
		}

		if (reflectionRays->GetSize() > 0)
		{
			foreach(LightRay*, rayIt, reflectionRays)
			{
				point2 = rayIt->GetData()->start;

				driver->draw3DLine(point1, point2);
				point1 = point2;

				rayIt->GetData()->Draw(driver);
			}

			driver->draw3DLine(point1, point1 + reflectionRays->GetTail()->GetData()->direction * 1000.0f);
		}

		point1 = start;
		point2 = Vector3_Zero;

		if (refractionRays->GetSize() > 0)
		{
			foreach(LightRay*, rayIt, refractionRays)
			{
				point2 = rayIt->GetData()->start;

				driver->draw3DLine(point1, point2);
				point1 = point2;

				rayIt->GetData()->Draw(driver);
			}

			driver->draw3DLine(point1, point1 + refractionRays->GetTail()->GetData()->direction * 1000.0f);
		}
	}
};

class IntersectionReturnType
{
public:
	Vector3 IntersectionPoint;
	Vector3 IntersectionNormal;

	IntersectionReturnType(Vector3 _IntersectionPoint, Vector3 _IntersectionNormal)
	{
		IntersectionPoint = _IntersectionPoint;
		IntersectionNormal = _IntersectionNormal;
	}
};

class TriangleNormalStorage
{
private:
	Vector3 point1;
	Vector3 point2;
	Vector3 point3;
	Vector3 normal;

public:
	TriangleNormalStorage()
	{
		point1 = Vector3_Zero;
		point2 = Vector3_Zero;
		point3 = Vector3_Zero;
		normal = Vector3_Zero;
	}

	TriangleNormalStorage(Vector3 pnt1, Vector3 pnt2, Vector3 pnt3)
	{
		point1 = pnt1;
		point2 = pnt2;
		point3 = pnt3;

		Vector3 side1 = point1 - point3;
        Vector3 side2 = point1 - point2;
		normal = side2.crossProduct(side1);
		normal.normalize();
	}

	/*~TriangleNormalStorage()
	{
	}*/

	//Parallel rays dont count as an intersection.
	IntersectionReturnType* IntersectWithLightRay(LightRay* ray)
	{
		//First check if ray starting point is above the one-sided plane/triangle.
		float sideCheck = normal.dotProduct(ray->start - point1);
		if (sideCheck <= 0.0f)
		{
			//Below or parallel to plane.
			return NULL;
		}

		//Then check if the ray intersects with the plane the triangle lies in and if the ray intersects
		//the plane head on and not from behind.
		float parallelCheck = ray->direction.dotProduct(normal);
		if(parallelCheck < 0.0f)
		{
			float planeDValue = normal.dotProduct(point1);

			float intersectionDistance = (planeDValue - normal.dotProduct(ray->start)) / (parallelCheck);
			
			//
			if (intersectionDistance >= RoundUpAccuracy)
			{			
				Vector3 intersectionPoint = ray->start + intersectionDistance * ray->direction;

				//Now check if the intersection point is in the triangle.
				float side1Dot = normal.dotProduct((point2 - point1).crossProduct(intersectionPoint - point1));
				float side2Dot = normal.dotProduct((point3 - point2).crossProduct(intersectionPoint - point2));
				float side3Dot = normal.dotProduct((point1 - point3).crossProduct(intersectionPoint - point3));

				if (side1Dot >= 0.0f && side2Dot >= 0.0f && side3Dot >= 0.0f)
				{
					return new IntersectionReturnType(intersectionPoint, normal);
				}
			}

			//Point not inside triangle
			return NULL;
		}
		//Ray was either parallel or intersected from behind.
		return NULL;
	}
};

class LightMediumSplitterObject
{
	friend class LightSimulation;
private:
	float IoR;
	List<TriangleNormalStorage*>* triangles;

public:
	LightMediumSplitterObject(float _IoR, ThreeDGraph* graph)
	{
		IoR = _IoR;

		triangles = new List<TriangleNormalStorage*>();

		SMeshBuffer* buf = (SMeshBuffer*)graph->GetMesh()->getMeshBuffer(0);
		u32 size = buf->Indices.size();
		for (unsigned int i = 0; i < size / 3; i++)
		{
			int index1 = buf->Indices[i * 3];
			int index2 = buf->Indices[i * 3 + 1];
			int index3 = buf->Indices[i * 3 + 2];

			Vector3 point1 = buf->Vertices[index1].Pos;
			Vector3 point2 = buf->Vertices[index2].Pos;
			Vector3 point3 = buf->Vertices[index3].Pos;

			/*Vector3 side1 = point1 - point3;
			Vector3 side2 = point1 - point2;
			Vector3 normal = side2.crossProduct(side1);*/

			triangles->Add(new TriangleNormalStorage(point1, point2, point3));
		}		
	}

	~LightMediumSplitterObject()
	{
		delete triangles;
	}

	IntersectionReturnType* IntersectWithLightRay(LightRay* ray)
	{
		foreach(TriangleNormalStorage*, triangleIt, triangles)
		{
			TriangleNormalStorage* triangle = triangleIt->GetData();

			IntersectionReturnType* retValue = triangle->IntersectWithLightRay(ray);
			if (retValue)
			{
				return retValue;
			}
		}

		return NULL;
	}
};

class LightSimulation: public GraphingSimulation
{
private:
	bool showReflection;
	bool showRefraction;
	int maxReflections;
	List<LightRay*>* lightRays;
	List<LightMediumSplitterObject*>* lightMediumSplitterObjects;	
	
public:
	LightSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*AddObjectToListBox)(wxString str, bool enabled));

	~LightSimulation();

	void AddLightRay(Vector3 _start, Vector3 _direction);
	
	void AddRectangularMedium(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, RectangularAxis _colorAxis, RectangularAxis _axis, 
		int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid = false, bool _enabled = true, float IoR = 1.0f);

	void AddSphericalMedium(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, SphericalAxis _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid = false, bool _enabled = true, float IoR = 1.0f);

	void AddCylindricalMedium(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, CylindricalAxis _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid = false, bool _enabled = true, float IoR = 1.0f);

	void AddParametricMedium(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, SColor _lowColor, SColor _highColor, ParametricAxis _colorAxis,
		int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid = false, bool _enabled = true, float IoR = 1.0f);
	
	void ChangeSelections(wxArrayInt intArray);

	void ChangeEnabled(int index);

	void RemoveMedium(int index);

	void CalculateSingleRayReflection(LightRay* ray, int* mediumNumReflected);
	void CalculateSingleRayRefraction(LightRay* ray);

	void RecalculateRay(int index);
	void RecalculateRays();

	void Reset();

	void Draw(WxIrrViewport* currentViewport = 0);

	void SerializeIn(istream& is);
	void SerializeOut(ostream& os);
};

#endif