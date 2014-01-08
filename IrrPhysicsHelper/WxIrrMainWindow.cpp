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

#include "WxIrrMainWindow.h"
#include <wx/artprov.h>
#include <wx/splitter.h>

BEGIN_EVENT_TABLE(WxIrrMainWindow, wxFrame)

	EVT_PAINT(WxIrrMainWindow::OnPaint)

	EVT_MENU(ID_SaveSimulation, WxIrrMainWindow::OnSaveSimulation)
	EVT_MENU(ID_LoadSimulation, WxIrrMainWindow::OnLoadSimulation)
	EVT_MENU(ID_Exit, WxIrrMainWindow::OnExit)
	EVT_MENU(ID_About, WxIrrMainWindow::OnAbout)
	EVT_MENU(ID_Help, WxIrrMainWindow::OnHelp)
	EVT_MENU(ID_SplitViewportHoriz, WxIrrMainWindow::OnSplitHorizontally)
	EVT_MENU(ID_SplitViewportVert, WxIrrMainWindow::OnSplitVertically)
	EVT_MENU(ID_RemoveViewport, WxIrrMainWindow::OnRemoveViewport)

	EVT_MENU(MENUBAR_SimulationAtwoodMachine, WxIrrMainWindow::OnAtwoodMachineSimulation)
	EVT_MENU(MENUBAR_CenterOfMass, WxIrrMainWindow::OnCenterOfMassSimulation)
	EVT_MENU(MENUBAR_SimulationCoulombLaw, WxIrrMainWindow::OnCoulombLawSimulation)
	EVT_MENU(MENUBAR_SimulationForceWithoutRamp, WxIrrMainWindow::OnForceWithoutRampSimulation)
	EVT_MENU(MENUBAR_SimulationForceWithRamp, WxIrrMainWindow::OnForceWithRampSimulation)
	EVT_MENU(MENUBAR_SimulationGraphing, WxIrrMainWindow::OnGraphingSimulation)
	EVT_MENU(MENUBAR_SimulationGravitation, WxIrrMainWindow::OnGravitationSimulation)
	EVT_MENU(MENUBAR_SimulationLight, WxIrrMainWindow::OnLightSimulation)
	EVT_MENU(MENUBAR_SimulationMotion, WxIrrMainWindow::OnMotionSimulation)
	EVT_MENU(MENUBAR_SimulationPendulum, WxIrrMainWindow::OnPendulumSimulation)
	EVT_MENU(MENUBAR_SimulationPlayground, WxIrrMainWindow::OnPlaygroundSimulation)
	EVT_MENU(MENUBAR_SimulationSpring, WxIrrMainWindow::OnSpringSimulation)
	EVT_MENU(MENUBAR_SimulationVectorAddition, WxIrrMainWindow::OnVectorAdditionSimulation)
	EVT_MENU(MENUBAR_SimulationWaves, WxIrrMainWindow::OnWavesSimulation)

	EVT_MENU(MENUBAR_SimulationShowAxes, WxIrrMainWindow::OnSimulationShowAxes)	
	EVT_MENU(MENUBAR_SimulationXAxisChangeColor, WxIrrMainWindow::OnSimulationShowXAxisChangeColor)
	EVT_MENU(MENUBAR_SimulationYAxisChangeColor, WxIrrMainWindow::OnSimulationShowYAxisChangeColor)
	EVT_MENU(MENUBAR_SimulationZAxisChangeColor, WxIrrMainWindow::OnSimulationShowZAxisChangeColor)
	EVT_MENU(MENUBAR_SimulationShowObjectNames, WxIrrMainWindow::OnSimulationShowObjectNames)
	EVT_MENU(MENUBAR_SimulationVisibilityXYGrid, WxIrrMainWindow::OnSimulationShowXYGrid)
	EVT_MENU(MENUBAR_SimulationVisibilityXZGrid, WxIrrMainWindow::OnSimulationShowXZGrid)
	EVT_MENU(MENUBAR_SimulationVisibilityYZGrid, WxIrrMainWindow::OnSimulationShowYZGrid)

	EVT_TOOL(TOOLBARID_New, WxIrrMainWindow::OnResetSimulation)
	EVT_TOOL(TOOLBARID_SaveSimulation, WxIrrMainWindow::OnSaveSimulation)
	EVT_TOOL(TOOLBARID_LoadSimulation, WxIrrMainWindow::OnLoadSimulation)
	EVT_TOOL(TOOLBARID_SplitViewportHoriz, WxIrrMainWindow::OnSplitHorizontally)
	EVT_TOOL(TOOLBARID_SplitViewportVert, WxIrrMainWindow::OnSplitVertically)
	EVT_TOOL(TOOLBARID_RemoveViewport, WxIrrMainWindow::OnRemoveViewport)

   
	EVT_TOOL(TOOLBARID_RunSimulation, WxIrrMainWindow::OnRunSimulation)
	EVT_TOOL(TOOLBARID_PauseSimulation, WxIrrMainWindow::OnPauseSimulation)
	EVT_TOOL(TOOLBARID_SimulationSkipBack, WxIrrMainWindow::OnSimulationSkipBack)
	EVT_TOOL(TOOLBARID_SimulationSkipNext, WxIrrMainWindow::OnSimulationSkipNext)
	EVT_TOOL(TOOLBARID_SimulationChangeTimeScale, WxIrrMainWindow::OnChangeSimulationTimeScale)
	EVT_TOOL(TOOLBARID_SimulationChangePositionScale, WxIrrMainWindow::OnChangeSimulationPositionScale)
	EVT_TOOL(TOOLBARID_SimulationChangeSkipAmount, WxIrrMainWindow::OnChangeSimulationSkipAmount)
	EVT_TOOL(TOOLBARID_SimulationStartRecord, WxIrrMainWindow::OnSimulationStartRecording)
	EVT_TOOL(TOOLBARID_SimulationStopRecord, WxIrrMainWindow::OnSimulationStopRecording)

