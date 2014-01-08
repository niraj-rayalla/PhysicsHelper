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

#include "ThreeDPlane.h"

void ThreeDPlane::CalculateD()
{
	D = normal.dotProduct(pos);
}

ThreeDPlane::ThreeDPlane(Vector3& _normal, Vector3& _pos)
{
	normal = _normal.normalize();
	pos = _pos;

	CalculateD();
}
//ThreeDPlane::ThreeDPlane(const Vector3 _normal, const Vector3 _pos)
//{
//	normal = normal.normalize();
//	pos = _pos;
//
//	CalculateD();
//}

bool ThreeDPlane::GetIntersectionWithRay(line3df& ray, Vector3& outIntersection)
{
	Vector3 rayDir = ray.getVector().normalize();
	float parallelCheck = rayDir.dotProduct(normal);
	if(parallelCheck != 0.0f)
	{
		float intersectionDistance = (D - normal.dotProduct(ray.start)) / (parallelCheck);

		outIntersection = ray.start + intersectionDistance * rayDir;

		return true;
	}

	outIntersection = Vector3_Zero;
	return false;
}

void ThreeDPlane::ChangePlane(Vector3& _normal, Vector3& _pos)
{
	normal = _normal.normalize();
	pos = _pos;

	CalculateD();
}

//void ThreeDPlane::ChangePlane(const Vector3 _normal, const Vector3 _pos)
//{
//	normal = _normal.normalize();
//	pos = _pos;
//
//	CalculateD();
//}