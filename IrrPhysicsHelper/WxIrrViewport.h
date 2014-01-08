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

#ifndef _WX_IRR_VIEWPORT
#define _WX_IRR_VIEWPORT

#include <wx/wx.h>
#include <wx/splitter.h>
#include "WxIrrKeyboardManager.h"
#include "UI/WxIrrMenuBar.h"
#include "UI/UIController.h"

enum ViewportSplitOrientation
{
	SPLITORIENT_NONE,
	SPLITORIENT_HORIZ,
	SPLITORIENT_VERT
};

enum ViewportSashOrientation
{
	SASHORIENT_TOP,
	SASHORIENT_BOTTOM,
	SASHORIENT_LEFT,
	SASHORIENT_RIGHT
};

const int WX_IRR_VIEWPORT_BORDER_WIDTH = 2;

class WxIrrViewport
{
private:
	WxIrrViewport* parentViewport;
	ViewportSplitOrientation orient;
	WxIrrViewport* split1;
	WxIrrViewport* split2;
	ICameraSceneNode* camera;
	wxPoint position;
	wxSize size;
	//The ratio of split1/(split1+split2)
	float splitRatio;
	bool selected;

	//Move camera to variables
	Vector3 targetPoint;
	bool isTargetingPoint;
	float targetStopDistance;

public:
	WxIrrViewport(wxPoint pos, wxSize _size);
	WxIrrViewport(wxPoint pos, wxSize _size, WxIrrViewport* parent, ICameraSceneNode* _camera);
	~WxIrrViewport();

	rect<s32> GetIrrArea();
	rect<s32> GetIrrClientArea();

	wxSize GetSize() { return size; }
	wxPoint GetPos() { return position; }
	void SetPos(wxPoint pos) { position = pos; }
	WxIrrViewport* GetParent() { return parentViewport; }
	ICameraSceneNode* GetCamera() { return camera; }
	void SetCamera(ICameraSceneNode* _camera) { camera = _camera; }
	ViewportSplitOrientation GetOrient() { return orient; }
	WxIrrViewport* GetSplit1() { return split1; }
	WxIrrViewport* GetSplit2() { return split2; }

	WxIrrViewport* GetSelectedViewport();
	bool isSelected() { return selected; }
	void Select() { selected = true; }
	void Unselect() { selected = false; }
	void RecursiveUnselect();
	void UnselectParentViewports();

	WxIrrViewport* GetSiblingViewport();

	WxIrrViewport* GetViewportClicked(int x, int y);

	bool CheckIfPointWithinArea(int x, int y, wxPoint upperLeft, wxPoint lowerRight);
	bool CheckIfPointWithin(int x, int y);
	bool CheckIfPointWithinClient(int x, int y);
	bool CheckIfPointWithinSash(int x, int y, ViewportSashOrientation sashOrient);

	ICameraSceneNode* GetCopiedCamera(ISceneManager* smgr);
	void SetCameraAspectRatio();

	void SplitHorizontal(ISceneManager* smgr);
	void SplitVertical(ISceneManager* smgr);

	void RefreshRatio();

	void PaintFunc(void (*Draw)(WxIrrViewport*));

	wxSize GetUpdatedChildSize(int difference, wxSize newSize, bool isSplit1);
	void ReSize(wxPoint pos, wxSize newSize);

	WxIrrViewport* GetIfGrabbed(int x, int y, ViewportSashOrientation sashOrient);

	void Remove(ISceneManager* smgr);
	void BecomeChild(bool isSplit1, ISceneManager* smgr);
	void RemoveChildren();

	//Returns true when both pointing at and a certain distance from point.
	void StartTargeting(Vector3& point, float linearStopDistance);
	void ResetTargeting();
	void MoveAndRotateCamLinearToPoint(float linearProportionSpeed, float angularProportionSpeed, float timePassedSinceLastFrame,
		float angularError = 1.0f);

	void Update(float timePassedSinceLastFrame);
	void RecursiveUpdate(float timePassedSinceLastFrame);
};


