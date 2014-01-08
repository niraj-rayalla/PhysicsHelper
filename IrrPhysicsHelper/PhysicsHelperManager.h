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

#ifndef _WX_IRR_PHYSICS_HELPER_MANAGER
#define _WX_IRR_PHYSICS_HELPER_MANAGER

#include "Include.h"
#include "General/GeneralClasses.h"
#include "Physics Engine/PhysicsEngine.h"
using namespace Physics_Engine;
#include "Simulation/SimulationInclude.h"
#include "General/ThreeDGraph.h"
#include "WxIrrMainWindow.h"
#include "UI/UIInclude.h"
//#include "GUI Enviornment/PhysicsHelperGUIEnviornment.h"
#include "IrrlichtEventReceiver.h"

#include <iostream>
#include <fstream>

Simulation* globalSimulationPtr;
WxIrrMainWindow* globalMainWindowPtr;
PhysicsEngine* globalPhysicsEnginePtr;

void SimulationReset(void)
{
	globalSimulationPtr->Reset();
}

void RunSimulation(void)
{
	globalSimulationPtr->Run();
}

void PauseSimulation(void)
{
	globalSimulationPtr->Pause();
}

void SimulationSkipNext(void)
{
	globalSimulationPtr->SkipNext();
}

void SimulationStartMouseChecking(void)
{
	return globalSimulationPtr->StartMouseCheck();
}

void SimulationMouseOver(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport);

bool SimulationMouseClick(bool isShiftDown, bool isControlDown)
{
	return globalSimulationPtr->MouseClick(isShiftDown, isControlDown);
}

bool SimulationMouseDoubleClick(void)
{
	return globalSimulationPtr->MouseDoubleClick();
}

void SimulationStartRecord(void)
{
	globalSimulationPtr->StartRecording();
}

void SimulationStopRecord(void)
{
	globalSimulationPtr->StopRecording();
}

void SimulationShowAxes(bool show)
{
	if (show)
	{
		globalSimulationPtr->ShowAxes();
	}
	else
	{
		globalSimulationPtr->HideAxes();
	}
}
SColor SimulationXAxisGetColor()
{
	return globalSimulationPtr->GetXAxisColor();
}
SColor SimulationYAxisGetColor()
{
	return globalSimulationPtr->GetYAxisColor();
}
SColor SimulationZAxisGetColor()
{
	return globalSimulationPtr->GetZAxisColor();
}
void SimulationXAxisChangeColor(wxColour& color)
{
	globalSimulationPtr->SetXAxisColor(SColor(255, color.Red(), color.Green(), color.Blue()));
}
void SimulationYAxisChangeColor(wxColour& color)
{
	globalSimulationPtr->SetYAxisColor(SColor(255, color.Red(), color.Green(), color.Blue()));
}
void SimulationZAxisChangeColor(wxColour& color)
{
	globalSimulationPtr->SetZAxisColor(SColor(255, color.Red(), color.Green(), color.Blue()));
}

void SimulationShowObjectNames(bool show)
{
	if (show)
	{
		globalSimulationPtr->ShowObjectNames();
	}
	else
	{
		globalSimulationPtr->HideObjectNames();
	}
}
void SimulationShowXYGrid(bool show)
{
	if (show)
	{
		globalSimulationPtr->showXYGrid();
	}
	else
	{
		globalSimulationPtr->hideXYGrid();
	}
}
void SimulationShowXZGrid(bool show)
{
	if (show)
	{
		globalSimulationPtr->showXZGrid();
	}
	else
	{
		globalSimulationPtr->hideXZGrid();
	}
}
void SimulationShowYZGrid(bool show)
{
	if (show)
	{
		globalSimulationPtr->showYZGrid();
	}
	else
	{
		globalSimulationPtr->hideYZGrid();
	}
}

void SetupPHManagerPointer(void* ptr);
void ChangeToAtwoodMachineSimulation(void);
void ChangeToCenterOfMassSimulation(void);
void ChangeToCoulombLawSimulation(void);
void ChangeToForceWithoutRampSimulation(void);
void ChangeToForceWithRampSimulation(void);
void ChangeToGraphingSimulation(void);
void ChangeToGravitationSimulation(void);
void ChangeToLightSimulation(void);
void ChangeToMotionSimulation(void);
void ChangeToPendulumSimulation(void);
void ChangeToPlaygroundSimulation(void);
void ChangeToSpringSimulation(void);
void ChangeToVectorAdditionSimulation(void);
void ChangeToWavesSimulation(void);

void ChangeStatusBarText(wxString& text)
{
	if (globalMainWindowPtr)
		globalMainWindowPtr->SetStatusBarText(text);
}


void SimulationSave(wxString path)
{

	ofstream saveFile;
	saveFile.open(path.ToAscii());


	//Simulation type
	saveFile << globalSimulationPtr->GetSimulationType() << endl;
	globalPhysicsEnginePtr->SerializeOut(saveFile);
	globalSimulationPtr->SerializeOut(saveFile);

	saveFile.close();
}

