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

#include "main.h"
#include <iostream>
using namespace std;

#include "IrrlichtEventReceiver.h"

IMPLEMENT_APP(WxIrrPhysicsHelperApp)

//Main variables
IrrlichtDevice *device;
IVideoDriver* driver;
ISceneManager* smgr;
IGUIEnvironment* guienv;

PhysicsHelperManager* physicsHelperManager;

PhysicsHeplerEventHandler* eventHandler;

bool IrrlichtLeftMouseDown(bool controlDown, bool shiftDown, int x, int y)
{
	SEvent mouseEvent;
	mouseEvent.EventType = EET_MOUSE_INPUT_EVENT;

	mouseEvent.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;
	mouseEvent.MouseInput.Control = controlDown;
	mouseEvent.MouseInput.Shift = shiftDown;
	mouseEvent.MouseInput.X = x;
	mouseEvent.MouseInput.Y = y;

	return device->postEventFromUser(mouseEvent);
}
bool IrrlichtLeftMouseUp(bool controlDown, bool shiftDown, int x, int y)
{
	SEvent mouseEvent;
	mouseEvent.EventType = EET_MOUSE_INPUT_EVENT;

	mouseEvent.MouseInput.Event = EMIE_LMOUSE_LEFT_UP;
	mouseEvent.MouseInput.Control = controlDown;
	mouseEvent.MouseInput.Shift = shiftDown;
	mouseEvent.MouseInput.X = x;
	mouseEvent.MouseInput.Y = y;

	return device->postEventFromUser(mouseEvent);
}
bool IrrlichtLeftMouseDoubleClick(bool controlDown, bool shiftDown, int x, int y)
{
	SEvent mouseEvent;
	mouseEvent.EventType = EET_MOUSE_INPUT_EVENT;

	mouseEvent.MouseInput.Event = EMIE_LMOUSE_DOUBLE_CLICK;
	mouseEvent.MouseInput.Control = controlDown;
	mouseEvent.MouseInput.Shift = shiftDown;
	mouseEvent.MouseInput.X = x;
	mouseEvent.MouseInput.Y = y;

	return guienv->postEventFromUser(mouseEvent);
}
bool IrrlichtMouseMove(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY)
{
	SEvent mouseEvent;
	mouseEvent.EventType = EET_MOUSE_INPUT_EVENT;

	mouseEvent.MouseInput.Event = EMIE_MOUSE_MOVED;
	mouseEvent.MouseInput.Control = controlDown;
	mouseEvent.MouseInput.Shift = shiftDown;
	mouseEvent.MouseInput.X = moveX;
	mouseEvent.MouseInput.Y = moveY;

	//if(guienv->postEventFromUser(mouseEvent))
	{
		//IGUIElement* selectedGUIElem = guienv->getFocus();
		IGUIElement* selectedGUIElem = PhysicsHelperGUIEnviornment::focusedGUIElement;

		if (selectedGUIElem)
		{
			if (selectedGUIElem->getType() == EGUIET_WINDOW)
			{
				IGUIWindow* selectedGUIWindow = (IGUIWindow*)(selectedGUIElem);
				selectedGUIWindow->move(vector2d<s32>(moveX, moveY));

				return true;
			}
		}
	}

	return device->postEventFromUser(mouseEvent);
}

void IrrlichtCameraMouseMove(int moveX, int moveY, WxIrrViewport* selectedViewport)
{
	ICameraSceneNode* selectedCamera = selectedViewport->GetCamera();

	Vector3 currentCameraRot = selectedCamera->getRotation();
	float YChange = (float)(moveX)*0.4f;
	float XChange = (float)(moveY)*0.4f;
	currentCameraRot.Y += YChange;
	currentCameraRot.X += XChange;
	//selectedCamera->setRotation(currentCameraRot);
				
	selectedCamera->setUpVector(currentCameraRot.rotationToDirection(Vector3(0.0f, 1.0f, 0.0f)));
	selectedCamera->setTarget(currentCameraRot.rotationToDirection() + selectedCamera->getPosition());
	selectedCamera->setRotation(currentCameraRot);
}