END_EVENT_TABLE()

WxIrrMainWindow::WxIrrMainWindow(const wxString& title, void (*draw)(WxIrrViewportManager*), void (*update)(void), 
	bool (*irrlichtLeftMouseDown)(bool controlDown, bool shiftDown, int x, int y),
	bool (*irrlichtLeftMouseUp)(bool controlDown, bool shiftDown, int x, int y),
	bool (*irrlichtLeftMouseDoubleClick)(bool controlDown, bool shiftDown, int x, int y),
	bool (*irrlichtMouseMove)(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY),
	void (*irrlichtCameraMouseMove)(int moveX, int moveY, WxIrrViewport* selectedViewport),
	void (*irrlichtCameraKeyDown)(int id, WxIrrViewport* selectedViewport),	void (*irrlichtCameraKeyUp)(int id), void (*irrlichtCameraKeyboardReset)(void),
	void (*simulationMouseMove)(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport),
	bool (*simulationMouseClick)(bool isShiftDown, bool isControlDown), bool (*simulationMouseDoubleClick)(void), void (*SimulationStartMouseChecking)(void),
	void (*onSimulationShowAxesFunctionPointer)(bool), void (*onSimulationShowObjectNameFunctionPointer)(bool),	
	SColor (*onSimulationXAxisGetColorFunctionPointer)(void), SColor (*onSimulationYAxisGetColorFunctionPointer)(void), SColor (*onSimulationZAxisGetColorFunctionPointer)(void),
	void (*onSimulationXAxisChangeColorFunctionPointer)(wxColour& color), void (*onSimulationYAxisChangeColorFunctionPointer)(wxColour& color), void (*onSimulationZAxisChangeColorFunctionPointer)(wxColour& color),
	void (*onSimulationShowXYGridFunctionPointer)(bool), void (*onSimulationShowXZGridFunctionPointer)(bool), void (*onSimulationShowYZGridFunctionPointer)(bool))
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
	OnSimulationShowAxesFunctionPointer = onSimulationShowAxesFunctionPointer;
	OnSimulationShowObjectNameFunctionPointer = onSimulationShowObjectNameFunctionPointer;

	OnSimulationXAxisGetColorFunctionPointer = onSimulationXAxisGetColorFunctionPointer;
	OnSimulationYAxisGetColorFunctionPointer = onSimulationYAxisGetColorFunctionPointer;
	OnSimulationZAxisGetColorFunctionPointer = onSimulationZAxisGetColorFunctionPointer;
	OnSimulationXAxisChangeColorFunctionPointer = onSimulationXAxisChangeColorFunctionPointer;
	OnSimulationYAxisChangeColorFunctionPointer = onSimulationYAxisChangeColorFunctionPointer;
	OnSimulationZAxisChangeColorFunctionPointer = onSimulationZAxisChangeColorFunctionPointer;

	OnSimulationShowXYGridFunctionPointer = onSimulationShowXYGridFunctionPointer;
	OnSimulationShowXZGridFunctionPointer = onSimulationShowXZGridFunctionPointer;
	OnSimulationShowYZGridFunctionPointer = onSimulationShowYZGridFunctionPointer;

	leftPanel = new WxIrrViewportWindow(this, 1000);
	leftPanel->SetBackgroundColour(wxColour(wxT("Black")));

	irr::SIrrlichtCreationParameters param;
	#if defined _WX_IRR_WINDOWS

		param.DriverType = EDT_DIRECT3D9;
		param.AntiAlias = false;
		param.WindowId = reinterpret_cast<void*>(GetLeftPanelHandle());

	#elif defined _WX_IRR_LINUX

		param.DriverType = EDT_OPENGL;
		param.AntiAlias = false;
		GtkWidget* handle = (GtkWidget*)GetLeftPanelHandle();
		gtk_widget_realize(handle);
		Window xHandle = GDK_WINDOW_XWINDOW(handle->window);
		param.WindowId = (void*)(xHandle);

	#elif defined _WX_IRR_MACOS

		//param.DriverType = EDT_OPENGL;

	#else

		//return false;
		Close();

	#endif

	leftPanel->InitalizeViewportManager();	
	SetupDevice(param, draw, update, irrlichtLeftMouseDown, irrlichtLeftMouseUp, irrlichtLeftMouseDoubleClick, irrlichtMouseMove, irrlichtCameraMouseMove, irrlichtCameraKeyDown, irrlichtCameraKeyUp, irrlichtCameraKeyboardReset,
		simulationMouseMove, simulationMouseClick, simulationMouseDoubleClick, SimulationStartMouseChecking);
	
	//Main camera
	ICameraSceneNode* camera = GetDevice()->getSceneManager()->addCameraSceneNode();
	camera->setPosition(Vector3(30,-10,30));
	//camera->bindTargetAndRotation(true);
	//camera->setTarget(Vector3(0,0,0));
	Vector3 currentCameraRot = camera->getRotation();	
	Vector3 rot = currentCameraRot.rotationToDirection();
	Vector3 pos = camera->getPosition();
	camera->setTarget(rot + pos);
	camera->setFarValue(100000);
	SetCamera(camera);

	rightPanel = new SimulationPanel(this, 1001, wxDefaultPosition, wxDefaultSize);
	rightPanel->SetBackgroundColour(wxColour(wxT("Black")));

	m_mgr.SetManagedWindow(this);

	//Create Main Menu
	menuBar = new wxMenuBar();
	menuBarManager = new PhysicsHelperMenuBar(menuBar);

    SetMenuBar( menuBar );
	//Status bar
    CreateStatusBar();
    SetStatusText( wxT("PhysicsHelper") );
	statusBarText = wxT("PhysicsHelper");

	toolBarsManager = new PhysicsHelperToolbars(this, m_mgr);

	//add the normal panes
	m_mgr.AddPane(leftPanel, wxAuiPaneInfo().CenterPane().Name(wxT("leftPanel")));
	m_mgr.AddPane(rightPanel, wxAuiPaneInfo().CloseButton(false).Right().PinButton(true).MinimizeButton(true).Name(wxT("rightPanel")));	

	m_mgr.Update();

	//Centre();
}

