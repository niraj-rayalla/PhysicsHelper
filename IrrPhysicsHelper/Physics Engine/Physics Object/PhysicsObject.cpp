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

#include "PhysicsObject.h"

using namespace Physics_Engine;

///PhysicsObject
PhysicsObject::PhysicsObject()
	: PathDrawableObject(), RecordableEntity()
{
	velocityArrow = NULL;
	netAccelerationArrow = NULL;
	netForceArrow = NULL;
}

PhysicsObject::PhysicsObject(wxString _name, bool _enabled, bool _charged, float _charge, float _mass,
	Vector3 pos, Vector3 vel, bool setUp) : PathDrawableObject(), RecordableEntity()
{
	if (setUp)
	{
		SetUp(_enabled, _charged, _charge, pos, pos, vel, _mass, _name);
	}
	else
	{
		velocityArrow = new ThreeDArrow(SColor(255, 255, 0, 0));
		netAccelerationArrow = new ThreeDArrow(SColor(255, 255, 255, 255));
		netForceArrow = new ThreeDArrow(SColor(255, 0, 0, 0));
	}

	physicsObjectType = PhysicsObjectType_Basic;
}

PhysicsObject::PhysicsObject(wxString _name, bool _enabled, bool _charged, float _charge, float _mass,
			Vector3 pos, Vector3 _oldPos, Vector3 vel, bool setUp) : PathDrawableObject(), RecordableEntity()
{
	
	if (setUp)
	{
		SetUp(_enabled, _charged, _charge, pos, pos, vel, _mass, _name);
	}
	else
	{
		velocityArrow = new ThreeDArrow(SColor(255, 255, 0, 0));
		netAccelerationArrow = new ThreeDArrow(SColor(255, 255, 255, 255));
		netForceArrow = new ThreeDArrow(SColor(255, 0, 0, 0));
	}
	oldPos = _oldPos;
}

PhysicsObject::~PhysicsObject()
{
	delete velocityArrow;
	delete netAccelerationArrow;
	delete netForceArrow;
}

void PhysicsObject::PhysicsObjectUpdate(float timeInSecondsSinceLastFrame)
{
	oldPos = position;

    acceleration = force / mass;

    velocity += acceleration * timeInSecondsSinceLastFrame;
	position += velocity * timeInSecondsSinceLastFrame;	
}

void PhysicsObject::Update(float timeInSecondsSinceLastFrame)//, NumericIntegratorType numericIntegratorType)
{
	if (enabled)
	{
		PhysicsObjectUpdate(timeInSecondsSinceLastFrame);

		UpdatePath(position);
	}
}

void PhysicsObject::PhysicsObjectUpdate(float timeInSecondsSinceLastFrame, float oldTimeInSecondsSinceLastFrame)
{
	//Verlet time corrected
	Vector3 tempOldPos = position;

	//make sure oldPos has the right value.
	if (oldPos == position)
	{
		oldPos = position - ((velocity - acceleration * oldTimeInSecondsSinceLastFrame) * oldTimeInSecondsSinceLastFrame + 0.5f * acceleration * timeInSecondsSinceLastFrame * timeInSecondsSinceLastFrame);
	}

    acceleration = force / mass;

	position += (position - oldPos) * (timeInSecondsSinceLastFrame / oldTimeInSecondsSinceLastFrame) + acceleration * timeInSecondsSinceLastFrame * timeInSecondsSinceLastFrame;

	oldPos = tempOldPos;
    velocity = (position - oldPos) / timeInSecondsSinceLastFrame;
}

void PhysicsObject::Update(float timeInSecondsSinceLastFrame, float oldTimeInSecondsSinceLastFrame)
{
	if (enabled)
	{
		PhysicsObjectUpdate(timeInSecondsSinceLastFrame, oldTimeInSecondsSinceLastFrame);

		UpdatePath(position);
	}
}

void PhysicsObject::Draw(IVideoDriver* driver)
{
}