void IrrlichtCameraKeyDown(int id, WxIrrViewport* selectedViewport)
{
	SEvent keyEvent;
	keyEvent.EventType = EET_KEY_INPUT_EVENT;
	keyEvent.KeyInput.PressedDown = true;

	if(id == 87)//if(globalReceiverPointer->IsKeyDown(irr::KEY_KEY_W))
	{
		keyEvent.KeyInput.Key = irr::KEY_KEY_W;
	}
    else if(id == 83)//if(globalReceiverPointer->IsKeyDown(irr::KEY_KEY_S))
	{
		keyEvent.KeyInput.Key = irr::KEY_KEY_S;
	}
	if(id == 65)
	{
		keyEvent.KeyInput.Key = irr::KEY_KEY_A;
	}
    else if(id == 68)
	{
		keyEvent.KeyInput.Key = irr::KEY_KEY_D;
	}
	
	device->postEventFromUser(keyEvent);
}

void IrrlichtCameraKeyUp(int id)
{
	SEvent keyEvent;
	keyEvent.EventType = EET_KEY_INPUT_EVENT;
	keyEvent.KeyInput.PressedDown = false;

	if(id == 87)
	{
		keyEvent.KeyInput.Key = irr::KEY_KEY_W;
	}
    else if(id == 83)
	{
		keyEvent.KeyInput.Key = irr::KEY_KEY_S;
	}
	if(id == 65)
	{
		keyEvent.KeyInput.Key = irr::KEY_KEY_A;
	}
    else if(id == 68)
	{
		keyEvent.KeyInput.Key = irr::KEY_KEY_D;
	}

	device->postEventFromUser(keyEvent);
}

void IrrlichtCameraKeyboardReset()
{
	SEvent keyEvent;
	keyEvent.EventType = EET_KEY_INPUT_EVENT;
	keyEvent.KeyInput.PressedDown = false;

	keyEvent.KeyInput.Key = irr::KEY_KEY_W;
	device->postEventFromUser(keyEvent);

	keyEvent.KeyInput.Key = irr::KEY_KEY_S;
	device->postEventFromUser(keyEvent);

	keyEvent.KeyInput.Key = irr::KEY_KEY_A;
	device->postEventFromUser(keyEvent);

	keyEvent.KeyInput.Key = irr::KEY_KEY_D;
	device->postEventFromUser(keyEvent);
}

IGUIStaticText* txt;

//void Draw(ICameraSceneNode* _camera, rect<s32> wholeArea, rect<s32> viewportArea, WxIrrRenderViewport* viewport)
//{
//	if(device->run())
//	{
//		//driver->setViewPort(wholeArea);
//		smgr->setActiveCamera(_camera);
//		driver->beginScene(true, true, SColor(255,100,101,140), SExposedVideoData(reinterpret_cast<void*>(viewport->GetHandle())));
//
//		
//		//driver->setViewPort(viewportArea);
//
//		smgr->drawAll();
//		guienv->drawAll();
//
//		driver->endScene();
//	}
//}
WxIrrViewport* rootViewport;

const double AxisArrowSideLength = 0.2;

void AxisArrow2DTextDraw(Vector3& point, int currentViewportWidth, int currentViewportHeight, rect<s32>& viewportClientArea, ISceneManager* customSmgr, ICameraSceneNode* camera, stringw text, SColor& color)
{
	vector2d<s32> screenPos = customSmgr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(point, camera);
	screenPos.X *= (float)viewportClientArea.getWidth() / (float)currentViewportWidth;
	screenPos.Y *= (float)viewportClientArea.getHeight() / (float)currentViewportHeight;
	screenPos += viewportClientArea.UpperLeftCorner;
	screenPos.X += 2;
	rect<s32> textRect(screenPos, viewportClientArea.LowerRightCorner);
	guienv->getSkin()->getFont()->draw(text, textRect, color, false, false, &textRect);
	//../../../../game items/irrlicht-1.7.3/irrlicht-1.7.3/media/bigfont.png
}