WxIrrMainWindow::~WxIrrMainWindow()
{
	delete leftPanel;
	delete menuBarManager;
	delete toolBarsManager;

	m_mgr.UnInit();
}


///Basic events
void WxIrrMainWindow::OnPaint(wxPaintEvent &WXUNUSED(event))
{
	//SetStatusBarText(_("Physics Helper"));
}


///Menu Item events
void WxIrrMainWindow::OnExit(wxCommandEvent &WXUNUSED(event))
{
	if(!IsSimulationSaved())
	{
		if (wxMessageBox(_("The current simulation has not been saved. Continue to exit?"), _("Changes have not been saved"),
							 wxICON_QUESTION | wxYES_NO, this) == wxNO )
				return;
	}

	Close(true);
}

void WxIrrMainWindow::OnAbout(wxCommandEvent &WXUNUSED(event))
{
	wxMessageBox( _("Made by Niraj Rayalla"), _("About PhysicsHelper"), wxOK | wxICON_INFORMATION, this );
}

void WxIrrMainWindow::OnHelp(wxCommandEvent &event)
{
	wxMessageBox( _("Need to implement help."), _("Help"), wxOK | wxICON_INFORMATION, this );
}

void WxIrrMainWindow::OnSplitHorizontally(wxCommandEvent &event)
{
	leftPanel->SplitViewportHorizontally();
}

