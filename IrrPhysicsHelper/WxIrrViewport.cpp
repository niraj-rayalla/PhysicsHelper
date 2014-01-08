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

#include "WxIrrViewport.h"

WxIrrViewport::WxIrrViewport(wxPoint pos, wxSize _size)
{
	orient = SPLITORIENT_NONE;
	parentViewport = NULL;
	split1 = NULL;
	split2 = NULL;

	selected = false;

	position = pos;
	size = _size;
	splitRatio = 0.5f;
	parentViewport = NULL;

	ResetTargeting();
}

WxIrrViewport::WxIrrViewport(wxPoint pos, wxSize _size, WxIrrViewport* parent, ICameraSceneNode* _camera)
{
	orient = SPLITORIENT_NONE;
	parentViewport = NULL;
	split1 = NULL;
	split2 = NULL;

	selected = false;

	position = pos;
	size = _size;
	splitRatio = 0.5f;
	parentViewport = parent;

	camera = _camera;
	SetCameraAspectRatio();

	ResetTargeting();
}

WxIrrViewport::~WxIrrViewport()
{
	delete split1;
	delete split2;

	camera->remove();
}

rect<s32> WxIrrViewport::GetIrrArea()
{
	rect<s32> area;

	area.UpperLeftCorner.X = position.x;
	area.UpperLeftCorner.Y = position.y;
	area.LowerRightCorner.X = position.x + size.GetWidth();
	area.LowerRightCorner.Y = position.y + size.GetHeight();

	return area;
}

rect<s32> WxIrrViewport::GetIrrClientArea()
{
	rect<s32> area;

	area.UpperLeftCorner.X = position.x + WX_IRR_VIEWPORT_BORDER_WIDTH;
	area.UpperLeftCorner.Y = position.y + WX_IRR_VIEWPORT_BORDER_WIDTH;
	area.LowerRightCorner.X = position.x + size.GetWidth() - WX_IRR_VIEWPORT_BORDER_WIDTH;
	area.LowerRightCorner.Y = position.y + size.GetHeight() - WX_IRR_VIEWPORT_BORDER_WIDTH;

	return area;
}

WxIrrViewport* WxIrrViewport::GetSiblingViewport()
{
	if (parentViewport)
	{
		if(parentViewport->GetSplit1() == this)
			return parentViewport->GetSplit2();
		if(parentViewport->GetSplit2() == this)
			return parentViewport->GetSplit1();
	}

	return NULL;
}

WxIrrViewport* WxIrrViewport::GetSelectedViewport()
{
	if (isSelected())
	{
		if (orient == SPLITORIENT_NONE)
			return this;
	}
	else
	{
		if (split1)
		{
			WxIrrViewport* split1Selected = split1->GetSelectedViewport();
			if (split1Selected)
				return split1Selected;
		}

		if (split2)
		{
			WxIrrViewport* split2Selected = split2->GetSelectedViewport();
			if (split2Selected)
				return split2Selected;
		}
	}

	return NULL;
}

void WxIrrViewport::RecursiveUnselect()
{
	Unselect();
	if (split1)
		split1->RecursiveUnselect();
	if (split2)
		split2->RecursiveUnselect();
}

//Unselect the parents from current viewport and also unselect ALL its children
//but dont reunselect this because it is unnecessary
void WxIrrViewport::UnselectParentViewports()
{
	if (parentViewport)
	{
		parentViewport->Unselect();

		//unselect the parent's children if it is not this one.
		if (parentViewport->GetSplit1() != this)
			parentViewport->GetSplit1()->RecursiveUnselect();
		if (parentViewport->GetSplit2() != this)
			parentViewport->GetSplit2()->RecursiveUnselect();

		//Now go higher
		parentViewport->UnselectParentViewports();

		WxIrrViewport* siblingViewport = GetSiblingViewport();
		if (siblingViewport)
			siblingViewport->Unselect();
	}
}

WxIrrViewport* WxIrrViewport::GetViewportClicked(int x, int y)
{
	if (orient == SPLITORIENT_NONE)
	{
		if (CheckIfPointWithinClient(x, y))
		{
			return this;
		}
	}
	else
	{
		WxIrrViewport* view1 = split1->GetViewportClicked(x, y);
		if (view1)
		{
			return view1;
		}
		else
		{
			WxIrrViewport* view2 = split2->GetViewportClicked(x, y);
			if (view2)
			{
				return view2;
			}
		}
	}

	return NULL;
}