void SimulationLoad(wxString path)
{
	if (globalSimulationPtr)
		globalSimulationPtr->Reset();

	ifstream loadFile;
	loadFile.open(path.ToAscii());
	

	//Simulation type
	int simulationType = 0;
	loadFile >> simulationType;

	if (simulationType == SimulationType_AtwoodMachine)
	{
		ChangeToAtwoodMachineSimulation();
	}
	else if (simulationType == SimulationType_CenterOfMass)
	{
		ChangeToCenterOfMassSimulation();
	}
	else if (simulationType == SimulationType_CoulombLaw)
	{
		ChangeToCoulombLawSimulation();
	}
	else if (simulationType == SimulationType_ForceWithoutRamp)
	{
		ChangeToForceWithoutRampSimulation();
	}
	else if (simulationType == SimulationType_ForceWithRamp)
	{
		ChangeToForceWithRampSimulation();
	}
	else if (simulationType == SimulationType_Graphing)
	{
		ChangeToGraphingSimulation();
	}
	else if (simulationType == SimulationType_Gravitation)
	{
		ChangeToGravitationSimulation();
	}
	else if (simulationType == SimulationType_LightReflectionAndRefraction)
	{
		ChangeToLightSimulation();
	}
	else if (simulationType == SimulationType_Motion)
	{
		ChangeToMotionSimulation();
	}
	else if (simulationType == SimulationType_Pendulum)
	{
		ChangeToPendulumSimulation();
	}
	else if (simulationType == SimulationType_Playground)
	{
		ChangeToPlaygroundSimulation();
	}
	else if (simulationType == SimulationType_Spring)
	{
		ChangeToSpringSimulation();
	}
	else if (simulationType == SimulationType_VectorAddition)
	{
		ChangeToVectorAdditionSimulation();
	}
	else if (simulationType == SimulationType_Waves)
	{
		ChangeToWavesSimulation();
	}
	globalPhysicsEnginePtr->SerializeIn(loadFile);

	globalSimulationPtr->SerializeIn(loadFile);

	loadFile.close();
}

bool IsSimulationSaved(void)
{
	return globalSimulationPtr->IsSaved();
}

//Simulation Pointer Functions

//Pendulum
void PendulumSimulationAdd(wxString _name, double theta, double phi, double length, float mass)
{
	((PendulumSimulation*)globalSimulationPtr)->AddPendulumSimulationNode(_name, theta, phi, length, mass);
}
void PendulumSimulationAddComponents(wxString _name, double X, double Y, double Z, float mass)
{
	((PendulumSimulation*)globalSimulationPtr)->AddPendulumSimulationNodeComponents(_name, X, Y, Z, mass);
}
void PendulumSimulationRemove(int index)
{
	((PendulumSimulation*)globalSimulationPtr)->RemovePendulumSimulationNode(index);
}
void PendulumChangeSelection(wxArrayInt intArray)
{
	((PendulumSimulation*)globalSimulationPtr)->ChangeSelectedColor(intArray);
}
void PendulumChangeAccelerationEquations(std::string XString, std::string YString, std::string ZString)
{
	((PendulumSimulation*)globalSimulationPtr)->ChangeEquations(XString, YString, ZString);
}
void PendulumChangeCurrentAccelerationLabel(float X, float Y, float Z);

//Vector
void VectorSimulationAddCartesian(float X, float Y, float Z)
{
	((VectorSimulation*)globalSimulationPtr)->AddVector(Vector3(X, Y, Z));
}
void VectorSimulationAddSpherical(float length, float theta, float phi)
{
	((VectorSimulation*)globalSimulationPtr)->AddVector(length, theta, phi);
}
void VectorSimulationRemove(int index)
{
	((VectorSimulation*)globalSimulationPtr)->RemoveVector(index);
}
void VectorSimulationClear()
{
	((VectorSimulation*)globalSimulationPtr)->Clear();
}
void VectorSimulationChangeSelection(wxArrayInt intArray)
{
	((VectorSimulation*)globalSimulationPtr)->ChangeSelectedVectors(intArray);
}
void VectorSimulationChangeLineUp()
{
	((VectorSimulation*)globalSimulationPtr)->ChangeVectorLineUp();
}
void VectorAddObjectToListBox(wxString str)
{
	((VectorPanel*)globalMainWindowPtr->GetRightPanel())->AddObjectToListBox(str);
}

//Gravitation
void GravitationSimulationAddSingle(wxString _name, bool enabled, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ, bool isRelative, int relativeIndex)
{
	((GravitationSimulation*)globalSimulationPtr)->AddObject(_name, Vector3(posX, posY, posZ), Vector3(velX, velY, velZ), mass, isRelative, relativeIndex, radius, enabled);
}
void GravitationSimulationAddMultiple(wxString _name, bool enabled, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			std::string velX, std::string velY, std::string velZ, bool isRelative, int relativeIndex)
{
	((GravitationSimulation*)globalSimulationPtr)->AddObject(_name, mass, radius, vector3d<std::string>(posX, posY, posZ), Vector3(posXBegin, posYBegin, posZBegin),
		Vector3(posXEnd, posYEnd, posZEnd), Vector3(posXRes, posYRes, posZRes), vector3d<std::string>(velX, velY, velZ), isRelative, relativeIndex, enabled);
}
void GravitationSimulationRemove(int index)
{
	((GravitationSimulation*)globalSimulationPtr)->RemoveObject(index);
}
void GravitationSimulationClear()
{
	((GravitationSimulation*)globalSimulationPtr)->Clear();
}
void GravitationSimulationChangeSelections(wxArrayInt intArray)
{
	((GravitationSimulation*)globalSimulationPtr)->ChangeSelections(intArray);
}
void GravitationSimulationChangeEnabledState(int index)
{
	((GravitationSimulation*)globalSimulationPtr)->ChangeEnabledState(index);
}
void GravitationSimulationAddObjectToListBox(wxString str, bool enabled)
{
	((GravitationPanel*)globalMainWindowPtr->GetRightPanel())->AddObjectToListBox(str, enabled);
}