void WxIrrMainWindow::OnSplitVertically(wxCommandEvent &event)
{
	leftPanel->SplitViewportVertically();
}

void WxIrrMainWindow::OnRemoveViewport(wxCommandEvent &event)
{
	leftPanel->RemoveViewport();
}


///Simulation events
void WxIrrMainWindow::OnResetSimulation(wxCommandEvent &event) 
{ 
	OnResetSimulationFunctionPointer();

	rightPanel->Reset();
}
void WxIrrMainWindow::OnSaveSimulation(wxCommandEvent &event) 
{
	wxFileDialog saveDialog(this, _("Save Simulation file"), "", "",
                        "Simulation files (*.sim)|*.sim", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

	if (saveDialog.ShowModal() == wxID_CANCEL)
        return;

	OnSaveSimulationFunctionPointer(saveDialog.GetPath());
}
void WxIrrMainWindow::OnLoadSimulation(wxCommandEvent &event) 
{
	if(!IsSimulationSaved())
	{
		if (wxMessageBox(_("The current simulation has not been saved. Continue to load a file?"), _("Changes have not been saved"),
								wxICON_QUESTION | wxYES_NO, this) == wxNO )
				return;
	}

	wxFileDialog loadDialog(this, _("Load Simulation file"), "", "",
                        "Simulation files (*.sim)|*.sim", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if (loadDialog.ShowModal() == wxID_CANCEL)
        return;

	OnLoadSimulationFunctionPointer(loadDialog.GetPath());
}
void WxIrrMainWindow::OnRunSimulation(wxCommandEvent &event) 
{
	OnRunSimulationFunctionPointer();
}
void WxIrrMainWindow::OnPauseSimulation(wxCommandEvent &event)
{
	OnPauseSimulationFunctionPointer();
}
void WxIrrMainWindow::OnChangeSimulationTimeScale(wxCommandEvent &event)
{
}
void WxIrrMainWindow::OnChangeSimulationPositionScale(wxCommandEvent &event)
{
}
void WxIrrMainWindow::OnSimulationSkipBack(wxCommandEvent &event)
{
	OnSimulationSkipBackFunctionPointer();
}
void WxIrrMainWindow::OnSimulationSkipNext(wxCommandEvent &event)
{
	OnSimulationSkipNextFunctionPointer();
}
void WxIrrMainWindow::OnChangeSimulationSkipAmount(wxCommandEvent &event)
{
}
void WxIrrMainWindow::OnSimulationStartRecording(wxCommandEvent &event)
{
	OnSimulationStartRecordingFunctionPointer();
}
void WxIrrMainWindow::OnSimulationStopRecording(wxCommandEvent &event)
{
	OnSimulationStopRecordingFunctionPointer();
}

void WxIrrMainWindow::OnAtwoodMachineSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationAtwoodMachine);
	OnAtwoodMachineSimulationFunctionPointer();
}
void WxIrrMainWindow::OnCenterOfMassSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_CenterOfMass);
	OnCenterOfMassSimulationFunctionPointer();
}
void WxIrrMainWindow::OnCoulombLawSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationCoulombLaw);
	OnCoulombLawSimulationFunctionPointer();
}
void WxIrrMainWindow::OnForceWithoutRampSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationForceWithoutRamp);
	OnForceWithoutRampSimulationFunctionPointer();
}
void WxIrrMainWindow::OnForceWithRampSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationForceWithRamp);
	OnForceWithRampSimulationFunctionPointer();
}
void WxIrrMainWindow::OnGraphingSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationGraphing);
	OnGraphingSimulationFunctionPointer();
}
void WxIrrMainWindow::OnGravitationSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationGravitation);
	OnGravitationSimulationFunctionPointer();
}
void WxIrrMainWindow::OnLightSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationLight);
	OnLightSimulationFunctionPointer();
}
void WxIrrMainWindow::OnMotionSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationMotion);
	OnMotionSimulationFunctionPointer();
}
void WxIrrMainWindow::OnPendulumSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationPendulum);
	OnPendulumSimulationFunctionPointer();
}
void WxIrrMainWindow::OnPlaygroundSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationPlayground);
	OnPlaygroundSimulationFunctionPointer();
}
void WxIrrMainWindow::OnSpringSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationSpring);
	OnSpringSimulationFunctionPointer();
}
void WxIrrMainWindow::OnVectorAdditionSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationVectorAddition);
	OnVectorAdditionSimulationFunctionPointer();
}
void WxIrrMainWindow::OnWavesSimulation(wxCommandEvent &event)
{
	menuBarManager->ChangeMenuSimulationSelection(MENUBAR_SimulationWaves);
	OnWavesSimulationFunctionPointer();
}

