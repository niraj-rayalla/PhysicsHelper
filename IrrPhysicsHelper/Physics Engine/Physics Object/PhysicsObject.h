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

#ifndef _WX_IRR_PhysicsObject
#define _WX_IRR_PhysicsObject

#include "../PhysicsEngineDefinitions.h"
#include "../../Include.h"
#include "../../General/GeneralClasses.h"
#include "./PathDrawableObject.h"

#include "../RecordableEntity.h"

#include "../../Serialization/Serialization.h"

class ElectricFieldPotReturnType
{
public:
	Vector3 electricField;
	float potential;

	ElectricFieldPotReturnType()
	{
		electricField = Vector3(0.0f, 0.0f, 0.0f);
		potential = 0.0f;
	}

	void operator+=(ElectricFieldPotReturnType& value)
	{
		electricField += value.electricField;
		potential += value.potential;
	}
};

namespace Physics_Engine
{
	enum PhysicsObjectType
	{
		PhysicsObjectType_Basic,
		PhysicsObjectType_Visible,
		PhysicsObjectType_Sphere,
		PhysicsObjectType_Cube
	};

	class PhysicsObject : public PathDrawableObject, public RecordableEntity
	{
	protected:
		PhysicsObjectType physicsObjectType;
		wxString name;

		ThreeDArrow* velocityArrow;
		ThreeDArrow* netAccelerationArrow;
		ThreeDArrow* netForceArrow;

		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;
		Vector3 force;
		bool enabled;
		bool charged;
		float mass;
		float charge;
		Vector3 oldPos;

		virtual void SetUp(bool _enabled, bool _charged, float _charge, Vector3 pos, Vector3 _oldPos, Vector3 vel, float _mass, wxString _name)
		{
			velocityArrow = new ThreeDArrow(SColor(255, 255, 0, 0));
			netAccelerationArrow = new ThreeDArrow(SColor(255, 255, 255, 255));
			netForceArrow = new ThreeDArrow(SColor(255, 0, 0, 0));

			enabled= _enabled;
			if (_charge == 0.0f)
			{
				charged = false;
			}
			else
			{
				charged = _charged;
			}
			charge = _charge;

			oldPos = _oldPos;
			position = pos;
			velocity = vel;
			mass = _mass;
			charged = _charged;

			name = _name;
		}
		void PhysicsObjectUpdate(float timeInSecondsSinceLastFrame);
		void PhysicsObjectUpdate(float timeInSecondsSinceLastFrame, float oldTimeInSecondsSinceLastFrame);

	public:
		PhysicsObject();
		PhysicsObject(wxString _name, bool _enabled = true, bool _charged = false, float _charge = 0.0f, float _mass = 1.0f,
			Vector3 pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 vel = Vector3(0.0f, 0.0f, 0.0f), bool setUp = true);
		PhysicsObject(wxString _name, bool _enabled = true, bool _charged = false, float _charge = 0.0f, float _mass = 1.0f,
			Vector3 pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 oldPos = Vector3(0.0f, 0.0f, 0.0f), Vector3 vel = Vector3(0.0f, 0.0f, 0.0f), bool setUp = true);
		virtual ~PhysicsObject();
		virtual void AddForce(Vector3 frc) { force += frc; }
		virtual void AddForceFromAcceleration(Vector3 acc) { force += acc * mass; }
		virtual void SetForceFromAcceleration(Vector3 acc) { force = acc * mass; }
		virtual void Update(float timeInSecondsSinceLastFrame);//, NumericIntegratorType numericIntegratorType = NumericIntegratorType_VerletTimeCorrected);
		virtual void Update(float timeInSecondsSinceLastFrame, float oldTimeInSecondsSinceLastFrame);
		void ResetForce() { force = Vector3(0.0f, 0.0f, 0.0f); }

		virtual void Draw(IVideoDriver* driver);

		void DrawVelocityArrow(IVideoDriver* driver);
		void DrawNetAccelerationArrow(IVideoDriver* driver);
		void DrawNetForceArrow(IVideoDriver* driver);

		ElectricFieldPotReturnType GetElecFieldPotAtPoint(Vector3 point);