void PhysicsObject::DrawVelocityArrow(IVideoDriver* driver)
{
	velocityArrow->Update(GetPosition(), acceleration);
	velocityArrow->Draw(driver);
}

void PhysicsObject::DrawNetAccelerationArrow(IVideoDriver* driver)
{
	netAccelerationArrow->Update(GetPosition(), acceleration);
	netAccelerationArrow->Draw(driver);
}

void PhysicsObject::DrawNetForceArrow(IVideoDriver* driver)
{
	netForceArrow->Update(GetPosition(), acceleration);
	netForceArrow->Draw(driver);
}

ElectricFieldPotReturnType PhysicsObject::GetElecFieldPotAtPoint(Vector3 point)
{
	ElectricFieldPotReturnType retValue;

	if (charged)
	{
		Vector3 direction = point - position;
		float lengthSquared = direction.getLengthSQ();
		float length = sqrt(lengthSquared);
		//normalize it
		direction /= length;

		float magnitude = (charge * Physics_Engine::k / lengthSquared);

		retValue.electricField += magnitude * direction;
		retValue.potential += magnitude;// * length;
	}

	return retValue;
}

void PhysicsObject::SerializeOut(ostream& os)
{
	os << physicsObjectType << endl;
	SerializeOutWxString(os, name);

	SerializeOutVector3(os, position);
	SerializeOutVector3(os, oldPos);
	SerializeOutVector3(os, velocity);
	SerializeOutVector3(os, force);

	os << enabled << endl;
	os << charged << endl;
	os << mass << endl;
	os << charge << endl;
}
void PhysicsObject::SerializeIn(istream& is)
{
	name = SerializeInWxString(is);

	position = SerializeInVector3(is);
	oldPos = SerializeInVector3(is);
	velocity = SerializeInVector3(is);
	force = SerializeInVector3(is);

	is >> enabled;
	is >> charged;
	is >> mass;
	is >> charge;
}



VisiblePhysicsObject::VisiblePhysicsObject(wxString _name, bool _enabled, bool _charged , float _charge, float _mass, Vector3 pos, Vector3 vel)
	: PhysicsObject(_name, _enabled, _charged, _charge, _mass, pos, vel, true)
{
	node = NULL;
	physicsObjectType = PhysicsObjectType_Visible;
}

VisiblePhysicsObject::VisiblePhysicsObject(wxString _name, bool _enabled, bool _charged , float _charge, float _mass, Vector3 pos, Vector3 oldPos, Vector3 vel)
	: PhysicsObject(_name, _enabled, _charged, _charge, _mass, pos, oldPos, vel)
{
	node = NULL;
	physicsObjectType = PhysicsObjectType_Visible;
}

VisiblePhysicsObject::~VisiblePhysicsObject()
{
	if(node)
		node->remove();
}

void VisiblePhysicsObject::ChangeObjectColor(SColor& color)
{
	SMaterial mat = node->getMaterial(0);
	mat.DiffuseColor = color;
	mat.ColorMaterial = ECM_DIFFUSE;

	node->getSceneManager()->getMeshManipulator()->setVertexColors(((IMeshSceneNode*)node)->getMesh(), color);
}

void VisiblePhysicsObject::SetPosition(Vector3 pos)
{
	PhysicsObject::SetPosition(pos);

	node->setPosition(pos);
}

//SimulationObject_Sphere
SimulationObject_Sphere::SimulationObject_Sphere() : VisiblePhysicsObject(_(""))
{
	physicsObjectType = PhysicsObjectType_Sphere;
}

SimulationObject_Sphere::SimulationObject_Sphere(irr::scene::ISceneManager *smgr, wxString _name, bool _enabled, bool _charged, float _charge, float _mass, Vector3 pos, Vector3 vel, float _radius)
: VisiblePhysicsObject(_name, _enabled, _charged, _charge, _mass, pos, vel)
{
	radius = _radius;

	node = smgr->addSphereSceneNode(_radius);
	node->setPosition(position);

	physicsObjectType = PhysicsObjectType_Sphere;
}