void RenderAxisArrows(WxIrrViewport* viewportAxisRender, irr::core::rect<s32>& rootViewportSize)
{
	//Dont render if no simulation is made.
	if(globalSimulationPtr)
	{
		static ICameraSceneNode* axisArrowCamera = NULL;
		static irr::core::array<S3DVertex> arrowVertices;
		static irr::core::array<u16> arrowIndicies;
		static ISceneManager* axisArrowsSceneManager = NULL;

		if (!axisArrowsSceneManager)
		{
			axisArrowsSceneManager = smgr->createNewSceneManager();

			axisArrowCamera = axisArrowsSceneManager->addCameraSceneNode(0, Vector3(0, 10, 0), Vector3_Zero);
			axisArrowCamera->bindTargetAndRotation(true);
			//axisArrowCamera->setRotation(Vector3_Zero);
			axisArrowCamera->setTarget(Vector3_Zero);
			axisArrowCamera->setFarValue(100);
			
			axisArrowsSceneManager->setActiveCamera(axisArrowCamera);
			axisArrowsSceneManager->addLightSceneNode(0, Vector3(0, 10, 0));

			arrowVertices.set_used(0);
			arrowIndicies.set_used(0);
			S3DVertex tempVertex = S3DVertex(Vector3_Zero, Vector3(0.0f, 0.0f, 0.0f), SColor(255, 255, 255, 255), vector2d<float>(0.0f, 0.0f));
			S3DVertex tempVertex2 = S3DVertex(Vector3_Zero, Vector3(0.0f, 0.0f, 0.0f), SColor(255, 255, 255, 255), vector2d<float>(0.0f, 0.0f));

			tempVertex.Color = globalSimulationPtr->GetXAxisColor();
			arrowVertices.push_back(tempVertex);
			tempVertex2.Pos = Vector3(5.0f, 0, 0);
			tempVertex2.Color = tempVertex.Color;
			arrowVertices.push_back(tempVertex2);

			tempVertex.Color = globalSimulationPtr->GetYAxisColor();
			arrowVertices.push_back(tempVertex);
			tempVertex2.Pos = Vector3(0, 5.0f, 0);
			tempVertex2.Color = tempVertex.Color;
			arrowVertices.push_back(tempVertex2);

			tempVertex.Color = globalSimulationPtr->GetZAxisColor();
			arrowVertices.push_back(tempVertex);
			tempVertex2.Pos = Vector3(0, 0, 5.0f);
			tempVertex2.Color = tempVertex.Color;
			arrowVertices.push_back(tempVertex2);

			arrowIndicies.push_back(0);
			arrowIndicies.push_back(1);
			arrowIndicies.push_back(2);
			arrowIndicies.push_back(3);
			arrowIndicies.push_back(4);
			arrowIndicies.push_back(5);
		}
		else
		{
			if (globalSimulationPtr->GetColorChangedFlag())
			{
				arrowVertices[0].Color = globalSimulationPtr->GetXAxisColor();
				arrowVertices[1].Color = arrowVertices[0].Color;

				arrowVertices[2].Color = globalSimulationPtr->GetYAxisColor();
				arrowVertices[3].Color = arrowVertices[2].Color;

				arrowVertices[4].Color = globalSimulationPtr->GetZAxisColor();
				arrowVertices[5].Color = arrowVertices[4].Color;
			}
		}


		//driver->setViewPort(rootViewport->GetIrrArea());

		irr::core::rect<s32> viewportClientArea = viewportAxisRender->GetIrrClientArea();
		int width = viewportClientArea.getWidth() * AxisArrowSideLength;
		int height = viewportClientArea.getHeight() * AxisArrowSideLength;
		axisArrowCamera->setAspectRatio((float)width/(float)height);

		viewportClientArea.UpperLeftCorner.X = viewportClientArea.LowerRightCorner.X - width;
		viewportClientArea.LowerRightCorner.Y = viewportClientArea.UpperLeftCorner.Y + height;

		ICameraSceneNode* currentCamera = viewportAxisRender->GetCamera();
		Vector3 currentPos = currentCamera->getAbsolutePosition();
		Vector3 currentTarget = currentCamera->getTarget();
		Vector3 targetDir = (currentTarget - currentPos).normalize() * 10.0f;
		axisArrowCamera->setPosition(-targetDir);
		axisArrowCamera->setTarget(Vector3_Zero);

		driver->setViewPort(viewportClientArea);

		axisArrowsSceneManager->drawAll();

		static SMaterial mat;
		mat.ZBuffer = 0;
		mat.ZWriteEnable = false;
		mat.Lighting = false;

		driver->setTransform(video::ETS_WORLD, matrix4());
		driver->setMaterial(mat);
		driver->drawVertexPrimitiveList(arrowVertices.pointer(), 4, arrowIndicies.pointer(), 3, EVT_STANDARD, EPT_LINES, EIT_16BIT);

		/*if (globalMainWindowPtr)
			globalMainWindowPtr->DrawTextOnRenderWindow(_("x"), wxPoint(screenPos.X, screenPos.Y));*/
		rect<s32> test = driver->getViewPort();

		driver->setViewPort(rootViewportSize);

		int wholeWidth = rootViewportSize.getWidth();
		int wholeHeight = rootViewportSize.getHeight();

		AxisArrow2DTextDraw(arrowVertices[1].Pos, wholeWidth, wholeHeight, viewportClientArea, axisArrowsSceneManager, axisArrowCamera, L"x", arrowVertices[1].Color);
		AxisArrow2DTextDraw(arrowVertices[3].Pos, wholeWidth, wholeHeight, viewportClientArea, axisArrowsSceneManager, axisArrowCamera, L"y", arrowVertices[3].Color);
		AxisArrow2DTextDraw(arrowVertices[5].Pos, wholeWidth, wholeHeight, viewportClientArea, axisArrowsSceneManager, axisArrowCamera, L"z", arrowVertices[5].Color);
	}
}

