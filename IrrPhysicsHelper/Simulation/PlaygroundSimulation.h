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

#ifndef _WX_IRR_PLAYGROUND_SIMULATION
#define _WX_IRR_PLAYGROUND_SIMULATION

#include "Simulation.h"
#include "../General/ThreeDGraph.h"
#include "../Physics Engine/IrrlichtToBulletConnector.h"
#include <chart.h>

enum MouseAddObjectType
{
	MouseAddObjectType_None,
	MouseAddObjectType_CapsuleOrSphere,
	MouseAddObjectType_BoxOrCube,
	MouseAddObjectType_Cylinder,
	MouseAddObjectType_Cone,
	MouseAddObjectType_Capsule,
	MouseAddObjectType_FromFile,
	MouseAddObjectType_Spring,
	MouseAddObjectType_PointToPointJoint,
	MouseAddObjectType_HingeJoint,
	MouseAddObjectType_Slider,
	MouseAddObjectType_GenericConstraint
};



class PlaygroundSimulation : public Simulation
{
private:
	IrrlichtToBulletConnector* irrToBullConnector;
	MouseAddObjectType mouseAddObjectType;

	SpringSceneNode* tempSpringSceneNode;
	IrrlichtBulletConstraint* tempConstraint;

	List<IrrlichtToBulletDynamicObject*>* recordingObjects;

	void (*AddObjectToListBox)(wxString& str);
	int objectCount;
	int springCount;
	int constraintCount;

public:
	PlaygroundSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*addObjectToListBox)(wxString& str));
	~PlaygroundSimulation();

	void Reset();

	void Update(float timeInSecondsSinceLastFrame, bool ignorePaused = false);
	void UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport);

	void Draw(WxIrrViewport* currentViewport = 0);
	virtual void DrawNames(WxIrrViewport* currentViewport);

	void ShowVelocityArrow();
	void ShowAngularVelocityArrow();
	void ShowAccelerationArrow();
	void ShowForceArrow();

	void HideVelocityArrow();
	void HideAngularVelocityArrow();
	void HideAccelerationArrow();
	void HideForceArrow();

	void ChangeVelocityArrowColor(SColor& color);
	void ChangeAngularVelocityArrowColor(SColor& color);
	void ChangeAccelerationArrowColor(SColor& color);
	void ChangeForceArrowColor(SColor& color);

	void AddSphereObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float radius, float mass);
	void AddBoxObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, Vector3 scale, float mass);
	void AddCapsuleObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float radius, float height, float mass);
	void AddConeObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float radius, float height, float mass);
	void AddCubeObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float scale, float mass);
	void AddCylinderObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float radius, float height, float mass);
	void AddFromFileObject(wxString name, wxString filename, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float scale, float mass);
	void AddSpring(int index1, int index2);

	void StartSphereMouseAdd();
	void StartCubeMouseAdd();
	void StartCylinderMouseAdd();
	void StartConeMouseAdd();
	void StartCapsuleMouseAdd();
	void StartFromFileMouseAdd(wxString filename);
	void StartSpringMouseAdd();
	void StartPointToPointJointMouseAdd();
	void StartHingeJointMouseAdd();
	void StartSliderJointMouseAdd();
	void StartGenericJointMouseAdd();

	void AddStaticGraphToBullet(ThreeDGraph* graph);
	void AddMultipleObjectsCylindrical(bool singleSurface, wxString zEquation, double thetaRes, double rRes, double minTheta, double maxTheta, double minR, double maxR,
		wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation);
	void AddMultipleObjectsParametric(bool singleSurface, wxString xEquation, wxString yEquation, wxString zEquation, double uRes, double vRes, double minU, double maxU, 
		double minV, double maxV, wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation);
	void AddMultipleObjectsRectangular(bool singleSurface, int axisIndex, wxString equation, double firstRes, double secondRes, double minFirst, double maxFirst,
		double minSecond, double maxSecond,	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation);
	void AddMultipleObjectsSpherical(bool singleSurface, wxString rEquation, double thetaRes, double phiRes, double minTheta, double maxTheta, double minPhi, double maxPhi,
		wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation);

	void (*DeselectSelectedObjectListView)(void);

	void RemoveObject(int index);
	void ClearObjects(void);
	void ChangeSelection(wxArrayInt intArray);
	void ObjectListDoubleClick(int index);

	void StartRecording();
	void StopRecording();

	//returns true if done checking for mouse clicks.
	void StartMouseCheck();
	bool MouseClick(bool isShiftDown, bool isControlDown);
	void UpdateMousePosition(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport, float collisionOffset);

	void AddMoveToPoint(Vector3& point);
	void AddMoveToObject(ISceneNode* obj);

	void SerializeInListOfIrrlichtToBulletObjects(istream& is);
	virtual void SerializeIn(istream& is);
	virtual void SerializeOut(ostream& os);
};

#endif