//Coulomb
void CoulombLawSimulationAddSingle(wxString _name, bool enabled, float mass, float charge, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ, bool isRelative, int relativeIndex)
{
	((CoulombLawSimulation*)globalSimulationPtr)->AddObject(_name, Vector3(posX, posY, posZ), Vector3(velX, velY, velZ), mass, charge, isRelative, relativeIndex, radius, enabled);
}
void CoulombLawSimulationAddMultiple(wxString _name, bool enabled, std::string mass, std::string charge, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			std::string velX, std::string velY, std::string velZ, bool isRelative, int relativeIndex)
{
	((CoulombLawSimulation*)globalSimulationPtr)->AddObject(_name,mass, charge, radius, vector3d<std::string>(posX, posY, posZ), Vector3(posXBegin, posYBegin, posZBegin),
		Vector3(posXEnd, posYEnd, posZEnd), Vector3(posXRes, posYRes, posZRes), vector3d<std::string>(velX, velY, velZ), isRelative, relativeIndex, enabled);
}
void CoulombLawSimulationRemove(int index)
{
	((CoulombLawSimulation*)globalSimulationPtr)->RemoveObject(index);
}
void CoulombLawSimulationClear()
{
	((CoulombLawSimulation*)globalSimulationPtr)->Clear();
}
void CoulombLawSimulationChangeSelections(wxArrayInt intArray)
{
	((CoulombLawSimulation*)globalSimulationPtr)->ChangeSelections(intArray);
}
void CoulombLawSimulationChangeEnabledState(int index)
{
	((CoulombLawSimulation*)globalSimulationPtr)->ChangeEnabledState(index);
}
void CoulombLawSimulationAddObjectToListBox(wxString str, bool enabled)
{
	((CoulombPanel*)globalMainWindowPtr->GetRightPanel())->AddObjectToListBox(str, enabled);
}


//Center Of Mass
wxString* CenterOfMassSimulationAddSingle(wxString _name, float mass, float radius, float posX, float posY, float posZ, bool isRelative, int relativeIndex)
{
	return ((CenterOfMassSimulation*)globalSimulationPtr)->AddObject(_name, Vector3(posX, posY, posZ), mass, radius, isRelative, relativeIndex);
}
wxString* CenterOfMassSimulationAddMultiple(wxString _name, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			bool isRelative, int relativeIndex)
{
	return ((CenterOfMassSimulation*)globalSimulationPtr)->AddObjectUsingEquation(_name, vector3d<std::string>(posX, posY, posZ), mass, radius, Vector3(posXBegin, posYBegin, posZBegin),
		Vector3(posXEnd, posYEnd, posZEnd), Vector3(posXRes, posYRes, posZRes), isRelative, relativeIndex);
}
wxString* CenterOfMassSimulationRemove(int index)
{
	return ((CenterOfMassSimulation*)globalSimulationPtr)->RemoveObject(index);
}
wxString* CenterOfMassSimulationClear()
{
	return ((CenterOfMassSimulation*)globalSimulationPtr)->ClearCenterOfMassObjects();
}
void CenterOfMassSimulationChangeSelections(wxArrayInt intArray)
{
	((CenterOfMassSimulation*)globalSimulationPtr)->ChangeSelected(intArray);
}
wxString* CenterOfMassSimulationChangeEnabledState(int index)
{
	return ((CenterOfMassSimulation*)globalSimulationPtr)->ChangeEnabled(index);
}
void CenterOfMassAddObjectToListBox(wxString str, bool enabled)
{
	((CenterOfMassPanel*)globalMainWindowPtr->GetRightPanel())->AddObjectToListBox(str, enabled);
}
void CenterOfMassChangeCOMLabels(float COMX, float COMY, float COMZ, float totalMass, int numObjects)
{
	((CenterOfMassPanel*)globalMainWindowPtr->GetRightPanel())->ChangeCOMLabels(COMX, COMY, COMZ, totalMass, numObjects);
}


//Graphing
void GraphingSimulationAddCylindrical(wxString _name, const char* equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid = false)
{
	CylindricalAxis _colorAxis = ThreeDGraphCylindrical_Radius;

	if (colorAxis == 1)
	{
		_colorAxis = ThreeDGraphCylindrical_Theta;
	}
	else if (colorAxis == 2)
	{
		_colorAxis = ThreeDGraphCylindrical_Z;
	}

	((GraphingSimulation*)globalSimulationPtr)->AddCylindricalGraph(_name, equationString, Scale, SColor(255, lowColorR, lowColorG, lowColorB), SColor(255, highColorR, highColorG, highColorB),
		_colorAxis, _thetaResolution, _thetaStart, _thetaEnd, _radiusResolution, _radiusStart, _radiusEnd, _solid);
}
void GraphingSimulationAddParametric(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
		int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid)
{
	ParametricAxis _colorAxis = ThreeDGraphParametric_U;

	if (colorAxis == 1)
	{
		_colorAxis = ThreeDGraphParametric_V;
	}
	else if (colorAxis == 2)
	{
		_colorAxis = ThreeDGraphParametric_X;
	}
	else if (colorAxis == 3)
	{
		_colorAxis = ThreeDGraphParametric_Y;
	}
	else if (colorAxis == 4)
	{
		_colorAxis = ThreeDGraphParametric_Z;
	}

	((GraphingSimulation*)globalSimulationPtr)->AddParametricGraph(_name, _xEquationString, _yEquationString, _zEquationString, Scale, SColor(255, lowColorR, lowColorG, lowColorB), SColor(255, highColorR, highColorG, highColorB),
		_colorAxis, _uResolution, _uStart, _uEnd, _vResolution, _vStart, _vEnd, _solid);
}
void GraphingSimulationAddRectangular(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis, int equationAxis, 
		int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid = false)
{
	RectangularAxis _colorAxis = ThreeDGraph_X;

	if (colorAxis == 1)
	{
		_colorAxis = ThreeDGraph_Y;
	}
	else if (colorAxis == 2)
	{
		_colorAxis = ThreeDGraph_Z;
	}

	RectangularAxis _equationAxis = ThreeDGraph_X;

	if (equationAxis == 1)
	{
		_equationAxis = ThreeDGraph_Y;
	}
	else if (equationAxis == 2)
	{
		_equationAxis = ThreeDGraph_Z;
	}

	((GraphingSimulation*)globalSimulationPtr)->AddRectangularGraph(_name, _equationString, Scale, SColor(255, lowColorR, lowColorG, lowColorB), SColor(255, highColorR, highColorG, highColorB), _colorAxis,
		_equationAxis, _graphWidthResolution, _widthStart, _widthEnd, _graphHeightResolution, _heightStart, _heightEnd, _solid);

}
void GraphingSimulationAddSpherical(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid = false)
{
	SphericalAxis _colorAxis = ThreeDGraphSpherical_Phi;

	if (colorAxis == 1)
	{
		_colorAxis = ThreeDGraphSpherical_Radius;
	}
	else if (colorAxis == 2)
	{
		_colorAxis = ThreeDGraphSpherical_Theta;
	}

	((GraphingSimulation*)globalSimulationPtr)->AddSphericalGraph(_name, _equationString, Scale, SColor(255, lowColorR, lowColorG, lowColorB), SColor(255, highColorR, highColorG, highColorB), _colorAxis,
		_thetaResolution, _thetaStart, _thetaEnd, _phiResolution, _phiStart, _phiEnd, _solid);
}
void GraphingSimulationRemove(int index)
{
	((GraphingSimulation*)globalSimulationPtr)->RemoveGraph(index);
}
void GraphingSimulationClear()
{
	((GraphingSimulation*)globalSimulationPtr)->Reset();
}
void GraphingSimulationChangeSelections(wxArrayInt intArray)
{
	((GraphingSimulation*)globalSimulationPtr)->ChangeSelections(intArray);
}
void GraphingSimulationChangeEnabledState(int index)
{
	((GraphingSimulation*)globalSimulationPtr)->ChangeEnabled(index);
}
void GraphingAddObjectToListBox(wxString str, bool enabled)
{
	((GraphingPanel*)globalMainWindowPtr->GetRightPanel())->AddObjectToListBox(str, enabled);
}

