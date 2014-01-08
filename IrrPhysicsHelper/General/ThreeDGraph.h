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

#ifndef _WX_IRR_THREE_D_GRAPH
#define _WX_IRR_THREE_D_GRAPH

#include <wx/wx.h>
#include "../IrrlichtInclude.h"
#include "../Math/MathExpression.h"
#include <math.h>

#include "../Shaders/GraphingShader.h"

#include <iostream>
#include <fstream>
using namespace std;

#include "../Serialization/Serialization.h"

enum ThreeDGraphType
{
	ThreeDGraph_Rectangular,
	ThreeDGraph_Cylindrical,
	ThreeDGraph_Spherical,
	ThreeDGraph_Parametric
};

class ThreeDGraph
{
	friend class GraphingSimulation;
	friend class LightSimulation;
	friend class IrrlichtToBulletStaticGraphObject;
	friend class PlaygroundSimulation;
protected:
	ThreeDGraphType graphType;

	wxString name;

	bool enableLighting;
	bool enableSpecular;
	bool bothSides;
	bool showWireframe;

	SColor lowColor;
	SColor highColor;
	int colorDifferenceRed;
	int colorDifferenceGreen;
	int colorDifferenceBlue;

	wxString equationString;

    float scale;
    SMesh* mesh;
	SMeshBuffer* buf;
	IMeshSceneNode* node;

	bool enabled;

	void ColorAcrossGridAxis(bool isWidth, int width, int height);
	void SetupGridIndices(int width, int height);
	void CalculateGridNormals();

public:
	static GraphingShaderCallBack* graphingShaderCallback;

	ThreeDGraph();
	ThreeDGraph(wxString _name, const char* _equationString, ThreeDGraphType _graphType, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device = 0, bool _enabled = true,
		bool _bothSides = false, bool _enableLighting = false, bool _enableSpecular = false);

	~ThreeDGraph();

	virtual bool CalculateGraph();

	virtual void AddToSceneManager(IrrlichtDevice* device, ISceneManager* smgr);

	ThreeDGraphType GetGraphType() { return graphType; }
	SMesh* GetMesh() { return mesh; }
	IMeshSceneNode* GetNode() { return node; }
	void ChangeEnabledState();

	virtual void SerializeIn(istream& is);
	virtual void SerializeOut(ostream& os);

	friend ostream& operator<<(ostream& os, ThreeDGraph& graph);
};


//Rectangular Graphs

enum RectangularAxis
{
	ThreeDGraph_X, //y:width, z: height
	ThreeDGraph_Y, //x:width, z: height
	ThreeDGraph_Z //x:width, y: height
};

class RectangularThreeDGraph : public ThreeDGraph
{
	friend class GraphingSimulation;
	friend class IrrlichtToBulletStaticGraphObject;
	friend class PlaygroundSimulation;
private:
	RectangularAxis colorAxis;
	RectangularAxis axis;

	int graphWidth;
	double widthStart;
	double widthEnd;
	int graphHeight;
	double heightStart;
	double heightEnd;

	bool solid;

	double valueMinimum;
	double valueMaximum;

	void GetXVertexColors(double min, double max);
	void GetYVertexColors(double min, double max);
	void GetZVertexColors(double min, double max);

public:
	RectangularThreeDGraph(){}
	RectangularThreeDGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device, RectangularAxis _colorAxis, RectangularAxis _axis, 
		int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid, bool _enabled = true);

	bool CalculateGraph();

	void SerializeIn(istream &is);
	void SerializeOut(ostream &os);

	friend istream& operator>>(istream& is, RectangularThreeDGraph& graph);
};


//Spherical Graphs

enum SphericalAxis
{
	ThreeDGraphSpherical_Theta, //width
	ThreeDGraphSpherical_Phi, //height
	ThreeDGraphSpherical_Radius //the value
};

class SphericalThreeDGraph : public ThreeDGraph
{
	friend class GraphingSimulation;
	friend class IrrlichtToBulletStaticGraphObject;
	friend class PlaygroundSimulation;
private:
	SphericalAxis colorAxis;

	int thetaResolution;
	double thetaStart;
	double thetaEnd;
	int phiResolution;
	double phiStart;
	double phiEnd;

	bool solid;

	double radiusMinimum;
	double radiusMaximum;	

public:
	SphericalThreeDGraph(){}
	SphericalThreeDGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device, SphericalAxis _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid = false, bool _enabled = true);

	bool CalculateGraph();

	void SerializeIn(istream &is);
	void SerializeOut(ostream &os);

	friend istream& operator>>(istream& is, SphericalThreeDGraph& graph);
};


//Cylindrical Graphs

enum CylindricalAxis
{
	ThreeDGraphCylindrical_Theta, //width
	ThreeDGraphCylindrical_Radius, //height
	ThreeDGraphCylindrical_Z //the value
};

class CylindricalThreeDGraph : public ThreeDGraph
{
	friend class GraphingSimulation;
	friend class IrrlichtToBulletStaticGraphObject;
	friend class PlaygroundSimulation;
private:
	CylindricalAxis colorAxis;

	int thetaResolution;
	double thetaStart;
	double thetaEnd;
	int radiusResolution;
	double radiusStart;
	double radiusEnd;

	bool solid;

	double zMinimum;
	double zMaximum;

	

public:
	CylindricalThreeDGraph(){}
	CylindricalThreeDGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device, CylindricalAxis _colorAxis,
		int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid = false, bool _enabled = true);

	bool CalculateGraph();

	void SerializeIn(istream &is);
	void SerializeOut(ostream &os);

	friend istream& operator>>(istream& is, CylindricalThreeDGraph& graph);
};


//Parametric Graphs

enum ParametricAxis
{
	ThreeDGraphParametric_U, //width
	ThreeDGraphParametric_V, //height
	ThreeDGraphParametric_X,
	ThreeDGraphParametric_Y,
	ThreeDGraphParametric_Z,
};

class ParametricThreeDGraph : public ThreeDGraph
{
	friend class GraphingSimulation;
	friend class IrrlichtToBulletStaticGraphObject;
	friend class PlaygroundSimulation;
private:
	ParametricAxis colorAxis;

	int uResolution;
	double uStart;
	double uEnd;
	int vResolution;
	double vStart;
	double vEnd;

	bool solid;

	wxString xEquationString;
	wxString yEquationString;
	wxString zEquationString;

public:
	ParametricThreeDGraph(){}
	ParametricThreeDGraph(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device, ParametricAxis _colorAxis,
		int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid = false, bool _enabled = true);

	bool CalculateGraph();

	void SerializeIn(istream &is);
	void SerializeOut(ostream &os);

	friend istream& operator>>(istream& is, ParametricThreeDGraph& graph);
};

#endif