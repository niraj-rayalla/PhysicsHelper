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

#include "WxIrrMenuBar.h"

PhysicsHelperMenuBar::PhysicsHelperMenuBar(wxMenuBar* menuBar)
{
	//File menu
	fileMenu = new wxMenu();
	fileMenu->Append(ID_New, wxT("&New"));
	fileMenu->Append(ID_SaveSimulation, wxT("&Save Simulation"));
	fileMenu->Append(ID_LoadSimulation, wxT("L&oad Simulation"));
	fileMenu->AppendSeparator();
	fileMenu->Append( ID_Exit, _("E&xit") );
	menuBar->Append(fileMenu, wxT("&File"));

	//Windows menu
	windowsMenu = new wxMenu();
	windowsMenu->Append(ID_SplitViewportHoriz, wxT("Split Horizontally"));
	windowsMenu->Append(ID_SplitViewportVert, wxT("Split Vertically"));
	windowsMenu->Append(ID_RemoveViewport, wxT("Remove Window"));
	menuBar->Append(windowsMenu, wxT("&Windows"));		

	//Units Menu
	unitsMenu = new wxMenu();
	conversionsMenu = new wxMenu();
	wxMenuItem* angleConversionMenuItem;
	angleConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Angle") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( angleConversionMenuItem );
		
	wxMenuItem* energyConversionMenuItem;
	energyConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Energy") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( energyConversionMenuItem );
		
	wxMenuItem* forceConversionMenuItem;
	forceConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Force") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( forceConversionMenuItem );
		
	wxMenuItem* lengthConversionMenuItem;
	lengthConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("length") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( lengthConversionMenuItem );
		
	wxMenuItem* magnetismConversionMenuItem;
	magnetismConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Magnetism") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( magnetismConversionMenuItem );
		
	wxMenuItem* massConversionMenuItem;
	massConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Mass") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( massConversionMenuItem );
		
	wxMenuItem* powerConversionMenuItem;
	powerConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Power") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( powerConversionMenuItem );
		
	wxMenuItem* pressureConversionMenuItem;
	pressureConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Pressure") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( pressureConversionMenuItem );
		
	wxMenuItem* temperatureConversionMenuItem;
	temperatureConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Temperature") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( temperatureConversionMenuItem );
		
	wxMenuItem* timeConversionMenuItem;
	timeConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Time") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( timeConversionMenuItem );
		
	wxMenuItem* volumeConversionMenuItem;
	volumeConversionMenuItem = new wxMenuItem( conversionsMenu, wxID_ANY, wxString( wxT("Volume") ) , wxEmptyString, wxITEM_NORMAL );
	conversionsMenu->Append( volumeConversionMenuItem );
		
	unitsMenu->Append( -1, wxT("Conversions"), conversionsMenu );
		
	wxMenuItem* m_separator1;
	m_separator1 = unitsMenu->AppendSeparator();
		
	wxMenuItem* significantFiguresMenuItem;
	significantFiguresMenuItem = new wxMenuItem( unitsMenu, wxID_ANY, wxString( wxT("Significant Figures") ) , wxEmptyString, wxITEM_NORMAL );
	unitsMenu->Append( significantFiguresMenuItem );
		
	wxMenuItem* unitPrefixesMenuItem;
	unitPrefixesMenuItem = new wxMenuItem( unitsMenu, wxID_ANY, wxString( wxT("Unit Prefixes") ) , wxEmptyString, wxITEM_NORMAL );
	unitsMenu->Append( unitPrefixesMenuItem );
		
	menuBar->Append( unitsMenu, wxT("Units") ); 

	//Simulations Menu
	simulationsMenu = new wxMenu();

	playgroundMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationPlayground, wxString(wxT("Playground")), wxEmptyString, wxITEM_CHECK );
	simulationsMenu->Append(playgroundMenuItem);
	playgroundMenuItem->Check( true );

	simulationsMenu->AppendSeparator();
	
	atwoodMachineMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationAtwoodMachine, wxString( wxT("Atwood Machine") ) , wxEmptyString, wxITEM_CHECK );
	atwoodMachineMenuItem = simulationsMenu->Append( atwoodMachineMenuItem );
	atwoodMachineMenuItem->Check( false );
		
	coulombsLawMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationCoulombLaw, wxString( wxT("Coulomb's Law") ) , wxEmptyString, wxITEM_CHECK );
	simulationsMenu->Append( coulombsLawMenuItem );
	coulombsLawMenuItem->Check( false );
		
	forcesMenu = new wxMenu();
	
	withoutRampForceMenuItem = new wxMenuItem( forcesMenu, MENUBAR_SimulationForceWithoutRamp, wxString( wxT("Without Ramp") ) , wxEmptyString, wxITEM_CHECK );
	forcesMenu->Append( withoutRampForceMenuItem );
	withoutRampForceMenuItem->Check( false );
		
	withRampMenuItem = new wxMenuItem( forcesMenu, MENUBAR_SimulationForceWithRamp, wxString( wxT("With Ramp") ) , wxEmptyString, wxITEM_CHECK );
	forcesMenu->Append( withRampMenuItem );
	withRampMenuItem->Check( false );
		
	simulationsMenu->Append( -1, wxT("Forces"), forcesMenu );
		
	gravitationMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationGravitation, wxString( wxT("Gravitation") ) , wxEmptyString, wxITEM_CHECK );
	gravitationMenuItem = simulationsMenu->Append( gravitationMenuItem );
	gravitationMenuItem->Check( false );
		
	lightMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationLight, wxString( wxT("Light") ) , wxEmptyString, wxITEM_CHECK );
	simulationsMenu->Append( lightMenuItem );
	lightMenuItem->Check( false );
		
	motionMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationMotion, wxString( wxT("Motion") ) , wxEmptyString, wxITEM_CHECK );
	simulationsMenu->Append( motionMenuItem );
	motionMenuItem->Check( false );
		
	pendulumMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationPendulum, wxString( wxT("Pendulum") ) , wxEmptyString, wxITEM_CHECK );
	simulationsMenu->Append( pendulumMenuItem );
	pendulumMenuItem->Check( false );
		
	springMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationSpring, wxString( wxT("Spring") ) , wxEmptyString, wxITEM_CHECK );
	simulationsMenu->Append( springMenuItem );
	springMenuItem->Check( false );
		
	vectorAdditionMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationVectorAddition, wxString( wxT("Vector Addition") ) , wxEmptyString, wxITEM_CHECK );
	simulationsMenu->Append( vectorAdditionMenuItem );
	vectorAdditionMenuItem->Check( false );
		
	wavesMenuItem = new wxMenuItem( simulationsMenu, MENUBAR_SimulationWaves, wxString( wxT("Waves") ) , wxEmptyString, wxITEM_CHECK );
	simulationsMenu->Append( wavesMenuItem );
	wavesMenuItem->Check( false );
		
	wxMenuItem* m_separator12;
	m_separator12 = simulationsMenu->AppendSeparator();
		
	simulationOptionsMenu = new wxMenu();
	simulationAxesMenu = new wxMenu();
		
	wxMenuItem* simulationShowAxesMenuItem;
	simulationShowAxesMenuItem = new wxMenuItem( simulationAxesMenu, MENUBAR_SimulationShowAxes, wxString( wxT("Show Axes") ) , wxEmptyString, wxITEM_CHECK );
	simulationAxesMenu->Append( simulationShowAxesMenuItem );
	simulationShowAxesMenuItem->Check( true );

	//Change axes color options
	wxMenu* changeAxisColorMenu = new wxMenu();

	wxMenuItem* colorXAxisGridMenuItem;
	colorXAxisGridMenuItem= new wxMenuItem( changeAxisColorMenu , MENUBAR_SimulationXAxisChangeColor, wxString( wxT("X Axis") ) , wxEmptyString, wxITEM_NORMAL);
	changeAxisColorMenu->Append( colorXAxisGridMenuItem);
		
	wxMenuItem* colorYAxisGridMenuItem;
	colorYAxisGridMenuItem= new wxMenuItem( changeAxisColorMenu , MENUBAR_SimulationYAxisChangeColor, wxString( wxT("Y Axis") ) , wxEmptyString, wxITEM_NORMAL);
	changeAxisColorMenu->Append( colorYAxisGridMenuItem);
		
	wxMenuItem* colorZAxisGridMenuItem;
	colorZAxisGridMenuItem= new wxMenuItem( changeAxisColorMenu , MENUBAR_SimulationZAxisChangeColor, wxString( wxT("Z Axis") ) , wxEmptyString, wxITEM_NORMAL);
	changeAxisColorMenu->Append( colorZAxisGridMenuItem);

	simulationAxesMenu->Append( -1, _("Axes Colors"), changeAxisColorMenu);
		
		
	simulationOptionsMenu->Append( -1, wxT("Axes"), simulationAxesMenu );

	wxMenuItem* simulationShowObjectNamesMenuItem;
	simulationShowObjectNamesMenuItem = new wxMenuItem( simulationOptionsMenu, MENUBAR_SimulationShowObjectNames, wxString( wxT("Show Object Names") ) , wxEmptyString, wxITEM_CHECK );
	simulationOptionsMenu->Append( simulationShowObjectNamesMenuItem );
		

	//Show Grid options
	showGridsMenu = new wxMenu();

	wxMenuItem* visibilityXYGridMenuItem;
	visibilityXYGridMenuItem = new wxMenuItem( showGridsMenu, MENUBAR_SimulationVisibilityXYGrid, wxString( wxT("XY Grid") ) , wxEmptyString, wxITEM_CHECK);
	showGridsMenu->Append( visibilityXYGridMenuItem );
		
	wxMenuItem* visibilityXZGridMenuItem;
	visibilityXZGridMenuItem = new wxMenuItem( showGridsMenu, MENUBAR_SimulationVisibilityXZGrid, wxString( wxT("XZ Grid") ) , wxEmptyString, wxITEM_CHECK);
	showGridsMenu->Append( visibilityXZGridMenuItem );
	visibilityXZGridMenuItem->Check(true);
		
	wxMenuItem* visibilityYZGridMenuItem;
	visibilityYZGridMenuItem = new wxMenuItem( showGridsMenu, MENUBAR_SimulationVisibilityYZGrid, wxString( wxT("YZ Grid") ) , wxEmptyString, wxITEM_CHECK);
	showGridsMenu->Append( visibilityYZGridMenuItem );

	simulationOptionsMenu->Append( -1, _("Grid Visibility"), showGridsMenu );
		
	simulationsMenu->Append( -1, wxT("Options"), simulationOptionsMenu );

	menuBar->Append( simulationsMenu, wxT("Simulations") );

	//Calculation Menu
	calculateMenu = new wxMenu();
	centerOfMassMenuItem = calculateMenu->Append(new wxMenuItem( mathMenu, MENUBAR_CenterOfMass, wxString( wxT("Center of Mass") ) , wxEmptyString, wxITEM_CHECK ));
	menuBar->Append(calculateMenu, wxT("&Calculate"));

	//Math menu
	mathMenu = new wxMenu();
	graphingMenuItem = new wxMenuItem( mathMenu, MENUBAR_SimulationGraphing, wxString( wxT("Graphing") ) , wxEmptyString, wxITEM_CHECK );
	mathMenu->Append( graphingMenuItem );
		
	wxMenuItem* triangleGeometryMenuItem;
	triangleGeometryMenuItem = new wxMenuItem( mathMenu, wxID_ANY, wxString( wxT("Triangle Geometry") ) , wxEmptyString, wxITEM_NORMAL );
	mathMenu->Append( triangleGeometryMenuItem );
		
	wxMenuItem* twoVectorPropertiesMenuItem;
	twoVectorPropertiesMenuItem = new wxMenuItem( mathMenu, wxID_ANY, wxString( wxT("Two Vector Properties") ) , wxEmptyString, wxITEM_NORMAL );
	mathMenu->Append( twoVectorPropertiesMenuItem );
		
	wxMenuItem* m_separator13;
	m_separator13 = mathMenu->AppendSeparator();
		
	wxMenuItem* calculatorMenuItem;
	calculatorMenuItem = new wxMenuItem( mathMenu, wxID_ANY, wxString( wxT("Calculator") ) , wxEmptyString, wxITEM_NORMAL );
	mathMenu->Append( calculatorMenuItem );
		
	menuBar->Append( mathMenu, wxT("Math") ); 

	//Help menu
	helpMenu = new wxMenu();
	helpMenu->Append(ID_Help, wxT("H&elp...\tF1"));		
	helpMenu->AppendSeparator();		
	helpMenu->Append(ID_About, wxT("&About"));
	menuBar->Append(helpMenu, wxT("&Help"));
}

