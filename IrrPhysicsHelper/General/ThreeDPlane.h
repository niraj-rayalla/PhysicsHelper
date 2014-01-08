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

#ifndef WX_IRR_THREE_D_PLANE
#define WX_IRR_THREE_D_PLANE

#include "../IrrlichtInclude.h"

class ThreeDPlane
{
private:
	Vector3 normal;
	Vector3 pos;
	float D;

	void CalculateD();

public:
	ThreeDPlane(){}
	ThreeDPlane(Vector3& _normal, Vector3& _pos);
	//ThreeDPlane(const Vector3 _normal, const Vector3 _pos);	

	bool GetIntersectionWithRay(line3df& ray, Vector3& outIntersection);

	void ChangePlane(Vector3& _normal, Vector3& _pos);
	//void ChangePlane(const Vector3 _normal, const Vector3 _pos);
};

#endif