SimulationObject_Sphere::SimulationObject_Sphere(irr::scene::ISceneManager *smgr, wxString _name, bool _enabled, bool _charged, float _charge, float _mass,
	Vector3 pos, Vector3 oldPos, Vector3 vel, float _radius)
	: VisiblePhysicsObject(_name, _enabled, _charged, _charge, _mass, pos, oldPos, vel)
{
	radius = _radius;

	node = smgr->addSphereSceneNode(_radius);
	node->setPosition(position);

	physicsObjectType = PhysicsObjectType_Sphere;
}

SimulationObject_Sphere::~SimulationObject_Sphere()
{
}

void SimulationObject_Sphere::Update(float timeInSecondsSinceLastFrame)
{
	PhysicsObject::Update(timeInSecondsSinceLastFrame);

}

void SimulationObject_Sphere::Update(float timeInSecondsSinceLastFrame, float oldTimeInSecondsSinceLastFrame)
{
	PhysicsObject::Update(timeInSecondsSinceLastFrame, oldTimeInSecondsSinceLastFrame);

	node->setPosition(position);
}

void SimulationObject_Sphere::CreateVisibleNode(ISceneManager* smgr)
{
	node = smgr->addSphereSceneNode(radius);
	node->setPosition(position);
}

void SimulationObject_Sphere::SerializeOut(ostream& os)
{
	PhysicsObject::SerializeOut(os);

	os << radius << endl;
}

void SimulationObject_Sphere::SerializeIn(istream& is)
{
	PhysicsObject::SerializeIn(is);

	is >> radius;

	/*node = smgr->addSphereSceneNode(radius);
	node->setPosition(position);*/
}

//SimulationObject_Cube
SimulationObject_Cube::SimulationObject_Cube() : VisiblePhysicsObject(_(""))
{
	physicsObjectType = PhysicsObjectType_Cube;
}

SimulationObject_Cube::SimulationObject_Cube(irr::scene::ISceneManager *smgr, wxString _name, bool _enabled, bool _charged, float _charge, float _mass, Vector3 pos, Vector3 vel, float _length)
: VisiblePhysicsObject(_name, _enabled, _charged, _charge, _mass, pos, vel)
{
	length = _length;

	node = smgr->addCubeSceneNode(_length);
	node->setPosition(position);
	physicsObjectType = PhysicsObjectType_Cube;
}

SimulationObject_Cube::SimulationObject_Cube(irr::scene::ISceneManager *smgr, wxString _name, bool _enabled, bool _charged, float _charge, float _mass,
	Vector3 pos, Vector3 oldPos, Vector3 vel, float _length)
	: VisiblePhysicsObject(_name, _enabled, _charged, _charge, _mass, pos, oldPos, vel)
{
	length = _length;

	node = smgr->addCubeSceneNode(_length);
	node->setPosition(position);
	physicsObjectType = PhysicsObjectType_Cube;
}

SimulationObject_Cube::~SimulationObject_Cube()
{
}

void SimulationObject_Cube::Update(float timeInSecondsSinceLastFrame)
{
	PhysicsObject::Update(timeInSecondsSinceLastFrame);
}

void SimulationObject_Cube::Update(float timeInSecondsSinceLastFrame, float oldTimeInSecondsSinceLastFrame)
{
	PhysicsObject::Update(timeInSecondsSinceLastFrame, oldTimeInSecondsSinceLastFrame);

	node->setPosition(position);
}

void SimulationObject_Cube::SerializeOut(ostream& os)
{
	PhysicsObject::SerializeOut(os);

	os << length << endl;
}

void SimulationObject_Cube::SerializeIn(istream& is)
{
	PhysicsObject::SerializeIn(is);

	is >> length;

	/*node = smgr->addSphereSceneNode(radius);
	node->setPosition(position);*/
}