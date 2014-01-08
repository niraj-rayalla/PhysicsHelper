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

#ifndef _WX_IRR_CONSTRAINT
#define _WX_IRR_CONSTRAINT

#include "../../IrrlichtInclude.h"
#include "../../General/GeneralFunctions.h"
#include "../Physics Object/PhysicsObject.h"
#include "../Forces/Force.h"

namespace Physics_Engine
{
	class Constraint
	{
	public:
		virtual void GetForces() {}
		virtual void Update(float timeInSecondsSinceLastFrame) {}
	};

	enum DistanceConstraintMovableObject
	{
		DCMO_Obj1,
		DCMO_Obj2,
		DCMO_Both
	};

	class DistanceConstraint : public Constraint
	{
	private:
		PhysicsObject* obj1;
		PhysicsObject* obj2;
		float constraintLength;
		DistanceConstraintMovableObject moveDirection;

	public:
		DistanceConstraint(PhysicsObject* _obj1, PhysicsObject* _obj2, float _constraintLength, DistanceConstraintMovableObject _moveDirection = DCMO_Obj2);

		void Update(float timeInSecondsSinceLastFrame);
	};

	class PhysicsString
	{
	private:
		ForceAfter* frcAfter;
		PhysicsObject* obj1;
		PhysicsObject* obj2;
		Vector3 tensionVector;
		float length;
		Vector3 centripital;

		static Vector3 frcAfterTension;

	public:
		PhysicsString(PhysicsObject* _obj1, PhysicsObject* _obj2, float _length);
		~PhysicsString();

		void Update(float timeInSecondsSinceLastFrame);
		void UpdateAfter();

		void Draw(IVideoDriver* driver);
	};
}

#endif