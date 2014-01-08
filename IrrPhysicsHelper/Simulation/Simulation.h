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

#ifndef _WX_IRR_SIMULATION
#define _WX_IRR_SIMULATION

#include <iostream>
#include <fstream>
using namespace std;

#include <wx/wx.h>
#include "../IrrlichtInclude.h"
#include "../Physics Engine/PhysicsEngineInclude.h"

#include "../Math/MathExpression.h"

#include "../Serialization/Serialization.h"

#include "../WxIrrViewport.h"

#include "../General/ThreeDPlane.h"

#include "../UI/ChartFrame/ChartFrame.h"

#include "../GUI Enviornment/PhysicsHelperGUIEnviornment.h"

enum SimulationType
{
	SimulationType_None,
    SimulationType_Playground,
    SimulationType_Motion,
    SimulationType_VectorAddition,
    SimulationType_TwoVector,
    SimulationType_ForceWithoutRamp,
    SimulationType_ForceWithRamp,
    SimulationType_Spring,
    SimulationType_Pendulum,
    SimulationType_CenterOfMass,
    SimulationType_AtwoodMachine,
    SimulationType_CoulombLaw,
    SimulationType_Gravitation,
	SimulationType_Graphing,
    SimulationType_LightReflectionAndRefraction,
    SimulationType_Waves
};

enum ModelTypes
{
    cone,
    cube,
    cylinder,
    hemisphere,
    pyramid,
    sphere
};

enum AddObjectMouseState
{
	AddObjectMouseState_None,
	AddObjectMouseState_Adding,
	AddObjectMouseState_Scaling
};


enum
{
    IDFlag_NotMousePickable = 0,
    IDFlag_IsMousePickable = 1 << 0,
    IDFlag_IsMouseHighlightable = 1 << 1
};

enum AxisIdentifier
{
	AxisIdentifier_X,
	AxisIdentifier_Y,
	AxisIdentifier_Z,
	AxisIdentifier_ALL
};

class Simulation
{
protected:
	IrrlichtDevice* device;
	IVideoDriver* driver;
	IGUIEnvironment* guiEnv;
	PhysicsEngine* physicsEngine;

	SimulationType simulationType;

	wxString statusBarText;

    bool showVelocity;
	bool showAngularVelocity;
    bool showAllAccelerations;
    bool showNetAcceleration;
	bool showAllForces;
    bool showNetForce;
	SColor velocityArrowColor;
	SColor angularVelocityArrowColor;
	SColor accelerationArrowColor;
	SColor forceArrowColor;

	bool simulationPaused;
	bool forward;
	float timePassedFrame;
	float timePassedDirectionFrame;
	float totalTime;
	float timeScale;

	float timeSkipAmount;

	wxString notes;

	bool showAxes;
	bool showNames;

	S3DVertex axesPoints[6];
	u16 axesIndices[6];

	bool colorChangedFlag;

	SColor XAxisColor;
	SColor YAxisColor;
	SColor ZAxisColor;

	SMaterial basicMaterial;

	bool saved;

	bool isRecording;
	bool isRecordingFirstFrame;

	//Selected Objects
	List<ISceneNode*>* selectedObjects;

	List<PhysicsObject*>* recordingObjects;

	//Mouse over add object
	bool isMouseChecking;
	int numOfMouseClicks;
	ISceneNode* mouseOverSceneNode;
	ISceneNode* tempAddMouseObject;
	Vector3 threeDMousePosition;

	ThreeDPlane mousePickingPlane;
	Vector3 mousePlanePosition;
	bool usePlaneForMousePicking;
	AxisIdentifier mousePlaneRotationAxis;
	bool rotateMousePlaneOnAxis;

	List<Vector3>* moveToList;

	bool showXZGridSceneNode;
	GridSceneNode* XZGridSceneNode;
	bool showXYGridSceneNode;
	GridSceneNode* XYGridSceneNode;
	bool showYZGridSceneNode;
	GridSceneNode* YZGridSceneNode;

public:
	static WxIrrViewportManager* viewportManager;
	static UIController* uiController;
	CustomSceneNodeManager* customSceneNodeManager;
	PhysicsHelperGUIEnviornment* physicsHelperGUIEnviornment;

	Simulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, SimulationType _simulationType = SimulationType_None, CustomSceneNodeManager* _customSceneNodeManager = 0);

	virtual ~Simulation();

	virtual void CopyBasicSimulationAttributes(Simulation* currentSimulation);

	virtual void Clear();

	virtual void Update(float timePassedSeconds, bool ignorePaused = false);
	virtual void UpdateAfter(float timePassedSeconds, WxIrrViewport* viewport);

	virtual void Draw(WxIrrViewport* currentViewport = 0);
	virtual void DrawNames(WxIrrViewport* currentViewport);

	virtual void Reset();

	void Run()
	{
		simulationPaused = false;
		physicsEngine->Run();
		uiController->SimulationRun();
	}

	void Pause()
	{
		simulationPaused = true;
		physicsEngine->Pause();
		uiController->SimulationPause();
	}

	bool IsRunning()
	{
		return !simulationPaused;
	}

	void ChangeTimeSkipAmount(float amt)
	{
		timeSkipAmount = amt;
	}

	void SkipNext()
	{
		Update(timeSkipAmount, true);
		physicsEngine->Update(timeSkipAmount, true);
	}

	float GetTotalTime()
	{
		return totalTime;
	}

	SimulationType GetSimulationType()
	{
		return simulationType;
	}

	virtual void ShowVelocityArrow() { showVelocity = true; }
	virtual void ShowAngularVelocityArrow() { showAngularVelocity = true; }
	virtual void ShowAccelerationArrow() { showNetAcceleration = true; }
	virtual void ShowForceArrow() { showNetForce = true; }

	virtual void HideVelocityArrow() { showVelocity = false; }
	virtual void HideAngularVelocityArrow() { showAngularVelocity = false; }
	virtual void HideAccelerationArrow() { showNetAcceleration = false; }
	virtual void HideForceArrow() { showNetForce = false; }

	virtual void ChangeVelocityArrowColor(SColor& color) { velocityArrowColor = color; }
	virtual void ChangeAngularVelocityArrowColor(SColor& color) { angularVelocityArrowColor = color; }
	virtual void ChangeAccelerationArrowColor(SColor& color) { accelerationArrowColor = color; }
	virtual void ChangeForceArrowColor(SColor& color) { forceArrowColor = color; }

	SColor GetXAxisColor() { return XAxisColor; }
	SColor GetYAxisColor() { return YAxisColor; }
	SColor GetZAxisColor() { return ZAxisColor; }

	bool GetColorChangedFlag();

	void ShowAxes()	{ showAxes = true; }
	void HideAxes()	{ showAxes = false; }

	virtual void SetXAxisColor(SColor& color);
	virtual void SetYAxisColor(SColor& color);
	virtual void SetZAxisColor(SColor& color);

	virtual void showXZGrid();
	virtual void hideXZGrid();
	virtual void showXYGrid();
	virtual void hideXYGrid();
	virtual void showYZGrid();
	virtual void hideYZGrid();

	void ShowObjectNames()	{ showNames = true; }
	void HideObjectNames()	{ showNames = false; }

	virtual void StartRecording();
	virtual void StopRecording();
	virtual void StartPhysicsEngineRecording();
	virtual void StopPhysicsEngineRecording();

	//Add object mouse
	//returns true if done checking for mouse clicks.
	virtual void StartMouseCheck();
	virtual void StopMouseCheck();
	virtual bool MouseClick(bool isShiftDown, bool isControlDown);
	virtual bool MouseClickNumLeft(bool isShiftDown, int num);
	virtual bool MouseDoubleClick();

	virtual void AddMoveToPoint(Vector3& point);
	virtual void AddMoveToObject(ISceneNode* obj);

	virtual void UsePlaneForMousePicking(bool shouldUse, Vector3& planePos)
	{
		usePlaneForMousePicking = shouldUse;
		mousePlanePosition = planePos;
	}
	virtual void DiablePlaneForMousePicking()
	{
		usePlaneForMousePicking = false;
	}
	virtual void UsePlaneForMousePicking(bool shouldUse, const Vector3 planePos)
	{
		usePlaneForMousePicking = shouldUse;
		mousePlanePosition = planePos;
	}
	virtual void UsePlaneForMousePicking(bool shouldUse, Vector3 planePos, Vector3& normal)
	{
		usePlaneForMousePicking = shouldUse;
		mousePickingPlane.ChangePlane(normal, planePos);
	}
	virtual void DisablePlaneForMousePicking()
	{
		usePlaneForMousePicking = false;
	}
	virtual void EnableRotationOfMousePlane(AxisIdentifier _mousePlaneRotationAxis)
	{
		rotateMousePlaneOnAxis = true;
		mousePlaneRotationAxis = _mousePlaneRotationAxis;
	}
	virtual void DisableRotationOfMousePlane()
	{
		rotateMousePlaneOnAxis = false;
	}

	virtual void UpdateMousePosition(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport, float collisionOffset = 0.0f);

	//Object selections
	List<ISceneNode*>* GetSelectedObjects() { return selectedObjects; }
	virtual void ClearSelectedObjects();
	virtual void ChangeSelectedObjects(ISceneNode* selectedNode);
	virtual void AddSelectedObject(ISceneNode* selectedNode);
	virtual bool UnselectObject(ISceneNode* selectedNode);
	virtual bool IsASelectedObject(ISceneNode* selectedNode);
	virtual bool IsASelectedObject(ISceneNode* selectedNode, Node<ISceneNode*>*& listNode);

	//Serialization
	void SetSaved() { saved = true; }
	void SetUnSaved() { saved = false; }
	bool IsSaved() { return saved;}

	virtual void SerializeIn(istream &is);
	virtual void SerializeOut(ostream &os);

	typedef void (*ChangeStatusBarText)(wxString& text);
	static ChangeStatusBarText changeStatusBarTextFunctionPointer;
	void ChangeStatusBarTextFunction(wxString& text)
	{
		statusBarText = text;
	}
};

#endif