bool WxIrrViewport::CheckIfPointWithinArea(int x, int y, wxPoint upperLeft, wxPoint lowerRight)
{
	if (x >= upperLeft.x && x <= lowerRight.x
		&& y >= upperLeft.y && y <= lowerRight.y)
	{
		return true;
	}
	return false;
}

bool WxIrrViewport::CheckIfPointWithin(int x, int y)
{
	if (x >= position.x && x <= position.x + size.GetWidth()
		&& y >= position.y && y <= position.y + size.GetHeight())
	{
		return true;
	}
	return false;
}

bool WxIrrViewport::CheckIfPointWithinClient(int x, int y)
{
	rect<s32> clientArea = GetIrrClientArea();
	if (x >= clientArea.UpperLeftCorner.X && x <= clientArea.LowerRightCorner.X
		&& y >= clientArea.UpperLeftCorner.Y && y <= clientArea.LowerRightCorner.Y)
	{
		return true;
	}
	return false;
}

bool WxIrrViewport::CheckIfPointWithinSash(int x, int y, ViewportSashOrientation sashOrient)
{
	wxPoint upperLeft;
	wxPoint lowerRight;

	switch(sashOrient)
	{
	case SASHORIENT_TOP:

		lowerRight = position;
		lowerRight.x += size.GetWidth();
		lowerRight.y += WX_IRR_VIEWPORT_BORDER_WIDTH;
		return CheckIfPointWithinArea(x, y, position, lowerRight);

		break;
	case SASHORIENT_BOTTOM:

		upperLeft = position;
		upperLeft.y += size.GetHeight() - WX_IRR_VIEWPORT_BORDER_WIDTH;
		lowerRight = position;
		lowerRight.x += size.GetWidth();
		lowerRight.y += size.GetHeight() + WX_IRR_VIEWPORT_BORDER_WIDTH;
		return CheckIfPointWithinArea(x, y, upperLeft, lowerRight);

		break;
	case SASHORIENT_LEFT:

		lowerRight = position;
		lowerRight.x += WX_IRR_VIEWPORT_BORDER_WIDTH;
		lowerRight.y += size.GetHeight();
		return CheckIfPointWithinArea(x, y, position, lowerRight);

		break;
	case SASHORIENT_RIGHT:

		upperLeft = position;
		upperLeft.x += size.GetWidth() - WX_IRR_VIEWPORT_BORDER_WIDTH;
		lowerRight = upperLeft;
		lowerRight.x += WX_IRR_VIEWPORT_BORDER_WIDTH;
		lowerRight.y += size.GetHeight();
		return CheckIfPointWithinArea(x, y, upperLeft, lowerRight);

		break;
	}

	return false;
}

ICameraSceneNode* WxIrrViewport::GetCopiedCamera(ISceneManager* smgr)
{
	ICameraSceneNode* newCamera = smgr->addCameraSceneNode();
	newCamera->setPosition(camera->getPosition());
	//newCamera->bindTargetAndRotation(true);
	newCamera->setTarget(camera->getTarget());
	newCamera->setFarValue(100000);

	return newCamera;
}

void WxIrrViewport::SplitHorizontal(ISceneManager* smgr)
{
	orient = SPLITORIENT_HORIZ;

	Unselect();
	UnselectParentViewports();

	wxSize halfSize = size;
	halfSize.SetHeight(halfSize.GetHeight()/2);
	split1 = new WxIrrViewport(position, halfSize, this, GetCopiedCamera(smgr));
	split1->Select();
	//split1->SetCamera(camera);

	wxPoint secondPositon = position;
	secondPositon.y += halfSize.GetHeight();
	halfSize.SetHeight(size.GetHeight() - halfSize.GetHeight());
	split2 = new WxIrrViewport(secondPositon, halfSize, this, GetCopiedCamera(smgr));
	//split2->SetCamera(camera);
}

void WxIrrViewport::SplitVertical(ISceneManager* smgr)
{
	orient = SPLITORIENT_VERT;
	
	Unselect();
	UnselectParentViewports();

	wxSize halfSize = size;
	halfSize.SetWidth(halfSize.GetWidth()/2);
	split1 = new WxIrrViewport(position, halfSize, this, GetCopiedCamera(smgr));
	split1->Select();
	//split1->SetCamera(GetCopiedCamera(smgr));

	wxPoint secondPositon = position;
	secondPositon.x += halfSize.GetWidth();
	halfSize.SetWidth(size.GetWidth() - halfSize.GetWidth());
	split2 = new WxIrrViewport(secondPositon, halfSize, this, GetCopiedCamera(smgr));
	//split2->SetCamera(GetCopiedCamera(smgr));	
}