void WxIrrMainWindow::OnSimulationShowAxes(wxCommandEvent &event)
{
	if (event.IsChecked())
	{
		OnSimulationShowAxesFunctionPointer(true);
	}
	else
	{
		OnSimulationShowAxesFunctionPointer(false);
	}
}
void WxIrrMainWindow::OnSimulationShowXAxisChangeColor(wxCommandEvent &event)
{
	wxColourData colorData;
	SColor currentIrrColor = OnSimulationXAxisGetColorFunctionPointer();
	wxColour currentWxColor(currentIrrColor.getRed(), currentIrrColor.getGreen(), currentIrrColor.getBlue());
	colorData.SetColour(currentWxColor);

	wxColourDialog colorDiag(this, &colorData);

	if (colorDiag.ShowModal() == wxID_OK)
	{
		wxColourData retData = colorDiag.GetColourData();
		wxColour col = retData.GetColour();
		
		OnSimulationXAxisChangeColorFunctionPointer(col);
	}
}
void WxIrrMainWindow::OnSimulationShowYAxisChangeColor(wxCommandEvent &event)
{
	wxColourData colorData;
	SColor currentIrrColor = OnSimulationYAxisGetColorFunctionPointer();
	wxColour currentWxColor(currentIrrColor.getRed(), currentIrrColor.getGreen(), currentIrrColor.getBlue());
	colorData.SetColour(currentWxColor);

	wxColourDialog colorDiag(this, &colorData);

	if (colorDiag.ShowModal() == wxID_OK)
	{
		wxColourData retData = colorDiag.GetColourData();
		wxColour col = retData.GetColour();
		
		OnSimulationYAxisChangeColorFunctionPointer(col);
	}
}
void WxIrrMainWindow::OnSimulationShowZAxisChangeColor(wxCommandEvent &event)
{
	wxColourData colorData;
	SColor currentIrrColor = OnSimulationZAxisGetColorFunctionPointer();
	wxColour currentWxColor(currentIrrColor.getRed(), currentIrrColor.getGreen(), currentIrrColor.getBlue());
	colorData.SetColour(currentWxColor);

	wxColourDialog colorDiag(this, &colorData);

	if (colorDiag.ShowModal() == wxID_OK)
	{
		wxColourData retData = colorDiag.GetColourData();
		wxColour col = retData.GetColour();
		
		OnSimulationZAxisChangeColorFunctionPointer(col);
	}
}
void WxIrrMainWindow::OnSimulationShowObjectNames(wxCommandEvent &event)
{
	if (event.IsChecked())
	{
		OnSimulationShowObjectNameFunctionPointer(true);
	}
	else
	{
		OnSimulationShowObjectNameFunctionPointer(false);
	}
}

