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

#include "GravitationSimulation.h"

GravitationSimulation::GravitationSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*addObjectToListBox)(wxString str, bool enabled))
: Simulation(dev, _driver, _physicsEngine, SimulationType_Gravitation)
{
	AddObjectToListBox = addObjectToListBox;

	physicsEngine->EnableGravitation();	
	selectedObjectsIndexes = new List<int>();
}

GravitationSimulation::~GravitationSimulation()
{
	physicsEngine->DisableGravitation();
	delete selectedObjectsIndexes;
}

void GravitationSimulation::AddObject(wxString _name, Vector3 pos, Vector3 intVel, float mass, bool isRelative, int relativeIndex, float radius, bool enabled)
{
	if (isRelative)
	{
		PhysicsObject* obj = physicsEngine->GetObjectList()->GetAt(relativeIndex)->GetData();

		pos += obj->GetPosition();
		intVel += obj->GetVelocity();
	}

	physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _name, enabled, false, 0.0f, mass, pos, intVel, radius));

	SetUnSaved();
}

void GravitationSimulation::AddObject(wxString _name, std::string mass, std::string radius, vector3d<std::string> posStrings, Vector3 posBegins, Vector3 posEnds, Vector3 posResolutions,
		vector3d<std::string> velStrings, bool isRelative, int relativeIndex, bool enabled)
{
	MathExpression massExpr = MathExpression(mass.c_str(), MathExpression::cartesianMathExpr, 3);
	MathExpression radiusExpr = MathExpression(radius.c_str(), MathExpression::cartesianMathExpr, 3);

	MathExpression posXExpr = MathExpression(posStrings.X.c_str(), MathExpression::cartesianMathExpr, 3);
	MathExpression posYExpr = MathExpression(posStrings.Y.c_str(), MathExpression::cartesianMathExpr, 3);
	MathExpression posZExpr = MathExpression(posStrings.Z.c_str(), MathExpression::cartesianMathExpr, 3);

	//Make sure no errors happen if an axis has a resolution of only 1.
	bool onceXInterval = false;
	bool onceYInterval = false;
	bool onceZInterval = false;

	double posXInterval = 0.0;
	if(posResolutions.X == 1.0)
	{
		posXInterval = 1.0;
		onceXInterval = true;
	}
	else
	{
		posXInterval = (posEnds.X - posBegins.X)/ (posResolutions.X - 1.0);
	}			
	
	double posYInterval = 0.0;
	if(posResolutions.Y == 1.0)
	{
		posYInterval = 1.0;
		onceYInterval = true;
	}
	else
	{
		posYInterval = (posEnds.Y - posBegins.Y)/ (posResolutions.Y - 1.0);
	}

	double posZInterval = 0.0;
	if(posResolutions.Z == 1.0)
	{
		posZInterval = 1.0;
		onceZInterval = true;
	}
	else
	{
		posZInterval = (posEnds.Z - posBegins.Z)/ (posResolutions.Z - 1.0);
	}

	MathExpression velXExpr = MathExpression(velStrings.X.c_str(), MathExpression::cartesianMathExpr, 3);
	MathExpression velYExpr = MathExpression(velStrings.Y.c_str(), MathExpression::cartesianMathExpr, 3);
	MathExpression velZExpr = MathExpression(velStrings.Z.c_str(), MathExpression::cartesianMathExpr, 3);

	Vector3 relativePos = Vector3_Zero;
	Vector3 relativeVel = Vector3_Zero;

	if (isRelative)
	{
		PhysicsObject* obj = physicsEngine->GetObjectList()->GetAt(relativeIndex)->GetData();

		relativePos = obj->GetPosition();
		relativeVel = obj->GetVelocity();
	}

	double validVarsValue[3] = {0,0,0};	

	int tempObjectCount = 1;

	for (float currentX = posBegins.X; currentX <= posEnds.X; currentX += posXInterval)
	{
		validVarsValue[0] = (double)currentX;
		for (float currentY = posBegins.Y; currentY <= posEnds.Y; currentY += posYInterval)
		{
			validVarsValue[1] = (double)currentY;
			for (float currentZ = posBegins.Z; currentZ <= posEnds.Z; currentZ += posZInterval)
			{
				validVarsValue[2] = (double)currentZ;

				double massValue = massExpr.GetValue(validVarsValue);
				double radiusValue = radiusExpr.GetValue(validVarsValue);

				double posXValue = posXExpr.GetValue(validVarsValue);
				double posYValue = posYExpr.GetValue(validVarsValue);
				double posZValue = posZExpr.GetValue(validVarsValue);

				double velXValue = velXExpr.GetValue(validVarsValue);
				double velYValue = velYExpr.GetValue(validVarsValue);
				double velZValue = velZExpr.GetValue(validVarsValue);

				physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _name + wxString::Format("%i", tempObjectCount++), enabled, false, 0.0f, (float)massValue, Vector3((float)posXValue, (float)posYValue, (float)posZValue) + relativePos,
					Vector3((float)velXValue, (float)velYValue, (float)velZValue) + relativeVel, radiusValue));

				if (onceZInterval)
					break;
			}

			if (onceYInterval)
				break;
		}

		if (onceXInterval)
			break;
	}

	SetUnSaved();
}

void GravitationSimulation::RemoveObject(int index)
{
	physicsEngine->RemovePhysicsObject(index);

	SetUnSaved();
}

void GravitationSimulation::ChangeEnabledState(int index)
{
	PhysicsObject* obj = physicsEngine->GetObjectList()->GetAt(index)->GetData();
	if (obj->GetEnabled())
	{
		obj->Disable();	
	}
	else
	{
		obj->Enable();
	}

	SetUnSaved();
}

void GravitationSimulation::ChangeSelections(wxArrayInt indices)
{
	static SColor newColor = SColor(255, 255, 255, 0);

	SColor whiteColor = SColor(255, 255, 255, 255);

	foreach(PhysicsObject*, objIt, physicsEngine->GetObjectList())
	{
		((VisiblePhysicsObject*)objIt->GetData())->ChangeObjectColor(whiteColor);
	}
	selectedObjectsIndexes->Clear();
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		((VisiblePhysicsObject*)physicsEngine->GetObjectList()->GetAt(indices[i])->GetData())->ChangeObjectColor(newColor);
	}
}


void GravitationSimulation::Reset()
{
	Simulation::Reset();

	physicsEngine->Clear();
	selectedObjectsIndexes->Clear();
}

void GravitationSimulation::Update(float timeInSecondsSinceLastFrame, bool ignorePaused)
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
}

void GravitationSimulation::UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport)
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

void GravitationSimulation::Draw(WxIrrViewport* currentViewport)
{
	Simulation::Draw(currentViewport);
}


void GravitationSimulation::StartRecording()
{
	Simulation::StartRecording();
	Simulation::StartPhysicsEngineRecording();
}

void GravitationSimulation::StopRecording()
{
	Simulation::StopRecording();
	Simulation::StopPhysicsEngineRecording();
}


void GravitationSimulation::SerializeIn(istream &is)
{
	Simulation::SerializeIn(is);

	foreach(PhysicsObject*, objIt, physicsEngine->GetObjectList())
	{
		PhysicsObject* obj = objIt->GetData();

		AddObjectToListBox(obj->GetName(), obj->GetEnabled());
	}
}
//void SerializeOut(ostream &os)
//{
//	Simulation::SerializeOut(os);
//}