//Playground Simulation
void PlaygrounSimulationAddObjectToListBox(wxString& str)
{
	if (globalMainWindowPtr)
		((PlaygroundPanel*)globalMainWindowPtr->GetRightPanel())->AddObjectToListBox(str);
}
void PlaygroundAddSphereUsingMouse()
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartSphereMouseAdd();
}
void PlaygroundAddCubeUsingMouse(void)
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartCubeMouseAdd();
}
void PlaygroundAddCylinderUsingMouse(void)
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartCylinderMouseAdd();
}
void PlaygroundAddConeUsingMouse(void)
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartConeMouseAdd();
}
void PlaygroundAddCapsuleUsingMouse(void)
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartCapsuleMouseAdd();
}
void PlaygroundAddFromFileUsingMouse(wxString filename)
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartFromFileMouseAdd(filename);
}
void PlaygroundAddSpringUsingMouse()
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartSpringMouseAdd();
}
void PlaygroundAddPointToPointJointUsingMouse()
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartPointToPointJointMouseAdd();
}
void PlaygroundAddHingeJointUsingMouse()
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartHingeJointMouseAdd();
}
void PlaygroundAddGenericJointUsingMouse()
{
	((PlaygroundSimulation*)globalSimulationPtr)->StartGenericJointMouseAdd();
}
void PlaygroundAddSphere(wxString name, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ)
{
	//((PlaygroundSimulation*)globalSimulationPtr)->AddSphereObject(name, Vector3(posX, posY, posZ), Vector3(velX, velY, velZ), radius, mass);
}
void PlaygroundAddCube(wxString name, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ)
{
	//((PlaygroundSimulation*)globalSimulationPtr)->AddCubeObject(name, Vector3(posX, posY, posZ), Vector3(velX, velY, velZ), scale, mass);
}
void PlaygroundAddFromFile(wxString name, wxString filename, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ)
{
	//((PlaygroundSimulation*)globalSimulationPtr)->AddFromFileObject(name, filename, Vector3(posX, posY, posZ), Vector3(velX, velY, velZ), scale, mass);
}
void PlaygroundAddMultipleObjectsCylindrical(bool singleSurface, wxString zEquation, double thetaRes, double rRes, double minTheta, double maxTheta, double minR, double maxR,
			wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation)
{
	((PlaygroundSimulation*)globalSimulationPtr)->AddMultipleObjectsCylindrical(singleSurface, zEquation, thetaRes, rRes, minTheta, maxTheta, minR, maxR,
		massEquation, xRotEquation, yRotEquation, zRotEquation);
}
void PlaygroundAddMultipleObjectsParametric(bool singleSurface, wxString xEquation, wxString yEquation, wxString zEquation, double uRes, double vRes, double minU, double maxU, 
	double minV, double maxV, wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation)
{
	((PlaygroundSimulation*)globalSimulationPtr)->AddMultipleObjectsParametric(singleSurface, xEquation, yEquation, zEquation, uRes, vRes, minU, maxU, minV, maxV,
		massEquation, xRotEquation, yRotEquation, zRotEquation);
}
void PlaygroundAddMultipleObjectsRectangular(bool singleSurface, int axisIndex, wxString equation, double firstRes, double secondRes, double minFirst, double maxFirst,
	double minSecond, double maxSecond,	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation)
{
	((PlaygroundSimulation*)globalSimulationPtr)->AddMultipleObjectsRectangular(singleSurface, axisIndex, equation, firstRes, secondRes, minFirst, maxFirst, minSecond, maxSecond,
		massEquation, xRotEquation, yRotEquation, zRotEquation);
}
void PlaygroundAddMultipleObjectsSpherical(bool singleSurface, wxString rEquation, double thetaRes, double phiRes, double minTheta, double maxTheta, double minPhi, double maxPhi,
	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation)
{
	((PlaygroundSimulation*)globalSimulationPtr)->AddMultipleObjectsSpherical(singleSurface, rEquation, thetaRes, phiRes, minTheta, maxTheta, minPhi, maxPhi,
		massEquation, xRotEquation, yRotEquation, zRotEquation);
}
void PlaygroundRemoveObjectFunction(int index)
{
	((PlaygroundSimulation*)globalSimulationPtr)->RemoveObject(index);
}
void PlaygroundClearObjectsFunction(void)
{
	((PlaygroundSimulation*)globalSimulationPtr)->ClearObjects();
}
void PlaygroundChangeSelection(wxArrayInt intArray)
{
	((PlaygroundSimulation*)globalSimulationPtr)->ChangeSelection(intArray);
}
void PlaygroundObjectListDoubleClick(int index)
{
	((PlaygroundSimulation*)globalSimulationPtr)->ObjectListDoubleClick(index);
}
void PlaygroundDeselectObjectListView()
{
	((PlaygroundPanel*)globalMainWindowPtr->GetRightPanel())->DeselectSelectedItem();
}




