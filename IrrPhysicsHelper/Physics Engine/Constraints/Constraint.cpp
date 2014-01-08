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

#include "Constraint.h"

using namespace Physics_Engine;

DistanceConstraint::DistanceConstraint(PhysicsObject* _obj1, PhysicsObject* _obj2, float _constraintLength, DistanceConstraintMovableObject _moveDirection)
{
	obj1 = _obj1;
	obj2 = _obj2;

	constraintLength = _constraintLength;

	moveDirection = _moveDirection;
}

void DistanceConstraint::Update(float timeInSecondsSinceLastFrame)
{
	Vector3 obj1Pos = obj1->GetPosition();
	Vector3 obj2Pos = obj2->GetPosition();

	if (moveDirection == DCMO_Obj1)
	{
		Vector3 Obj2toObj1 = obj1Pos - obj2Pos;
		float ratio = constraintLength / Obj2toObj1.getLength();
		Obj2toObj1 *= ratio;

		obj1->SetPosition(obj2Pos + Obj2toObj1);
	}
	else
	{
		Vector3 Obj1toObj2 = obj2Pos - obj1Pos;
		float length = Obj1toObj2.getLength();
		Obj1toObj2 /= length;
		Vector3 correctionVector = Obj1toObj2 * (length-constraintLength);
		Vector3 correctionVectorHalf = correctionVector * 0.5f;
		float ratio = constraintLength / Obj1toObj2.getLength();
		Obj1toObj2 *= ratio;

		obj2->SetPosition(obj2Pos - correctionVector);
	}
}

PhysicsString::PhysicsString(Physics_Engine::PhysicsObject *_obj1, Physics_Engine::PhysicsObject *_obj2, float _length)
{
	obj1 = _obj1;
	obj2 = _obj2;

	frcAfter = new ForceAfter(new DirectionalForce(Vector3_Zero), obj1);

	length = _length;
}
Vector3 PhysicsString::frcAfterTension = Vector3_Zero;

PhysicsString::~PhysicsString()
{
	delete frcAfter;
}

void PhysicsString::Update(float timeInSecondsSinceLastFrame)
{
	Vector3 obj1Pos = obj1->GetPosition();
	Vector3 obj2Pos = obj2->GetPosition();

	Vector3 Obj2toObj1 = (obj1Pos - obj2Pos);
	Obj2toObj1.normalize();


	/*Obj1toObj2 = Obj1toObj2.normalize();
	Vector3 frc = obj2->GetForce();
	float theta = acosf(Obj1toObj2.dotProduct(frc) / frc.getLength());

	obj1->AddForce(frc.getLength() * cosf(theta) * Obj1toObj2);
	obj2->AddForce(-frc.getLength() * cosf(theta) * Obj1toObj2 + -Obj1toObj2*obj2->GetVelocity().getLength() * obj2->GetVelocity().getLength() * obj2->GetMass() / length);*/


	/*float Obj1toObj2Length = Obj1toObj2.getLength();
	Obj1toObj2 /= Obj1toObj2Length;*/
	Vector3 frc = obj2->GetForce();
	float tension = Obj2toObj1.dotProduct(frc);

	tensionVector = tension * Obj2toObj1;
	
	Vector3 tangetTension = frc - tensionVector;
	tangetTension.normalize();
	float tangetVelocity = tangetTension.dotProduct(obj2->GetVelocity());
	//obj2->AddForce(-Obj1toObj2 * tangetVelocity * tangetVelocity * obj2->GetMass() / length);
	//obj2->temp = -tension * Obj1toObj2;

	centripital = Obj2toObj1 * tangetVelocity * tangetVelocity * obj2->GetMass() / length;
	//tensionVector += Obj1toObj2 * tangetVelocity * tangetVelocity * obj2->GetMass() / length;

	obj1->AddForce(tensionVector-centripital);
	//((DirectionalForce*)frcAfter->force)->ChangeDirection(tensionVector);
	obj2->AddForce(-tensionVector+centripital);
}

void PhysicsString::UpdateAfter()
{
	//obj2->AddForce(-tensionVector+centripital);
	////frcAfter->force->AddForcetoObject(*(obj1));

	//Vector3 tempVec = PhysicsString::frcAfterTension;
	//tensionVector.normalize();
	//float dot = tempVec.dotProduct(tensionVector);
	//obj2->AddForce(PhysicsString::frcAfterTension - tensionVector * abs(dot));

	//if (obj1->GetEnabled())
	//{
	//	PhysicsString::frcAfterTension = ((DirectionalForce*)frcAfter->force)->GetDirection();
	//}
	//else
	//{
	//	PhysicsString::frcAfterTension = Vector3_Zero;
	//}
}

void PhysicsString::Draw(IVideoDriver* driver)
{
	driver->draw3DLine(obj1->GetPosition(), obj2->GetPosition(), SColor(255, 0, 0, 0));

	/*driver->draw3DLine(obj1->GetPosition(), obj1->GetPosition() + tensionVector, SColor(255, 255, 0, 0));
	driver->draw3DLine(obj2->GetPosition(), obj2->GetPosition() - tensionVector, SColor(255, 255, 0, 0));*/
}