void DrawViewport(WxIrrViewport* viewport, irr::core::rect<s32>& rootViewportSize, WxIrrKeyboardManager* keyboardManager, WxIrrMouseManager* mouseManager)
{
	if (viewport->GetOrient() == SPLITORIENT_NONE)
	{
		driver->setViewPort(rootViewportSize);
		if (viewport->isSelected())
		{
			driver->draw2DRectangle(SColor(255, 100, 100, 100), viewport->GetIrrArea());

			ICameraSceneNode* selectedCamera = viewport->GetCamera();
			selectedCamera->setInputReceiverEnabled(false);

			////update camera rotation
			/*if(eventHandler->GetEventType() == PHEventType_Mouse && eventHandler->mouseLeftDown)
			{
				Vector3 currentCameraRot = selectedCamera->getRotation();
				float YChange = (float)(eventHandler->mouseXMove)*0.4f;
				float XChange = (float)(eventHandler->mouseYMove)*0.4f;
				currentCameraRot.Y += YChange;
				currentCameraRot.X += XChange;
				//selectedCamera->setRotation(currentCameraRot);
				
				selectedCamera->setUpVector(currentCameraRot.rotationToDirection(Vector3(0.0f, 1.0f, 0.0f)));
				selectedCamera->setTarget(currentCameraRot.rotationToDirection() + selectedCamera->getPosition());
				selectedCamera->setRotation(currentCameraRot);
			}*/
			//if (mouseManager->mouseMovedFlag)
			//{
			//	Vector3 currentCameraRot = selectedCamera->getRotation();
			//	float YChange = (float)(mouseManager->moveXAmount)*0.4f;
			//	float XChange = (float)(mouseManager->moveYAmount)*0.4f;
			//	currentCameraRot.Y += YChange;
			//	currentCameraRot.X += XChange;
			//	//selectedCamera->setRotation(currentCameraRot);
			//	
			//	selectedCamera->setUpVector(currentCameraRot.rotationToDirection(Vector3(0.0f, 1.0f, 0.0f)));
			//	selectedCamera->setTarget(currentCameraRot.rotationToDirection() + selectedCamera->getPosition());
			//	selectedCamera->setRotation(currentCameraRot);

			//	mouseManager->Reset();
			//}

			//Update camera movement
			Vector3 target = selectedCamera->getTarget();
			Vector3 targetDir = (selectedCamera->getTarget() - selectedCamera->getPosition()).normalize();

			if(eventHandler->IsKeyDown(irr::KEY_KEY_W))//if(globalReceiverPointer->IsKeyDown(irr::KEY_KEY_W))
                selectedCamera->setPosition(selectedCamera->getPosition() + targetDir*100.0f*physicsHelperManager->deltaTimeInSeconds);
            else if(eventHandler->IsKeyDown(irr::KEY_KEY_S))//if(globalReceiverPointer->IsKeyDown(irr::KEY_KEY_S))
                selectedCamera->setPosition(selectedCamera->getPosition() - targetDir*100.0f*physicsHelperManager->deltaTimeInSeconds);

			if(eventHandler->IsKeyDown(irr::KEY_KEY_A))
				selectedCamera->setPosition(selectedCamera->getPosition() + 
				targetDir.crossProduct(selectedCamera->getUpVector()).normalize()*100.0f*physicsHelperManager->deltaTimeInSeconds);
            else if(eventHandler->IsKeyDown(irr::KEY_KEY_D))
                selectedCamera->setPosition(selectedCamera->getPosition() + 
				selectedCamera->getUpVector().crossProduct(targetDir).normalize()*100.0f*physicsHelperManager->deltaTimeInSeconds);

			selectedCamera->setTarget(selectedCamera->getPosition() + targetDir);			
		}
		else
		{
			driver->draw2DRectangle(SColor(255, 223, 226, 235), viewport->GetIrrArea());
		}

		driver->draw2DRectangle(SColor(255, 172, 172, 172), viewport->GetIrrClientArea());

		smgr->setActiveCamera(viewport->GetCamera());
		driver->setViewPort(viewport->GetIrrClientArea());

		smgr->drawAll();
		physicsHelperManager->Draw(viewport);

		RenderAxisArrows(viewport, rootViewportSize);
	}
	else
	{
		if (viewport->GetSplit1())
			DrawViewport(viewport->GetSplit1(), rootViewportSize, keyboardManager, mouseManager);

		if (viewport->GetSplit2())
			DrawViewport(viewport->GetSplit2(), rootViewportSize, keyboardManager, mouseManager);
	}
}