//class WxIrrRenderViewport : public wxWindow
//{
//private:
//	ViewportSplitOrientation orient;
//	WxIrrRenderViewport* split1;
//	WxIrrRenderViewport* split2;
//	ICameraSceneNode* camera;
//public:
//	WxIrrRenderViewport(wxWindow* parent, wxWindowID id)
//		: wxWindow(parent, id, wxDefaultPosition, parent->GetSize())
//	{
//		orient = SPLITORIENT_NONE;
//		split1 = NULL;
//		split2 = NULL;
//	}
//
//	WxIrrRenderViewport(wxWindow* parent, wxWindowID id, bool isSmall)
//		: wxWindow(parent, id)
//	{
//		orient = SPLITORIENT_NONE;
//		split1 = NULL;
//		split2 = NULL;
//	}
//
//	~WxIrrRenderViewport()
//	{
//		delete split1;
//		delete split2;
//	}
//
//	rect<s32> GetIrrArea(wxPoint point, wxSize size)
//	{
//		rect<s32> area;
//
//		area.UpperLeftCorner.X = point.x;
//		area.UpperLeftCorner.Y = point.y;
//		area.LowerRightCorner.X = point.x + size.GetWidth();
//		area.LowerRightCorner.Y = point.y + size.GetHeight();
//
//		return area;
//	}
//
//	void SetCamera(ICameraSceneNode* _camera) { camera = _camera; }
//	WxIrrRenderViewport* MakeNewCopyOfSelf(wxWindow* parent, int id);
//
//	void PaintFunc(void (*Draw)(ICameraSceneNode*, rect<s32>, rect<s32>, WxIrrRenderViewport*))
//	{
//		wxPaintDC dc(this);
//		if (orient == SPLITORIENT_NONE)
//		{
//			Draw(camera, GetIrrArea(GetParent()->GetPosition(), GetParent()->GetSize()), GetIrrArea(wxPoint(0, 0), GetClientSize()), this);
//		}
//		else
//		{
//			if (split1)
//				split1->PaintFunc(Draw);
//
//			if (split2)
//				split2->PaintFunc(Draw);
//		}
//		Refresh(false);
//	}
//
//	rect<s32> GetViewportArea()
//	{
//		return GetIrrArea(GetPosition(), GetClientSize());
//	}
//
//	void EraseBackground(wxEraseEvent &event)
//	{
//	}
//
//	void OnPaint(wxPaintEvent &event);
//	void OnSize(wxSizeEvent &event);
//	void OnLeftClick(wxMouseEvent &event);
//	void OnRightClick(wxMouseEvent &event);
//
//	DECLARE_EVENT_TABLE()
//
//};


/*class WxIrrRenderViewport
{

};

class WxIrrRenderViewportHolder
{
	
};*/

class WxIrrViewportManager
{
	friend class PhysicsHelperManager;
private:
	UIController* uiController;

	wxWindow* viewportWindow;

	WxIrrViewport* rootViewport;	

	WxIrrViewport* grabableViewport;
	wxPoint grabStartPoint;
	bool viewportGrabbed;

	wxCursor sizerNS;
	wxCursor sizerWE;

	WxIrrKeyboardManager* keyboardManager;
	WxIrrMouseManager* mouseManager;

	wxPoint mousePos;
	bool mouseInWindow;

public:
	bool mouseDown;
	wxPoint mouseDownStartPos;

	WxIrrViewportManager(wxWindow* parent, wxWindowID id)
	{
		viewportWindow = parent;

		rootViewport = new WxIrrViewport(wxPoint(0,0), parent->GetClientSize());
		SetSelectedViewport(rootViewport);

		grabableViewport = NULL;
		grabStartPoint = wxPoint(0, 0);
		viewportGrabbed = false;

		sizerNS = wxCursor(wxCURSOR_SIZENS);
		sizerWE = wxCursor(wxCURSOR_SIZEWE);

		keyboardManager = new WxIrrKeyboardManager();
		mouseManager = new WxIrrMouseManager();

		mouseInWindow = true;
		mouseDown = false;
	}

	~WxIrrViewportManager()
	{
		delete rootViewport;
		delete keyboardManager;
		delete mouseManager;
	}

	void SetCamera(ICameraSceneNode* _camera)
	{
		rootViewport->SetCamera(_camera);
	}

	void OnPaint(void (*Draw)(WxIrrViewport*))
	{
		rootViewport->PaintFunc(Draw);
	}

	void OnSize(wxSize newSize)
	{
		if (rootViewport)
			rootViewport->ReSize(wxPoint(0, 0), newSize);
	}

	WxIrrViewport* GetViewportClicked(int x, int y)
	{
		return rootViewport->GetViewportClicked(x, y);
	}

	WxIrrViewport* GetRootViewport()
	{
		return rootViewport;
	}

	WxIrrViewport* GetGrabableViewport()
	{
		return grabableViewport;
	}

	void SetSelectedViewport(WxIrrViewport* viewport)
	{
		WxIrrViewport* selectedViewport = GetSelectedViewport();
		if (!selectedViewport)
		{
			selectedViewport = rootViewport;
		}
		else
		{
			selectedViewport->Unselect();
		}
		selectedViewport = viewport;
		selectedViewport->Select();
	}

