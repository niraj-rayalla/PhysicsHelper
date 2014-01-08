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

#include "BasicMotionSimulation.h"

BasicMotionTimedEquation::BasicMotionTimedEquation(float _startTime, float _endTime, char *_equationX, char *_equationY, char *_equationZ, BasicMotionEquationType _equationType)
{
	startTime = _startTime;
	endTime = _endTime;
	equationX = _equationX;
	equationY = _equationY;
	equationZ = _equationZ;

	equationExprX = new MathExpression(equationX, validVariables, 1);
	equationExprY = new MathExpression(equationY, validVariables, 1);
	equationExprZ = new MathExpression(equationZ, validVariables, 1);

	equationType = _equationType;
}
std::string BasicMotionTimedEquation::validVariables[1] = {"t"};


/////////////////////////////////////////
BasicMotionTimedEquation::~BasicMotionTimedEquation()
{
	delete equationExprX;
	delete equationExprY;
	delete equationExprZ;
}

BasicMotionObject::BasicMotionObject(wxString _name, float _mass, Vector3 pos, Vector3 vel)
	: VisiblePhysicsObject(_name, true, false, 0.0f, _mass, pos, vel)
{
	global = true;
	motionEquationList = new List<BasicMotionTimedEquation*>();
}

BasicMotionObject::~BasicMotionObject()
{
	delete motionEquationList;
}

bool BasicMotionObject::AddEquation(BasicMotionTimedEquation* eqn)
{
	if (eqn->startTime < eqn->endTime)
	{

		List<BasicMotionTimedEquation*>::iterator previous = NULL;
		foreach(BasicMotionTimedEquation*, timedEqnIt, motionEquationList)
		{
			BasicMotionTimedEquation* data = timedEqnIt->GetData();
			if (data->startTime >= eqn->endTime)
			{
				if (previous && previous->GetData()->endTime > eqn->startTime)
				{
					return false;
				}
				motionEquationList->AddBefore(timedEqnIt, eqn, true);
				
				global = false;
				enabled = false;

				return true;
			}

			previous = timedEqnIt;
		}

		motionEquationList->Add(eqn, true);

		global = false;
		enabled = false;

		return true;
	}

	return false;
}

void BasicMotionObject::RemoveEquation(int index)
{
	motionEquationList->Remove(index);

	if (motionEquationList->GetSize() == 0)
	{
		global = true;
		enabled = true;
	}
}

void BasicMotionObject::Update(float timeInSecondsSinceLastFrame)
{
	PhysicsObject::Update(timeInSecondsSinceLastFrame);
}

void BasicMotionObject::UpdateEquationValues(double* validVarValues, float totalPassedFrame)
{
	float totalTime = (float)validVarValues[0];

	if (totalPassedFrame != 0.0f)
	{
		foreach(BasicMotionTimedEquation*, timedEquationIt, motionEquationList)
		{
			BasicMotionTimedEquation* data = timedEquationIt->GetData();

			if (totalTime >= data->startTime)
			{
				if (totalTime <= data->endTime)
				{
					Vector3 newValue = Vector3(data->equationExprX->GetValue(validVarValues),
						data->equationExprY->GetValue(validVarValues), data->equationExprZ->GetValue(validVarValues));

					Vector3 newPosition;
					Vector3 newVelocity;
					Vector3 newAcceleration;


					switch(data->equationType)
					{
					case BasicMotionEquationType_Position:
						
						newPosition = newValue;
						newVelocity = (newPosition - position) / totalPassedFrame;
						newAcceleration = (newVelocity - velocity) / totalPassedFrame;

						break;

					case BasicMotionEquationType_Velocity:

						newVelocity = newValue;
						newPosition = position + newVelocity*totalPassedFrame;
						newAcceleration = (newVelocity - velocity) / totalPassedFrame;

						break;

					case BasicMotionEquationType_Acceleration:

						newAcceleration = newValue;
						newVelocity = velocity + newAcceleration*totalPassedFrame;
						newPosition = position + newVelocity*totalPassedFrame;

						break;
					}

					position = newPosition;
					velocity = newVelocity;
					acceleration = newAcceleration;
				}
			}		
			else
			{
				break;
			}
		}
	}
}



BasicMotionObjectSphere::BasicMotionObjectSphere(irr::scene::ISceneManager *smgr, wxString _name, float _mass, Vector3 pos, Vector3 vel, float _radius)
	: BasicMotionObject(_name, _mass, pos, vel)
{
	radius = _radius;

	node = smgr->addSphereSceneNode(_radius);
}

BasicMotionObjectSphere::~BasicMotionObjectSphere()
{

}

