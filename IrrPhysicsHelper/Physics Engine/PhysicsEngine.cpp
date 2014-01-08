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

#include "PhysicsEngine.h"

using namespace Physics_Engine;

PhysicsEngine::PhysicsEngine(IrrlichtDevice* _device, NumericIntegratorType _numericIntegratorType)
{
	device = _device;

	numericIntegratorType = _numericIntegratorType;

	objectList = new List<PhysicsObject*>();
	staticObjectList = new List<PhysicsObject*>();
	dynamicObjectList = new List<PhysicsObject*>();
	objectListTracker = new List<PhysicsObjectTrackerType*>();
	forceList = new List<Force*>();
	springList = new List<Spring*>();
	stringList = new List<PhysicsString*>();
	constraintList = new List<Constraint*>();

	speed = 1.0f;
	DisableGravitation();
	DisableMagnetism();

	EnableForceCalculation();
	EnablePositionUpdating();

	Run();
	oldTimeFramePassed = 0.0f;

	canSerialize = true;
}

PhysicsEngine::~PhysicsEngine()
{
	delete objectList;
	delete staticObjectList;
	delete dynamicObjectList;
	delete objectListTracker;
	delete forceList;
	delete springList;
	delete stringList;
	delete constraintList;
}

List<PhysicsObjectTrackerType*>::iterator PhysicsEngine::AddPhysicsObject(PhysicsObject* obj, bool deleteData)
{
	List<PhysicsObjectTrackerType*>::iterator retValue = NULL;

	PhysicsObjectTrackerType* tracker = new PhysicsObjectTrackerType();
	tracker->objectListIt = 	objectList->Add(obj, deleteData);

	if (obj->GetEnabled())
	{
		tracker->objectListTrackerIt = dynamicObjectList->Add(obj, false);
		retValue = objectListTracker->Add(tracker);
	}
	else
	{
		tracker->objectListTrackerIt = staticObjectList->Add(obj, false);
		retValue = objectListTracker->Add(tracker);
	}

	return retValue;
}

PhysicsObject* PhysicsEngine::AddPhysicsObject(wxString _name, bool _enabled, bool _charged, float _charge, float _mass, Vector3 pos, Vector3 vel)
{
	PhysicsObject* newObj = new PhysicsObject(_name, _enabled, _charged, _charge, _mass, pos, vel, true);
	AddPhysicsObject(newObj);

	return newObj;
}

void PhysicsEngine::RemovePhysicsObject(int index)
{
	bool wasEnabled = objectList->GetAt(index)->GetData()->GetEnabled();
	objectList->Remove(index);

	//Remove object tracker and from the corresponding link to the static object list or the dynamic object list.
	if (wasEnabled)
	{
		dynamicObjectList->Remove(objectListTracker->GetAt(index)->GetData()->objectListTrackerIt);
	}
	else
	{
		staticObjectList->Remove(objectListTracker->GetAt(index)->GetData()->objectListTrackerIt);
	}
	objectListTracker->Remove(index);
}

void PhysicsEngine::RemovePhysicsObjectUsingTracker(List<PhysicsObjectTrackerType*>::iterator objTrackerListIt)
{
	if (objTrackerListIt)
	{
		PhysicsObjectTrackerType* trackerIt = objTrackerListIt->GetData();
		bool wasEnabled = trackerIt->objectListIt->GetData()->GetEnabled();
		objectList->Remove(trackerIt->objectListIt);

		//Remove object tracker and from the corresponding link to the static object list or the dynamic object list.
		if (wasEnabled)
		{
			dynamicObjectList->Remove(trackerIt->objectListTrackerIt);
		}
		else
		{
			staticObjectList->Remove(trackerIt->objectListTrackerIt);
		}

		objectListTracker->Remove(objTrackerListIt);
	}
}

void PhysicsEngine::ResetandAddForces()
{
	foreach(PhysicsObject*, objIt, dynamicObjectList)
	{
		PhysicsObject* obj = objIt->GetData();
		obj->ResetForce();
		foreach(Force*, frcIt, forceList)
		{
			frcIt->GetData()->AddForcetoObject(*obj);
		}
	}
}