void WxIrrMainWindow::OnSimulationShowXYGrid(wxCommandEvent &event)
{
	if (event.IsChecked())
	{
		OnSimulationShowXYGridFunctionPointer(true);
	}
	else
	{
		OnSimulationShowXYGridFunctionPointer(false);
	}
}
void WxIrrMainWindow::OnSimulationShowXZGrid(wxCommandEvent &event)
{
	if (event.IsChecked())
	{
		OnSimulationShowXZGridFunctionPointer(true);
	}
	else
	{
		OnSimulationShowXZGridFunctionPointer(false);
	}
}
void WxIrrMainWindow::OnSimulationShowYZGrid(wxCommandEvent &event)
{
	if (event.IsChecked())
	{
		OnSimulationShowYZGridFunctionPointer(true);
	}
	else
	{
		OnSimulationShowYZGridFunctionPointer(false);
	}
}



void WxIrrMainWindow::SetupDevice(SIrrlichtCreationParameters& paramaters, void (*draw)(WxIrrViewportManager*), void (*update)(void), 
	bool (*irrlichtLeftMouseDown)(bool controlDown, bool shiftDown, int x, int y),
	bool (*irrlichtLeftMouseUp)(bool controlDown, bool shiftDown, int x, int y),
	bool (*irrlichtLeftMouseDoubleClick)(bool controlDown, bool shiftDown, int x, int y),
	bool (*irrlichtMouseMove)(bool controlDown, bool shiftDown, int x, int y, int moveX, int moveY),
	void (*irrlichtCameraMouseMove)(int moveX, int moveY, WxIrrViewport* selectedViewport),
	void (*irrlichtCameraKeyDown)(int id, WxIrrViewport* selectedViewport),	void (*irrlichtCameraKeyUp)(int id), void (*irrlichtCameraKeyboardReset)(void),
	void (*simulationMouseMove)(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport),
	bool (*simulationMouseClick)(bool isShiftDown, bool isControlDown),	bool (*simulationMouseDoubleClick)(void), void (*simulationStartMouseChecking)(void))
{
	leftPanel->SetupDevice(paramaters, draw, update, irrlichtLeftMouseDown, irrlichtLeftMouseUp, irrlichtLeftMouseDoubleClick, irrlichtMouseMove, irrlichtCameraMouseMove, irrlichtCameraKeyDown, irrlichtCameraKeyUp, irrlichtCameraKeyboardReset,
		simulationMouseMove, simulationMouseClick, simulationMouseDoubleClick, simulationStartMouseChecking);
}


void WxIrrMainWindow::SetStatusBarText(wxString text)
{
	SetStatusText(text);
	statusBarText = text;
}

void WxIrrMainWindow::DrawTextOnRenderWindow(wxString text, wxPoint& point)
{
	if (leftPanel)
		leftPanel->DrawText(text, point);
}


void WxIrrMainWindow::ShowRecordingToolbar()
{
	toolBarsManager->ShowRecordingToolbar();
}
void WxIrrMainWindow::HideRecordingToolbar()
{
	toolBarsManager->HideRecordingToolbar();
}

void WxIrrMainWindow::ChangeRightPane()
{

	//m_mgr.AddPane(leftPanel, wxAuiPaneInfo().CenterPane());
	m_mgr.AddPane(rightPanel, wxAuiPaneInfo().CloseButton(false).Right().PinButton(true).MinimizeButton(true).Name(wxT("rightPanel")));	
	m_mgr.GetPane("rightPanel").MinSize(rightPanel->GetSize());
	m_mgr.GetPane("rightPanel").MaxSize(rightPanel->GetSize());
	//m_mgr.GetPane("rightPanel").MinimizeButton(true).Maximize();
	m_mgr.Update();
}

