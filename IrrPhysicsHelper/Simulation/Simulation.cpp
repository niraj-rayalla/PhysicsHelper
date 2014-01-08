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

#include "Simulation.h"

WxIrrViewportManager* Simulation::viewportManager = NULL;
UIController* Simulation::uiController = NULL;

Simulation::ChangeStatusBarText Simulation::changeStatusBarTextFunctionPointer = NULL;

Simulation::Simulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, SimulationType _simulationType, CustomSceneNodeManager* _customSceneNodeManager )
{
	simulationPaused = true;
	forward = true;
	timePassedFrame = 0.0f;
	timePassedDirectionFrame = 0.0f;
	totalTime = 0.0f;
	timeScale = 1.0f;

	timeSkipAmount = 1.0f;

	device = dev;
	driver = _driver;
	guiEnv = device->getGUIEnvironment();

	physicsEngine = _physicsEngine;

	simulationType = _simulationType;
	customSceneNodeManager = _customSceneNodeManager;

	statusBarText = _("Physics Helper");

	basicMaterial = SMaterial();
	basicMaterial.Lighting = false;

	ShowVelocityArrow();
	ShowAccelerationArrow();
	ShowForceArrow();
	HideAngularVelocityArrow();
	showAllAccelerations = false;
	showAllForces = false;

	XZGridSceneNode = NULL;
	hideXZGrid();
	XYGridSceneNode = NULL;
	hideXYGrid();
	YZGridSceneNode = NULL;
	hideYZGrid();

	showAxes = true;
	showNames = false;

	SetXAxisColor(SColor(255, 197, 227, 137));
	SetYAxisColor(SColor(255, 0, 0, 200));
	SetZAxisColor(SColor(255, 255, 255, 0));

	axesPoints[0] = S3DVertex(Vector3(-2000.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), XAxisColor, vector2d<float>(0.0f, 0.0f)); 
	axesPoints[1] = S3DVertex(Vector3(2000.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), XAxisColor, vector2d<float>(0.0f, 0.0f));
	axesPoints[2] = S3DVertex(Vector3(0.0, -2000.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), YAxisColor, vector2d<float>(0.0f, 0.0f));
	axesPoints[3] = S3DVertex(Vector3(0.0, 2000.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), YAxisColor, vector2d<float>(0.0f, 0.0f));
	axesPoints[4] = S3DVertex(Vector3(0.0, 0.0, -2000.0f), Vector3(0.0f, 0.0f, 0.0f), ZAxisColor, vector2d<float>(0.0f, 0.0f));
	axesPoints[5] = S3DVertex(Vector3(0.0, 0.0, 2000.0f), Vector3(0.0f, 0.0f, 0.0f), ZAxisColor, vector2d<float>(0.0f, 0.0f));

	axesIndices[0] = 0;
	axesIndices[1] = 1;
	axesIndices[2] = 2;
	axesIndices[3] = 3;
	axesIndices[4] = 4;
	axesIndices[5] = 5;

	saved = true;

	isRecording = false;
	isRecordingFirstFrame = true;

	selectedObjects = new List<ISceneNode*>();

	recordingObjects = new List<PhysicsObject*>();

	isMouseChecking = false;
	numOfMouseClicks = 0;
	mouseOverSceneNode = NULL;
	tempAddMouseObject = NULL;
	threeDMousePosition = Vector3_Zero;

	mousePickingPlane = ThreeDPlane(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
	UsePlaneForMousePicking(false, Vector3_Zero);
	EnableRotationOfMousePlane(AxisIdentifier_ALL);

	moveToList = new List<Vector3>();

	Pause();

	/*PhysicsObject* obj1 = new SimulationObject_Sphere(device->getSceneManager(), false, false, 0.0f, 100.0f, Vector3(0.0f, 0.0f, 0.0f));
	obj2 = new SimulationObject_Cube(device->getSceneManager(), true, false, 0.0f, 1.0f, Vector3(3.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
	PhysicsObject* obj3 = new SimulationObject_Cube(device->getSceneManager(), true, false, 0.0f, 1.0f, Vector3(7.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
	PhysicsObject* obj4 = new SimulationObject_Cube(device->getSceneManager(), true, false, 0.0f, 1.0f, Vector3(19.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
	physicsEngine->AddPhysicsObject(obj1);
	physicsEngine->AddPhysicsObject(obj2);
	physicsEngine->AddPhysicsObject(obj3);
	physicsEngine->AddPhysicsObject(obj4);
	physicsEngine->AddSpring(obj1, obj2);
	physicsEngine->AddSpring(obj2, obj3);
	physicsEngine->AddSpring(obj3, obj4);*/
	//physicsEngine->AddForce(new UniformalForce(Vector3(0.0f, -9.8f, 0.0f)));

	//std::string validVars[1] = {"x"};
	//MathExpression mathExpr = MathExpression("sin(x)", validVars, 1);
	//double validVarsValue[1] = {10};

	//for (double x = 5.0; x <= 10.0; x+=1.0)
	//{
	//	validVarsValue[0] = x;
	//	double yVal = mathExpr.GetValue(validVarsValue);

	//	//physicsEngine->AddPhysicsObject(new SimulationObject_Sphere(device->getSceneManager(), false, false, 0.0f, 100.0f, Vector3(x, yVal, 0.0f)));
	//}
}

Simulation::~Simulation()
{
	Clear();

	delete selectedObjects;

	delete recordingObjects;

	if (tempAddMouseObject)
		tempAddMouseObject->remove();

	if (XZGridSceneNode)
		XZGridSceneNode->remove();
	if (XYGridSceneNode)
		XYGridSceneNode->remove();
	if (YZGridSceneNode)
		YZGridSceneNode->remove();

	delete moveToList;
}

void Simulation::Clear()
{
	physicsEngine->Clear();
	recordingObjects->Clear();
	moveToList->Clear();

	mouseOverSceneNode = NULL;
}

void Simulation::CopyBasicSimulationAttributes(Simulation* existingSimulation)
{
	if (existingSimulation)
	{
		SetXAxisColor(existingSimulation->GetXAxisColor());
		SetYAxisColor(existingSimulation->GetYAxisColor());
		SetZAxisColor(existingSimulation->GetZAxisColor());

		if (existingSimulation->showXYGridSceneNode)
		{
			existingSimulation->showXYGrid();
		}
		else
		{
			existingSimulation->hideXYGrid();
		}

		if (existingSimulation->showXZGridSceneNode)
		{
			existingSimulation->showXZGrid();
		}
		else
		{
			existingSimulation->hideXZGrid();
		}

		if (existingSimulation->showXZGridSceneNode)
		{
			existingSimulation->showYZGrid();
		}
		else
		{
			existingSimulation->hideYZGrid();
		}

		if (existingSimulation->showVelocity)
		{
			ShowVelocityArrow();
		}
		else
		{
			HideVelocityArrow();
		}

		if (existingSimulation->showAngularVelocity)
		{
			ShowAngularVelocityArrow();
		}
		else
		{
			HideAngularVelocityArrow();
		}

		if (existingSimulation->showVelocity)
		{
			ShowVelocityArrow();
		}
		else
		{
			HideVelocityArrow();
		}
	}
}

void Simulation::Update(float timePassedSeconds, bool ignorePaused)
{
	if (!simulationPaused || ignorePaused)
	{
		timePassedFrame = timePassedSeconds;
		timePassedFrame *= timeScale;
        if (forward)
        {
            timePassedDirectionFrame = timePassedFrame;
            totalTime += timePassedFrame;
        }
        else
        {
            timePassedDirectionFrame = -timePassedFrame;
            totalTime -= timePassedFrame;
        }
	}

	changeStatusBarTextFunctionPointer(statusBarText);
}

void Simulation::UpdateAfter(float timePassedSeconds, WxIrrViewport* viewport)
{
	//if(viewport)
	//{
	//	List<List<Vector3>::iterator>* removeList = new List<List<Vector3>::iterator>();

	//	foreach(Vector3, pointIt, moveToList)
	//	{
	//		/*bool isDone = viewport->MoveAndRotateCamLinearToPoint(pointIt->GetData(), 2.0f, 2.5f, timePassedSeconds, 15.0f);

	//		if(isDone)
	//			removeList->Add(pointIt, false);*/
	//	}

	//	foreach(List<Vector3>::iterator, removeIt, removeList)
	//	{
	//		moveToList->Remove(removeIt->GetData());
	//	}

	//	delete removeList;
	//}
}

void Simulation::Draw(WxIrrViewport* currentViewport)
{
	driver->setTransform(video::ETS_WORLD, matrix4());
	if (showAxes)
	{
		//Draw the axes
		driver->setMaterial(basicMaterial);
		driver->drawVertexPrimitiveList(axesPoints, 6, axesIndices, 3, EVT_STANDARD, EPT_LINES, EIT_16BIT);
	}

	if (showNetForce)
	{

	}

	if (showNetAcceleration)
	{

	}

	if (showVelocity)
	{
		//obj2->DrawVelocityArrow(driver);
	}

	if (showNames)
	{
		DrawNames(currentViewport);		
	}

	static ISceneNode* shperePointer = NULL;
	if (!shperePointer)
		shperePointer = device->getSceneManager()->addSphereSceneNode(0.7f);
	shperePointer->setPosition(threeDMousePosition);

	//Draw selected object colors
	/*foreach(ISceneNode*, selectedIt, selectedObjects)
	{
		if (selectedIt->GetData() == selectedNode)
			return true;
	}*/
}

void Simulation::DrawNames(WxIrrViewport* currentViewport)
{
	rect<irr::s32> currentViewportWholeArea = viewportManager->GetRootViewport()->GetIrrArea();
	rect<irr::s32> currentViewportClientArea = currentViewport->GetIrrClientArea();

	driver->setViewPort(currentViewportWholeArea);

	stringw text = L"";
	foreach(PhysicsObject*, phyObjIt, physicsEngine->GetObjectList())
	{
		PhysicsObject* currentObj = phyObjIt->GetData();
		text = currentObj->GetName().ToStdWstring().c_str();
		
		DrawTextOnScreenFrom3DPos(currentObj->GetPosition(), currentViewportWholeArea.getWidth(), currentViewportWholeArea.getHeight(), currentViewportClientArea, device->getSceneManager(),
			guiEnv, currentViewport->GetCamera(), text, SColor(255, 0, 0, 255));
	}	

	driver->setViewPort(currentViewportClientArea);
}

void Simulation::Reset()
{
	Clear();
	totalTime = 0.0f;
	timePassedFrame = 0.0f;
	timePassedDirectionFrame = 0.0f;

	selectedObjects->Clear();

	isMouseChecking = false;
	mouseOverSceneNode = NULL;
	if (tempAddMouseObject)
		tempAddMouseObject->remove();
	tempAddMouseObject = NULL;
	threeDMousePosition = Vector3_Zero;

	if (XZGridSceneNode)
	{
		XZGridSceneNode->remove();
	}
	hideXZGrid();
	if (XYGridSceneNode)
	{
		XYGridSceneNode->remove();
	}
	hideXYGrid();
	if (YZGridSceneNode)
	{
		YZGridSceneNode->remove();
	}
	hideYZGrid();

	SetSaved();

	isRecording = false;
	isRecordingFirstFrame = true;
	recordingObjects->Clear();
}

bool Simulation::GetColorChangedFlag()
{
	bool tempColorChanged = colorChangedFlag;
	colorChangedFlag = false;
	return tempColorChanged;
}

void Simulation::SetXAxisColor(SColor& color)
{
	XAxisColor = color;
	axesPoints[0].Color = XAxisColor;
	axesPoints[1].Color = XAxisColor;

	if (showXZGridSceneNode)
	{
		if (XZGridSceneNode)
		{
			XZGridSceneNode->remove();
			XZGridSceneNode = NULL;
		}

		showXZGrid();
	}

	if (showXYGridSceneNode)
	{
		if (XYGridSceneNode)
		{
			XYGridSceneNode->remove();
			XYGridSceneNode = NULL;
		}

		showXYGrid();
	}

	colorChangedFlag = true;
}
void Simulation::SetYAxisColor(SColor& color)
{
	YAxisColor = color;
	axesPoints[2].Color = YAxisColor;
	axesPoints[3].Color = YAxisColor;

	if (showXYGridSceneNode)
	{
		if (XYGridSceneNode)
		{
			XYGridSceneNode->remove();
			XYGridSceneNode = NULL;
		}

		showXYGrid();
	}

	if (showYZGridSceneNode)
	{
		if (YZGridSceneNode)
		{
			YZGridSceneNode->remove();
			YZGridSceneNode = NULL;
		}

		showYZGrid();
	}

	colorChangedFlag = true;
}
void Simulation::SetZAxisColor(SColor& color)
{
	ZAxisColor = color;
	axesPoints[4].Color = ZAxisColor;
	axesPoints[5].Color = ZAxisColor;

	if (showYZGridSceneNode)
	{
		if (YZGridSceneNode)
		{
			YZGridSceneNode->remove();
			YZGridSceneNode = NULL;
		}

		showYZGrid();
	}

	if (showXZGridSceneNode)
	{
		if (XZGridSceneNode)
		{
			XZGridSceneNode->remove();
			XZGridSceneNode = NULL;
		}

		showXZGrid();
	}

	colorChangedFlag = true;
}

void Simulation::showXZGrid()
{
	showXZGridSceneNode = true;

	if (!XZGridSceneNode)
	{
		u32 newRed = (GetXAxisColor().getRed() + GetZAxisColor().getRed()) / 2;
		u32 newGreen = (GetXAxisColor().getGreen() + GetZAxisColor().getGreen()) / 2;
		u32 newBlue = (GetXAxisColor().getBlue() + GetZAxisColor().getBlue()) / 2;

		XZGridSceneNode = new GridSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), 123, SColor(255, newRed, newGreen, newBlue), 101, 101, 10.0f, 10.0f);
		XZGridSceneNode->drop();
	}
	else
	{
		XZGridSceneNode->setVisible(true);
	}

	uiController->SetXZGridVisibility(true);
}