//Get the gravitational force between two objects
Vector3 PhysicsEngine::GetGravitationForce(PhysicsObject* first, PhysicsObject* second)
{
	Vector3 temp(0.0f, 0.0f, 0.0f);
	Vector3 firstPos = first->GetPosition();
	Vector3 secondPos = second->GetPosition();
	float distanceSquared = firstPos.getDistanceFromSQ(secondPos);
	//float totalMass = first->GetMass() * second->GetMass();
	float constant = G * first->GetMass() * second->GetMass() / distanceSquared;
	temp = constant * (secondPos - firstPos) / sqrt(distanceSquared);
	return temp;
}

void PhysicsEngine::AddGravitationForces()
{
	//Find all the gravitational forces between physic objects.
	/*foreach(PhysicsObject*, objIt, staticObjectList)
	{
		PhysicsObject* obj = objIt->GetData();

		foreach(PhysicsObject*, objItDyanmic, dynamicObjectList)
		{
			PhysicsObject* obj2 = objItDyanmic->GetData();
			
			Vector3 frc = GetGravitationForce(obj, obj2);
			obj2->AddForce(-frc);
		}
	}*/
	/*for(irr::core::list<PhysicsObject*>::Iterator i = staticObjectListTwo.begin(); i != staticObjectListTwo.end(); i++)
	{
		for(irr::core::list<PhysicsObject*>::Iterator j = dynamicObjectListTwo.begin(); j != dynamicObjectListTwo.end(); j++)
		{
			PhysicsObject* obj2 = *j;
			Vector3 frc = GetGravitationForce(*i, obj2);
			obj2->AddForce(-frc);
		}
	}*/


	foreach(PhysicsObject*, objIt, dynamicObjectList)
	{
		PhysicsObject* obj = objIt->GetData();

		foreach(PhysicsObject*, objIt2, staticObjectList)
		{
			PhysicsObject* obj2 = objIt2->GetData();

			Vector3 frc = GetGravitationForce(obj2, obj);
			obj->AddForce(-frc);
		}
		
		List<PhysicsObject*>::iterator other;
		objIt->advance(other);

		foreachfrom(other)
		{
			PhysicsObject* obj2 = other->GetData();
			
			Vector3 frc = GetGravitationForce(obj, obj2);
			obj->AddForce(frc);
			obj2->AddForce(-frc);
		}
	}

	/*for(irr::core::list<PhysicsObject*>::Iterator i = dynamicObjectListTwo.begin(); i != dynamicObjectListTwo.end(); i++)
	{
		irr::core::list<PhysicsObject*>::Iterator j = i;
		j++;
		for(j; j != dynamicObjectListTwo.end(); j++)
		{
			PhysicsObject* obj = *i;
			PhysicsObject* obj2 = *j;
			
			Vector3 frc = GetGravitationForce(obj, obj2);
			obj->AddForce(frc);
			obj2->AddForce(-frc);
		}
	}*/
}

//Get the coulomb force between two objects
Vector3 PhysicsEngine::GetCoulombForce(PhysicsObject* first, PhysicsObject* second)
{
    Vector3 temp;
	Vector3 firstPos = first->GetPosition();
	Vector3 secondPos = second->GetPosition();
    float distanceSquared = firstPos.getDistanceFromSQ(secondPos);
	float constant = Physics_Engine::k * first->GetCharge() * second->GetCharge();
    temp = constant / distanceSquared * (firstPos - secondPos) / squareroot(distanceSquared);
    return temp;
}

