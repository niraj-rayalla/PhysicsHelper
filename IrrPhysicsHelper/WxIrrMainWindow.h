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

#ifndef _WX_IRR_MAIN_WINDOW
#define _WX_IRR_MAIN_WINDOW

#include "Include.h"
#include "WxIrrViewport.h"
#include "UI/UIInclude.h"
#include <wx/bitmap.h>
#include <wx/filedlg.h>
#include <wx/colordlg.h>

class WxIrrMainWindow : public wxFrame
{
	friend class PhysicsHelperManager;
private:
	wxMenuBar *menuBar;
	PhysicsHelperMenuBar* menuBarManager;
	PhysicsHelperToolbars* toolBarsManager;
	WxIrrViewportWindow* leftPanel;
	SimulationPanel* rightPanel;
	wxAuiManager m_mgr;

	wxString statusBarText;

public:
    WxIrrMainWindow(const wxString& title, void (*draw)(WxIrrViewportManager*), void (*update)(void), 
			bool (*irrlichtLeftMouseDown)(bool controlDown, bool shiftDown, int x, int y),
			bool (*irrlichtLeftMouseUp)(bool controlDown, bool shiftDown, int x, int y),
			bool (*irrlichtLeftMouseDoubleClick)(bool controlDown, bool shiftDown, int x, int y),
			bool (*irrlichtMouseMove)(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY),
			void (*IrrlichtCameraMouseMove)(int moveX, int moveY, WxIrrViewport* selectedViewport),
			void (*IrrlichtCameraKeyDown)(int id, WxIrrViewport* selectedViewport), void (*IrrlichtCameraKeyUp)(int id), void (*IrrlichtCameraKeyboardReset)(void),
			void (*simulationMouseMove)(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport),
			bool (*SimulationMouseClick)(bool isShiftDown, bool isControlDown), bool (*SimulationMouseDoubleClick)(void), void (*SimulationStartMouseChecking)(void),
			void (*OnSimulationShowAxesFunctionPointer)(bool), void (*OnSimulationShowObjectNameFunctionPointer)(bool),
			SColor (*onSimulationXAxisGetColorFunctionPointer)(void), SColor (*onSimulationYAxisGetColorFunctionPointer)(void), SColor (*onSimulationZAxisGetColorFunctionPointer)(void),
			void (*onSimulationXAxisChangeColorFunctionPointer)(wxColour& color), void (*onSimulationYAxisChangeColorFunctionPointer)(wxColour& color), void (*onSimulationZAxisChangeColorFunctionPointer)(wxColour& color),
			void (*OnSimulationShowXYGrid)(bool), void (*OnSimulationShowXZGrid)(bool), void (*OnSimulationShowYZGrid)(bool));
	~WxIrrMainWindow();

	PhysicsHelperMenuBar* GetMenuBarManager() { return menuBarManager; }
	PhysicsHelperToolbars* GetToolBarsManager() { return toolBarsManager; }

	//Basic events
	void OnPaint(wxPaintEvent &event);

	//Menu Item Events
	void OnExit(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);
	void OnHelp(wxCommandEvent &event);
	void OnSplitHorizontally(wxCommandEvent &event);
	void OnSplitVertically(wxCommandEvent &event);
	void OnRemoveViewport(wxCommandEvent &event);

	//Simulation functions
	void (*OnResetSimulationFunctionPointer)(void);
	void (*OnSaveSimulationFunctionPointer)(wxString path);
	void (*OnLoadSimulationFunctionPointer)(wxString path);
	bool (*IsSimulationSaved)(void);
	void (*OnRunSimulationFunctionPointer)(void);
	void (*OnPauseSimulationFunctionPointer)(void);
	void (*OnChangeSimulationTimeScaleFunctionPointer)(float timeScale);
	void (*OnChangeSimulationPositionScaleFunctionPointer)(float positionScale);
	void (*OnSimulationSkipBackFunctionPointer)(void);
	void (*OnSimulationSkipNextFunctionPointer)(void);
	void (*OnChangeSimulationSkipAmountFunctionPointer)(float skipAmount);
	void (*OnSimulationStartRecordingFunctionPointer)(void);
	void (*OnSimulationStopRecordingFunctionPointer)(void);

	void (*OnSimulationShowAxesFunctionPointer)(bool);
	SColor (*OnSimulationXAxisGetColorFunctionPointer)(void);
	SColor (*OnSimulationYAxisGetColorFunctionPointer)(void);
	SColor (*OnSimulationZAxisGetColorFunctionPointer)(void);
	void (*OnSimulationXAxisChangeColorFunctionPointer)(wxColour& color);
	void (*OnSimulationYAxisChangeColorFunctionPointer)(wxColour& color);
	void (*OnSimulationZAxisChangeColorFunctionPointer)(wxColour& color);
	void (*OnSimulationShowObjectNameFunctionPointer)(bool);
	void (*OnSimulationShowXYGridFunctionPointer)(bool);
	void (*OnSimulationShowXZGridFunctionPointer)(bool);
	void (*OnSimulationShowYZGridFunctionPointer)(bool);