void WxIrrViewport::RefreshRatio()
{
	if (split1 && split2)
	{
		if (orient == SPLITORIENT_HORIZ)
		{
			splitRatio = (float)split1->GetSize().GetWidth() / ( (float)split1->GetSize().GetWidth() + (float)split2->GetSize().GetWidth() );
		}
		else if (orient == SPLITORIENT_VERT)
		{
			splitRatio = (float)split1->GetSize().GetHeight() / ( (float)split1->GetSize().GetHeight() + (float)split2->GetSize().GetHeight() );
		}
	}
}

void WxIrrViewport::SetCameraAspectRatio()
{
	camera->setAspectRatio((float)size.GetWidth()/(float)size.GetHeight());
}

void WxIrrViewport::PaintFunc(void (*Draw)(WxIrrViewport*))
{
	if (orient == SPLITORIENT_NONE)
	{
		Draw(this);
	}
	else
	{
		if (split1)
			split1->PaintFunc(Draw);

		if (split2)
			split2->PaintFunc(Draw);
	}
}

wxSize WxIrrViewport::GetUpdatedChildSize(int difference, wxSize newSize, bool isSplit1)
{
	WxIrrViewport* child = isSplit1 ? split1 : split2;
	int changeSize = isSplit1 ? (int)((float)difference*splitRatio) : difference-(int)((float)difference*(splitRatio));
	if (orient == SPLITORIENT_HORIZ)
	{
		wxSize horizSize = child->GetSize();
		horizSize.SetHeight(newSize.GetHeight());
		horizSize.SetWidth(horizSize.GetWidth() + changeSize);

		return horizSize;
	}
	else if (orient == SPLITORIENT_VERT)
	{
		wxSize vertSize = child->GetSize();
		vertSize.SetWidth(newSize.GetWidth());
		vertSize.SetHeight(vertSize.GetHeight() + changeSize);

		return vertSize;
	}

	return GetSize();
}

void WxIrrViewport::ReSize(wxPoint pos, wxSize newSize)
{
	position = pos;
	if (orient == SPLITORIENT_HORIZ)
	{
		int difference = newSize.GetWidth() - size.GetWidth();

		split1->ReSize(position, GetUpdatedChildSize(difference, newSize, true));

		wxPoint split2Pos = split1->GetPos();
		split2Pos.x += split1->GetSize().GetWidth();

		split2->ReSize(split2Pos, GetUpdatedChildSize(difference, newSize, false));
	}
	else if (orient == SPLITORIENT_VERT)
	{
		int difference = newSize.GetHeight() - size.GetHeight();

		split1->ReSize(position, GetUpdatedChildSize(difference, newSize, true));

		wxPoint split2Pos = split1->GetPos();
		split2Pos.y += split1->GetSize().GetHeight();

		split2->ReSize(split2Pos, GetUpdatedChildSize(difference, newSize, false));
	}
	size = newSize;
	camera->setAspectRatio((float)size.GetWidth()/(float)size.GetHeight());
}

WxIrrViewport* WxIrrViewport::GetIfGrabbed(int x, int y, ViewportSashOrientation sashOrient)
{
	//if (orient == SPLITORIENT_NONE)
	//{
	//	if (parentViewport)
	//	{
	//		return CheckIfPointWithinSash(x, y, sashOrient) ? this : NULL;
	//	}
	//	return NULL;
	//}
	//else
	//{
	//	if (orient == SPLITORIENT_HORIZ)
	//	{
	//		WxIrrViewport* split1Grab = split1->GetIfGrabbed(x, y, SASHORIENT_RIGHT);
	//		return split1Grab ? split1Grab : split2->GetIfGrabbed(x, y, SASHORIENT_LEFT);
	//	}
	//	else if (orient == SPLITORIENT_VERT)
	//	{
	//		WxIrrViewport* split1Grab = split1->GetIfGrabbed(x, y, SASHORIENT_BOTTOM);
	//		return split1Grab ? split1Grab : split2->GetIfGrabbed(x, y, SASHORIENT_TOP);
	//	}
	//}

	WxIrrViewport* thisGrab = NULL;

	if (parentViewport)
	{
		thisGrab = CheckIfPointWithinSash(x, y, sashOrient) ? this : NULL;
	}

	if (orient == SPLITORIENT_HORIZ && split1 && split2)
	{
		WxIrrViewport* split1Grab = split1->GetIfGrabbed(x, y, SASHORIENT_RIGHT);
		WxIrrViewport* split2Grab = split2->GetIfGrabbed(x, y, SASHORIENT_LEFT);
		if (split1Grab)
			return split1Grab;
		if (split2Grab)
			return split2Grab;
	}
	else if (orient == SPLITORIENT_VERT && split1 && split2)
	{
		WxIrrViewport* split1Grab = split1->GetIfGrabbed(x, y, SASHORIENT_BOTTOM);
		WxIrrViewport* split2Grab = split2->GetIfGrabbed(x, y, SASHORIENT_TOP);
		if (split1Grab)
			return split1Grab;
		if (split2Grab)
			return split2Grab;
	}

	//Havent found any inside so just return thisGrab
	return thisGrab;

	return NULL;
}