void PhysicsEngine::AddCoulombForces()
{   
	//Find all the coulomb forces between physic objects.
	/*foreach(PhysicsObject*, objIt, objectList)
	{
		PhysicsObject* obj = objIt->GetData();
		if (obj->GetCharged())
		{
			List<PhysicsObject*>::iterator other;
			objIt->advance(other);

			foreachfrom(other)
			{
				PhysicsObject* obj2 = other->GetData();
				if (obj2->GetEnabled() && obj2->GetCharged())
				{
					Vector3 frc = GetCoulombForce(obj, obj2);
					obj->AddForce(frc);
					obj2->AddForce(-frc);
				}
			}
		}
	}*/	


	foreach(PhysicsObject*, objIt, dynamicObjectList)
	{
		PhysicsObject* obj = objIt->GetData();

		if (obj->GetCharged())
		{
			foreach(PhysicsObject*, objIt2, staticObjectList)
			{
				PhysicsObject* obj2 = objIt2->GetData();

				if(obj2->GetCharged())
				{
					Vector3 frc = GetCoulombForce(obj2, obj);
					obj->AddForce(-frc);
				}
			}
			
			List<PhysicsObject*>::iterator other;
			objIt->advance(other);

			foreachfrom(other)
			{
				PhysicsObject* obj2 = other->GetData();
				
				if(obj2->GetCharged())
				{
					Vector3 frc = GetCoulombForce(obj, obj2);
					obj->AddForce(frc);
					obj2->AddForce(-frc);
				}
			}
		}
	}
}

void PhysicsEngine::Clear()
{
	totalTime = 0.0f;

	objectList->Clear();
	staticObjectList->Clear();
	dynamicObjectList->Clear();
	objectListTracker->Clear();
	forceList->Clear();
	springList->Clear();
	stringList->Clear();
	constraintList->Clear();
}

void PhysicsEngine::Update(float timeSinceLastFrame, bool ignorePaused)
{
	if (!paused || ignorePaused)
	{
		float timeInSecondsSinceLastFrame = speed * timeSinceLastFrame;
		totalTime += timeInSecondsSinceLastFrame;

		if (timeInSecondsSinceLastFrame == 0)
			return;

		if (oldTimeFramePassed == 0.0f)
		{
			oldTimeFramePassed = timeInSecondsSinceLastFrame;
		}

		if (calculateForces)
		{
			ResetandAddForces();

			//Add Gravitation forces if simulating gravitation
			if (simulateGravitation)
			{
				AddGravitationForces();
			}
			//Add Coulomb forces if simulating gravitation
			if (simulateMagnetism)
			{
				AddCoulombForces();
			}

			foreach(PhysicsString*, stringIt, stringList)
			{
				stringIt->GetData()->Update(timeInSecondsSinceLastFrame);
			}

			foreach(PhysicsString*, stringIt, stringList)
			{
				stringIt->GetData()->UpdateAfter();
			}

			foreach(Spring*, springIt, springList)
			{
				springIt->GetData()->UpdateForces();
			}
		}	

		

		/*foreach(ForceAfter*, frcAfterIt, forceAfterList)
		{
			ForceAfter* frcAft = frcAfterIt->GetData();
			frcAft->obj->AddForce(frcAft);
		}*/

		if (updatePositions)
		{
			//Update the object positions, velocity etc...
			foreach (PhysicsObject*, objIt, dynamicObjectList)
			{
				objIt->GetData()->Update(timeInSecondsSinceLastFrame, oldTimeFramePassed);
			}

			//Update the constraints
			foreach (Constraint*, constraintIt, constraintList)
			{
				constraintIt->GetData()->Update(timeInSecondsSinceLastFrame);
			}
		}

		oldTimeFramePassed = timeInSecondsSinceLastFrame;
	}
}

void PhysicsEngine::Draw(IrrlichtDevice* device)
{
	IVideoDriver* driver = device->getVideoDriver();

    //Draw object paths
    foreach (PhysicsObject*, objIt, objectList)
    {
		objIt->GetData()->DrawPath(driver);
    }

	foreach(PhysicsString*, stringIt, stringList)
	{
		stringIt->GetData()->Draw(driver);
	}
}

ElectricFieldPotReturnType PhysicsEngine::GetElecFieldPotAtPoint(Vector3 point)
{
	ElectricFieldPotReturnType retValue;

	foreach(PhysicsObject*, objIt, objectList)
	{
		ElectricFieldPotReturnType singleValue = objIt->GetData()->GetElecFieldPotAtPoint(point);
		retValue += singleValue;
	}

	return retValue;
}