	void OnResetSimulation(wxCommandEvent &event);
	void OnSaveSimulation(wxCommandEvent &event);
	void OnLoadSimulation(wxCommandEvent &event);
	void OnRunSimulation(wxCommandEvent &event);
	void OnPauseSimulation(wxCommandEvent &event);
	void OnChangeSimulationTimeScale(wxCommandEvent &event);
	void OnChangeSimulationPositionScale(wxCommandEvent &event);
	void OnSimulationSkipBack(wxCommandEvent &event);
	void OnSimulationSkipNext(wxCommandEvent &event);
	void OnChangeSimulationSkipAmount(wxCommandEvent &event);
	void OnSimulationStartRecording(wxCommandEvent &event);
	void OnSimulationStopRecording(wxCommandEvent &event);

	//Change Simulations
	void (*OnAtwoodMachineSimulationFunctionPointer)(void);
	void (*OnCenterOfMassSimulationFunctionPointer)(void);
	void (*OnCoulombLawSimulationFunctionPointer)(void);
	void (*OnForceWithoutRampSimulationFunctionPointer)(void);
	void (*OnForceWithRampSimulationFunctionPointer)(void);
	void (*OnGraphingSimulationFunctionPointer)(void);
	void (*OnGravitationSimulationFunctionPointer)(void);
	void (*OnLightSimulationFunctionPointer)(void);
	void (*OnMotionSimulationFunctionPointer)(void);
	void (*OnPendulumSimulationFunctionPointer)(void);
	void (*OnPlaygroundSimulationFunctionPointer)(void);
	void (*OnSpringSimulationFunctionPointer)(void);
	void (*OnVectorAdditionSimulationFunctionPointer)(void);
	void (*OnWavesSimulationFunctionPointer)(void);

	void OnAtwoodMachineSimulation(wxCommandEvent &event);
	void OnCenterOfMassSimulation(wxCommandEvent &event);
	void OnCoulombLawSimulation(wxCommandEvent &event);
	void OnForceWithoutRampSimulation(wxCommandEvent &event);
	void OnForceWithRampSimulation(wxCommandEvent &event);
	void OnGraphingSimulation(wxCommandEvent &event);
	void OnGravitationSimulation(wxCommandEvent &event);
	void OnLightSimulation(wxCommandEvent &event);
	void OnMotionSimulation(wxCommandEvent &event);
	void OnPendulumSimulation(wxCommandEvent &event);
	void OnPlaygroundSimulation(wxCommandEvent &event);
	void OnSpringSimulation(wxCommandEvent &event);
	void OnVectorAdditionSimulation(wxCommandEvent &event);
	void OnWavesSimulation(wxCommandEvent &event);

	void OnSimulationShowAxes(wxCommandEvent &event);
	void OnSimulationShowXAxisChangeColor(wxCommandEvent &event);
	void OnSimulationShowYAxisChangeColor(wxCommandEvent &event);
	void OnSimulationShowZAxisChangeColor(wxCommandEvent &event);
	void OnSimulationShowObjectNames(wxCommandEvent &event);
	void OnSimulationShowXYGrid(wxCommandEvent &event);
	void OnSimulationShowXZGrid(wxCommandEvent &event);
	void OnSimulationShowYZGrid(wxCommandEvent &event);

	void ShowRecordingToolbar();
	void HideRecordingToolbar();

	void ChangeRightPane();

	void ChangeRightPanelTime(float time);

	void RemoveRightPanel();

	void ChangeRightPanelToNothing();

	void ChangeRightPanelToPendulum(void (*addPendulumFunctionPointer)(wxString _name, double theta, double phi, double length, float mass),
			void (*addPendulumComponentsFunctionPointer)(wxString _name, double X, double Y, double Z, float mass),
			void (*removePendulumunctionPointer)(int index),
			void (*changeSelectionPendulumPointer)(wxArrayInt indices),
			void (*changeAccelerationEquations)(std::string XString, std::string YString, std::string ZString));

	void ChangeRightPanelToGravitation(void (*AddObjectSingle)(wxString _name, bool enabled, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ, bool isRelative, int relativeIndex),
			void (*AddObjectMultiple)(wxString _name, bool enabled, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			std::string velX, std::string velY, std::string velZ, bool isRelative, int relativeIndex ),
			void (*RemoveObjectFunction)(int index), void (*ClearObjectsFunction)(void),
			void (*ChangeSelection)(wxArrayInt intArray), void (*ChangeEnabledState)(int index));

	void ChangeRightPanelToCoulomb(void (*AddObjectSingle)(wxString _name, bool enabled, float mass, float charge, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ, bool isRelative, int relativeIndex),
			void (*AddObjectMultiple)(wxString _name, bool enabled, std::string mass, std::string charge, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			std::string velX, std::string velY, std::string velZ, bool isRelative, int relativeIndex ),
			void (*RemoveObjectFunction)(int index), void (*ClearObjectsFunction)(void),
			void (*ChangeSelection)(wxArrayInt intArray), void (*ChangeEnabledState)(int index));