class PhysicsHelperManager
{
private:
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;

	//PhysicsHelperGUIEnviornment* physicsHelperGUIEnviornment;
	PhysicsHeplerEventHandler* eventHandler;

	Simulation* currentSimulation;
	WxIrrMainWindow* mainWindow;
	WxIrrViewportManager* viewportManager;
	UIController* uiController;

public:
	ITimer* deviceTimer;
	u32 oldTime;
	u32 newTime;
	float deltaTimeInSeconds;

	PhysicsEngine* physicsEngine;
	CustomSceneNodeManager* customSceneNodeManager;

	PhysicsHelperManager(PhysicsHeplerEventHandler* _eventHandler)
	{
		physicsEngine = NULL;
		globalPhysicsEnginePtr = physicsEngine;

		customSceneNodeManager = new CustomSceneNodeManager();

		viewportManager = NULL;
		uiController = NULL;

		globalSimulationPtr = NULL;
		currentSimulation = NULL;
		globalMainWindowPtr = NULL;

		eventHandler = _eventHandler;
	}

	~PhysicsHelperManager()
	{		
		delete currentSimulation;
		delete uiController;
		delete physicsEngine;
		delete customSceneNodeManager;
		delete eventHandler;
	}

	void SetupDevice(IrrlichtDevice* dev, WxIrrMainWindow* _mainWindow)
	{
		physicsEngine = new PhysicsEngine(dev);
		globalPhysicsEnginePtr = physicsEngine;

		device = dev;
		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
		guienv = device->getGUIEnvironment();

		//Setup Timer
		deviceTimer = device->getTimer();
		oldTime = deviceTimer->getTime();

		mainWindow = _mainWindow;
		
		mainWindow->OnResetSimulationFunctionPointer = SimulationReset;
		mainWindow->OnSaveSimulationFunctionPointer = SimulationSave;
		mainWindow->OnLoadSimulationFunctionPointer = SimulationLoad;
		mainWindow->IsSimulationSaved = IsSimulationSaved;
		mainWindow->OnRunSimulationFunctionPointer = RunSimulation;
		mainWindow->OnPauseSimulationFunctionPointer = PauseSimulation;
		mainWindow->OnSimulationSkipNextFunctionPointer = SimulationSkipNext;
		mainWindow->OnSimulationStartRecordingFunctionPointer = SimulationStartRecord;
		mainWindow->OnSimulationStopRecordingFunctionPointer = SimulationStopRecord;

		mainWindow->OnAtwoodMachineSimulationFunctionPointer = ChangeToAtwoodMachineSimulation;
		mainWindow->OnCenterOfMassSimulationFunctionPointer = ChangeToCenterOfMassSimulation;
		mainWindow->OnCoulombLawSimulationFunctionPointer = ChangeToCoulombLawSimulation;
		mainWindow->OnForceWithoutRampSimulationFunctionPointer = ChangeToForceWithoutRampSimulation;
		mainWindow->OnForceWithRampSimulationFunctionPointer = ChangeToForceWithRampSimulation;
		mainWindow->OnGraphingSimulationFunctionPointer = ChangeToGraphingSimulation;
		mainWindow->OnGravitationSimulationFunctionPointer = ChangeToGravitationSimulation;
		mainWindow->OnLightSimulationFunctionPointer = ChangeToLightSimulation;
		mainWindow->OnMotionSimulationFunctionPointer = ChangeToMotionSimulation;
		mainWindow->OnPendulumSimulationFunctionPointer = ChangeToPendulumSimulation;
		mainWindow->OnPlaygroundSimulationFunctionPointer = ChangeToPlaygroundSimulation;
		mainWindow->OnSpringSimulationFunctionPointer = ChangeToSpringSimulation;
		mainWindow->OnVectorAdditionSimulationFunctionPointer = ChangeToVectorAdditionSimulation;
		mainWindow->OnWavesSimulationFunctionPointer = ChangeToWavesSimulation;

		globalMainWindowPtr = mainWindow;

		uiController = new UIController(mainWindow->GetMenuBar(), mainWindow->GetMenuBarManager(), mainWindow->GetToolBarsManager());
		uiController->DisableRemoveWindow();

		SetupPHManagerPointer(this);
		
		viewportManager = mainWindow->GetViewportWindow()->GetViewportManager();
		viewportManager->uiController = uiController;

		Simulation::changeStatusBarTextFunctionPointer = ChangeStatusBarText;
		Simulation::uiController = uiController;
		Simulation::viewportManager = viewportManager;

		ChangeSimulation(SimulationType_Playground);
	}