void BasicMotionObjectSphere::Update(float timeInSecondsSinceLastFrame)
{
	BasicMotionObject::Update(timeInSecondsSinceLastFrame);

	node->setPosition(position);
}


///////////////////////////////////////

Vector3 BasicMotionTimedEquation::GetValue(double* validVarValues)
{
	return Vector3(equationExprX->GetValue(validVarValues), equationExprY->GetValue(validVarValues), equationExprZ->GetValue(validVarValues));
}




BasicMotionSimulation::BasicMotionSimulation(irr::IrrlichtDevice *dev, irr::video::IVideoDriver *_driver, Physics_Engine::PhysicsEngine *_physicsEngine)
: Simulation(dev, _driver, _physicsEngine, SimulationType_Motion)
{
	globalAccelerationList = new List<BasicMotionTimedEquation*>();
	currentGlobalAccelerationList = new List<BasicMotionTimedEquation*>();

	basicMotionObjectList = new List<BasicMotionObject*>();

	physicsEngine->DisableForceCalculation();
}

BasicMotionSimulation::~BasicMotionSimulation()
{
	delete globalAccelerationList;
	delete currentGlobalAccelerationList;

	delete basicMotionObjectList;

	physicsEngine->EnableForceCalculation();
}

void BasicMotionSimulation::AddObject(wxString _name, Vector3 pos, Vector3 intVel, float mass)
{
	BasicMotionObject* obj = new BasicMotionObjectSphere(device->getSceneManager(), _name, mass, pos, intVel, 1.0f);

	basicMotionObjectList->Add(obj, true);
	physicsEngine->AddPhysicsObject(obj, false);

	SetSaved();
}

//Check for no overlapping time ranges.
void BasicMotionSimulation::AddGlobalAcceleration(float startTime, float endTime, char* equationX, char* equationY, char* equationZ)
{
	if (startTime < endTime)
	{
		BasicMotionTimedEquation* newElement = new BasicMotionTimedEquation(startTime, endTime, equationX, equationY, equationZ);
		
		if (globalAccelerationList->GetSize() == 0)
		{
			globalAccelerationList->Add(newElement, true);
		}
		else
		{
			List<BasicMotionTimedEquation*>::iterator previous = NULL;
			foreach(BasicMotionTimedEquation*, timedAccIt, globalAccelerationList)
			{
				if (timedAccIt->GetData()->startTime >= endTime)
				{
					if (previous && previous->GetData()->endTime > startTime)
					{
						return;
					}

					globalAccelerationList->AddBefore(timedAccIt, newElement, true);
					return;
				}
			}
			
			globalAccelerationList->Add(newElement, true);
		}
	}
	
	SetSaved();
}

void BasicMotionSimulation::Reset()
{
	Simulation::Reset();

	physicsEngine->Clear();
	globalAccelerationList->Clear();
	currentGlobalAccelerationList->Clear();

	basicMotionObjectList->Clear();
}

void BasicMotionSimulation::Update(float timePassedSeconds, bool ignorePaused)
{
	Simulation::Update(timePassedSeconds, ignorePaused);

	if (!simulationPaused || ignorePaused)
	{
		double validVarsValue[1] = { totalTime };

		//Reset forces
		foreach(BasicMotionObject*, basicMotionObjectIt, basicMotionObjectList)
		{
			BasicMotionObject* currentObj = basicMotionObjectIt->GetData();
			currentObj->SetForceFromAcceleration(Vector3_Zero);
		}

		foreach(BasicMotionTimedEquation*, timedAccelerationIt, globalAccelerationList)
		{
			BasicMotionTimedEquation* data = timedAccelerationIt->GetData();
			if (totalTime >= data->startTime)
			{
				if (totalTime <= data->endTime)
				{
					foreach(BasicMotionObject*, basicMotionObjectIt, basicMotionObjectList)
					{
						BasicMotionObject* currentObj = basicMotionObjectIt->GetData();
						if (currentObj->global)
							currentObj->SetForceFromAcceleration(data->GetValue(validVarsValue));
					}
				}
			}
			else
			{
				break;
			}
		}

		foreach(BasicMotionObject*, basicMotionObjectIt, basicMotionObjectList)
		{
			BasicMotionObject* currentObj = basicMotionObjectIt->GetData();
			if (!(currentObj->global))
			{
				currentObj->UpdateEquationValues(validVarsValue, timePassedFrame);
			}
		}
	}
}

void BasicMotionSimulation::Draw(WxIrrViewport* currentViewport)
{
	Simulation::Draw(currentViewport);
}