void WxIrrViewport::Remove(ISceneManager* smgr)
{
	//Check if this viewport has a parent. This makes it so the root viewport can't be removed.
	if (parentViewport)
	{
		//Check if this is the parent's split1 or split2.
		bool isSplit1 = (parentViewport->split1 == this) ? true : false;

		//Set the the remaining viewport as the parent;
		if (isSplit1)
		{
			parentViewport->BecomeChild(false, smgr);
		}
		else
		{
			parentViewport->BecomeChild(true, smgr);
		}
	}
}

//Deletes other child but gains the properties of the chosen child.
void WxIrrViewport::BecomeChild(bool isSplit1, ISceneManager* smgr)
{
	selected = split1->selected || split2->selected;
	if (isSplit1)
	{
		delete split2;
	}
	else
	{
		delete split1;
	}

	WxIrrViewport* child = isSplit1 ? split1 : split2;
	camera->remove();
	camera = child->GetCopiedCamera(smgr);//child->camera;
	WxIrrViewport* split1Child = child->split1;
	WxIrrViewport* split2Child = child->split2;
	ViewportSplitOrientation orientTemp = child->orient;

	orient = orientTemp;
	split1 = split1Child;
	if (split1)
		split1->parentViewport = this;
	split2 = split2Child;
	if (split2)
		split2->parentViewport = this;
	splitRatio = child->splitRatio;

	if (split1 || split2)
	{
		if (split1)
		{
			split1->selected = selected;
		}
		else
		{
			split2->selected = selected;
		}

		selected = false;
	}

	child->split1 = NULL;
	child->split2 = NULL;

	delete child;

	//ReSize(position, size);
	if (orient != SPLITORIENT_NONE)
	{
		int difference= 0;
		if (orient == SPLITORIENT_HORIZ)
		{
			difference = size.GetWidth() - (split1->GetSize().GetWidth() + split2->GetSize().GetWidth());
		}
		else if (orient == SPLITORIENT_VERT)
		{
			difference = size.GetHeight() - (split1->GetSize().GetHeight() + split2->GetSize().GetHeight());
		}
		split1->ReSize(position, GetUpdatedChildSize(difference, size, true));
		wxPoint split2Pos = position;
		if (orient == SPLITORIENT_HORIZ)
		{
			split2Pos.x += split1->GetSize().GetWidth();
		}
		else if (orient == SPLITORIENT_VERT)
		{
			split2Pos.y += split1->GetSize().GetHeight();
		}
		split2->ReSize(split2Pos, GetUpdatedChildSize(difference, size, false));
	}
	SetCameraAspectRatio();
}

void WxIrrViewport::RemoveChildren()
{
	orient = SPLITORIENT_NONE;

	delete split1;
	delete split2;

	split1 = NULL;
	split2 = NULL;
}

void WxIrrViewport::StartTargeting(Vector3& point, float linearStopDistance)
{
	isTargetingPoint = true;
	targetPoint = point;
}

void WxIrrViewport::ResetTargeting()
{
	isTargetingPoint = false;
	targetPoint = Vector3_Zero;
	targetStopDistance = 15.0f;
}