	void ChangeSimulation(SimulationType simulationType)
	{
		if (currentSimulation && simulationType == currentSimulation->GetSimulationType())
		{
			return;
		}

		Simulation* oldSimulation = currentSimulation;
		currentSimulation = NULL;

		switch(simulationType)
		{
		case SimulationType_None:
			{
				currentSimulation = new Simulation(device, driver, physicsEngine);
				mainWindow->ChangeRightPanelToNothing();

				break;
			}
		case SimulationType_VectorAddition:
			{
				VectorSimulation* vectorSimulation = new VectorSimulation(device, driver, physicsEngine, VectorAddObjectToListBox);
				if (oldSimulation)
				{
					vectorSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}

				/*vectorSimulation->AddVector(Vector3(0.0f, 10.0f, 0.0f));
				vectorSimulation->AddVector(Vector3(20.0f, 10.0f, 10.0f));
				vectorSimulation->AddVector(Vector3(20.0f, -20.0f, 10.0f));
				vectorSimulation->ChangeVectorLineUp();*/

				currentSimulation = vectorSimulation;
				mainWindow->ChangeRightPanelToVector(VectorSimulationAddSpherical, VectorSimulationAddCartesian, VectorSimulationRemove, VectorSimulationClear, VectorSimulationChangeLineUp, VectorSimulationChangeSelection);

				break;
			}
		case SimulationType_CenterOfMass:
			{
				CenterOfMassSimulation* centerOfMassSimulation = new CenterOfMassSimulation(device, driver, physicsEngine, CenterOfMassAddObjectToListBox, CenterOfMassChangeCOMLabels);
				if (oldSimulation)
				{
					centerOfMassSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}
				

				currentSimulation = centerOfMassSimulation;
				mainWindow->ChangeRightPanelToCenterOfMass(CenterOfMassSimulationAddSingle, CenterOfMassSimulationAddMultiple, CenterOfMassSimulationRemove, CenterOfMassSimulationClear, CenterOfMassSimulationChangeSelections, CenterOfMassSimulationChangeEnabledState);

				break;
			}
		case SimulationType_Gravitation:
			{
				GravitationSimulation* gravitationSimulation = new GravitationSimulation(device, driver, physicsEngine, GravitationSimulationAddObjectToListBox);
				if (oldSimulation)
				{
					gravitationSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}

				/*gravitationSimulation->AddObject(Vector3(0, 0, 0), Vector3(0, 0, 1), 1000000000000.0f);
				gravitationSimulation->AddObject(Vector3(-5, 0, 0), Vector3(0, 0, -1), 1000000000000.0f);*/

				currentSimulation = gravitationSimulation;
				mainWindow->ChangeRightPanelToGravitation(GravitationSimulationAddSingle, GravitationSimulationAddMultiple, GravitationSimulationRemove, GravitationSimulationClear, GravitationSimulationChangeSelections, GravitationSimulationChangeEnabledState);

				break;
			}
		case SimulationType_CoulombLaw:
			{
				CoulombLawSimulation* coulombLawSimulation = new CoulombLawSimulation(device, driver, physicsEngine, CoulombLawSimulationAddObjectToListBox);			
				if (oldSimulation)
				{
					coulombLawSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}

				coulombLawSimulation->ShowSensors();
				coulombLawSimulation->ShowVectorFieldSensors();
				//coulombLawSimulation->AddVectorFieldSensors(vector3d<std::string>("x", "y", "z"), Vector3(0, 0, 0), Vector3(10, 10, 10), Vector3(10, 10, 10));
				
				currentSimulation = coulombLawSimulation;
				mainWindow->ChangeRightPanelToCoulomb(CoulombLawSimulationAddSingle, CoulombLawSimulationAddMultiple, CoulombLawSimulationRemove, CoulombLawSimulationClear, CoulombLawSimulationChangeSelections, CoulombLawSimulationChangeEnabledState);

			break;
			}
		case SimulationType_Graphing:
			{
				GraphingSimulation* graphingSimulation = new GraphingSimulation(device, driver, physicsEngine, GraphingAddObjectToListBox);
				if (oldSimulation)
				{
					graphingSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}

				/*RectangularThreeDGraph* graph = new RectangularThreeDGraph("10*sin(x*cos(x)*3)*sin(z)/(x*z)", 1.0f, SColor(255, 0, 0, 255), SColor(255, 255, 0, 0), device, ThreeDGraph_X, ThreeDGraph_Y, 100, -10.0, 10.0, 100, -10.0, 10.0);
				graph->CalculateGraph();
				graph->AddToSceneManager(device, smgr);*/

				//graphingSimulation->AddRectangularGraph("10*sin(x*cos(x)*3)*sin(z)/(x*z)", 1.0f, SColor(255, 0, 0, 255), SColor(255, 255, 0, 0), ThreeDGraph_X, ThreeDGraph_Y, 100, -10.0, 10.0, 100, -10.0, 10.0);
				//graphingSimulation->AddParametricGraph("cos(u)*sin(v)", "sin(u)*sin(v)", "v", 1.0f, SColor(255, 0, 0, 255), SColor(255, 255, 0, 0), ThreeDGraphParametric_U, 100, 0.0, 6.28, 100, 0.0, 6.28);
				//graphingSimulation->AddCylindricalGraph("10+sin(theta*10)", 1.0f, SColor(255, 0, 0, 255), SColor(255, 255, 0, 0), ThreeDGraphCylindrical_Z, 100, 0.0, 6.28, 100, 1.0, 6.28);
				//graphingSimulation->AddSphericalGraph("10+10*1/5*sin(6*theta)*sin(5*phi)", 1.0f, SColor(255, 0, 0, 255), SColor(255, 255, 0, 0), ThreeDGraphSpherical_Radius, 100, 0.0, 6.28, 100, 0.0, 3.14);

				currentSimulation = graphingSimulation;
				mainWindow->ChangeRightPanelToGraphing(GraphingSimulationAddCylindrical, GraphingSimulationAddParametric, GraphingSimulationAddRectangular, GraphingSimulationAddSpherical,
					GraphingSimulationRemove, GraphingSimulationClear, GraphingSimulationChangeSelections, GraphingSimulationChangeEnabledState);

				break;
			}
		case SimulationType_Motion:
			{
				BasicMotionSimulation* basicMotionSimulation = new BasicMotionSimulation(device, driver, physicsEngine);			
				if (oldSimulation)
				{
					basicMotionSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}

				/*basicMotionSimulation->AddGlobalAcceleration(0.0f, 3.0f, "0", "-9.8", "0");
				basicMotionSimulation->AddGlobalAcceleration(3.0f, 7.0f, "0", "9.8", "0");
				basicMotionSimulation->AddObject(Vector3_Zero, Vector3_Zero, 1.0f);
				BasicMotionTimedEquation* eqn = new BasicMotionTimedEquation(0.0f, 3.0f, "20t", "10*sin(t*2)", "0", BasicMotionEquationType_Position);
				basicMotionSimulation->basicMotionObjectList->GetHead()->GetData()->AddEquation(eqn);*/

				currentSimulation = basicMotionSimulation;
				mainWindow->ChangeRightPanelToNothing();

				break;
			}
		case SimulationType_Pendulum:
			{
				//currentSimulation->AddPendulumSimulationNode(1.0, 1.4, -1.0, 10.0, 1.0);// Vector3(-10.0f, 0.0f, 0.0f), 1.0);
				//currentSimulation->AddPendulumSimulationNode(1.0, 1.8, -1.0, 10.0, 1.0);// Vector3(-10.0f, 0.0f, 0.0f), 1.0);
				//currentSimulation->AddPendulumSimulationNode(1.0, 1.2, -1.0, 10.0, 1.0);// Vector3(-10.0f, 0.0f, 0.0f), 1.0);
				//currentSimulation->AddPendulumSimulationNode(1.0, 1.8, -1.0, 10.0, 1.0);// Vector3(-10.0f, 0.0f, 0.0f), 1.0);
				//currentSimulation->AddPendulumSimulationNode(1.0, 1.2, -1.0, 10.0, 1.0);// Vector3(-10.0f, 0.0f, 0.0f), 1.0);
				//currentSimulation->AddPendulumSimulationNode(1.0, 1.1, -1.0, 10.0, 1.0);// Vector3(-10.0f, 0.0f, 0.0f), 1.0);
				//pendulumSimulation->AddPendulumSimulationNode(Vector3(-10.0f, 5.0f, 0.0f), 1.0);
				//pendulumSimulation->AddPendulumSimulationNode(Vector3(0.0f, -10.0f, 0.0f), 1.0);
				//pendulumSimulation->AddPendulumSimulationNode(1.0, Vector3(0.0f, -10.0f, 0.0f), 1.0);
				//physicsEngine->GetObjectList()->GetHead()->GetNext()->GetNext()->GetData()->ShowObjectPath();
				/*currentSimulation->AddPendulumSimulationNode(1.0, Vector3(0.0f, -10.0f, 0.0f), 1.0);
				currentSimulation->AddPendulumSimulationNode(1.0, Vector3(0.0f, -10.0f, 0.0f), 1.0);
				currentSimulation->AddPendulumSimulationNode(1.0, Vector3(0.0f, -10.0f, 0.0f), 1.0);*/
				//currentSimulation->AddPendulumSimulationNode(1.0, 1.0, 1.0, 10.0, 1.0);

				mainWindow->ChangeRightPanelToPendulum(PendulumSimulationAdd, PendulumSimulationAddComponents, PendulumSimulationRemove, PendulumChangeSelection, PendulumChangeAccelerationEquations);

				PendulumSimulation* pendulumSimulation = new PendulumSimulation(device, driver, physicsEngine, PendulumChangeCurrentAccelerationLabel);
				if (oldSimulation)
				{
					pendulumSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}

				currentSimulation = pendulumSimulation;

				break;
			}

		case SimulationType_LightReflectionAndRefraction:
			{
				LightSimulation* lightSimulation = new LightSimulation(device, driver, physicsEngine, GraphingAddObjectToListBox);
				if (oldSimulation)
				{
					lightSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}

				currentSimulation = lightSimulation;

				lightSimulation->AddRectangularMedium(_("adfs"), "-40", 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), ThreeDGraph_X, ThreeDGraph_Y, 10, -30.0, 30.0, 10, -30.0, 30.0, false, true, 1.8f);
				lightSimulation->AddRectangularMedium(_("adfs"), "10", 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), ThreeDGraph_X, ThreeDGraph_Y, 10, -30.0, 30.0, 10, -30.0, 30.0, false, true, 1.4f);
				lightSimulation->AddRectangularMedium(_("adfs"), "50", 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), ThreeDGraph_X, ThreeDGraph_Y, 10, -30.0, 30.0, 10, -30.0, 30.0, false, true, 1.2f);
				lightSimulation->AddSphericalMedium(_("ASDF"), "20", 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), ThreeDGraphSpherical_Theta, 20, -3.14, 0.0, 20, 0.0, 3.14, false, true, 1.0f);
				lightSimulation->AddRectangularMedium(_("adfs"), "30", 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), ThreeDGraph_X, ThreeDGraph_X, 10, 0.0, 60.0, 10, -30.0, 30.0);
				lightSimulation->AddRectangularMedium(_("adfs"), "-30", 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), ThreeDGraph_X, ThreeDGraph_X, 10, 0.0, 60.0, 10, -30.0, 30.0);
				//lightSimulation->AddRectangularMedium(_("adfs"), "x", 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), ThreeDGraph_X, ThreeDGraph_Y, 100, -30.0, 30.0, 100, -30.0, 30.0);
				lightSimulation->AddLightRay(Vector3(20.0f, 40.0f, 0), Vector3(-0.15f, -1.0f, 0.0f));

				break;
			}
		case SimulationType_Playground:
			{
				mainWindow->ChangeRightPanelToPlayground(PlaygroundAddSphereUsingMouse, PlaygroundAddCubeUsingMouse, PlaygroundAddCylinderUsingMouse, 
					PlaygroundAddConeUsingMouse, PlaygroundAddCapsuleUsingMouse, PlaygroundAddSpringUsingMouse, PlaygroundAddFromFileUsingMouse,
					PlaygroundAddPointToPointJointUsingMouse, PlaygroundAddHingeJointUsingMouse, PlaygroundAddGenericJointUsingMouse,
					PlaygroundAddSphere, PlaygroundAddCube, PlaygroundAddFromFile,
					PlaygroundAddMultipleObjectsCylindrical, PlaygroundAddMultipleObjectsParametric, PlaygroundAddMultipleObjectsRectangular, PlaygroundAddMultipleObjectsSpherical,
					PlaygroundRemoveObjectFunction, PlaygroundClearObjectsFunction, PlaygroundChangeSelection, PlaygroundObjectListDoubleClick);

				PlaygroundSimulation* playgroundSimulation = new PlaygroundSimulation(device, driver, physicsEngine, PlaygrounSimulationAddObjectToListBox);
				if (oldSimulation)
				{
					playgroundSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}

				currentSimulation = playgroundSimulation;

				playgroundSimulation->DeselectSelectedObjectListView = PlaygroundDeselectObjectListView;

				break;
			}

		case SimulationType_Spring:
			{
				SpringSimulation* springSimulation = new SpringSimulation(device, driver, physicsEngine);
				if (oldSimulation)
				{
					springSimulation->CopyBasicSimulationAttributes(oldSimulation);
				}

				currentSimulation = springSimulation;

				springSimulation->AddSpringSimulationNode(_("Test"), 1.0, 10.0f, 25.0f, 1.0f);
				springSimulation->AddSpringSimulationNode(_("Test"), 1.0, 10.0f, 25.0f, 1.0f);
				springSimulation->AddSpringSimulationNode(_("Test"), 1.0, 10.0f, 25.0f, 1.0f);
				springSimulation->AddSpringSimulationNode(_("Test"), 1.0, 10.0f, 25.0f, 1.0f);
				springSimulation->AddSpringSimulationNode(_("Test"), 1.0, 10.0f, 25.0f, 1.0f);

				mainWindow->ChangeRightPanelToSpring();

				break;
			}
		}

		delete oldSimulation;

		currentSimulation->customSceneNodeManager = customSceneNodeManager;
		currentSimulation->physicsHelperGUIEnviornment = eventHandler->GetGUIEnvironment();

		currentSimulation->ChangeVelocityArrowColor(SColor(255, 0, 0, 255));
		currentSimulation->ChangeForceArrowColor(SColor(255, 255, 0, 0));
		currentSimulation->ChangeAccelerationArrowColor(SColor(255, 0, 255, 0));

		globalSimulationPtr = currentSimulation;
	}

	void Update()
	{
		//Get time
		newTime = deviceTimer->getTime();
		deltaTimeInSeconds = (float)(newTime - oldTime) * 0.001f;
		oldTime = newTime;

		//physicsHelperManager->deviceTimer->tick();

		//mainWindow->SetStatusBarText(_("Physics Helper"));

		if (currentSimulation)
		{
			currentSimulation->Update(deltaTimeInSeconds);
			if (currentSimulation->IsRunning())
				mainWindow->ChangeRightPanelTime(currentSimulation->GetTotalTime());
		}
		physicsEngine->Update(deltaTimeInSeconds);
		if (currentSimulation)
		{
			currentSimulation->UpdateAfter(deltaTimeInSeconds, mainWindow->GetViewportWindow()->GetViewportManager()->GetSelectedViewport());
		}

		if (viewportManager)
			viewportManager->GetRootViewport()->RecursiveUpdate(deltaTimeInSeconds);
	}

	void MouseOverViewportUpdate(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport)
	{
		if (currentSimulation && mouseOverViewport)
			currentSimulation->UpdateMousePosition(mousePos, isShiftDown, mouseOverViewport);
	}

	Simulation* GetCurrentSimulation()
	{
		return currentSimulation;
	}

	void Draw(WxIrrViewport* viewport)
	{
		if (currentSimulation)
			currentSimulation->Draw(viewport);
		physicsEngine->Draw(device);
	}

	WxIrrMainWindow* GetMainWindow() { return mainWindow; }
};

