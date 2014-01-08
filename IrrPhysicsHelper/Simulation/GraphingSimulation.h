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

#ifndef _WX_IRR_GRAPHING_SIMULATION
#define _WX_IRR_GRAPHING_SIMULATION

#include "Simulation.h"
#include "../General/ThreeDGraph.h"

class GraphingSimulation : public Simulation
{
protected:
	List<ThreeDGraph*>* graphList;

	void (*AddObjectToListBox)(wxString str, bool enabled);
public:
	GraphingSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*AddObjectToListBox)(wxString str, bool enabled));
	~GraphingSimulation();

	virtual void AddRectangularGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, RectangularAxis _colorAxis, RectangularAxis _axis, 
		int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid = false, bool _enabled = true);

	virtual void AddSphericalGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, SphericalAxis _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid = false, bool _enabled = true);

	virtual void AddCylindricalGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, CylindricalAxis _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid = false, bool _enabled = true);

	virtual void AddParametricGraph(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, SColor _lowColor, SColor _highColor, ParametricAxis _colorAxis,
		int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid = false, bool _enabled = true);
	
	virtual void ChangeSelections(wxArrayInt intArray);

	virtual void ChangeEnabled(int index);

	virtual void RemoveGraph(int index);

	virtual void Reset();

	virtual void Draw(WxIrrViewport* currentViewport = 0);

	virtual void SerializeIn(istream& is);
	virtual void SerializeOut(ostream& os);
};

#endif