void PhysicsEngine::SerializeInPhysicsObjects(istream &is)
{
	//List<PhysicsObject*>* list = new List<PhysicsObject*>();

	int size = 0;
	is >> size;

	for(int i = 0; i < size; i++)
	{
		int objTypeInt = 0;
		is >> objTypeInt;
	
		if (objTypeInt ==  PhysicsObjectType_Basic)
		{
			PhysicsObject basicElem;
			is >> basicElem;
			PhysicsObject* basicPtrElem = new PhysicsObject(basicElem.GetName(), basicElem.GetEnabled(), basicElem.GetCharged(), basicElem.GetCharge(), basicElem.GetMass(),
				basicElem.GetPosition(), basicElem.GetOldPosition(), basicElem.GetVelocity(), true);
			AddPhysicsObject(basicPtrElem);
			//list->Add(basicPtrElem);
		}
		else if (objTypeInt == PhysicsObjectType_Sphere)
		{
			SimulationObject_Sphere sphereElem;
			is >> sphereElem;
			SimulationObject_Sphere* spherePtrElem = new SimulationObject_Sphere(device->getSceneManager(), sphereElem.GetName(), sphereElem.GetEnabled(), sphereElem.GetCharged(), sphereElem.GetCharge(), sphereElem.GetMass(),
				sphereElem.GetPosition(), sphereElem.GetOldPosition(), sphereElem.GetVelocity(), sphereElem.GetRadius());
			AddPhysicsObject(spherePtrElem);
			//list->Add(spherePtrElem);
		}
		else if (objTypeInt == PhysicsObjectType_Cube)
		{
			SimulationObject_Cube cubeElem;
			is >> cubeElem;
			SimulationObject_Cube* cubePtrElem = new SimulationObject_Cube(device->getSceneManager(), cubeElem.GetName(), cubeElem.GetEnabled(), cubeElem.GetCharged(), cubeElem.GetCharge(), cubeElem.GetMass(),
				cubeElem.GetPosition(), cubeElem.GetOldPosition(), cubeElem.GetVelocity(), cubeElem.GetLength());
			AddPhysicsObject(cubePtrElem);
			//list->Add(spherePtrElem);
		}
	}

	//return list;
}

void PhysicsEngine::SerializeInSprings(istream &is)
{
	int size = 0;
	is >> size;

	for(int i = 0; i < size; i++)
	{
		Spring* newSpring = Spring::SerializeInStatic(is);
		if (newSpring)
			springList->Add(newSpring);
	}
}

void PhysicsEngine::SerializeIn(istream &is)
{
	if (canSerialize)
	{
		is >> paused;
		is >> totalTime;
		is >> oldTimeFramePassed;
		is >> speed;

		SerializeInPhysicsObjects(is); //SerializeInListPointer<PhysicsObject>(is);
		//foreach(PhysicsObject*, objIt, tempObjectList)
		//{
		//	PhysicsObject* tempObj = objIt->GetData();
		//	//AddPhysicsObject(tempObj->GetEnabled(), tempObj->GetCharged(), tempObj->GetCharge(), tempObj->GetMass(), tempObj->GetPosition(), tempObj->GetVelocity());
		//	AddPhysicsObject(tempObj);
		//}
		//delete tempObjectList;
		SerializeInSprings(is);

		is >> simulateGravitation;
		is >> simulateMagnetism;
	}

}
void PhysicsEngine::SerializeOut(ostream &os)
{
	if (canSerialize)
	{
		os << paused << endl;
		os << totalTime << endl;
		os << oldTimeFramePassed << endl;
		os << speed << endl;

		SerializeOutListPointer(os, objectList);
		SerializeOutListPointer(os, springList);
		/*SerializeOutListPointer(os, forceList);
		SerializeOutListPointer(os, stringList);
		SerializeOutListPointer(os, constraintList);*/

		os << simulateGravitation << endl;
		os << simulateMagnetism << endl;
	}
}