PhysicsHelperManager* globalPHManagerPointer;

void SetupPHManagerPointer(void* ptr)
{
	globalPHManagerPointer = (PhysicsHelperManager*)ptr;
}

void SimulationMouseOver(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport)
{
	globalPHManagerPointer->MouseOverViewportUpdate(mousePos, isShiftDown, mouseOverViewport);
}



void ChangeToAtwoodMachineSimulation(void)
{
}

void ChangeToCenterOfMassSimulation(void)
{
	globalPHManagerPointer->ChangeSimulation(SimulationType_CenterOfMass);
}

void ChangeToCoulombLawSimulation(void)
{
	globalPHManagerPointer->ChangeSimulation(SimulationType_CoulombLaw);
}

void ChangeToForceWithoutRampSimulation(void)
{
}

void ChangeToForceWithRampSimulation(void)
{
}

void ChangeToGraphingSimulation(void)
{
	globalPHManagerPointer->ChangeSimulation(SimulationType_Graphing);
}

void ChangeToGravitationSimulation(void)
{
	globalPHManagerPointer->ChangeSimulation(SimulationType_Gravitation);
}

void ChangeToLightSimulation(void)
{
}

void ChangeToMotionSimulation(void)
{
	globalPHManagerPointer->ChangeSimulation(SimulationType_Motion);
}

void ChangeToPendulumSimulation(void)
{
	globalPHManagerPointer->ChangeSimulation(SimulationType_Pendulum);
}

void ChangeToPlaygroundSimulation(void)
{
	globalPHManagerPointer->ChangeSimulation(SimulationType_Playground);
}

void ChangeToSpringSimulation(void)
{
}

void ChangeToVectorAdditionSimulation(void)
{
	globalPHManagerPointer->ChangeSimulation(SimulationType_VectorAddition);
}

void ChangeToWavesSimulation(void)
{
}


void PendulumChangeCurrentAccelerationLabel(float X, float Y, float Z)
{
	((PendulumPanel*)globalPHManagerPointer->GetMainWindow()->GetRightPanel())->ChangeCurrentAcceleration(X, Y, Z);
}

#endif