	WxIrrViewport* GetSelectedViewport()
	{
		return rootViewport->GetSelectedViewport();
	}

	void UnselectAllViewports()
	{
		rootViewport->RecursiveUnselect();
	}

	WxIrrKeyboardManager* GetKeyboardManager()
	{
		return keyboardManager;
	}

	WxIrrMouseManager* GetMouseManager()
	{
		return mouseManager;
	}

	bool IsMouseInWindow()
	{
		return mouseInWindow;
	}
	void SetMouseInWindow(bool isMouseInWindow)
	{
		mouseInWindow = isMouseInWindow;
	}

	void ChangeSelectedViewportCameraRotation(wxPoint mouseDifference)
	{
		WxIrrViewport* selectedViewport = GetSelectedViewport();
		Vector3 currentCameraRot = selectedViewport->GetCamera()->getRotation();
		currentCameraRot.Y += mouseDifference.x*0.2f;
		currentCameraRot.X += mouseDifference.y*0.2f;
		selectedViewport->GetCamera()->setRotation(currentCameraRot);
	}

	void FindGrabableViewport(int x, int y)
	{
		grabableViewport = rootViewport->GetIfGrabbed(x, y, SASHORIENT_TOP);
		if (grabableViewport)
		{
			WxIrrViewport* grabableParent = grabableViewport->GetParent();
			if (grabableParent->GetOrient() == SPLITORIENT_HORIZ)
			{
				viewportWindow->SetCursor(sizerWE);
			}
			else if (grabableParent->GetOrient() == SPLITORIENT_VERT)
			{
				viewportWindow->SetCursor(sizerNS);
			}
		}
		else
		{
			viewportWindow->SetCursor(wxNullCursor);
		}
	}

	void SetViewportGrabbed(bool grabbed, wxPoint pnt)
	{
		viewportGrabbed = grabbed;
		if (grabbed)
		{
			grabStartPoint = pnt;
		}
	}

	bool isViewportGrabbed()
	{
		return viewportGrabbed;
	}

	void SetMousePosition(wxPoint pos)
	{
		mousePos = pos;
	}

	wxPoint GetMousePosition()
	{
		return mousePos;
	}

	void SplitViewportHorizontally(ISceneManager* smgr)
	{
		GetSelectedViewport()->SplitHorizontal(smgr);
		uiController->EnableRemoveWindow();
	}

	void SplitViewportVertically(ISceneManager* smgr)
	{
		GetSelectedViewport()->SplitVertical(smgr);
		uiController->EnableRemoveWindow();
	}

	void RemoveViewport(ISceneManager* smgr)
	{
		GetSelectedViewport()->Remove(smgr);

		if(rootViewport->GetSplit1() == NULL && rootViewport->GetSplit2() == NULL)
		{
			uiController->DisableRemoveWindow();
		}
		else
		{
			uiController->EnableRemoveWindow();
		}
	}

	void ResizeGrabbedViewport(wxPoint currentMousePos)
	{
		wxPoint mouseDifference = currentMousePos - grabStartPoint;
		WxIrrViewport* grabbedParent = grabableViewport->GetParent();

		if (grabbedParent)
		{
			//Depending on the orientation the sizes and positions change differently.
			if (grabbedParent->GetOrient() == SPLITORIENT_HORIZ)
			{
				//if (grabableViewport == grabbedParent->GetSplit1())
				//{

				//}
				//else if (grabableViewport == grabbedParent->GetSplit2())
				//{
				//	
				//}

				wxSize split1NewSize = grabbedParent->GetSplit1()->GetSize();
				split1NewSize.SetWidth(split1NewSize.GetWidth() + mouseDifference.x);
				grabbedParent->GetSplit1()->ReSize(grabbedParent->GetSplit1()->GetPos(), split1NewSize);

				wxSize split2NewSize = grabbedParent->GetSplit2()->GetSize();
				split2NewSize.SetWidth(split2NewSize.GetWidth() - mouseDifference.x);
				wxPoint newSplit2Pos = grabbedParent->GetSplit2()->GetPos();
				newSplit2Pos.x += mouseDifference.x;
				grabbedParent->GetSplit2()->ReSize(newSplit2Pos, split2NewSize);
			}
			else if (grabbedParent->GetOrient() == SPLITORIENT_VERT)
			{
				wxSize split1NewSize = grabbedParent->GetSplit1()->GetSize();
				split1NewSize.SetHeight(split1NewSize.GetHeight() + mouseDifference.y);
				grabbedParent->GetSplit1()->ReSize(grabbedParent->GetSplit1()->GetPos(), split1NewSize);

				wxSize split2NewSize = grabbedParent->GetSplit2()->GetSize();
				split2NewSize.SetHeight(split2NewSize.GetHeight() - mouseDifference.y);
				wxPoint newSplit2Pos = grabbedParent->GetSplit2()->GetPos();
				newSplit2Pos.y += mouseDifference.y;
				grabbedParent->GetSplit2()->ReSize(newSplit2Pos, split2NewSize);
			}

			//Change the ratio of the parent because the children positions have changed.
			grabbedParent->RefreshRatio();

			//Change the start point for the next mousemove event.
			grabStartPoint = currentMousePos;
		}
	}
};


