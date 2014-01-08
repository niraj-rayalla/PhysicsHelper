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

#include "IrrlichtToBulletConnector.h"

IrrlichtToBulletConnector::IrrlichtToBulletConnector()
{
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0.0f, -9.8f, 0.0f));

	IrrlichtToBulletObjectStorage::SetDynamicWorld(dynamicsWorld);


	objectList = new List<IrrlichtToBulletObjectStorage*>();
	constraintList = new List<IrrlichtBulletConstraint*>();
	springList = new List<IrrlichtBulletSpring*>();

	//Shape Initialization
	customCollisionShapeList = new List<btCollisionShape*>();
	sphereShape = new btSphereShape(1.0f);
	cubeShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
}

IrrlichtToBulletConnector::~IrrlichtToBulletConnector()
{
	delete sphereShape;
	delete cubeShape;

	delete objectList;
	delete customCollisionShapeList;
	foreach(IrrlichtBulletConstraint*, constraintIt, constraintList)
	{
		//dynamicsWorld->removeConstraint(constraintIt->GetData()->GetConstraint());
	}
	delete constraintList;
	delete springList;

	//delete dynamics world
	delete dynamicsWorld;
	//delete solver
	delete solver;
	//delete broadphase
	delete overlappingPairCache;
	//delete dispatcher
	delete dispatcher;
	delete collisionConfiguration;
}

void IrrlichtToBulletConnector::AddRigidBody(wxString name, ISceneNode* _node)
{
	IrrlichtToBulletObjectStorage* obj = new IrrlichtToBulletObjectStorage(name, _node);
	obj->listNodePointer = objectList->Add(obj);
	void* addedPtr = obj->listNodePointer;
	entityTrackerList.Add(new IrrlichtToBulletEntityListPointer(addedPtr, IrrlichtToBulletEntityListPointerType_Object));
	//_body->setRestitution(0.4f);
	//dynamicsWorld->addRigidBody(_body);

	///*if(_node)
	//	_physicsEngine->AddPhysicsObject(obj, false);*/
}

void IrrlichtToBulletConnector::AddRigidBody(IrrlichtToBulletObjectStorage* obj, PhysicsEngine* _physicsEngine)
{
	obj->listNodePointer = objectList->Add(obj);
	void* addedPtr = obj->listNodePointer;
	entityTrackerList.Add(new IrrlichtToBulletEntityListPointer(addedPtr, IrrlichtToBulletEntityListPointerType_Object));

	if (obj->objType == IrrlichtBulletObjectType_Dynamic)
	{
		IrrlichtToBulletDynamicObject* dynObj = (IrrlichtToBulletDynamicObject*)obj;
		dynObj->body->setRestitution(0.4f);
		dynamicsWorld->addRigidBody(dynObj->body);

		if(dynObj->node)
			obj->physicsObjectTrackerListIt = _physicsEngine->AddPhysicsObject(dynObj, false);
	}
	else if (obj->objType == IrrlichtBulletObjectType_Static)
	{
		IrrlichtToBulletStaticObject* statObj = (IrrlichtToBulletStaticObject*)obj;
		statObj->body->setRestitution(0.4f);
		dynamicsWorld->addRigidBody(statObj->body);
	}
}

void IrrlichtToBulletConnector::AddCustomCollisionShape(btCollisionShape* collShape)
{
	customCollisionShapeList->Add(collShape);
}

