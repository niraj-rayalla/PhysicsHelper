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

#ifndef WX_IRR_IRRLICHT_TO_BULLET_CONNECTOR
#define WX_IRR_IRRLICHT_TO_BULLET_CONNECTOR

#include "../IrrlichtInclude.h"
#include "../Physics Engine/PhysicsEngineInclude.h"
#include "../General/GeneralClasses.h"
#include "btBulletDynamicsCommon.h"

using namespace Physics_Engine;

#include "IrrlichtToBulletObjects.h"

enum IrrlichtToBulletEntityListPointerType
{
	IrrlichtToBulletEntityListPointerType_Object,
	IrrlichtToBulletEntityListPointerType_Spring,
	IrrlichtToBulletEntityListPointerType_Constraint
};

class IrrlichtToBulletEntityListPointer
{
public:
	void* entityListPointer;
	IrrlichtToBulletEntityListPointerType entityType;

	IrrlichtToBulletEntityListPointer(void* _entityListPointer, IrrlichtToBulletEntityListPointerType _entityType)
	{
		entityListPointer = _entityListPointer;
		entityType = _entityType;
	}
};

class IrrlichtToBulletConnector
{
private:
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

public:
	List<IrrlichtToBulletObjectStorage*>* objectList;
	List<btCollisionShape*>* customCollisionShapeList;
	List<IrrlichtBulletConstraint*>* constraintList;
	List<IrrlichtBulletSpring*>* springList;

	List<IrrlichtToBulletEntityListPointer*> entityTrackerList;

	//Collision shapes
	btCollisionShape* sphereShape;
	btCollisionShape* cubeShape;

	IrrlichtToBulletConnector();
	~IrrlichtToBulletConnector();

	void AddRigidBody(wxString name, ISceneNode* _node);
	void AddRigidBody(IrrlichtToBulletObjectStorage* obj, PhysicsEngine* _physicsEngine);
	void AddCustomCollisionShape(btCollisionShape* collShape);

	void RemoveEntity(int index, PhysicsEngine* physicsEngine);
	void ClearEntities(PhysicsEngine* physicsEngine);

	void Update(float totalTime, float timeInSecondsSinceLastFrame, bool isRecording,
		List<IrrlichtToBulletDynamicObject*>* recordingObjects = 0);

	void Draw(IVideoDriver* driver);

	void Reset();

	void Record(float totalTime, bool isRecording, List<IrrlichtToBulletDynamicObject*>* recordingObjects);

	void SetVisibilityVelocityArrow(bool isVisible) 
	{
		foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
		{
			IrrlichtToBulletObjectStorage* data = objIt->GetData();
			if (data->objType == IrrlichtBulletObjectType_Dynamic)
				((IrrlichtToBulletDynamicObject*)data)->SetVelocityArrowVisibility(isVisible);
		}
	}
	void SetVisibilityAngularVelocityArrow(bool isVisible)
	{
		foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
		{
			IrrlichtToBulletObjectStorage* data = objIt->GetData();
			if (data->objType == IrrlichtBulletObjectType_Dynamic)
				((IrrlichtToBulletDynamicObject*)data)->SetAngularVelocityArrowVisibility(isVisible);
		}
	}
	void SetVisibilityAccelerationArrow(bool isVisible) 
	{
		foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
		{
			IrrlichtToBulletObjectStorage* data = objIt->GetData();
			if (data->objType == IrrlichtBulletObjectType_Dynamic)
				((IrrlichtToBulletDynamicObject*)data)->SetAccelerationArrowVisibility(isVisible);
		}
	}
	void SetVisibilityForceArrow(bool isVisible) 
	{
		foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
		{
			IrrlichtToBulletObjectStorage* data = objIt->GetData();
			if (data->objType == IrrlichtBulletObjectType_Dynamic)
				((IrrlichtToBulletDynamicObject*)data)->SetForceArrowVisibility(isVisible);
		}
	}

	void ChangeVelocityArrowColor(SColor& color) 
	{ 
		IrrlichtToBulletDynamicObject::ChangeArrowColors(ArrowType_Velocity, color);
		foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
		{
			IrrlichtToBulletObjectStorage* data = objIt->GetData();
			if (data->objType == IrrlichtBulletObjectType_Dynamic)
			{
				ThreeDArrow* velArrow = ((IrrlichtToBulletDynamicObject*)data)->GetVelocityArrow();
				if (velArrow)
					velArrow->ChangeColor(color);
			}
		}
	}
	void ChangeAngularVelocityArrowColor(SColor& color) 
	{ 
		IrrlichtToBulletDynamicObject::ChangeArrowColors(ArrowType_AngularVelocity, color);
		foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
		{
			IrrlichtToBulletObjectStorage* data = objIt->GetData();
			if (data->objType == IrrlichtBulletObjectType_Dynamic)
			{
				ThreeDArrow* angVelArrow = ((IrrlichtToBulletDynamicObject*)data)->angularVelocityArrow;
				if (angVelArrow)
					angVelArrow->ChangeColor(color);
			}
		}
	}
	void ChangeAccelerationArrowColor(SColor& color) 
	{ 
		IrrlichtToBulletDynamicObject::ChangeArrowColors(ArrowType_Acceleration, color);
		foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
		{
			IrrlichtToBulletObjectStorage* data = objIt->GetData();
			if (data->objType == IrrlichtBulletObjectType_Dynamic)
			{
				ThreeDArrow* accArrow = ((IrrlichtToBulletDynamicObject*)data)->accelerationArrow;
				if (accArrow)
					accArrow->ChangeColor(color);
			}
		}
	}
	void ChangeForceArrowColor(SColor& color) 
	{ 
		IrrlichtToBulletDynamicObject::ChangeArrowColors(ArrowType_Force, color);
		foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
		{
			IrrlichtToBulletObjectStorage* data = objIt->GetData();
			if (data->objType == IrrlichtBulletObjectType_Dynamic)
			{
				ThreeDArrow* frcArrow = ((IrrlichtToBulletDynamicObject*)data)->forceArrow;
				if (frcArrow)
					frcArrow->ChangeColor(color);
			}
		}
	}

	IrrlichtToBulletObjectStorage* FindObjectWithSceneNode(ISceneNode* node);

	void AddConstraint(IrrlichtBulletConstraint* constraintData, btTypedConstraint* constraint)
	{
		constraintData->listNodePointer = constraintList->Add(constraintData);
		void* addedPtr = constraintData->listNodePointer;
		entityTrackerList.Add(new IrrlichtToBulletEntityListPointer(addedPtr, IrrlichtToBulletEntityListPointerType_Constraint));
		dynamicsWorld->addConstraint(constraint);
	}

	void RemoveConstraint(List<IrrlichtBulletConstraint*>::iterator& constraintIt)
	{
		if (constraintIt)
		{
			dynamicsWorld->removeConstraint(constraintIt->GetData()->GetConstraint());
			constraintList->Remove(constraintIt);
		}
	}

	void AddSpring(SpringSceneNode* springNode, float k, List<Physics_Engine::Spring*>::iterator _springListElem)
	{
		void* addedPtr = springList->Add(new IrrlichtBulletSpring(springNode, k, _springListElem));
		entityTrackerList.Add(new IrrlichtToBulletEntityListPointer(addedPtr, IrrlichtToBulletEntityListPointerType_Spring));
	}

	void RemoveSpring(List<IrrlichtBulletSpring*>::iterator& springIt, PhysicsEngine*& physicsEngine)
	{
		if (springIt)
		{
			physicsEngine->RemoveSpring(springIt->GetData()->springListElem);
			springList->Remove(springIt);
		}
	}
};

#endif