void Simulation::hideXZGrid()
{
	showXZGridSceneNode = false;

	if (XZGridSceneNode)
	{
		XZGridSceneNode->setVisible(false);
	}

	uiController->SetXZGridVisibility(false);
}

void Simulation::showXYGrid()
{
	showXYGridSceneNode = true;

	if (!XYGridSceneNode)
	{
		u32 newRed = (GetXAxisColor().getRed() + GetYAxisColor().getRed()) / 2;
		u32 newGreen = (GetXAxisColor().getGreen() + GetYAxisColor().getGreen()) / 2;
		u32 newBlue = (GetXAxisColor().getBlue() + GetYAxisColor().getBlue()) / 2;

		XYGridSceneNode = new GridSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), 123, SColor(255, newRed, newGreen, newBlue), 101, 101, 10.0f, 10.0f);
		XYGridSceneNode->setRotation(Vector3(90.0f, 0.0f, 0.0f));
		XYGridSceneNode->drop();
	}
	else
	{
		XYGridSceneNode->setVisible(true);
	}

	uiController->SetXYGridVisibility(true);
}

void Simulation::hideXYGrid()
{
	showXYGridSceneNode = false;

	if (XYGridSceneNode)
	{
		XYGridSceneNode->setVisible(false);
	}

	uiController->SetXYGridVisibility(false);
}