void WxIrrMainWindow::ChangeRightPanelTime(float time)
{
	TimedSimulationPanel* rightSimulationPanel = dynamic_cast<TimedSimulationPanel*>(rightPanel);

	if (rightSimulationPanel)
	{
		rightSimulationPanel->ChangeSimulationTime(time);
	}
}

void WxIrrMainWindow::RemoveRightPanel()
{		
	m_mgr.DetachPane(rightPanel);
	rightPanel->GetParent()->RemoveChild(rightPanel);
	rightPanel->Destroy();
}

void WxIrrMainWindow::ChangeRightPanelToNothing()
{	
	RemoveRightPanel();
	rightPanel = new SimulationPanel(this, 1001, wxDefaultPosition, wxDefaultSize);

	ChangeRightPane();
}

void WxIrrMainWindow::ChangeRightPanelToPendulum(void (*addPendulumFunctionPointer)(wxString _name, double theta, double phi, double length, float mass),
		void (*addPendulumComponentsFunctionPointer)(wxString _name, double X, double Y, double Z, float mass),
		void (*removePendulumunctionPointer)(int index),
		void (*changeSelectionPendulumPointer)(wxArrayInt indices),
		void (*changeAccelerationEquations)(std::string XString, std::string YString, std::string ZString))
{
	RemoveRightPanel();
	rightPanel = new PendulumPanel(this, addPendulumFunctionPointer, addPendulumComponentsFunctionPointer, removePendulumunctionPointer, changeSelectionPendulumPointer, changeAccelerationEquations, 1001);

	ChangeRightPane();
}

void WxIrrMainWindow::ChangeRightPanelToGravitation(void (*AddObjectSingle)(wxString _name, bool enabled, float mass, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ, bool isRelative, int relativeIndex),
		void (*AddObjectMultiple)(wxString _name, bool enabled, std::string mass, std::string radius,
		std::string posX, float posXBegin, float posXEnd, float posXRes,
		std::string posY, float posYBegin, float posYEnd, float posYRes,
		std::string posZ, float posZBegin, float posZEnd, float posZRes,
		std::string velX, std::string velY, std::string velZ, bool isRelative, int relativeIndex ),
		void (*RemoveObjectFunction)(int index), void (*ClearObjectsFunction)(void),
		void (*ChangeSelection)(wxArrayInt intArray), void (*ChangeEnabledState)(int index))
{
	RemoveRightPanel();
	rightPanel = new GravitationPanel(this, AddObjectSingle, AddObjectMultiple, RemoveObjectFunction, ClearObjectsFunction, ChangeSelection, ChangeEnabledState, 1001);

	ChangeRightPane();
}

void WxIrrMainWindow::ChangeRightPanelToCoulomb(void (*AddObjectSingle)(wxString _name, bool enabled, float mass, float charge, float radius, float posX, float posY, float posZ, float velX, float velY, float velZ, bool isRelative, int relativeIndex),
		void (*AddObjectMultiple)(wxString _name, bool enabled, std::string mass, std::string charge, std::string radius,
		std::string posX, float posXBegin, float posXEnd, float posXRes,
		std::string posY, float posYBegin, float posYEnd, float posYRes,
		std::string posZ, float posZBegin, float posZEnd, float posZRes,
		std::string velX, std::string velY, std::string velZ, bool isRelative, int relativeIndex ),
		void (*RemoveObjectFunction)(int index), void (*ClearObjectsFunction)(void),
		void (*ChangeSelection)(wxArrayInt intArray), void (*ChangeEnabledState)(int index))
{
	RemoveRightPanel();
	rightPanel = new CoulombPanel(this, AddObjectSingle, AddObjectMultiple, RemoveObjectFunction, ClearObjectsFunction, ChangeSelection, ChangeEnabledState, 1001);

	ChangeRightPane();
}