#ifdef _WX_IRR_WINDOWS

	class WxIrrViewportWindow : public wxWindow
	{
		friend class PhysicsHelperManager;
	private:
		WxIrrViewportManager* viewportManager;
		wxTimer gameTime;
		irr::SIrrlichtCreationParameters param;
		IrrlichtDevice* device;
		wxMenu* contextMenu;

		bool mouseLeftClickAddObject;

		bool GUIActive;
	public:
		WxIrrViewportWindow(wxWindow* parent, wxWindowID id) : wxWindow(parent, id), gameTime(this)
		{
			Setup();
		}

		void Setup();

		void InitalizeViewportManager();

		~WxIrrViewportWindow();

		void SetupDevice(SIrrlichtCreationParameters& paramaters, void (*Draw)(WxIrrViewportManager*), void (*Update)(void), 
			bool (*IrrlichtLeftMouseDown)(bool controlDown, bool shiftDown, int x, int y),
			bool (*IrrlichtLeftMouseUp)(bool controlDown, bool shiftDown, int x, int y),
			bool (*irrlichtLeftMouseDoubleClick)(bool controlDown, bool shiftDown, int x, int y),
			bool (*IrrlichtMouseMove)(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY),
			void (*IrrlichtCameraMouseMove)(int moveX, int moveY, WxIrrViewport* selectedViewport),
			void (*IrrlichtCameraKeyDown)(int id, WxIrrViewport* selectedViewport), void (*IrrlichtCameraKeyUp)(int id), void (*IrrlichtCameraKeyboardReset)(void),
			void (*SimulationMouseMove)(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport),
			bool (*SimulationMouseClick)(bool isShiftDown, bool isControlDown),	bool (*SimulationMouseDoubleClick)(void), void (*SimulationStartMouseChecking)(void));
		IrrlichtDevice* GetDevice() { return device; }

		void SetCamera(ICameraSceneNode* _camera)
		{
			viewportManager->SetCamera(_camera);
		}

		WxIrrViewportManager* GetViewportManager();

		void SplitViewportHorizontally();
		void SplitViewportVertically();
		void RemoveViewport();

		void OnPaint(wxPaintEvent &event);
		void OnSize(wxSizeEvent &event);
		void OnTimer(wxTimerEvent &event);
		void OnLeftClick(wxMouseEvent &event);
		void OnLeftDoubleClick(wxMouseEvent &event);
		void OnLeftUnClick(wxMouseEvent &event);
		void OnRightClick(wxMouseEvent &event);
		void OnMiddleClick(wxMouseEvent &event);
		void OnMouseMove(wxMouseEvent &event);
		void OnMouseEnter(wxMouseEvent &event);
		void OnMouseLeave(wxMouseEvent &event);
		void OnKeyDown(wxKeyEvent &event);
		void OnKeyUp(wxKeyEvent &event);
		void EraseBackground(wxEraseEvent &event)
		{
		}

		void ChangeMouseClickBehavior();

		void DrawText(wxString text, wxPoint& point);

		void (*Draw)(WxIrrViewportManager*);
		void (*Update)(void);
		void (*SimulationStartMouseChecking)(void);
		void (*SimulationMouseMove)(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport);
		bool (*SimulationMouseClick)(bool isShiftDown, bool isControlDown);
		bool (*SimulationMouseDoubleClick)(void);

		bool (*IrrlichtLeftMouseDown)(bool controlDown, bool shiftDown, int x, int y);
		bool (*IrrlichtLeftMouseUp)(bool controlDown, bool shiftDown, int x, int y);
		bool (*IrrlichtLeftMouseDoubleClick)(bool controlDown, bool shiftDown, int x, int y);
		bool (*IrrlichtMouseMove)(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY);
		void (*IrrlichtCameraMouseMove)(int moveX, int moveY, WxIrrViewport* selectedViewport);
		void (*IrrlichtCameraKeyDown)(int id, WxIrrViewport* selectedViewport);
		void (*IrrlichtCameraKeyUp)(int id);
		void (*IrrlichtCameraKeyboardReset)(void);

		DECLARE_EVENT_TABLE()
	};