void Simulation::showYZGrid()
{
	showYZGridSceneNode = true;

	if (!YZGridSceneNode)
	{
		u32 newRed = (GetYAxisColor().getRed() + GetZAxisColor().getRed()) / 2;
		u32 newGreen = (GetYAxisColor().getGreen() + GetZAxisColor().getGreen()) / 2;
		u32 newBlue = (GetYAxisColor().getBlue() + GetZAxisColor().getBlue()) / 2;

		YZGridSceneNode = new GridSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), 123, SColor(255, newRed, newGreen, newBlue), 101, 101, 10.0f, 10.0f);
		YZGridSceneNode->setRotation(Vector3(0.0f, 0.0f, 90.0f));
		YZGridSceneNode->drop();
	}
	else
	{
		XZGridSceneNode->setVisible(true);
	}

	uiController->SetYZGridVisibility(true);
}

void Simulation::hideYZGrid()
{
	showYZGridSceneNode = false;

	if (YZGridSceneNode)
	{
		YZGridSceneNode->setVisible(false);
	}

	uiController->SetYZGridVisibility(false);
}

void Simulation::StartRecording()
{
	isRecording = true;
}

void Simulation::StopRecording()
{
	isRecording = false;
	isRecordingFirstFrame = true;

	Pause();
}

