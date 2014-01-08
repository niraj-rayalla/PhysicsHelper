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

#include "CoulombLawSimulation.h"

List<Vector3> VectorElectricFieldCameraPlaneRenderer::startingPoints;
ICameraSceneNode* VectorElectricFieldCameraPlaneRenderer::lastCamera = NULL;
Vector3 VectorElectricFieldCameraPlaneRenderer::lastCameraDir = Vector3_Zero;
unsigned int VectorElectricFieldCameraPlaneRenderer::resolution = 6;
unsigned int VectorElectricFieldCameraPlaneRenderer::depth = 3;
float VectorElectricFieldCameraPlaneRenderer::depthLength = 0.5f;

//unsigned int VectorElectricFieldSphericalRenderer::resolution = 30;
//unsigned int VectorElectricFieldSphericalRenderer::depth = 9;
//float VectorElectricFieldSphericalRenderer::depthLength = 0.5f;
//irr::core::array<S3DVertex> VectorElectricFieldSphericalRenderer::vertexArray;
//irr::core::array<u16> VectorElectricFieldSphericalRenderer::indexArray;

unsigned int VectorElectricFieldSphericalRenderer::resolution = 16;
unsigned int VectorElectricFieldSphericalRenderer::depth = 9;
float VectorElectricFieldSphericalRenderer::depthLength = 0.5f;
ThreeDArrowList VectorElectricFieldSphericalRenderer::staticArrowList;
List<Vector3> VectorElectricFieldSphericalRenderer::startingPoints;

CoulombLawSimulation::CoulombLawSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*addObjectToListBox)(wxString str, bool enabled))
: Simulation(dev, _driver, _physicsEngine, SimulationType_CoulombLaw)
{
	physicsEngine->EnableMagnetism();

	sensorList = new List<PotentialSensor*>();
	selectedObjectsIndexes = new List<int>();

	AddObjectToListBox = addObjectToListBox;

	showVectorFieldSensors = false;
	vectorFieldSensorList = new List<PotentialSensor*>();
}

CoulombLawSimulation::~CoulombLawSimulation()
{
	physicsEngine->DisableMagnetism();
	delete sensorList;
	delete selectedObjectsIndexes;
	delete vectorFieldSensorList;
}

void CoulombLawSimulation::AddObject(wxString _name, Vector3 pos, Vector3 intVel, float mass, float charge, bool isRelative, int relativeIndex, float radius, bool enabled)
{
	if (isRelative)
	{
		PhysicsObject* obj = physicsEngine->GetObjectList()->GetAt(relativeIndex)->GetData();

		pos += obj->GetPosition();
		intVel += obj->GetVelocity();
	}

	PhysicsObject* newObj = new SimulationObject_Sphere(device->getSceneManager(), _name, enabled, charge != 0.0f, charge, mass, pos, intVel, radius);
	physicsEngine->AddPhysicsObject(newObj);

	if (charge > 0.0f)
	{
		vectorFieldSensorCameraList.Add(new VectorElectricFieldCameraPlaneRenderer(newObj, physicsEngine));
		//vectorFieldSensorSphericalList.Add(new VectorElectricFieldSphericalRenderer(newObj, physicsEngine));
	}

	/*List<VectorElectricFieldSphericalRenderer*>* vectorFieldSensorSphericalListPointer = &vectorFieldSensorSphericalList;
	foreach(VectorElectricFieldSphericalRenderer*, vecFieldIt, vectorFieldSensorSphericalListPointer)
	{
		vecFieldIt->GetData()->Update(physicsEngine);
	}
	VectorElectricFieldSphericalRenderer::UpdateStaticArrowList();*/

	SetUnSaved();
}

void CoulombLawSimulation::AddObject(wxString _name, std::string mass, std::string charge, std::string radius, vector3d<std::string> posStrings, Vector3 posBegins, Vector3 posEnds, Vector3 posResolutions,
		vector3d<std::string> velStrings, bool isRelative, int relativeIndex, bool enabled)
{
	MathExpression massExpr = MathExpression(mass.c_str(), MathExpression::cartesianMathExpr, 3);
	MathExpression chargeExpr = MathExpression(charge.c_str(), MathExpression::cartesianMathExpr, 3);
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
				double chargeValue = chargeExpr.GetValue(validVarsValue);
				double radiusValue = radiusExpr.GetValue(validVarsValue);

				double posXValue = posXExpr.GetValue(validVarsValue);
				double posYValue = posYExpr.GetValue(validVarsValue);
				double posZValue = posZExpr.GetValue(validVarsValue);

				double velXValue = velXExpr.GetValue(validVarsValue);
				double velYValue = velYExpr.GetValue(validVarsValue);
				double velZValue = velZExpr.GetValue(validVarsValue);

				physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), _name + wxString::Format("%i", tempObjectCount++), enabled, chargeValue != 0.0, chargeValue, (float)massValue, Vector3((float)posXValue, (float)posYValue, (float)posZValue) + relativePos,
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

void CoulombLawSimulation::RemoveObject(int index)
{
	physicsEngine->RemovePhysicsObject(index);

	SetUnSaved();
}

void CoulombLawSimulation::AddSensor(Vector3 pos)
{
	sensorList->Add(new PotentialSensor(pos), true);

	SetUnSaved();
}

void CoulombLawSimulation::RemoveSensor(int index)
{
	sensorList->Remove(index);

	SetUnSaved();
}