void IrrlichtToBulletConnector::RemoveEntity(int index, PhysicsEngine* physicsEngine)
{
	Node<IrrlichtToBulletEntityListPointer*>* entityIt = entityTrackerList.GetAt(index);
	IrrlichtToBulletEntityListPointer* entityPtr = entityIt->GetData();

	switch(entityPtr->entityType)
	{
	case IrrlichtToBulletEntityListPointerType_Object:
		{
			List<IrrlichtToBulletObjectStorage*>::iterator objectListElem = ((List<IrrlichtToBulletObjectStorage*>::iterator)entityPtr->entityListPointer);
			IrrlichtToBulletObjectStorage* irrBullObj = objectListElem->GetData();
			ISceneNode* irrBullObjSceneNode = irrBullObj->node;

			//delete connected springs
			List<List<IrrlichtBulletSpring*>::iterator>* springRemoveList = new List<List<IrrlichtBulletSpring*>::iterator>();

			foreach(IrrlichtBulletSpring*, springIt, springList)
			{
				IrrlichtBulletSpring* irrBullSpring = springIt->GetData();

				if (irrBullObjSceneNode == irrBullSpring->node->GetSceneNode1() || irrBullObjSceneNode == irrBullSpring->node->GetSceneNode2())
				{
					springRemoveList->Add(springIt, false);
				}
			}
			foreach(List<IrrlichtBulletSpring*>::iterator, removeSpringIt, springRemoveList)
			{
				List<IrrlichtBulletSpring*>::iterator springIT = removeSpringIt->GetData();
				RemoveSpring(springIT, physicsEngine);

				List<IrrlichtToBulletEntityListPointer*>* enityListPointer = &entityTrackerList;
				foreach(IrrlichtToBulletEntityListPointer*, entitySpringIt, enityListPointer)
				{
					if (entitySpringIt->GetData()->entityListPointer == springIT)
					{
						entityTrackerList.Remove(entitySpringIt);
						break;
					}
				}
			}

			delete springRemoveList;

			//delete connected constraints
			List<List<IrrlichtBulletConstraint*>::iterator>* constraintRemoveList = new List<List<IrrlichtBulletConstraint*>::iterator>();

			foreach(IrrlichtBulletConstraint*, constraintIt, constraintList)
			{
				IrrlichtBulletConstraint* irrBullConstraint = constraintIt->GetData();

				if (irrBullObjSceneNode == irrBullConstraint->GetNode1() || irrBullObjSceneNode == irrBullConstraint->GetNode2())
				{
					constraintRemoveList->Add(constraintIt, false);
				}
			}
			foreach(List<IrrlichtBulletConstraint*>::iterator, removeConstraintIt, constraintRemoveList)
			{
				List<IrrlichtBulletConstraint*>::iterator constraintIT = removeConstraintIt->GetData();
				RemoveConstraint(constraintIT);

				List<IrrlichtToBulletEntityListPointer*>* enityListPointer = &entityTrackerList;
				foreach(IrrlichtToBulletEntityListPointer*, entityConstraintIt, enityListPointer)
				{
					if (entityConstraintIt->GetData()->entityListPointer == constraintIT)
					{
						entityTrackerList.Remove(entityConstraintIt);
						break;
					}
				}
			}

			delete constraintRemoveList;

			physicsEngine->RemovePhysicsObjectUsingTracker(irrBullObj->physicsObjectTrackerListIt);
			objectList->Remove(irrBullObj->listNodePointer);
		
			break;
		}

	case IrrlichtToBulletEntityListPointerType_Spring:
		{		
			List<IrrlichtBulletSpring*>::iterator springListElem = ((List<IrrlichtBulletSpring*>::iterator)entityPtr->entityListPointer);

			physicsEngine->RemoveSpring(springListElem->GetData()->springListElem);

			springList->Remove(springListElem);

			break;
		}

	case IrrlichtToBulletEntityListPointerType_Constraint:
		{
			List<IrrlichtBulletConstraint*>::iterator constraintListElem = ((List<IrrlichtBulletConstraint*>::iterator)entityPtr->entityListPointer);

			constraintList->Remove(constraintListElem->GetData()->listNodePointer);

			break;
		}
	}

	entityTrackerList.Remove(entityIt);
}

void IrrlichtToBulletConnector::ClearEntities(PhysicsEngine* physicsEngine)
{
	int initialSize = entityTrackerList.GetSize();
	for(int i = 0; i < initialSize; i++)
		RemoveEntity(0, physicsEngine);
}

void IrrlichtToBulletConnector::Update(float totalTime, float timeInSecondsSinceLastFrame, bool isRecording,
	List<IrrlichtToBulletDynamicObject*>* recordingObjects)
{
	foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
	{
		IrrlichtToBulletDynamicObject* dynObj = CastToDynamicObject(objIt->GetData());

		if (dynObj)
		{
			dynObj->UpdateBulletBody();
			//dynObj->body->applyCentralForce(btVector3(0.0f, -9.8f, 0.0f)*dynObj->GetMass());
		}
	}

	float maxSubStepFloat = timeInSecondsSinceLastFrame * 60.0f;
	int maxSubStep = ceilf(maxSubStepFloat);

	dynamicsWorld->stepSimulation(timeInSecondsSinceLastFrame, maxSubStep);	

	foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
	{
		objIt->GetData()->Update();
	}

	Record(totalTime, isRecording, recordingObjects);
}

void IrrlichtToBulletConnector::Draw(IVideoDriver* driver)
{
	foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
	{
		objIt->GetData()->Draw(driver);
	}	

	foreach(IrrlichtBulletConstraint*, constraintIt, constraintList)
	{
		constraintIt->GetData()->Draw(driver);
	}
}

void IrrlichtToBulletConnector::Reset()
{
	objectList->Clear();
	customCollisionShapeList->Clear();
	constraintList->Clear();
	springList->Clear();
}

void IrrlichtToBulletConnector::Record(float totalTime, bool isRecording, List<IrrlichtToBulletDynamicObject*>* recordingObjects)
{
	if (isRecording)
	{
		foreach(IrrlichtToBulletDynamicObject*, dynObjIt, recordingObjects)
		{
			dynObjIt->GetData()->Record(totalTime);
		}
	}
}

//TODO: Search with binary search tree or hash table
IrrlichtToBulletObjectStorage* IrrlichtToBulletConnector::FindObjectWithSceneNode(ISceneNode* node)
{
	foreach(IrrlichtToBulletObjectStorage*, objIt, objectList)
	{
		IrrlichtToBulletObjectStorage* obj = objIt->GetData();
		if (node == obj->node)
			return obj;
	}

	return NULL;
}