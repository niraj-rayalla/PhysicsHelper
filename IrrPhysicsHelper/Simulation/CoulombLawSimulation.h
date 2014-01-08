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

#ifndef _WX_IRR_COULOMB_LAW_SIMULATION
#define _WX_IRR_COULOMB_LAW_SIMULATION

#include "Simulation.h"
#include "../General/ThreeDArrowList.h"

class PotentialSensor
{
private:
	Vector3 position;
	Vector3 electricField;
	float potential;
	ThreeDArrow* arrowRender;

public:
	PotentialSensor(Vector3 pos)
	{
		position = pos;
		electricField = Vector3(0,0,0);
		potential = 0;
		arrowRender = new ThreeDArrow(SColor(255, 255, 0, 0));
		arrowRender->Update(position, electricField);
	}

	~PotentialSensor()
	{
		delete arrowRender;
	}

	void ResetValues()
	{
		electricField = Vector3(0,0,0);
		potential = 0;
	}

	void SetValues(Vector3& elecField, float pot, bool normalize = false)
	{
		electricField = elecField;
		potential = pot;

		if (normalize)
			electricField.normalize();

		arrowRender->Update(position, electricField);
	}

	void SetValues(ElectricFieldPotReturnType& value, bool normalize = false)
	{
		electricField = value.electricField;
		potential = value.potential;

		if (normalize)
			electricField.normalize();

		arrowRender->Update(position, electricField);
	}

	Vector3 GetPosition() { return position; }

	void Draw(IVideoDriver* driver)
	{
		arrowRender->Draw(driver);
	}
};

class VectorElectricFieldCameraPlaneRenderer
{
private:
	PhysicsObject* obj;
	ICameraSceneNode* lastLocalCamera;
	List<ThreeDArrow*>* arrowList;

	ThreeDArrowList threeDArrowList;
	List<ThreeDArrow*>::iterator threeDArrowListReferenceStart;

	static unsigned int resolution;
	static unsigned int depth;
	static float depthLength;

	static List<Vector3> startingPoints;
	static ICameraSceneNode* lastCamera;
	static Vector3 lastCameraDir;
public:
	VectorElectricFieldCameraPlaneRenderer(PhysicsObject* _obj, PhysicsEngine* physicsEngine)
	{
		obj = _obj;
		lastLocalCamera = NULL;
		arrowList = new List<ThreeDArrow*>();

		if (startingPoints.GetSize() == 0)
		{
			SetupStartingPoints(NULL);
		}

		List<Vector3>* startingPointsPointer = &startingPoints;
		foreach(Vector3, vecIt, startingPointsPointer)
		{
			Vector3 lastPos = vecIt->GetData();
			for(unsigned int i = 0; i < depth; i++)
			{
				ThreeDArrow* newArrow = new ThreeDArrow(SColor(255, 255, 0, 255));
				arrowList->Add(newArrow);

				Vector3 dir = physicsEngine->GetElecFieldPotAtPoint(lastPos).electricField.normalize()*depthLength;
				newArrow->Update(lastPos, dir);
				lastPos += dir;
			}
		}

		threeDArrowListReferenceStart = threeDArrowList.Add(arrowList);
		arrowList = NULL;
	}

	~VectorElectricFieldCameraPlaneRenderer()
	{
		//delete arrowList;
	}

	void Draw(ICameraSceneNode* currentCamera, PhysicsEngine* physicsEngine, IVideoDriver* driver, bool isPaused)
	{
		//if (!isPaused)
		SetupStartingPoints(currentCamera, obj);

		//Change points.
		List<ThreeDArrow*>::iterator currentThreeDArrow = threeDArrowListReferenceStart;
		List<Vector3>* startingPointsPointer = &startingPoints;
		foreach(Vector3, vecIt, startingPointsPointer)
		{
			Vector3 lastPos = vecIt->GetData() + obj->GetPosition();
			for(unsigned int i = 0; i < depth; i++)
			{
				Vector3 dir = physicsEngine->GetElecFieldPotAtPoint(lastPos).electricField.normalize()*depthLength;
				currentThreeDArrow->GetData()->Update(lastPos, dir);
				lastPos += dir;

				currentThreeDArrow->advance(currentThreeDArrow);
			}
		}

		/*foreach(ThreeDArrow*, arrowIt, arrowList)
		{
			arrowIt->GetData()->Draw(driver);
		}*/
		threeDArrowList.Update();
		threeDArrowList.Draw(driver);
	}

