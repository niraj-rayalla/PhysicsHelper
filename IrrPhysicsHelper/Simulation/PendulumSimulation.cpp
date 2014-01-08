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

#include "PendulumSimulation.h"

PendulumSimulation::PendulumSimulation(irr::IrrlichtDevice *dev, irr::video::IVideoDriver *_driver, Physics_Engine::PhysicsEngine *_physicsEngine,
	void (*changeCurrentAccelerationLabel)(float x, float y, float z),
	const char* _uniformalAccelerationX, const char* _uniformalAccelerationY, const char* _uniformalAccelerationZ)
	: Simulation(dev, _driver, _physicsEngine, SimulationType_Pendulum)
{
	uniformalAccelerationX = _uniformalAccelerationX;
	uniformalAccelerationY = _uniformalAccelerationY;
	uniformalAccelerationZ = _uniformalAccelerationZ;

	uniformalAccelerationExprX = new MathExpression(uniformalAccelerationX, MathExpression::timeOnlyMathExpr, 1);
	uniformalAccelerationExprY = new MathExpression(uniformalAccelerationY, MathExpression::timeOnlyMathExpr, 1);
	uniformalAccelerationExprZ = new MathExpression(uniformalAccelerationZ, MathExpression::timeOnlyMathExpr, 1);

	physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _(""), false, false, 0.0, 1.0, Vector3_Zero, Vector3_Zero, 0.5f));

	ChangeCurrentAccelerationLabel = changeCurrentAccelerationLabel;

	lastNodeIndex = 0;
}

PendulumSimulation::~PendulumSimulation()
{
	delete uniformalAccelerationExprX;
	delete uniformalAccelerationExprY;
	delete uniformalAccelerationExprZ;
}

void PendulumSimulation::AddPendulumSimulationNode(wxString _name, double theta, double phi, double length, float mass)
{
	PhysicsObject* firstObj = physicsEngine->GetObjectList()->GetTail()->GetData();
	Vector3 lastNodePos = firstObj->GetPosition();
	Vector3 newNodePos = lastNodePos + Vector3((float)(length*sin(phi)*cos(theta)), (float)(length*sin(phi)*sin(theta)), (float)(length*cos(phi)));
	physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _name, true, false, 0.0, mass, newNodePos));
	physicsEngine->AddStringConnection(firstObj, physicsEngine->GetObjectList()->GetTail()->GetData(), (float)length);
	physicsEngine->AddConstraint(new DistanceConstraint(firstObj, physicsEngine->GetObjectList()->GetTail()->GetData(), (float)length));

	lastNodeIndex++;

	SetUnSaved();
}

void PendulumSimulation::AddPendulumSimulationNode(wxString _name, Vector3 pointer, float mass)
{
	PhysicsObject* firstObj = physicsEngine->GetObjectList()->GetTail()->GetData();
	Vector3 lastNodePos = firstObj->GetPosition();
	Vector3 newNodePos = lastNodePos + pointer;
	physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _name, true, false, 0.0, mass, newNodePos));
	physicsEngine->AddStringConnection(firstObj, physicsEngine->GetObjectList()->GetTail()->GetData(), pointer.getLength());
	physicsEngine->AddConstraint(new DistanceConstraint(firstObj, physicsEngine->GetObjectList()->GetTail()->GetData(), pointer.getLength()));

	lastNodeIndex++;

	SetUnSaved();
}

void PendulumSimulation::AddPendulumSimulationNodeComponents(wxString _name, double X, double Y, double Z, float mass)
{
	AddPendulumSimulationNode(_name, Vector3((float)X, (float)Y, (float)Z), mass);

	SetUnSaved();
}

void PendulumSimulation::RemovePendulumSimulationNode(int index)
{
	physicsEngine->RemovePhysicsObject(lastNodeIndex);
	physicsEngine->RemoveStringConnection(lastNodeIndex-1);
	physicsEngine->RemoveConstraint(lastNodeIndex-1);

	lastNodeIndex--;

	SetUnSaved();
}

void PendulumSimulation::ChangeSelectedColor(wxArrayInt indices)
{
	SColor whiteColor = SColor(255, 255, 255, 255);
	SColor yellowColor = SColor(255, 255, 255, 0);

	//Reset all nodes to white color
	foreach(PhysicsObject*, objIt, physicsEngine->GetObjectList())
	{
		((VisiblePhysicsObject*)objIt->GetData())->ChangeObjectColor(whiteColor);
	}

	for (unsigned int i = 0; i < indices.size(); i++)
	{
		((VisiblePhysicsObject*)physicsEngine->GetObjectList()->GetAt(indices[i] + 1)->GetData())->ChangeObjectColor(yellowColor);
	}
}

void PendulumSimulation::ChangeEquations(std::string _uniformalAccelerationX, std::string _uniformalAccelerationY, std::string _uniformalAccelerationZ)
{
	delete uniformalAccelerationExprX;
	delete uniformalAccelerationExprY;
	delete uniformalAccelerationExprZ;

	uniformalAccelerationX = _uniformalAccelerationX;
	uniformalAccelerationY = _uniformalAccelerationY;
	uniformalAccelerationZ = _uniformalAccelerationZ;

	uniformalAccelerationExprX = new MathExpression(uniformalAccelerationX, MathExpression::timeOnlyMathExpr, 1);
	uniformalAccelerationExprY = new MathExpression(uniformalAccelerationY, MathExpression::timeOnlyMathExpr, 1);
	uniformalAccelerationExprZ = new MathExpression(uniformalAccelerationZ, MathExpression::timeOnlyMathExpr, 1);

	SetUnSaved();
}

void PendulumSimulation::Reset()
{
	Simulation::Reset();

	physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _(""), false, false, 0.0, 1.0, Vector3_Zero, Vector3_Zero, 0.5f));

	lastNodeIndex = 0;

	ChangeEquations("0", "-9.8", "0");
}

void PendulumSimulation::Update(float timeInSecondsSinceLastFrame, bool ignorePaused)
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
		float accelerationX = (float)uniformalAccelerationExprX->GetValue(validVariableValue);
		float accelerationY = (float)uniformalAccelerationExprY->GetValue(validVariableValue);
		float accelerationZ = (float)uniformalAccelerationExprZ->GetValue(validVariableValue);

		ChangeCurrentAccelerationLabel(accelerationX, accelerationY, accelerationZ);

		physicsEngine->ClearForces();
		physicsEngine->AddForce(new UniformalForce(Vector3(accelerationX, accelerationY, accelerationZ)));
	}
}

void PendulumSimulation::UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport)
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

void PendulumSimulation::Draw(WxIrrViewport* currentViewport)
{
	Simulation::Draw(currentViewport);

	foreach(PhysicsObject*, objIt, physicsEngine->GetObjectList())
	{
		objIt->GetData()->DrawVelocityArrow(driver);
	}

	//physicsEngine->GetObjectList()->GetAt(1)->GetData()->DrawVelocityArrow(driver);
}

void PendulumSimulation::StartRecording()
{
	Simulation::StartRecording();	
	Simulation::StartPhysicsEngineRecording();
}

void PendulumSimulation::StopRecording()
{
	Simulation::StopRecording();
	Simulation::StopPhysicsEngineRecording();
}