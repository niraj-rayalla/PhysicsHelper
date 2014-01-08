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

#include "GraphingSimulation.h"

GraphingSimulation::GraphingSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*addObjectToListBox)(wxString str, bool enabled))
	: Simulation(dev, _driver, _physicsEngine, SimulationType_Graphing)
{
	graphList = new List<ThreeDGraph*>();

	AddObjectToListBox = addObjectToListBox;
}

GraphingSimulation::~GraphingSimulation()
{
	delete graphList;
}

void GraphingSimulation::AddRectangularGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, RectangularAxis _colorAxis, RectangularAxis _axis, 
		int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid, bool _enabled)
{
	Node<ThreeDGraph*>* graphPointer = graphList->Add(new RectangularThreeDGraph(_name, _equationString, Scale, _lowColor, _highColor, device, _colorAxis, _axis, 
		_graphWidthResolution, _widthStart, _widthEnd, _graphHeightResolution, _heightStart, _heightEnd, _solid, _enabled));

	graphPointer->GetData()->CalculateGraph();
	graphPointer->GetData()->AddToSceneManager(device, device->getSceneManager());

	SetUnSaved();
}

void GraphingSimulation::AddSphericalGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, SphericalAxis _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid, bool _enabled)
{
	Node<ThreeDGraph*>* graphPointer = graphList->Add(new SphericalThreeDGraph(_name, _equationString, Scale, _lowColor, _highColor, device, _colorAxis, 
		_thetaResolution, _thetaStart, _thetaEnd, _phiResolution, _phiStart, _phiEnd, _solid, _enabled));

	graphPointer->GetData()->CalculateGraph();
	graphPointer->GetData()->AddToSceneManager(device, device->getSceneManager());

	SetUnSaved();
}

void GraphingSimulation::AddCylindricalGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, CylindricalAxis _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid, bool _enabled)
{
	Node<ThreeDGraph*>* graphPointer = graphList->Add(new CylindricalThreeDGraph(_name, _equationString, Scale, _lowColor, _highColor, device, _colorAxis, 
		_thetaResolution, _thetaStart, _thetaEnd, _radiusResolution, _radiusStart, _radiusEnd, _solid, _enabled));

	graphPointer->GetData()->CalculateGraph();
	graphPointer->GetData()->AddToSceneManager(device, device->getSceneManager());

	SetUnSaved();
}

void GraphingSimulation::AddParametricGraph(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, SColor _lowColor, SColor _highColor, ParametricAxis _colorAxis,
		int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid, bool _enabled)
{
	Node<ThreeDGraph*>* graphPointer = graphList->Add(new ParametricThreeDGraph(_name, _xEquationString, _yEquationString, _zEquationString, Scale, _lowColor, _highColor, 
		device, _colorAxis, _uResolution, _uStart, _uEnd, _vResolution, _vStart, _vEnd, _solid, _enabled));

	graphPointer->GetData()->CalculateGraph();
	graphPointer->GetData()->AddToSceneManager(device, device->getSceneManager());

	SetUnSaved();
}


void GraphingSimulation::RemoveGraph(int index)
{
	graphList->Remove(index);

	SetUnSaved();
}

void GraphingSimulation::ChangeSelections(wxArrayInt intArray)
{
	
}

void GraphingSimulation::ChangeEnabled(int index)
{
	graphList->GetAt(index)->GetData()->ChangeEnabledState();

	SetUnSaved();
}

void GraphingSimulation::Reset()
{
	graphList->Clear();
}

void GraphingSimulation::Draw(WxIrrViewport* currentViewport)
{
	Simulation::Draw(currentViewport);
}

void GraphingSimulation::SerializeIn(istream& is)
{
	Simulation::SerializeIn(is);

	int size = 0;
	is >> size;

	for(int i = 0; i < size; i++)
	{
		int graphType = 0;
		is >> graphType;
	
		if (graphType == ThreeDGraph_Rectangular)
		{
			RectangularThreeDGraph rectangularGraph;
			is >> rectangularGraph;
			AddRectangularGraph(rectangularGraph.name, rectangularGraph.equationString.ToAscii(), rectangularGraph.scale, rectangularGraph.lowColor, rectangularGraph.highColor, rectangularGraph.colorAxis,
				rectangularGraph.axis, rectangularGraph.graphWidth, rectangularGraph.widthStart, rectangularGraph.widthEnd, rectangularGraph.graphHeight, rectangularGraph.heightStart,
				rectangularGraph.heightEnd, rectangularGraph.solid, rectangularGraph.enabled);
			AddObjectToListBox(rectangularGraph.name, rectangularGraph.enabled);
		}
		else if (graphType == ThreeDGraph_Cylindrical)
		{
			CylindricalThreeDGraph cylindricalGraph;
			is >> cylindricalGraph;
			AddCylindricalGraph(cylindricalGraph.name, cylindricalGraph.equationString.ToAscii(), cylindricalGraph.scale, cylindricalGraph.lowColor, cylindricalGraph.highColor, cylindricalGraph.colorAxis,
				cylindricalGraph.thetaResolution, cylindricalGraph.thetaStart, cylindricalGraph.thetaEnd, cylindricalGraph.radiusResolution, cylindricalGraph.radiusStart,
				cylindricalGraph.radiusEnd, cylindricalGraph.solid, cylindricalGraph.enabled);
			AddObjectToListBox(cylindricalGraph.name, cylindricalGraph.enabled);
		}
		else if (graphType == ThreeDGraph_Spherical)
		{
			SphericalThreeDGraph sphericalGraph;
			is >> sphericalGraph;
			AddSphericalGraph(sphericalGraph.name, sphericalGraph.equationString.ToAscii(), sphericalGraph.scale, sphericalGraph.lowColor, sphericalGraph.highColor, sphericalGraph.colorAxis,
				sphericalGraph.thetaResolution, sphericalGraph.thetaStart, sphericalGraph.thetaEnd, sphericalGraph.phiResolution, sphericalGraph.phiStart,
				sphericalGraph.phiEnd, sphericalGraph.solid, sphericalGraph.enabled);
			AddObjectToListBox(sphericalGraph.name, sphericalGraph.enabled);
		}
		else if (graphType == ThreeDGraph_Parametric)
		{
			ParametricThreeDGraph parametricGraph;
			is >> parametricGraph;
			AddParametricGraph(parametricGraph.name, parametricGraph.xEquationString.ToAscii(), parametricGraph.yEquationString.ToAscii(), parametricGraph.zEquationString.ToAscii(), parametricGraph.scale, 
				parametricGraph.lowColor, parametricGraph.highColor, parametricGraph.colorAxis,
				parametricGraph.uResolution, parametricGraph.uStart, parametricGraph.uEnd, parametricGraph.vResolution, parametricGraph.vStart, parametricGraph.vEnd, parametricGraph.solid, parametricGraph.enabled);
			AddObjectToListBox(parametricGraph.name, parametricGraph.enabled);
		}
	}
}
void GraphingSimulation::SerializeOut(ostream& os)
{
	Simulation::SerializeOut(os);

	SerializeOutListPointer(os, graphList);
}