void Simulation::StartPhysicsEngineRecording()
{	
	foreach(PhysicsObject*, phyObjIt, physicsEngine->GetObjectList())
	{
		PhysicsObject* obj = phyObjIt->GetData();
		if (obj->GetEnabled())
		{
			wxString posName = _("Position");
			wxString velName = _("Velocity");
			wxString frcName = _("Force");
			List<wxString> yNames;
			yNames.Add(_("X"));
			yNames.Add(_("Y"));
			yNames.Add(_("Z"));

			obj->AddDataToRecord(posName, &yNames, obj->GetPositionPointer());
			obj->AddDataToRecord(velName, &yNames, obj->GetVelocityPointer());
			obj->AddDataToRecord(frcName, &yNames, obj->GetForcePointer());

			recordingObjects->Add(obj, false);
		}
	}
}

void Simulation::StopPhysicsEngineRecording()
{
	if (recordingObjects->GetSize() > 0)
	{
		List<ObjectTabStructure*> chartTabStructure;

		foreach(PhysicsObject*, phyObjIt, recordingObjects)
		{
			PhysicsObject* obj = phyObjIt->GetData();

			chartTabStructure.Add(obj->GetObjectTabStructure(obj->GetName()));
		}

		WxIrrChartWindow* chartWindow = new WxIrrChartWindow(&chartTabStructure);
		chartWindow->Show();

		foreach(PhysicsObject*, phyObjIt, recordingObjects)
		{
			PhysicsObject* obj = phyObjIt->GetData();

			obj->ClearRecordings();
		}

		chartTabStructure.Clear(); 

		recordingObjects->Clear();
	}
}