	void ChangeRightPanelToVector(void (*addPolarVector)(float X, float Y, float Z),
			void (*addRectangularVector)(float X, float Y, float Z),
			void (*removeVector)(int index),
			void (*clearVectors)(void),
			void (*changeLineUpOrientation)(void),
			void (*changeSelection)(wxArrayInt intArray));

	void ChangeRightPanelToCenterOfMass(wxString* (*AddObjectSingle)(wxString _name, float mass, float radius, float posX, float posY, float posZ, bool isRelative, int relativeIndex),
			wxString* (*AddObjectMultiple)(wxString _name, std::string mass, std::string radius,
			std::string posX, float posXBegin, float posXEnd, float posXRes,
			std::string posY, float posYBegin, float posYEnd, float posYRes,
			std::string posZ, float posZBegin, float posZEnd, float posZRes,
			bool isRelative, int relativeIndex ),
			wxString* (*RemoveObjectFunction)(int index), wxString* (*ClearObjectsFunction)(void),
			void (*ChangeSelection)(wxArrayInt intArray), wxString* (*ChangeEnabledState)(int index));

	void ChangeRightPanelToGraphing(void (*GraphingSimulationAddCylindrical)(wxString _name, const char* equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid),
		void (*GraphingSimulationAddParametric)(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
		int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid),
		void (*GraphingSimulationAddRectangular)(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis, int equationAxis, 
		int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid),
		void (*GraphingSimulationAddSpherical)(wxString _name, const char* _equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid),
		void (*GraphingSimulationRemove)(int index),
		void (*GraphingSimulationClear)(void),
		void (*GraphingChangeSelections)(wxArrayInt intArray),
		void (*GraphingChangeEnabledState)(int index));

	void ChangeRightPanelToPlayground(void (*AddSphereUsingMouse)(void), void (*AddCubeUsingMouse)(void), void (*AddCylinderUsingMouse)(void), void (*AddConeUsingMouse)(void),
			void (*AddCapsuleUsingMouse)(void),  void (*AddSpringUsingMouse)(void), void (*AddFromFileUsingMouse)(wxString filename),
			void (*AddPointToPointJointUsingMouse)(void), void (*AddHingeJointUsingMouse)(void), void (*AddGenericJointUsingMouse)(void),
			void (*AddSphere)(wxString name, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ),
			void (*AddCube)(wxString name, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ),
			void (*AddFromFile)(wxString name, wxString filename, float mass, float scale, float posX, float posY, float posZ, float velX, float velY, float velZ),
			void (*AddMultipleObjectsCylindrical)(bool singleSurface, wxString zEquation, double thetaRes, double rRes, double minTheta, double maxTheta, double minR, double maxR,
				wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*AddMultipleObjectsParametric)(bool singleSurface, wxString xEquation, wxString yEquation, wxString zEquation, double uRes, double vRes, double minU, double maxU, 
				double minV, double maxV, wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*AddMultipleObjectsRectangular)(bool singleSurface, int axisIndex, wxString equation, double firstRes, double secondRes, double minFirst, double maxFirst,
				double minSecond, double maxSecond,	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*AddMultipleObjectsSpherical)(bool singleSurface, wxString rEquation, double thetaRes, double phiRes, double minTheta, double maxTheta, double minPhi, double maxPhi,
				wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation),
			void (*RemoveObjectFunction)(int index), void (*ClearObjectsFunction)(void), void (*ChangeSelection)(wxArrayInt intArray), void (*ObjectListDoubleClick)(int index));

	void ChangeRightPanelToSpring();



	void* GetLeftPanelHandle() { return leftPanel->GetHandle(); }
	void* GetRightPanelHandle() { return rightPanel->GetHandle(); }

	WxIrrViewportWindow* GetViewportWindow() { return leftPanel; }
	SimulationPanel* GetRightPanel() { return rightPanel; }

	void SetupDevice(SIrrlichtCreationParameters& paramaters, void (*Draw)(WxIrrViewportManager*), void (*Update)(void), 
		bool (*irrlichtLeftMouseDown)(bool controlDown, bool shiftDown, int x, int y),
		bool (*irrlichtLeftMouseUp)(bool controlDown, bool shiftDown, int x, int y),
		bool (*irrlichtLeftMouseDoubleClick)(bool controlDown, bool shiftDown, int x, int y),
		bool (*irrlichtMouseMove)(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY),
		void (*IrrlichtCameraMouseMove)(int moveX, int moveY, WxIrrViewport* selectedViewport),
		void (*IrrlichtCameraKeyDown)(int id, WxIrrViewport* selectedViewport),	void (*IrrlichtCameraKeyUp)(int id), void (*IrrlichtCameraKeyboardReset)(void),
		void (*simulationMouseMove)(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport),
		bool (*simulationMouseClick)(bool isShiftDown, bool isControlDown), bool (*simulationMouseDoubleClick)(void), void (*simulationStartMouseChecking)(void));
	IrrlichtDevice* GetDevice() { return leftPanel->GetDevice(); }

	void SetCamera(ICameraSceneNode* _camera) { leftPanel->SetCamera(_camera); }

	void SetStatusBarText(wxString text);

	void DrawTextOnRenderWindow(wxString text, wxPoint& point);

	DECLARE_EVENT_TABLE()

};

#endif 