	static void SetupStartingPoints(ICameraSceneNode* currentCamera, PhysicsObject* obj = NULL)
	{
		if (!currentCamera)
		{
			startingPoints.Clear();

			float currentAngle = 0.0f;
			float changeAngle = 2.0f*PI / resolution;

			for(unsigned int i = 0; i < resolution; i++)
			{
				float x = cosf(currentAngle);
				float y = sinf(currentAngle);

				startingPoints.Add(Vector3(x, y, 0.0f));

				currentAngle += changeAngle;
			}

			lastCameraDir = Vector3_Zero;
		}
		else
		{
			if (obj)
			{
				Vector3 currentCameraDir = (obj->GetPosition() - currentCamera->getPosition()).normalize();
				Vector3 zeroAngleVec = currentCamera->getUpVector().crossProduct(currentCameraDir).normalize();

				if (currentCameraDir != lastCameraDir)
				{
					startingPoints.Remove(0);
					startingPoints.AddAt(0, zeroAngleVec);

					float changeAngle = 2.0f*PI / resolution;
					float currentAngle = changeAngle;

					List<Vector3>::iterator currentPointIt = startingPoints.GetAt(1);
					for(unsigned int i = 1; i < resolution; i++)
					{
						List<Vector3>::iterator removeIt = currentPointIt;

						quaternion quat(0, 0, 0);
						quat.fromAngleAxis(currentAngle, currentCameraDir);

						Vector3 rotVec;
						quat.toEuler(rotVec);

						currentPointIt = startingPoints.AddBefore(currentPointIt,
							(rotVec*RADTODEG).rotationToDirection(zeroAngleVec));

						startingPoints.Remove(removeIt);

						currentAngle += changeAngle;
						currentPointIt->advance(currentPointIt);
					}

					lastCameraDir = currentCameraDir;
				}
			}
		}
	}
};

//class VectorElectricFieldSphericalRenderer
//{
//private:
//	PhysicsObject* obj;
//	List<ThreeDArrow*>* arrowList;
//
//	static unsigned int resolution;
//	static unsigned int depth;
//	static float depthLength;
//	static irr::core::array<S3DVertex> vertexArray;
//	static irr::core::array<u16> indexArray;
//
//	S3DVertex* vertexStartPointer;
//
//	List<Vector3> startingPoints;
//public:
//	VectorElectricFieldSphericalRenderer(PhysicsObject* _obj, PhysicsEngine* physicsEngine)
//	{
//		obj = _obj;
//		arrowList = new List<ThreeDArrow*>();
//
//		if (startingPoints.GetSize() == 0)
//		{
//			SetupStartingPoints();
//		}
//		
//		if (vertexArray.size() == 0)
//			vertexArray.set_used(1);
//		vertexStartPointer = vertexArray.pointer() + vertexArray.size();
//
//		List<Vector3>* startingPointsPointer = &startingPoints;
//		foreach(Vector3, vecIt, startingPointsPointer)
//		{
//			Vector3 lastPos = vecIt->GetData();
//			for(unsigned int i = 0; i < depth; i++)
//			{
//				ThreeDArrow* newArrow = new ThreeDArrow(SColor(255, 255, 0, 255));
//				arrowList->Add(newArrow);
//
//				int size = vertexArray.size();
//				S3DVertex* arrowVertexPointer = newArrow->GetVerticesPointer();
//				u16* arrowIndexPointer = newArrow->GetIndicesPointer();
//				for (int j = 0; j < 4; j++)
//				{
//					vertexArray.push_back(arrowVertexPointer[j]);
//				}
//				for (int j = 0; j < 6; j++)
//				{
//					indexArray.push_back(arrowIndexPointer[j] + size);
//				}
//
//				Vector3 dir = physicsEngine->GetElecFieldPotAtPoint(lastPos).electricField.normalize()*depthLength;
//				newArrow->Update(lastPos, dir);
//				lastPos += dir;
//			}
//		}
//	}
//
//	~VectorElectricFieldSphericalRenderer()
//	{
//		delete arrowList;
//	}
//
//	void Draw(PhysicsEngine* physicsEngine, IVideoDriver* driver)
//	{
//		//Change points.
//		List<ThreeDArrow*>::iterator currentThreeDArrow = arrowList->begin();
//		List<Vector3>* startingPointsPointer = &startingPoints;
//		int vertIndex = 0;
//		/*foreach(Vector3, vecIt, startingPointsPointer)
//		{
//			Vector3 lastPos = vecIt->GetData() + obj->GetPosition();
//			for(unsigned int i = 0; i < depth; i++)
//			{
//				Vector3 dir = physicsEngine->GetElecFieldPotAtPoint(lastPos).electricField.normalize()*depthLength;
//				currentThreeDArrow->GetData()->Update(lastPos, dir);
//
//				S3DVertex* arrowVertexPointer = currentThreeDArrow->GetData()->GetVerticesPointer();
//				for (int j = 0; j < 4; j++)
//				{
//					vertexArray.pointer()[vertIndex + 1].Pos = arrowVertexPointer[j].Pos;
//					vertIndex++;
//				}
//
//				lastPos += dir;
//
//				currentThreeDArrow->advance(currentThreeDArrow);
//			}
//		}*/
//
//		/*foreach(ThreeDArrow*, arrowIt, arrowList)
//		{
//			arrowIt->GetData()->Draw(driver);
//		}*/
//
//		driver->setTransform(video::ETS_WORLD, ThreeDArrow::mat);
//		driver->drawVertexPrimitiveList(vertexArray.pointer(), vertexArray.size(), indexArray.pointer(), indexArray.size()/2, EVT_STANDARD, EPT_LINES, EIT_16BIT);
//	}
//
//	void SetupStartingPoints()
//	{		
//		startingPoints.Clear();
//
//		float currentThetaAngle = 0.0f;
//		float currentPhiAngle = 0.0f;
//		float changeAngle = 2.0f*PI / resolution;
//
//		for(unsigned int i = 0; i < resolution; i++)
//		{
//			for(unsigned int j = 0; j < resolution; j++)
//			{				
//				float x = sinf(currentPhiAngle)*cosf(currentThetaAngle);
//				float y = sinf(currentPhiAngle)*sinf(currentThetaAngle);
//				float z = cosf(currentPhiAngle);
//
//				startingPoints.Add(Vector3(x, y, z));
//				
//				currentPhiAngle += changeAngle;
//			}
//
//			currentThetaAngle += changeAngle;
//		}
//	}
//};

