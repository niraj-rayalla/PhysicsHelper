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

#include "SpringSimulation.h"

SpringSimulation::SpringSimulation(irr::IrrlichtDevice *dev, irr::video::IVideoDriver *_driver, Physics_Engine::PhysicsEngine *_physicsEngine,
	const char* _uniformalAcceleration)
	: Simulation(dev, _driver, _physicsEngine, SimulationType_Spring)
{
	uniformalAcceleration = _uniformalAcceleration;

	uniformalAccelerationExpr = new MathExpression(uniformalAcceleration, MathExpression::timeOnlyMathExpr, 1);

	physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _(""), false, false, 0.0, 1.0, Vector3_Zero, Vector3_Zero, 0.5f));

	lastNodeIndex = 0;
}

SpringSimulation::~SpringSimulation()
{
	delete uniformalAccelerationExpr;
	for(List<SpringSceneNode*>::iterator springSceneNodeIt = springSceneNodeList.begin(); springSceneNodeIt != NULL; springSceneNodeIt->advance(springSceneNodeIt))
	{
		SpringSceneNode* springNode = springSceneNodeIt->GetData();
		springNode->remove();
		delete springNode;
	}
	springSceneNodeList.Clear();
}

//void SpringSimulation::AddSpringSimulationNode(wxString _name, double kConstant, double theta, double phi, double length, float mass)
//{
//	PhysicsObject* firstObj = physicsEngine->GetObjectList()->GetTail()->GetData();
//	Vector3 lastNodePos = firstObj->GetPosition();
//	Vector3 newNodePos = lastNodePos + Vector3((float)(length*sin(phi)*cos(theta)), (float)(length*sin(phi)*sin(theta)), (float)(length*cos(phi)));
//	physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _name, true, false, 0.0, mass, newNodePos));
//	physicsEngine->AddSpring(firstObj, physicsEngine->GetObjectList()->GetTail()->GetData(), (float)kConstant, (float)length );
//
//	lastNodeIndex++;
//
//	SetUnSaved();
//}

void SpringSimulation::AddSpringSimulationNode(wxString _name, double kConstant, float length, float equilibriumLength, float mass)
{
	PhysicsObject* firstObj = physicsEngine->GetObjectList()->GetTail()->GetData();
	Vector3 lastNodePos = firstObj->GetPosition();
	Vector3 newNodePos = lastNodePos + Vector3(abs_(length), 0.0f, 0.0f);

	SimulationObject_Cube* newNode = new SimulationObject_Cube(device->getSceneManager(), _name, true, false, 0.0, mass, newNodePos);

	physicsEngine->AddPhysicsObject(newNode);
	physicsEngine->AddSpring(firstObj, physicsEngine->GetObjectList()->GetTail()->GetData(), (float)kConstant, equilibriumLength);
	springSceneNodeList.Add(new SpringSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), -1,
		((VisiblePhysicsObject*)firstObj)->GetSceneNode(), newNode->GetSceneNode()), false);

	lastNodeIndex++;

	SetUnSaved();
}

void SpringSimulation::LoadSpringSimulationNode(wxString _name, double kConstant, float length, float equilibriumLength, float mass, Vector3& oldPos, Vector3& vel)
{
	PhysicsObject* firstObj = physicsEngine->GetObjectList()->GetTail()->GetData();
	Vector3 lastNodePos = firstObj->GetPosition();
	Vector3 newNodePos = lastNodePos + Vector3(abs_(length), 0.0f, 0.0f);

	SimulationObject_Cube* newNode = new SimulationObject_Cube(device->getSceneManager(), _name, true, false, 0.0, mass, newNodePos, oldPos, vel, 1.0f);

	physicsEngine->AddPhysicsObject(newNode);
	physicsEngine->AddSpring(firstObj, physicsEngine->GetObjectList()->GetTail()->GetData(), (float)kConstant, equilibriumLength);
	springSceneNodeList.Add(new SpringSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), -1,
		((VisiblePhysicsObject*)firstObj)->GetSceneNode(), newNode->GetSceneNode()), false);

	lastNodeIndex++;

	SetUnSaved();
}

void SpringSimulation::RemoveLastSpringSimulationNode()
{
	physicsEngine->RemovePhysicsObject(lastNodeIndex);
	physicsEngine->RemoveSpring(lastNodeIndex-1);
	springSceneNodeList.Remove(lastNodeIndex-1);

	SetUnSaved();
}