void WxIrrViewport::MoveAndRotateCamLinearToPoint(float linearProportionSpeed, float angularProportionSpeed, float timePassedSinceLastFrame,
		float angularError)
{
	if (isTargetingPoint)
	{
		Vector3 cameraTargetDir = (camera->getTarget() - camera->getPosition()).normalize();
		Vector3 pointTargetDir = targetPoint - camera->getPosition();
		float distance = pointTargetDir.getLength();
		pointTargetDir /= distance;

		float angle = acosf(cameraTargetDir.dotProduct(pointTargetDir));
		//change to degrees
		angle *= RADTODEG;

		float changeAngle = angle * angularProportionSpeed * timePassedSinceLastFrame;
		float changeDistance = distance * linearProportionSpeed * timePassedSinceLastFrame;

		float newAngle = angle - changeAngle;
		float newDistance = distance - changeDistance;

		bool doneAngleChange = false;
		bool doneLinearChange = false;
		bool doAngularChange = true;
		bool doLinearChange = true;
		
		if (distance <= targetStopDistance)
		{
			doneLinearChange = true;
			doLinearChange = false;
		}
		if (angle >= 0.0f && angle <= angularError)
		{
			doneAngleChange = true;
			doAngularChange = false;
		}

		if (!doneAngleChange)
		{
			if (newAngle < 0.0f)
			{
				changeAngle = angle;
				doneAngleChange = true;
			}
			else
			{
				if (newAngle <= angularError)
				{
					doneAngleChange = true;
				}
			}
		}

		if (!doneLinearChange && newDistance < targetStopDistance)
		{
			changeDistance = distance - targetStopDistance;
			doneLinearChange = true;
		}

		if (doAngularChange)
		{
			Vector3 currentCameraRot = camera->getRotation();
			Vector3 changeAngleVec = cameraTargetDir.crossProduct(pointTargetDir).normalize() * changeAngle;
			currentCameraRot.Y += changeAngleVec.Y;
			currentCameraRot.X += changeAngleVec.X;

			camera->setUpVector(currentCameraRot.rotationToDirection(Vector3(0.0f, 1.0f, 0.0f)));
			cameraTargetDir = currentCameraRot.rotationToDirection();
			camera->setTarget(cameraTargetDir + camera->getPosition());
			camera->setRotation(currentCameraRot);
		}

		if (doLinearChange)
		{
			camera->setPosition(camera->getPosition() + changeDistance*pointTargetDir);
			camera->setTarget(camera->getPosition() + cameraTargetDir);
		}

		isTargetingPoint = !(doneAngleChange && doneLinearChange);
	}
}

void WxIrrViewport::Update(float timePassedSinceLastFrame)
{
	MoveAndRotateCamLinearToPoint(2.0f, 2.5f, timePassedSinceLastFrame);
}
void WxIrrViewport::RecursiveUpdate(float timePassedSinceLastFrame)
{
	if (split1)
	{
		split1->RecursiveUpdate(timePassedSinceLastFrame);
	}
	if (split2)
	{
		split2->RecursiveUpdate(timePassedSinceLastFrame);
		return;
	}

	Update(timePassedSinceLastFrame);
}

BEGIN_EVENT_TABLE(WxIrrViewportWindow, wxWindow)
	EVT_PAINT(WxIrrViewportWindow::OnPaint)
	EVT_SIZE(WxIrrViewportWindow::OnSize)
	EVT_TIMER( wxID_ANY, WxIrrViewportWindow::OnTimer)
	EVT_LEFT_DOWN(WxIrrViewportWindow::OnLeftClick)
	EVT_LEFT_DCLICK(WxIrrViewportWindow::OnLeftDoubleClick)
	EVT_LEFT_UP(WxIrrViewportWindow::OnLeftUnClick)
	EVT_RIGHT_DOWN(WxIrrViewportWindow::OnRightClick)
	EVT_MIDDLE_DOWN(WxIrrViewportWindow::OnMiddleClick)
	EVT_ENTER_WINDOW(WxIrrViewportWindow::OnMouseEnter)
	EVT_LEAVE_WINDOW(WxIrrViewportWindow::OnMouseLeave)
	EVT_KEY_DOWN(WxIrrViewportWindow::OnKeyDown)
	EVT_KEY_UP(WxIrrViewportWindow::OnKeyUp)
	EVT_MOTION(WxIrrViewportWindow::OnMouseMove)
	//EVT_ERASE_BACKGROUND(WxIrrRenderViewport::EraseBackground)
END_EVENT_TABLE()

WxIrrViewportWindow::~WxIrrViewportWindow()
{
	delete viewportManager;
	delete contextMenu;
	//device->drop();
}

void WxIrrViewportWindow::Setup()
{
	viewportManager = NULL;
	device = NULL;
	gameTime.Start(1000/60); 

	contextMenu = new wxMenu();
	contextMenu->Append(ID_SplitViewportHoriz, wxT("Split Horizontally"));
	contextMenu->Append(ID_SplitViewportVert, wxT("Split Vertically"));
	contextMenu->Append(ID_RemoveViewport, wxT("Remove Window"));

	mouseLeftClickAddObject = false;
	GUIActive = false;
}