		//Properties
		PhysicsObjectType GetPhysicsObjectType() { return physicsObjectType; }
		wxString GetName() { return name; }
		float GetMass() { return mass; }
		bool GetEnabled() { return enabled; }
		Vector3 GetOldPosition() { return oldPos; }
		virtual void SetOldPosition(Vector3& pos) { oldPos = pos; }
		Vector3 GetPosition() { return position; }
		Vector3* GetPositionPointer() { return &position; }
		virtual void SetPosition(Vector3& pos) { position = pos; }
		Vector3 GetVelocity() { return velocity; }
		Vector3* GetVelocityPointer() { return &velocity; }
		void AddVelocity(Vector3 vel) { velocity += vel; }
		Vector3 GetAcceleration() { return acceleration; }
		Vector3* GetAccelerationPointer() { return &acceleration; }
		Vector3 GetForce() { return force; }
		Vector3* GetForcePointer() { return &force; }
		bool GetCharged() { return charged; }
		float GetCharge() { return charge; }
		void Enable() { enabled = true; }
		void Disable() { enabled = false; }

		virtual void SerializeOut(ostream& os);
		virtual void SerializeIn(istream& is);

		friend ostream& operator<<(ostream& os, PhysicsObject& obj)
		{
			obj.SerializeOut(os);

			return os;
		}
		friend istream& operator>>(istream& is, PhysicsObject& obj)
		{
			obj.SerializeIn(is);

			return is;
		}
	};

	class VisiblePhysicsObject : public PhysicsObject
	{
	protected:
		ISceneNode* node;

	public:
		VisiblePhysicsObject(wxString _name, bool _enabled = true, bool _charged = false, float _charge = 0.0f, float _mass = 1.0f,
			Vector3 pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 vel = Vector3(0.0f, 0.0f, 0.0f));
		VisiblePhysicsObject(wxString _name, bool _enabled, bool _charged, float _charge, float _mass,
			Vector3 pos, Vector3 oldPos, Vector3 vel);
		virtual ~VisiblePhysicsObject();

		void ChangeObjectColor(SColor& color);

		void SetPosition(Vector3 pos);

		ISceneNode* GetSceneNode() { return node; }

		virtual void CreateVisibleNode(ISceneManager* smgr) {}
	};

	class SimulationObject_Sphere : public VisiblePhysicsObject
	{
	private:
		float radius;
	public:
		SimulationObject_Sphere();
		SimulationObject_Sphere(ISceneManager* smgr, wxString _name, bool _enabled = true, bool _charged = false, float _charge = 0.0f, float _mass = 1.0f,
			Vector3 pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 vel = Vector3(0.0f, 0.0f, 0.0f), float _radius = 1.0f);
		SimulationObject_Sphere(ISceneManager* smgr, wxString _name, bool _enabled, bool _charged, float _charge, float _mass,
			Vector3 pos, Vector3 oldPos, Vector3 vel, float _radius);
		~SimulationObject_Sphere();

		void Update(float timeInSecondsSinceLastFrame);
		void Update(float timeInSecondsSinceLastFrame, float oldTimeInSecondsSinceLastFrame);

		void CreateVisibleNode(ISceneManager* smgr);

		void SerializeOut(ostream& os);
		void SerializeIn(istream& is);

		float GetRadius() { return radius; }
	};

	class SimulationObject_Cube : public VisiblePhysicsObject
	{
	private:
		float length;
	public:
		SimulationObject_Cube();
		SimulationObject_Cube(ISceneManager* smgr, wxString _name, bool _enabled = true, bool _charged = false, float _charge = 0.0f, float _mass = 1.0f,
			Vector3 pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 vel = Vector3(0.0f, 0.0f, 0.0f), float _length = 1.0f);
		SimulationObject_Cube(ISceneManager* smgr, wxString _name, bool _enabled, bool _charged, float _charge, float _mass,
			Vector3 pos, Vector3 oldPos, Vector3 vel, float _length);
		~SimulationObject_Cube();

		void Update(float timeInSecondsSinceLastFrame);
		void Update(float timeInSecondsSinceLastFrame, float oldTimeInSecondsSinceLastFrame);

		void SerializeOut(ostream& os);
		void SerializeIn(istream& is);

		float GetLength() { return length; }
	};




	class PhysicsObjectTrackerType
	{
	public:
		List<PhysicsObject*>::iterator objectListIt;
		List<PhysicsObject*>::iterator objectListTrackerIt;

		PhysicsObjectTrackerType()
		{
			objectListIt = NULL;
			objectListTrackerIt = NULL;
		}
	};
}

#endif