class VectorElectricFieldSphericalRenderer
{
private:
	PhysicsObject* obj;
	List<ThreeDArrow*>* arrowList;

	List<ThreeDArrow*>::iterator threeDArrowListReferenceStart;

	static unsigned int resolution;
	static unsigned int depth;
	static float depthLength;
	static ThreeDArrowList staticArrowList;

	static List<Vector3> startingPoints;
public:
	VectorElectricFieldSphericalRenderer(PhysicsObject* _obj, PhysicsEngine* physicsEngine)
	{
		obj = _obj;
		arrowList = new List<ThreeDArrow*>();

		if (startingPoints.GetSize() == 0)
		{
			SetupStartingPoints();
		}

		List<Vector3>* startingPointsPointer = &startingPoints;
		foreach(Vector3, vecIt, startingPointsPointer)
		{
			Vector3 lastPos = vecIt->GetData() + obj->GetPosition();
			for(unsigned int i = 0; i < depth; i++)
			{
				ThreeDArrow* newArrow = new ThreeDArrow(SColor(255, 255, 0, 255));
				arrowList->Add(newArrow);

				Vector3 dir = physicsEngine->GetElecFieldPotAtPoint(lastPos).electricField.normalize()*depthLength;
				newArrow->Update(lastPos, dir);
				lastPos += dir;
			}
		}

		threeDArrowListReferenceStart = staticArrowList.Add(arrowList);
		arrowList = NULL;
	}

	~VectorElectricFieldSphericalRenderer()
	{
		//delete arrowList;
	}

	static void DrawStaticArrowList(IVideoDriver* driver)
	{
		staticArrowList.Draw(driver);
	}

	void Update(PhysicsEngine* physicsEngine)
	{
		List<ThreeDArrow*>::iterator currentThreeDArrow = threeDArrowListReferenceStart;
		List<Vector3>* startingPointsPointer = &startingPoints;
		foreach(Vector3, vecIt, startingPointsPointer)
		{
			Vector3 lastPos = vecIt->GetData() + obj->GetPosition();
			for(unsigned int i = 0; i < depth; i++)
			{
				Vector3 dir = physicsEngine->GetElecFieldPotAtPoint(lastPos).electricField.normalize()*depthLength;
				currentThreeDArrow->GetData()->Update(lastPos, dir);

				lastPos += dir;

				currentThreeDArrow->advance(currentThreeDArrow);
			}
		}
	}