void WxIrrViewportWindow::InitalizeViewportManager()
{
	viewportManager = new WxIrrViewportManager(this, wxID_ANY);
}

void WxIrrViewportWindow::SetupDevice(SIrrlichtCreationParameters& paramaters, void (*draw)(WxIrrViewportManager*), void (*update)(void), 
			bool (*irrlichtLeftMouseDown)(bool controlDown, bool shiftDown, int x, int y),
			bool (*irrlichtLeftMouseUp)(bool controlDown, bool shiftDown, int x, int y),
			bool (*irrlichtLeftMouseDoubleClick)(bool controlDown, bool shiftDown, int x, int y),
			bool (*irrlichtMouseMove)(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY),
			void (*irrlichtCameraMouseMove)(int moveX, int moveY, WxIrrViewport* selectedViewport),
			void (*irrlichtCameraKeyDown)(int id, WxIrrViewport* selectedViewport), void (*irrlichtCameraKeyUp)(int id), void (*irrlichtCameraKeyboardReset)(void),
			void (*simulationMouseMove)(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport),
	bool (*simulationMouseClick)(bool isShiftDown, bool isControlDown), bool (*simulationMouseDoubleClick)(void), void (*simulationStartMouseChecking)(void))
{
	param = paramaters;

	device = createDeviceEx(param);
	if (!device)
		Close(true);

	Draw = draw;
	Update = update;
	SimulationStartMouseChecking = simulationStartMouseChecking;
	SimulationMouseMove = simulationMouseMove;
	SimulationMouseClick = simulationMouseClick;
	SimulationMouseDoubleClick = simulationMouseDoubleClick;

	IrrlichtLeftMouseDown = irrlichtLeftMouseDown;
	IrrlichtLeftMouseUp = irrlichtLeftMouseUp;
	IrrlichtLeftMouseDoubleClick = irrlichtLeftMouseDoubleClick;
	IrrlichtMouseMove = irrlichtMouseMove;
	IrrlichtCameraMouseMove = irrlichtCameraMouseMove;
	IrrlichtCameraKeyDown = irrlichtCameraKeyDown;
	IrrlichtCameraKeyUp = irrlichtCameraKeyUp;
	IrrlichtCameraKeyboardReset = irrlichtCameraKeyboardReset;
}

WxIrrViewportManager* WxIrrViewportWindow::GetViewportManager()
{
	return viewportManager;
}

void WxIrrViewportWindow::SplitViewportHorizontally()
{
	viewportManager->SplitViewportHorizontally(device->getSceneManager());
}

void WxIrrViewportWindow::SplitViewportVertically()
{
	viewportManager->SplitViewportVertically(device->getSceneManager());
}

void WxIrrViewportWindow::RemoveViewport()
{
	viewportManager->RemoveViewport(device->getSceneManager());
}

void WxIrrViewportWindow::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	Draw(viewportManager);
}

void WxIrrViewportWindow::OnSize(wxSizeEvent &event)
{
	irr::u32 w=GetClientSize().GetWidth();
	irr::u32 h=GetClientSize().GetHeight();

	if ( device )
	{
	   IVideoDriver* driver=device->getVideoDriver();

	  if ( driver )
	  {   
		 driver->OnResize( irr::core::dimension2d<irr::u32>(w,h) );
		 //TODO:Possibly change aspect ration of camera
		 if ( !gameTime.IsRunning() )
			Update();
	  }
	}

	if (viewportManager)
		viewportManager->OnSize(GetClientSize());
}

void WxIrrViewportWindow::OnTimer(wxTimerEvent &event)
{
	Update();
	Refresh( false );
	//event.Skip();
	
	event.Skip();
}

void WxIrrViewportWindow::ChangeMouseClickBehavior()
{
	mouseLeftClickAddObject = !mouseLeftClickAddObject;
	SimulationStartMouseChecking();
}