void WxIrrMainWindow::ChangeRightPanelToVector(void (*addPolarVector)(float X, float Y, float Z),
		void (*addRectangularVector)(float X, float Y, float Z),
		void (*removeVector)(int index),
		void (*clearVectors)(void),
		void (*changeLineUpOrientation)(void),
		void (*changeSelection)(wxArrayInt intArray))
{
	RemoveRightPanel();
	rightPanel = new VectorPanel(this, addPolarVector, addRectangularVector, removeVector, clearVectors, changeLineUpOrientation, changeSelection, 1001);

	ChangeRightPane();
}

void WxIrrMainWindow::ChangeRightPanelToCenterOfMass(wxString* (*AddObjectSingle)(wxString _name, float mass, float radius, float posX, float posY, float posZ, bool isRelative, int relativeIndex),
		wxString* (*AddObjectMultiple)(wxString _name, std::string mass, std::string radius,
		std::string posX, float posXBegin, float posXEnd, float posXRes,
		std::string posY, float posYBegin, float posYEnd, float posYRes,
		std::string posZ, float posZBegin, float posZEnd, float posZRes,
		bool isRelative, int relativeIndex ),
		wxString* (*RemoveObjectFunction)(int index), wxString* (*ClearObjectsFunction)(void),
		void (*ChangeSelection)(wxArrayInt intArray), wxString* (*ChangeEnabledState)(int index))
{
	RemoveRightPanel();
	rightPanel = new CenterOfMassPanel(this, AddObjectSingle, AddObjectMultiple, RemoveObjectFunction, ClearObjectsFunction, ChangeSelection, ChangeEnabledState, 1001);

	ChangeRightPane();
}

void WxIrrMainWindow::ChangeRightPanelToGraphing(void (*GraphingSimulationAddCylindrical)(wxString _name, const char* equationString, float Scale, int lowColorR, int lowColorG, int lowColorB, int highColorR, int highColorG, int highColorB, int colorAxis,
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
	void (*GraphingChangeEnabledState)(int index))
{
	RemoveRightPanel();
	rightPanel = new GraphingPanel(this, GraphingSimulationAddCylindrical, GraphingSimulationAddParametric, GraphingSimulationAddRectangular, GraphingSimulationAddSpherical,
		GraphingSimulationRemove, GraphingSimulationClear, GraphingChangeSelections, GraphingChangeEnabledState, 1001);

	ChangeRightPane();
}

void WxIrrMainWindow::ChangeRightPanelToPlayground(void (*AddSphereUsingMouse)(void), void (*AddCubeUsingMouse)(void), void (*AddCylinderUsingMouse)(void), void (*AddConeUsingMouse)(void),
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
		void (*RemoveObjectFunction)(int index), void (*ClearObjectsFunction)(void), void (*ChangeSelection)(wxArrayInt intArray), void (*ObjectListDoubleClick)(int index))
{
	RemoveRightPanel();
	rightPanel = new PlaygroundPanel(this, AddSphereUsingMouse, AddCubeUsingMouse, AddCylinderUsingMouse, AddConeUsingMouse, AddCapsuleUsingMouse, AddSpringUsingMouse,
		AddFromFileUsingMouse, AddPointToPointJointUsingMouse, AddHingeJointUsingMouse,
		AddGenericJointUsingMouse, AddSphere, AddCube, AddFromFile,
		AddMultipleObjectsCylindrical, AddMultipleObjectsParametric, AddMultipleObjectsRectangular, AddMultipleObjectsSpherical,
		RemoveObjectFunction, ClearObjectsFunction, ChangeSelection, ObjectListDoubleClick, 1001);

	ChangeRightPane();
}

void WxIrrMainWindow::ChangeRightPanelToSpring()
{
	//RemoveRightPanel();
	////rightPanel = new PendulumPanel(this, addPendulumFunctionPointer, addPendulumComponentsFunctionPointer, removePendulumunctionPointer, changeSelectionPendulumPointer, changeAccelerationEquations, 1001);

	//ChangeRightPane();

	ChangeRightPanelToNothing();
}