#endif

#ifdef _WX_IRR_LINUX	

	#include <wx/glcanvas.h>

	class WxIrrViewportWindow : public wxGLCanvas
	{
		friend class PhysicsHelperManager;
	private:
		WxIrrViewportManager* viewportManager;
		wxTimer gameTime;
		irr::SIrrlichtCreationParameters param;
		IrrlichtDevice* device;
		wxMenu* contextMenu;

		bool mouseLeftClickAddObject;

		bool GUIActive;
	public:
		WxIrrViewportWindow(wxWindow* parent, wxWindowID id) : wxGLCanvas(parent, id, 0), gameTime(this)
		{
			Setup();
		}

		void Setup();

		void InitalizeViewportManager();

		~WxIrrViewportWindow();

		void SetupDevice(SIrrlichtCreationParameters& paramaters, void (*Draw)(WxIrrViewportManager*), void (*Update)(void), 
			bool (*IrrlichtLeftMouseDown)(bool controlDown, bool shiftDown, int x, int y),
			bool (*IrrlichtLeftMouseUp)(bool controlDown, bool shiftDown, int x, int y),
			bool (*irrlichtLeftMouseDoubleClick)(bool controlDown, bool shiftDown, int x, int y),
			bool (*IrrlichtMouseMove)(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY),
			void (*IrrlichtCameraMouseMove)(int moveX, int moveY, WxIrrViewport* selectedViewport),
			void (*IrrlichtCameraKeyDown)(int id, WxIrrViewport* selectedViewport), void (*IrrlichtCameraKeyUp)(int id), void (*IrrlichtCameraKeyboardReset)(void),
			void (*SimulationMouseMove)(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport),
			bool (*SimulationMouseClick)(bool isShiftDown),	bool (*SimulationMouseDoubleClick)(void), void (*SimulationStartMouseChecking)(void));
		IrrlichtDevice* GetDevice() { return device; }

		void SetCamera(ICameraSceneNode* _camera)
		{
			viewportManager->SetCamera(_camera);
		}

		WxIrrViewportManager* GetViewportManager();
		
		void SplitViewportHorizontally();
		void SplitViewportVertically();
		void RemoveViewport();

		void OnPaint(wxPaintEvent &event);
		void OnSize(wxSizeEvent &event);
		void OnTimer(wxTimerEvent &event);
		void OnLeftClick(wxMouseEvent &event);
		void OnLeftDoubleClick(wxMouseEvent &event);
		void OnLeftUnClick(wxMouseEvent &event);
		void OnRightClick(wxMouseEvent &event);
		void OnMiddleClick(wxMouseEvent &event);
		void OnMouseMove(wxMouseEvent &event);
		void OnMouseEnter(wxMouseEvent &event);
		void OnMouseLeave(wxMouseEvent &event);
		void OnKeyDown(wxKeyEvent &event);
		void OnKeyUp(wxKeyEvent &event);
		void EraseBackground(wxEraseEvent &event)
		{
		}

		void ChangeMouseClickBehavior();
		
		void DrawText(wxString text, wxPoint& point);

		void (*Draw)(WxIrrViewportManager*);
		void (*Update)(void);
		void (*SimulationStartMouseChecking)(void);
		void (*SimulationMouseMove)(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport);
		bool (*SimulationMouseClick)(bool isShiftDown, bool isControlDown);
		bool (*SimulationMouseDoubleClick)(void);

		bool (*IrrlichtLeftMouseDown)(bool controlDown, bool shiftDown, int x, int y); 
		bool (*IrrlichtLeftMouseUp)(bool controlDown, bool shiftDown, int x, int y);
		bool (*IrrlichtLeftMouseDoubleClick)(bool controlDown, bool shiftDown, int x, int y);
		bool (*IrrlichtMouseMove)(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY);
		void (*IrrlichtCameraMouseMove)(int moveX, int moveY, WxIrrViewport* selectedViewport);
		void (*IrrlichtCameraKeyDown)(int id, WxIrrViewport* selectedViewport);
		void (*IrrlichtCameraKeyUp)(int id);
		void (*IrrlichtCameraKeyboardReset)(void);

		DECLARE_EVENT_TABLE()
	};

#endif

#ifdef _WX_IRR_MACOS	
#endif




#endif