//First check if other behavior for left click is being used such as add object.
//Then if the mouse is over a viewport sash or the viewport client area.
//If it is on the sash make it avialable for resizing on mousemove else split.
void WxIrrViewportWindow::OnLeftClick(wxMouseEvent &event)
{
	wxPoint mousePoint = event.GetPosition();

	if (!IrrlichtLeftMouseDown(event.ControlDown(), event.ShiftDown(), mousePoint.x, mousePoint.y))
	{
		GUIActive = false;

		viewportManager->mouseDown = true;
		viewportManager->mouseDownStartPos = mousePoint;
		viewportManager->SetMousePosition(mousePoint);	

		WxIrrViewport* grabableViewport = viewportManager->GetGrabableViewport();
		if (grabableViewport)
		{
			viewportManager->SetViewportGrabbed(true, event.GetPosition());
		}
		else
		{			
			WxIrrViewport* clickedViewport = viewportManager->GetViewportClicked(event.GetX(), event.GetY());
			if(clickedViewport)
			{
				//Unselect all viewports because a viewport will still be selected because the viewportmanager doesn't take care of this.
				viewportManager->UnselectAllViewports();
				//Now select the viewport that was clicked.
				viewportManager->SetSelectedViewport(clickedViewport);
			}			
		}
	}
	else
	{
		GUIActive = true;
	}

	event.Skip();
}

//If it is in mouse simulation mode, this acts as two normal clicks.
void WxIrrViewportWindow::OnLeftDoubleClick(wxMouseEvent &event)
{
	wxPoint mousePoint = event.GetPosition();

	viewportManager->SetMousePosition(mousePoint);

	if (!IrrlichtLeftMouseDown(event.ControlDown(), event.ShiftDown(), mousePoint.x, mousePoint.y))
	{
		if (mouseLeftClickAddObject)
		{
			mouseLeftClickAddObject = SimulationMouseDoubleClick();
		}
		else
		{
			SimulationMouseDoubleClick();
		}
	}

	/*if (mouseLeftClickAddObject)
	{
		mouseLeftClickAddObject = SimulationMouseClick();
	}
	if (mouseLeftClickAddObject)
	{
		mouseLeftClickAddObject = SimulationMouseClick();
	}*/

	event.Skip();
}


//A viewport is no longer grabbed and so set it to false.
void WxIrrViewportWindow::OnLeftUnClick(wxMouseEvent &event)
{
	IrrlichtLeftMouseUp(event.ControlDown(), event.ShiftDown(), event.GetX(), event.GetY());
	
	GUIActive = false;

	viewportManager->mouseDown = false;

	wxPoint oldMousePos = viewportManager->mouseDownStartPos;
	wxPoint currentMousePos = event.GetPosition();
	//A Mouse click occured
	if (oldMousePos == currentMousePos)
	{
		mouseLeftClickAddObject = SimulationMouseClick(event.ShiftDown(), event.ControlDown());
	}

	viewportManager->SetViewportGrabbed(false, currentMousePos);

	event.Skip();
}

void WxIrrViewportWindow::OnRightClick(wxMouseEvent &event)
{
	WxIrrViewport* clickedViewport = viewportManager->GetViewportClicked(event.GetX(), event.GetY());
	if(clickedViewport)
	{
		//Unselect all viewports because a viewport will still be selected because the viewportmanager doesn't take care of this.
		viewportManager->UnselectAllViewports();
		//Now select the viewport that was clicked.
		viewportManager->SetSelectedViewport(clickedViewport);
	}
	if (viewportManager->GetSelectedViewport()->GetParent())
	{
		contextMenu->Enable(ID_RemoveViewport, true);
	}
	else
	{
		contextMenu->Enable(ID_RemoveViewport, false);
	}
	PopupMenu(contextMenu, event.GetPosition());

	event.Skip();
}

void WxIrrViewportWindow::OnMiddleClick(wxMouseEvent &event)
{
	//WxIrrViewport* clickedViewport = viewportManager->GetViewportClicked(event.GetX(), event.GetY());
	//if(clickedViewport)
	//	clickedViewport->Remove();
	//event.Skip();
	
	event.Skip();
}

