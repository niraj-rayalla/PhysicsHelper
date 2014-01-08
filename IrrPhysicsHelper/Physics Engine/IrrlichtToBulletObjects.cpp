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

#include "IrrlichtToBulletObjects.h"

btDiscreteDynamicsWorld* IrrlichtToBulletObjectStorage::dynamicsWorld = NULL;
bool IrrlichtToBulletDynamicObject::showVelocity = false;
bool IrrlichtToBulletDynamicObject::showAngularVelocity = false;
bool IrrlichtToBulletDynamicObject::showNetAcceleration = false;
bool IrrlichtToBulletDynamicObject::showNetForce = false;
SColor IrrlichtToBulletDynamicObject::velocityArrowColor = SColor(255,255,255,255);
SColor IrrlichtToBulletDynamicObject::angularVelocityArrowColor = SColor(255,255,255,255);
SColor IrrlichtToBulletDynamicObject::accelerationArrowColor = SColor(255,0,255,0);
SColor IrrlichtToBulletDynamicObject::forceArrowColor = SColor(255,255,0,0);

btVector3 IrrlichtToBulletVector3(Vector3& input)
{
	return btVector3(input.X, input.Y, input.Z);
}

Vector3 BulletToIrrlichtVector3(btVector3& input)
{
	return Vector3(input.x(), input.y(), input.z());
}

Vector3 BulletToIrrlichtVector3(const btVector3& input)
{
	return Vector3(input.x(), input.y(), input.z());
}



void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler)
{
   btScalar W = TQuat.getW();
   btScalar X = TQuat.getX();
   btScalar Y = TQuat.getY();
   btScalar Z = TQuat.getZ();
   float WSquared = W * W;
   float XSquared = X * X;
   float YSquared = Y * Y;
   float ZSquared = Z * Z;
   TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
   TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
   TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
   TEuler *= RADTODEG;
}

btQuaternion EulerToQuaternion(Vector3& vec)
{
	btQuaternion quat(vec.Z, vec.Y, vec.X);
	return quat;
}



void IrrlichtToBulletObjectStorage::SerializeOut(ostream& os)
{
	os << specificObjType << endl;
	SerializeOutWxString(os, name);
	if (node)
	{
		SerializeOutVector3(os, node->getAbsolutePosition());
		Vector3 rot = node->getRotation();
		SerializeOutVector3(os, rot);
	}
	else
	{
		Vector3 zeroVec = Vector3(0.0f, 0.0f, 0.0f);
		SerializeOutVector3(os, zeroVec);
		SerializeOutVector3(os, zeroVec);
	}
}
void IrrlichtToBulletObjectStorage::SerializeIn(istream& is)
{
	name = SerializeInWxString(is);
	nodePos = SerializeInVector3(is);
	nodeRot = SerializeInVector3(is);
}


IrrlichtToBulletDynamicObject* CastToDynamicObject(IrrlichtToBulletObjectStorage* obj)
{
	if (obj->objType == IrrlichtBulletObjectType_Dynamic)
		return (IrrlichtToBulletDynamicObject*)obj;

	return NULL;
}

void IrrlichtToBulletDynamicObject::Update()
{
	if (node)
	{
		btVector3 pos = body->getWorldTransform().getOrigin();
		Vector3 irrPos = Vector3(pos.x(), pos.y(), pos.z());
		node->setPosition(irrPos);
		position = irrPos;

		btVector3 rotAxis;
		QuaternionToEuler(body->getWorldTransform().getRotation(), rotAxis);
		node->setRotation(Vector3(rotAxis.getX(), rotAxis.getY(), rotAxis.getZ()));

		btVector3 vel = body->getLinearVelocity();
		Vector3 irrVel = BulletToIrrlichtVector3(vel);
		velocity = irrVel;
		if (velocityArrow)
			velocityArrow->Update(irrPos, irrVel);

		btVector3 angVel = body->getAngularVelocity();
		Vector3 irrAngVel = BulletToIrrlichtVector3(angVel);
		if (angularVelocityArrow)
			angularVelocityArrow->Update(irrPos, irrAngVel);

		btVector3 frc = body->getTotalForce();
		Vector3 irrFrc = BulletToIrrlichtVector3(frc);
		force = irrFrc;
		if (accelerationArrow)
			accelerationArrow->Update(irrPos, irrFrc/mass);

		if (forceArrow)
			forceArrow->Update(irrPos, irrFrc);
	}

	if (objectGUI)
	{
		objectGUI->UpdatePosition(position);
		objectGUI->UpdateVelocity(velocity);
		objectGUI->UpdateForce(force);
	}
}