void Simulation::StartMouseCheck()
{
	numOfMouseClicks = 0;
	isMouseChecking = true;
}

void Simulation::StopMouseCheck()
{
	numOfMouseClicks = 0;
	isMouseChecking = false;
}

//returns false if done checking for mouse clicks.
bool Simulation::MouseClick(bool isShiftDown, bool isControlDown)
{
	if (isMouseChecking)
	{
		return true;
	}

	return false;
}

bool Simulation::MouseClickNumLeft(bool isShiftDown, int num)
{
	if (num != 0 && isMouseChecking)
	{
		numOfMouseClicks++;

		if (numOfMouseClicks == num)
		{
			numOfMouseClicks = 0;
			isMouseChecking = false;
			return false;
		}

		return true;
	}
	else
	{
		if (mouseOverSceneNode)
		{
			if (isShiftDown)
			{
				if (!UnselectObject(mouseOverSceneNode))
				{
					AddSelectedObject(mouseOverSceneNode);
				}
			}
			else
			{
				ChangeSelectedObjects(mouseOverSceneNode);
			}
		}
		else
		{
			ClearSelectedObjects();
		}
	}

	numOfMouseClicks = 0;
	isMouseChecking = false;
	return false;
}

bool Simulation::MouseDoubleClick()
{
	//UpdateMousePosition(mousePos, mouseOverViewport);

	if (isMouseChecking)
	{
		if (MouseClick(false, false))
		{
			return MouseClick(false, false);
		}

		return false;
	}
	else
	{
		//Point at and move towards object.
		if (mouseOverSceneNode)
		{
			//AddMoveToPoint(mouseOverSceneNode->getAbsolutePosition());
			viewportManager->GetSelectedViewport()->StartTargeting(mouseOverSceneNode->getAbsolutePosition(), 15.0f);
		}
	}

	return false;
}