void WxIrrViewportWindow::OnMouseMove(wxMouseEvent &event)
{
	wxPoint mousePos = event.GetPosition();

	static wxPoint oldMousePos = mousePos;

	if(!GUIActive)
	{
		SimulationMouseMove(mousePos, event.ShiftDown(), viewportManager->GetViewportClicked(mousePos.x, mousePos.y));
		//If a viewport is already grabbed then change its size
		//else check if it is over a viewport sash.
		/*if (!mouseLeftClickAddObject)
		{*/
			if (viewportManager->isViewportGrabbed())
			{
				viewportManager->ResizeGrabbedViewport(event.GetPosition());
			}
			else
			{
				if (!viewportManager->mouseDown)
					viewportManager->FindGrabableViewport(event.GetX(), event.GetY());
			}

			if (!viewportManager->GetGrabableViewport() && viewportManager->mouseDown && event.LeftIsDown())
			{
				wxPoint mouseDifference = mousePos - viewportManager->GetMousePosition();
				viewportManager->SetMousePosition(mousePos);
				//viewportManager->ChangeSelectedViewportCameraRotation(mouseDifference);
				/*viewportManager->GetMouseManager()->mouseMovedFlag = true;
				viewportManager->GetMouseManager()->moveXAmount = mouseDifference.x;
				viewportManager->GetMouseManager()->moveYAmount = mouseDifference.y;*/

				IrrlichtCameraMouseMove(mouseDifference.x , mouseDifference.y, viewportManager->GetSelectedViewport());
				//IrrlichtMouseMove(event.ControlDown(), event.ShiftDown(), mousePos.x, mousePos.y, mouseDifference.x, mouseDifference.y) ;
			}
		/*}
		else
		{
			viewportManager->SetMousePosition(mousePos);
		}*/
	}
	else
	{
		wxPoint mouseDifference = mousePos - oldMousePos;
		IrrlichtMouseMove(event.ControlDown(), event.ShiftDown(), mousePos.x, mousePos.y, mouseDifference.x, mouseDifference.y) ;
		viewportManager->SetMousePosition(mousePos);
	}

	oldMousePos = mousePos;
	
	event.Skip();
}

void WxIrrViewportWindow::OnMouseEnter(wxMouseEvent &event)
{
	viewportManager->SetMouseInWindow(true);
	viewportManager->SetMousePosition(event.GetPosition());

	//this->SetFocus();
	
	event.Skip();
}

void WxIrrViewportWindow::OnMouseLeave(wxMouseEvent &event)
{
	viewportManager->SetMouseInWindow(false);
	//viewportManager->GetKeyboardManager()->Reset();
	IrrlichtCameraKeyboardReset();
	
	/*if (!event.Dragging())
	{
		this->GetParent()->SetFocus();
		viewportManager->GetMouseManager()->Reset();
	}*/

	event.Skip();
}

void WxIrrViewportWindow::OnKeyDown(wxKeyEvent &event)
{
	if (viewportManager->IsMouseInWindow())
	{
		if (event.GetKeyCode() == 87 && !viewportManager->GetKeyboardManager()->upKey)
		{
			IrrlichtCameraKeyDown(87, viewportManager->GetSelectedViewport());
			//viewportManager->GetKeyboardManager()->upKey = true;
			//viewportManager->GetKeyboardManager()->IncrementCount();
		}
		if (event.GetKeyCode() == 83 && !viewportManager->GetKeyboardManager()->downKey)
		{
			IrrlichtCameraKeyDown(83, viewportManager->GetSelectedViewport());
			//viewportManager->GetKeyboardManager()->downKey = true;
			//viewportManager->GetKeyboardManager()->IncrementCount();
		}
		if (event.GetKeyCode() == 65 && !viewportManager->GetKeyboardManager()->leftKey)
		{
			IrrlichtCameraKeyDown(65, viewportManager->GetSelectedViewport());
			//viewportManager->GetKeyboardManager()->leftKey = true;
			//viewportManager->GetKeyboardManager()->IncrementCount();
		}
		if (event.GetKeyCode() == 68 && !viewportManager->GetKeyboardManager()->rightKey)
		{
			IrrlichtCameraKeyDown(68, viewportManager->GetSelectedViewport());
			//viewportManager->GetKeyboardManager()->rightKey = true;
			//viewportManager->GetKeyboardManager()->IncrementCount();
		}

	}

	//event.Skip();
}

void WxIrrViewportWindow::OnKeyUp(wxKeyEvent &event)
{
	if (viewportManager->IsMouseInWindow())
	{
		/*if (event.GetKeyCode() == 87)
			viewportManager->GetKeyboardManager()->upKey = false;
		if (event.GetKeyCode() == 83)
			viewportManager->GetKeyboardManager()->downKey = false;
		if (event.GetKeyCode() == 65)
			viewportManager->GetKeyboardManager()->leftKey = false;
		if (event.GetKeyCode() == 68)
			viewportManager->GetKeyboardManager()->rightKey = false;

		viewportManager->GetKeyboardManager()->DecrementCount();*/

		int keyCode = event.GetKeyCode();
		if (keyCode == 87 || keyCode == 83 || keyCode == 65 || keyCode == 68)
		IrrlichtCameraKeyUp(event.GetKeyCode());
	}

	event.Skip();
}

void WxIrrViewportWindow::DrawText(wxString text, wxPoint& point)
{
	wxPaintDC dc(this);

	wxSize halfSize = dc.GetTextExtent(text) / 2;
	dc.DrawText(text, point - halfSize);
}