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

#ifndef _WX_IRR_PHYSICS_ENGINE
#define _WX_IRR_PHYSICS_ENGINE

#include "PhysicsEngineDefinitions.h"
#include "../Include.h"
#include "./Physics Object/PhysicsObject.h"
#include "./Forces/Force.h"
#include "./Springs/Spring.h"
#include "./Constraints/Constraint.h"

#include "../Serialization/Serialization.h"


//The namespace that will contain all physics capabilities.
namespace Physics_Engine
{
	enum NumericIntegratorType
	{
		NumericIntegratorType_Euler,
		NumericIntegratorType_VerletTimeCorrected
	};

	//The PhysicsEngine itself. Initalize an instance of this in the main function and
	//add/remove objects in this class so that the objects get updated.
	class PhysicsEngine
	{
	private:
		IrrlichtDevice* device;

		NumericIntegratorType numericIntegratorType;
		bool paused;
		float totalTime;
		float oldTimeFramePassed;
		float speed;
		List<PhysicsObject*>* objectList;
		List<PhysicsObject*>* staticObjectList;
		List<PhysicsObject*>* dynamicObjectList;
		//Used to keep track of objects in the static and dynamic object lists.
		List<PhysicsObjectTrackerType*>* objectListTracker;
		List<Force*>* forceList;
		List<Spring*>* springList;
		List<PhysicsString*>* stringList;
		List<Constraint*>* constraintList;

		bool calculateForces;
		bool updatePositions;

		bool canSerialize;
		
		void ResetandAddForces();
		void AddGravitationForces();
		static Vector3 GetGravitationForce(PhysicsObject* first, PhysicsObject* second);
		static Vector3 GetCoulombForce(PhysicsObject* first, PhysicsObject* second);
		void AddCoulombForces();
	public:
		bool simulateGravitation;
		bool simulateMagnetism;


		PhysicsEngine(IrrlichtDevice* _device, NumericIntegratorType _numericIntegratorType = NumericIntegratorType_VerletTimeCorrected);
		~PhysicsEngine();

		void Clear();

		void Update(float timeSinceLastFrame, bool ignorePaused = false);

		void Draw(IrrlichtDevice* device);


		List<PhysicsObjectTrackerType*>::iterator AddPhysicsObject(PhysicsObject* obj, bool deleteData = true);
		PhysicsObject* AddPhysicsObject(wxString _name, bool _enabled = true, bool _charged = false, float _charge = 0.0f, float _mass = 1.0f, Vector3 pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 vel = Vector3(0.0f, 0.0f, 0.0f));
		void RemovePhysicsObject(int index);
		void RemovePhysicsObjectUsingTracker(List<PhysicsObjectTrackerType*>::iterator objTrackerListIt);
		void ClearObjects() { objectList->Clear(); }
		List<Physics_Engine::Spring*>::iterator AddSpring(PhysicsObject* obj1, PhysicsObject* obj2, float _k = 1.0f, float length = 10.0f) { return springList->Add(new DoubleSpring(obj1, obj2, _k, length), true); }
		void RemoveSpring(int index) { springList->Remove(index); }
		void RemoveSpring(List<Physics_Engine::Spring*>::iterator listElem) { springList->Remove(listElem); }
		void ClearSpring() { springList->Clear(); }
		void AddForce(Force* frc) { forceList->Add(frc, true); }
		void RemoveForce(int index) { forceList->Remove(index); }
		void ClearForces() { forceList->Clear(); }
		void AddStringConnection(PhysicsObject* obj1, PhysicsObject* obj2, float length) { stringList->AddFront(new PhysicsString(obj1, obj2, length), true); }
		void RemoveStringConnection(int index) { stringList->Remove(index); }
		void ClearStringConnections() { stringList->Clear(); }
		void AddConstraint(Constraint* constraint) { constraintList->Add(constraint, true); }
		void RemoveConstraint(int index) { constraintList->Remove(index); }
		void ClearConstraints() { constraintList->Clear(); }

		void Pause() { paused = true; }
		void Run() { paused = false; }

		ElectricFieldPotReturnType GetElecFieldPotAtPoint(Vector3 point);

		//Properties
		void ChangeIntegratorType(NumericIntegratorType _numericIntegratorType) { numericIntegratorType = _numericIntegratorType; }
		float GetOldTimeFrame() { return oldTimeFramePassed; }
		float getSpeed() { return speed; }
		void setSpeed(float value) { speed = value; }
		void EnableGravitation() { simulateGravitation = true; }
		void DisableGravitation() { simulateGravitation = false; }
		void EnableMagnetism() { simulateMagnetism = true; }
		void DisableMagnetism() { simulateMagnetism = false; }
		void EnableForceCalculation() { calculateForces = true; }
		void DisableForceCalculation() { calculateForces = false; }
		void EnablePositionUpdating() { updatePositions = true; }
		void DisablePositionUpdating() { updatePositions = false; }

		List<PhysicsObject*>* GetObjectList() { return objectList; }
		List<Spring*>* GetSpringList() { return springList; }
		List<PhysicsObject*>** GetObjectListAddress() { return &objectList; }
		List<Spring*>** GetSpringListAddress() { return &springList; }
		template <class T>
		void ForgetList(List<T*>** list)
		{
			*list = NULL;
			*list = new List<T*>();
		}

		void EnableSerialization() { canSerialize = true; }
		void DisableSerialization() { canSerialize = false; }
		void SerializeInPhysicsObjects(istream &is);
		void SerializeInSprings(istream &is);
		virtual void SerializeIn(istream &is);
		virtual void SerializeOut(ostream &os);
	};
}

#endif