void SpringSimulation::ChangeEquations(const char* _uniformalAcceleration)
{
	delete uniformalAccelerationExpr;

	uniformalAcceleration = _uniformalAcceleration;

	uniformalAccelerationExpr = new MathExpression(uniformalAcceleration, MathExpression::timeOnlyMathExpr, 1);

	SetUnSaved();
}

void SpringSimulation::Reset()
{
	Simulation::Reset();

	physicsEngine->Clear();

	for(List<SpringSceneNode*>::iterator springSceneNodeIt = springSceneNodeList.begin(); springSceneNodeIt != NULL; springSceneNodeIt->advance(springSceneNodeIt))
	{
		SpringSceneNode* springNode = springSceneNodeIt->GetData();
		springNode->remove();
		delete springNode;
	}
	springSceneNodeList.Clear();

	physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _(""), false, false, 0.0, 1.0, Vector3_Zero, Vector3_Zero, 0.5f));

	lastNodeIndex = 0;

	ChangeEquations("0");
}

void SpringSimulation::Update(float timeInSecondsSinceLastFrame, bool ignorePaused)
{
	if (isRecording && isRecordingFirstFrame)
	{
		foreach(PhysicsObject*, phyObjIt, recordingObjects)
		{
			phyObjIt->GetData()->Record(totalTime);
		}
		isRecordingFirstFrame = false;
	}

	Simulation::Update(timeInSecondsSinceLastFrame, ignorePaused);

	if (!simulationPaused || ignorePaused)
	{
		double validVariableValue[1] = { totalTime };
		float acceleration = (float)uniformalAccelerationExpr->GetValue(validVariableValue);

		physicsEngine->ClearForces();
		physicsEngine->AddForce(new UniformalForce(Vector3(acceleration, 0.0f, 0.0f)));
	}
}

void SpringSimulation::UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport)
{
	if (!simulationPaused)
	{
		foreach(PhysicsObject*, phyObjIt, recordingObjects)
		{
			phyObjIt->GetData()->Record(totalTime);
		}

		Simulation::UpdateAfter(timeInSecondsSinceLastFrame, viewport);
	}
}

void SpringSimulation::Draw(WxIrrViewport* currentViewport)
{
	Simulation::Draw(currentViewport);
}

void SpringSimulation::StartRecording()
{
	Simulation::StartRecording();	
	Simulation::StartPhysicsEngineRecording();
}

void SpringSimulation::StopRecording()
{
	Simulation::StopRecording();
	Simulation::StopPhysicsEngineRecording();
}


void SpringSimulation::SerializeIn(istream& is)
{
	Simulation::SerializeIn(is);

	int tempIndex = 0;
	is >> tempIndex;

	physicsEngine->RemovePhysicsObject(0);
	physicsEngine->RemovePhysicsObject(0);

	List<Spring*>* springList = physicsEngine->GetSpringList();
	List<PhysicsObject*>* objectList = physicsEngine->GetObjectList();

	physicsEngine->ForgetList<Spring>(physicsEngine->GetSpringListAddress());
	physicsEngine->ForgetList<PhysicsObject>(physicsEngine->GetObjectListAddress());

	physicsEngine->Clear();

	physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _(""), false, false, 0.0, 1.0, Vector3_Zero, Vector3_Zero, 0.5f));

	if (springList->GetSize() == objectList->GetSize())
	{
		List<Spring*>::iterator currentSpring = springList->begin();
		foreach(PhysicsObject*, objIt, objectList)
		{
			PhysicsObject* obj = objIt->GetData();

			DoubleSpring* tempSpring = (DoubleSpring*)currentSpring->GetData();
			LoadSpringSimulationNode(obj->GetName(), tempSpring->GetK(), obj->GetPosition().X - physicsEngine->GetObjectList()->GetTail()->GetData()->GetPosition().X,
				tempSpring->GetEquilibriumLength(), obj->GetMass(), obj->GetOldPosition(), obj->GetVelocity());
			physicsEngine->GetObjectList()->GetTail()->GetData()->ResetForce();
			currentSpring->advance(currentSpring);
		}
	}
	else
	{
		wxMessageBox(_("Simulation save file has been curropted."), _("Error"));
	}

	delete springList;
	delete objectList;
}
void SpringSimulation::SerializeOut(ostream& os)
{
	Simulation::SerializeOut(os);

	os << lastNodeIndex << endl;
}