void Draw(WxIrrViewportManager* viewportManager)
{
	WxIrrViewport* viewport = viewportManager->GetRootViewport();
	rootViewport = viewport;

	/*wxPoint mousePos = viewportManager->GetMousePosition();
	physicsHelperManager->MouseOverViewportUpdate(mousePos, viewportManager->GetViewportClicked(mousePos.x, mousePos.y));*/

	irr::core::rect<s32> rootViewportArea = rootViewport->GetIrrArea();
	if(device && device->run())
	{
		driver->setViewPort(rootViewportArea);
		driver->beginScene(true, true, SColor(255,100,101,140));
		
		//driver->setViewPort(viewport->GetIrrArea());

		//smgr->drawAll();
		//guienv->drawAll();

		DrawViewport(viewport, rootViewportArea, viewportManager->GetKeyboardManager(), viewportManager->GetMouseManager());

		driver->setViewPort(rootViewportArea);
		guienv->drawAll();


		driver->endScene();
	}
}

void Update(void)
{
	if (physicsHelperManager)
		physicsHelperManager->Update();
}


bool WxIrrPhysicsHelperApp::OnInit()
{
	WxIrrMainWindow *mainWindow = new WxIrrMainWindow(wxT("PhysicsHelper"), Draw, Update, IrrlichtLeftMouseDown, IrrlichtLeftMouseUp, IrrlichtLeftMouseDoubleClick, IrrlichtMouseMove,
		IrrlichtCameraMouseMove, IrrlichtCameraKeyDown, IrrlichtCameraKeyUp, IrrlichtCameraKeyboardReset,
		SimulationMouseOver, SimulationMouseClick, SimulationMouseDoubleClick, SimulationStartMouseChecking,
		SimulationShowAxes, SimulationShowObjectNames,
		SimulationXAxisGetColor, SimulationYAxisGetColor, SimulationZAxisGetColor,
		SimulationXAxisChangeColor, SimulationYAxisChangeColor, SimulationZAxisChangeColor,
		SimulationShowXYGrid, SimulationShowXZGrid, SimulationShowYZGrid);
    mainWindow->Show(true);
	globalMainWindowPtr = mainWindow;

	//Setup device
	device = mainWindow->GetDevice();
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	eventHandler = new PhysicsHeplerEventHandler(guienv);
	device->setEventReceiver(eventHandler);

	physicsHelperManager = new PhysicsHelperManager(eventHandler);
	if (!physicsHelperManager)
		exit(0);

	physicsHelperManager->SetupDevice(device, mainWindow);

	txt = guienv->addStaticText(L"Physics Helper",rect<s32>(10,10,260,22), true);


	/*WxIrrChartWindow* chartWindow = new WxIrrChartWindow();
	chartWindow->Show(true);*/

	smgr->addLightSceneNode(NULL, vector3df(0.0f, 200.0f, 0.0f), SColorf(1.0, 1.0, 1.0), 2000.0f);

    return true;
}


WxIrrPhysicsHelperApp::~WxIrrPhysicsHelperApp()
{
	delete physicsHelperManager;
	if(ThreeDGraph::graphingShaderCallback)
		delete ThreeDGraph::graphingShaderCallback;
	device->drop();
}
