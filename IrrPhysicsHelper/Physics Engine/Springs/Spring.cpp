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

#include "Spring.h"

using namespace Physics_Engine;

Spring* Spring::SerializeInStatic(istream& is)
{
	int tempEnum = 0;
	is >> tempEnum;

	switch(tempEnum)
	{
	case SpringType_DoubleSpring:

		DoubleSpring springFromFile;
		is >> springFromFile;
		return new DoubleSpring(0, 0, springFromFile.k, springFromFile.equilibriumLength);

		break;
	}

	return NULL;
}

DoubleSpring::DoubleSpring(Physics_Engine::PhysicsObject *obj1, Physics_Engine::PhysicsObject *obj2, float _k, float _equilibriumLength)
: Spring()
{
	springType = SpringType_DoubleSpring;

	object1 = obj1;
	object2 = obj2;

	k = _k;
	equilibriumLength = _equilibriumLength;
}

void DoubleSpring::UpdateForces()
{
	Spring::UpdateForces();

	Vector3 Obj1toObj2 = object2->GetPosition() - object1->GetPosition();
	float x = (Obj1toObj2).getLength() - equilibriumLength;
	Obj1toObj2 = Obj1toObj2.normalize();	
	force = k * x;

	if (object1)
		object1->AddForce(force * Obj1toObj2);
	if (object2)
		object2->AddForce(-force * Obj1toObj2);
}

void DoubleSpring::Update(float timeInSecondsSinceLastFrame)
{
	Vector3 obj1Pos = object1->GetPosition();
	Vector3 obj2Pos = object2->GetPosition();

	Vector3 Obj1toObj2 = obj2Pos - obj1Pos;
	float x = (Obj1toObj2).getLength() - equilibriumLength;
	Obj1toObj2 = Obj1toObj2.normalize();

	bool Obj1toObj2IsPositive = Obj1toObj2.X > 0.0f ? true : false;

	Vector3 obj1Vel = object1->GetVelocity();
	Vector3 obj2Vel = object2->GetVelocity();
	Vector3 obj1CurrentSpringVel = obj1Vel.dotProduct(-Obj1toObj2)*-Obj1toObj2;
	Vector3 obj2CurrentSpringVel = obj2Vel.dotProduct(Obj1toObj2)*Obj1toObj2;

	//positiveDirection = Obj1toObj2;
	//
	//force = k * x;

	//object1->AddForce(force * Obj1toObj2);
 //   object2->AddForce(-force * Obj1toObj2);

	float timeRemaining = timeInSecondsSinceLastFrame;
	float timeSkip = timeInSecondsSinceLastFrame;
	while(1)
	{
		force = k * x;

		Vector3 obj1NewSpringVel = force * Obj1toObj2 / object1->GetMass() * timeRemaining + obj1CurrentSpringVel;
		Vector3 obj2NewSpringVel = force * -Obj1toObj2 / object2->GetMass() * timeRemaining + obj2CurrentSpringVel;

		Vector3 obj1NewPos = obj1Pos + (obj1NewSpringVel) * timeRemaining;
		Vector3 obj2NewPos = obj2Pos + (obj2NewSpringVel) * timeRemaining;

		//Must redo
		Vector3 newDirection = (obj2NewPos - obj1NewPos).normalize();
		bool Obj1toObj2NewIsPositive = newDirection.X > 0.0f ? true : false;
		if (newDirection.dotProduct(Obj1toObj2) < 0.0f)
		{
			timeSkip *= 0.5f;
			timeRemaining -= timeSkip;
		}
		else
		{
			//Everything fine get out of loop and return from function
			object1->AddVelocity(obj1NewSpringVel - obj1CurrentSpringVel);
			object2->AddVelocity(obj2NewSpringVel - obj2CurrentSpringVel);
			object1->AddForce(force * Obj1toObj2);
			object2->AddForce(force * -Obj1toObj2);
			object1->SetPosition(obj1NewPos);
			object2->SetPosition(obj2NewPos);
			break;
		}
	}
}

void DoubleSpring::SerializeOut(ostream& os)
{
	Spring::SerializeOut(os);

	os << k << endl;
	os << equilibriumLength << endl;
}
void DoubleSpring::SerializeIn(istream& is)
{
	//Spring::SerializeIn(is);

	is >> k;
	is >> equilibriumLength;
}