	static void UpdateStaticArrowList()
	{
		staticArrowList.Update();
	}

	void Draw(PhysicsEngine* physicsEngine, IVideoDriver* driver)
	{
		//Change points.
		List<ThreeDArrow*>::iterator currentThreeDArrow = arrowList->begin();
		List<Vector3>* startingPointsPointer = &startingPoints;
		int vertIndex = 0;
		/*foreach(Vector3, vecIt, startingPointsPointer)
		{
			Vector3 lastPos = vecIt->GetData() + obj->GetPosition();
			for(unsigned int i = 0; i < depth; i++)
			{
				Vector3 dir = physicsEngine->GetElecFieldPotAtPoint(lastPos).electricField.normalize()*depthLength;
				currentThreeDArrow->GetData()->Update(lastPos, dir);

				S3DVertex* arrowVertexPointer = currentThreeDArrow->GetData()->GetVerticesPointer();
				for (int j = 0; j < 4; j++)
				{
					vertexArray.pointer()[vertIndex + 1].Pos = arrowVertexPointer[j].Pos;
					vertIndex++;
				}

				lastPos += dir;

				currentThreeDArrow->advance(currentThreeDArrow);
			}
		}*/

		/*foreach(ThreeDArrow*, arrowIt, arrowList)
		{
			arrowIt->GetData()->Draw(driver);
		}*/

		//staticArrowList.Draw(driver);
	}

	static void SetupStartingPoints()
	{		
		startingPoints.Clear();

		float currentThetaAngle = 0.0f;
		float currentPhiAngle = 0.0f;
		float changeAngle = 2.0f*PI / resolution;

		for(unsigned int i = 0; i < resolution; i++)
		{
			for(unsigned int j = 0; j < resolution; j++)
			{				
				float x = sinf(currentPhiAngle)*cosf(currentThetaAngle);
				float y = sinf(currentPhiAngle)*sinf(currentThetaAngle);
				float z = cosf(currentPhiAngle);

				startingPoints.Add(Vector3(x, y, z));
				
				currentPhiAngle += changeAngle;
			}

			currentThetaAngle += changeAngle;
		}
	}
};

class CoulombLawSimulation : public Simulation
{
private:
	bool showSensors;
	List<PotentialSensor*>* sensorList;
	List<int>* selectedObjectsIndexes;

	bool showVectorFieldSensors;
	List<PotentialSensor*>* vectorFieldSensorList;
	
	List<VectorElectricFieldCameraPlaneRenderer*> vectorFieldSensorCameraList;
	List<VectorElectricFieldSphericalRenderer*> vectorFieldSensorSphericalList;	

	Vector3 uniformElectricField;
	
	void (*AddObjectToListBox)(wxString str, bool enabled);
public:
	CoulombLawSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*AddObjectToListBox)(wxString str, bool enabled));
	~CoulombLawSimulation();

	void AddObject(wxString _name, Vector3 pos, Vector3 intVel, float mass, float charge, bool isRelative, int relativeIndex, float radius = 1.0f, bool enabled = true);
	void AddObject(wxString _name, std::string mass, std::string charge, std::string radius, vector3d<std::string> posStrings, Vector3 posBegins, Vector3 posEnds, Vector3 posResolutions,
		vector3d<std::string> velStrings, bool isRelative, int relativeIndex, bool enabled = true);
	void RemoveObject(int index);
	void ChangeEnabledState(int index);
	void ChangeSelections(wxArrayInt indices);

	void AddSensor(Vector3 pos);
	void RemoveSensor(int index);

	void ShowSensors() { showSensors = true; }
	void HideSensors() { showSensors = false; }

	void Reset();

	void Update(float timeInSecondsSinceLastFrame, bool ignorePaused = false);
	void UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport);

	void Draw(WxIrrViewport* currentViewport = 0);

	void StartRecording();
	void StopRecording();
	
	void SetUniformElectricField(Vector3& field);

	void ShowVectorFieldSensors();
	void HideVectorFieldSensors();
	void AddVectorFieldSensors(vector3d<std::string>& posStrings, Vector3& posBegins, Vector3& posEnds, Vector3& posResolutions);
	void ClearVectorFieldSensors();

	void SerializeIn(istream &is);
};

#endif