void Simulation::AddMoveToPoint(Vector3& point)
{
	moveToList->Add(point);
}
void Simulation::AddMoveToObject(ISceneNode* obj)
{
}

void Simulation::UpdateMousePosition(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport, float collisionOffset)
{
	rect<s32> viewportArea = mouseOverViewport->GetIrrClientArea();
	driver->setViewPort(viewportArea);

	vector2d<s32> irrMousePos = vector2d<s32>(mousePos.x, mousePos.y);
	
	ICameraSceneNode* cam = mouseOverViewport->GetCamera();
	line3df ray = device->getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates(irrMousePos - 
		vector2d<s32>(viewportArea.UpperLeftCorner.X, viewportArea.UpperLeftCorner.Y), mouseOverViewport->GetCamera());

	Vector3 rayIntersection;
	triangle3df intersectionTriangle;

	if (mouseOverSceneNode)
	{
		if (IsASelectedObject(mouseOverSceneNode))
		{
			mouseOverSceneNode->getSceneManager()->getMeshManipulator()->setVertexColors(((IMeshSceneNode*)mouseOverSceneNode)->getMesh(), SColor(255, 255, 255, 0));
		}
		else
		{
			mouseOverSceneNode->getSceneManager()->getMeshManipulator()->setVertexColors(((IMeshSceneNode*)mouseOverSceneNode)->getMesh(), SColor(255, 255, 255, 255));
		}
	}

	if(usePlaneForMousePicking)
	{
		mouseOverSceneNode = NULL;

		if (rotateMousePlaneOnAxis)
		{
			//Rotate plane toward camera.
			if (rotateMousePlaneOnAxis)
			{
				Vector3 normalVec = cam->getPosition() - mousePlanePosition;
				switch(mousePlaneRotationAxis)
				{
				case AxisIdentifier_X:
					normalVec.X = 0.0f;
					break;
				case AxisIdentifier_Y:
					normalVec.Y = 0.0f;
					break;
				case AxisIdentifier_Z:
					normalVec.Z = 0.0f;
					break;
				}
				//driver->draw3DLine(mousePlanePosition, normalVec + cam->getPosition() + Vector3(0.0f, 10.0f, 0.0f), SColor(255, 255, 255, 0));
				mousePickingPlane.ChangePlane(normalVec, mousePlanePosition);
			}
		}
		mousePickingPlane.GetIntersectionWithRay(ray, threeDMousePosition);
	}
	else
	{
		mouseOverSceneNode = device->getSceneManager()->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, rayIntersection, intersectionTriangle, 0);
	}

	if (mouseOverSceneNode)
	{
		mouseOverSceneNode->getSceneManager()->getMeshManipulator()->setVertexColors(((IMeshSceneNode*)mouseOverSceneNode)->getMesh(), SColor(255, 255, 0, 0));
	}
	Vector3 rayDirection = ray.getVector().normalize();

	//No need to worry about location of intersection if no objects are being added. If no objects are being added, all we
	//need is the selectedSceneNode.
	if (mouseOverSceneNode)
	{
		//Collision occured so place new object before it.

		threeDMousePosition = rayIntersection - intersectionTriangle.getNormal().normalize() * collisionOffset;
	}
	if (isMouseChecking)
	{
		if (!usePlaneForMousePicking)
		{
			if (!mouseOverSceneNode)
			{
				//No collision
				Vector3 point = ray.start + rayDirection * 100.0f;

				threeDMousePosition = point;
			}
			else
			{
				//Collision occured so place new object before it.

				threeDMousePosition = rayIntersection - intersectionTriangle.getNormal().normalize() * collisionOffset;
			}
		}
	}
}