void PhysicsHelperMenuBar::ClearMenuSimulationSelection()
{
	playgroundMenuItem->Check( false );
	atwoodMachineMenuItem->Check( false );
	coulombsLawMenuItem->Check( false );
	withoutRampForceMenuItem->Check( false );
	withRampMenuItem->Check( false );
	gravitationMenuItem->Check( false );
	lightMenuItem->Check( false );
	motionMenuItem->Check( false );
	pendulumMenuItem->Check( false );
	springMenuItem->Check( false );
	vectorAdditionMenuItem->Check( false );
	wavesMenuItem->Check( false );
	centerOfMassMenuItem->Check( false );
	graphingMenuItem->Check( false );
}

void PhysicsHelperMenuBar::ChangeMenuSimulationSelection(int menuId)
{	
	ClearMenuSimulationSelection();

	switch(menuId)
	{
	case MENUBAR_SimulationPlayground:
		playgroundMenuItem->Check( true );
		break;

	case MENUBAR_SimulationAtwoodMachine:
		atwoodMachineMenuItem->Check( true );
		break;

	case MENUBAR_SimulationCoulombLaw:
		coulombsLawMenuItem->Check( true );
		break;

	case MENUBAR_SimulationForceWithoutRamp:
		withoutRampForceMenuItem->Check( true );
		break;

	case MENUBAR_SimulationForceWithRamp:
		withRampMenuItem->Check( true );
		break;

	case MENUBAR_SimulationGravitation:
		gravitationMenuItem->Check( true );
		break;

	case MENUBAR_SimulationLight:
		lightMenuItem->Check( true );
		break;

	case MENUBAR_SimulationMotion:
		motionMenuItem->Check( true );
		break;

	case MENUBAR_SimulationPendulum:
		pendulumMenuItem->Check( true );
		break;

	case MENUBAR_SimulationSpring:
		springMenuItem->Check( true );
		break;

	case MENUBAR_SimulationVectorAddition:
		vectorAdditionMenuItem->Check( true );
		break;

	case MENUBAR_SimulationWaves:
		wavesMenuItem->Check( true );
		break;

	case MENUBAR_CenterOfMass:
		centerOfMassMenuItem->Check( true );
		break;

	case MENUBAR_SimulationGraphing:
		graphingMenuItem->Check( true );
		break;

	default:
		return;
	}
}