void CoulombLawSimulation::ChangeEnabledState(int index)
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

void CoulombLawSimulation::ChangeSelections(wxArrayInt indices)
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


void CoulombLawSimulation::Reset()
{
	Simulation::Reset();

	physicsEngine->Clear();
	sensorList->Clear();
	selectedObjectsIndexes->Clear();

	showVectorFieldSensors = false;
	vectorFieldSensorList->Clear();
}

void CoulombLawSimulation::Update(float timeInSecondsSinceLastFrame, bool ignorePaused)
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
		if (showSensors)
		{
			foreach(PotentialSensor*, sensor, sensorList)
			{
				PotentialSensor* sensorData = sensor->GetData();
				ElectricFieldPotReturnType electricFieldPot = physicsEngine->GetElecFieldPotAtPoint(sensorData->GetPosition());
				sensorData->SetValues(electricFieldPot);
			}
		}

		if (showVectorFieldSensors)
		{
			foreach(PotentialSensor*, sensor, vectorFieldSensorList)
			{
				PotentialSensor* sensorData = sensor->GetData();
				ElectricFieldPotReturnType electricFieldPot = physicsEngine->GetElecFieldPotAtPoint(sensorData->GetPosition());
				sensorData->SetValues(electricFieldPot, true);
			}

			List<VectorElectricFieldSphericalRenderer*>* vectorFieldSensorSphericalListPointer = &vectorFieldSensorSphericalList;
			foreach(VectorElectricFieldSphericalRenderer*, vecFieldIt, vectorFieldSensorSphericalListPointer)
			{
				vecFieldIt->GetData()->Update(physicsEngine);
			}
			if (vectorFieldSensorSphericalList.GetSize() > 0)
			{
				VectorElectricFieldSphericalRenderer::UpdateStaticArrowList();
			}
		}
	}
}

void CoulombLawSimulation::UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport)
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

void CoulombLawSimulation::Draw(WxIrrViewport* currentViewport)
{
	Simulation::Draw(currentViewport);

	if (showSensors)
	{
		foreach(PotentialSensor*, sensor, sensorList)
		{
			sensor->GetData()->Draw(driver);
		}
	}

	if (showVectorFieldSensors)
	{
		foreach(PotentialSensor*, sensor, vectorFieldSensorList)
		{
			sensor->GetData()->Draw(driver);
		}
		
		List<VectorElectricFieldCameraPlaneRenderer*>* vectorFieldSensorCameraListPointer = &vectorFieldSensorCameraList;
		foreach(VectorElectricFieldCameraPlaneRenderer*, vecFieldIt, vectorFieldSensorCameraListPointer)
		{
			vecFieldIt->GetData()->Draw(device->getSceneManager()->getActiveCamera(), physicsEngine, driver, !IsRunning());
		}

		/*List<VectorElectricFieldSphericalRenderer*>* vectorFieldSensorSphericalListPointer = &vectorFieldSensorSphericalList;
		foreach(VectorElectricFieldSphericalRenderer*, vecFieldIt, vectorFieldSensorSphericalListPointer)
		{
			vecFieldIt->GetData()->Draw(physicsEngine, driver);
		}*/
		VectorElectricFieldSphericalRenderer::DrawStaticArrowList(driver);
	}
}


void CoulombLawSimulation::StartRecording()
{
	Simulation::StartRecording();
	Simulation::StartPhysicsEngineRecording();
}

void CoulombLawSimulation::StopRecording()
{
	Simulation::StopRecording();
	Simulation::StopPhysicsEngineRecording();
}

void CoulombLawSimulation::SetUniformElectricField(Vector3& field)
{
	uniformElectricField = field;
}

void CoulombLawSimulation::ShowVectorFieldSensors()
{
	showVectorFieldSensors = true;
}
void CoulombLawSimulation::HideVectorFieldSensors()
{
	showVectorFieldSensors = false;
}
void CoulombLawSimulation::AddVectorFieldSensors(vector3d<std::string>& posStrings, Vector3& posBegins, Vector3& posEnds, Vector3& posResolutions)
{
	//vectorFieldSensorList->Append(sensors);

	ShowVectorFieldSensors();

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

				double posXValue = posXExpr.GetValue(validVarsValue);
				double posYValue = posYExpr.GetValue(validVarsValue);
				double posZValue = posZExpr.GetValue(validVarsValue);

				vectorFieldSensorList->Add(new PotentialSensor(Vector3((float)posXValue, (float)posYValue, (float)posZValue)));

				if (onceZInterval)
					break;
			}

			if (onceYInterval)
				break;
		}

		if (onceXInterval)
			break;
	}

	foreach(PotentialSensor*, sensor, vectorFieldSensorList)
	{
		PotentialSensor* sensorData = sensor->GetData();
		ElectricFieldPotReturnType electricFieldPot = physicsEngine->GetElecFieldPotAtPoint(sensorData->GetPosition());
		sensorData->SetValues(electricFieldPot, true);
	}
}
void CoulombLawSimulation::ClearVectorFieldSensors()
{
	vectorFieldSensorList->Clear();
}

void CoulombLawSimulation::SerializeIn(istream &is)
{
	Simulation::SerializeIn(is);

	foreach(PhysicsObject*, objIt, physicsEngine->GetObjectList())
	{
		PhysicsObject* obj = objIt->GetData();

		AddObjectToListBox(obj->GetName(), obj->GetEnabled());
	}
}