void Simulation::ClearSelectedObjects()
{
	foreach(ISceneNode*, selectedIt, selectedObjects)
	{
		ISceneNode* currentSelectedNode = selectedIt->GetData();
		currentSelectedNode->getSceneManager()->getMeshManipulator()->setVertexColors(((IMeshSceneNode*)currentSelectedNode)->getMesh(), SColor(255, 255, 255, 255));
	}

	selectedObjects->Clear();
}

void Simulation::ChangeSelectedObjects(ISceneNode* selectedNode)
{
	foreach(ISceneNode*, selectedIt, selectedObjects)
	{
		ISceneNode* currentSelectedNode = selectedIt->GetData();
		currentSelectedNode->getSceneManager()->getMeshManipulator()->setVertexColors(((IMeshSceneNode*)currentSelectedNode)->getMesh(), SColor(255, 255, 255, 255));
	}

	selectedObjects->Clear();
	if (selectedNode)
	{
		AddSelectedObject(selectedNode);
	}
}

void Simulation::AddSelectedObject(ISceneNode* selectedNode)
{
	if (selectedNode)
	{
		selectedObjects->Add(selectedNode, false);
		selectedNode->getSceneManager()->getMeshManipulator()->setVertexColors(((IMeshSceneNode*)selectedNode)->getMesh(), SColor(255, 255, 255, 0));
	}
}

//Unselect object if it was selected and true, but it wasnt selected return false.
bool Simulation::UnselectObject(ISceneNode* selectedNode)
{
	Node<ISceneNode*>* temp = 0;
	if (IsASelectedObject(selectedNode, temp))
	{
		selectedObjects->Remove(temp);
		return true;
	}
	return false;
}

//TODO: Change to binary search tree
bool Simulation::IsASelectedObject(ISceneNode* selectedNode, Node<ISceneNode*>*& listNode)
{
	foreach(ISceneNode*, selectedIt, selectedObjects)
	{
		if (selectedIt->GetData() == selectedNode)
		{
			listNode = selectedIt;
			return true;
		}
	}

	listNode = NULL;
	return false;
}

bool Simulation::IsASelectedObject(ISceneNode* selectedNode)
{
	Node<ISceneNode*>* temp = 0;
	return IsASelectedObject(selectedNode, temp);
}

//Serialization
void Simulation::SerializeIn(istream &is)
{
	is >> showVelocity;
	is >> showAllAccelerations;
	is >> showNetAcceleration;
	is >> showAllForces;
	is >> showNetForce;

	is >> simulationPaused;
	is >> forward;
	is >> timePassedFrame;
	is >> timePassedDirectionFrame;
	is >> totalTime;
	is >> timeScale;

	is >> timeSkipAmount;

	notes = SerializeInWxString(is);

	is >> showAxes;
	is >> showNames;

	XAxisColor = SerializeInSColor(is);
	YAxisColor = SerializeInSColor(is);
	ZAxisColor = SerializeInSColor(is);

	SetSaved();
}

void Simulation::SerializeOut(ostream &os)
{ 
	os << showVelocity << endl;
	os << showAllAccelerations << endl;
	os << showNetAcceleration << endl;
	os << showAllForces << endl;
	os << showNetForce << endl;

	os << simulationPaused << endl;
	os << forward << endl;
	os << timePassedFrame << endl;
	os << timePassedDirectionFrame << endl;
	os << totalTime << endl;
	os << timeScale << endl;

	os << timeSkipAmount << endl;

	//os << notes << endl;
	//notes = _("ASDFASFASDF");
	SerializeOutWxString(os, notes);

	os << showAxes << endl;
	os << showNames << endl;

	SerializeOutSColor(os, XAxisColor);
	SerializeOutSColor(os, YAxisColor);
	SerializeOutSColor(os, ZAxisColor);

	SetSaved();
}