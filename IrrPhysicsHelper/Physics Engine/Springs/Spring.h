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

#ifndef _WX_IRR_SPRING
#define _WX_IRR_SPRING

#include "../../IrrlichtInclude.h"
#include "../Physics Object/PhysicsObject.h"
#include "SpringSceneNode.h"


namespace Physics_Engine
{
	enum SpringTypes
	{
		SpringType_DoubleSpring = 0
	};

	class Spring
	{
	protected:
		SpringTypes springType;
	public:
		virtual void UpdateForces() {}
		virtual void Update(float timeInSecondsSinceLastFrame) {}

		virtual void SerializeOut(ostream& os)
		{
			os << springType << endl;
		}
		virtual void SerializeIn(istream& is)
		{
			int tempEnum = 0;
			is >> tempEnum;
		}

		static Spring* SerializeInStatic(istream& is);

		friend ostream& operator<<(ostream& os, Spring& obj)
		{
			obj.SerializeOut(os);

			return os;
		}
		friend istream& operator>>(istream& is, Spring& obj)
		{
			obj.SerializeIn(is);

			return is;
		}
	};

	class DoubleSpring : public Spring
	{
		friend class Spring;
	private:
		float k;
        float equilibriumLength;
		PhysicsObject* object1;
        PhysicsObject* object2;
		float force;
		Vector3 positiveDirection;
	public:
		DoubleSpring(){}
		DoubleSpring(PhysicsObject* obj1, PhysicsObject* obj2, float _k = 1.0f, float _equilibriumLength = 10.0f);
		void UpdateForces();
		void Update(float timeInSecondsSinceLastFrame);
		
		float GetK() { return k; }
		float GetEquilibriumLength() { return equilibriumLength; }

		void SerializeOut(ostream& os);
		void SerializeIn(istream& is);
	};
}

#endif