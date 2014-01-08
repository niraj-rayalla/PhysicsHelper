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

#include "ThreeDGraph.h"
#include "../DefinitionsInclude.h"

GraphingShaderCallBack* ThreeDGraph::graphingShaderCallback = NULL;

ThreeDGraph::ThreeDGraph()
{
	node = NULL;
	mesh = NULL;
	buf = NULL;
}

ThreeDGraph::ThreeDGraph(wxString _name, const char* _equationString, ThreeDGraphType _graphType, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device,
	bool _enabled, bool _bothSides, bool _enableLighting, bool _enableSpecular)
{
	equationString = _(_equationString);

	name = _name;

	scale = Scale;

	graphType = _graphType;

	lowColor = _lowColor;
	highColor = _highColor;

	bothSides = _bothSides;
	enableLighting = _enableLighting;
	enableSpecular = _enableSpecular;
	showWireframe = false;

	static int graphingShaderTest = 0;
	if (!graphingShaderTest)
	{
		graphingShaderCallback = SetupGraphingShader(device);
		graphingShaderTest++;
	}

	enabled = _enabled;

	node = NULL;
	mesh = NULL;
	buf = NULL;
}

ThreeDGraph::~ThreeDGraph()
{
	if (node)
		node->remove();
	delete mesh;

	/*if (graphingShaderCallback)
	{
		delete graphingShaderCallback;
		graphingShaderCallback = NULL;
	}*/
}

void ThreeDGraph::ChangeEnabledState()
{
	if (enabled)
	{
		enabled = false;
		node->setVisible(false);
	}
	else
	{
		enabled = true;
		node->setVisible(true);
	}
}

bool ThreeDGraph::CalculateGraph()
{
	return false;
}

void ThreeDGraph::AddToSceneManager(IrrlichtDevice* device, irr::scene::ISceneManager* smgr)
{
	node = smgr->addMeshSceneNode(mesh);	
	if (!enabled)
	{
		node->setVisible(false);
	}

	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialType((video::E_MATERIAL_TYPE)GetGraphingShader());

	if (device)
	{
		node->setMaterialTexture(0, device->getVideoDriver()->getTexture("../IrrPhysicsHelper/Content/Textures/Square.tga"));
	}
}

void ThreeDGraph::ColorAcrossGridAxis(bool isWidth, int width, int height)
{
	u32 numDistinctVertices = (u32)(width * height);

	int lowColorRed = lowColor.getRed();
	int lowColorGreen = lowColor.getGreen();
	int lowColorBlue = lowColor.getBlue();

	if (isWidth)
	{
		for (int x = 0; x < width; x++)
		{
			float ratio = (float)x / (float)width;
			for (int y = 0; y < height; y++)
			{
				buf->Vertices[x + y*width].Color.set(255, colorDifferenceRed*ratio + lowColorRed, colorDifferenceGreen*ratio + lowColorGreen, colorDifferenceBlue*ratio + lowColorBlue);
				buf->Vertices[x + y*width + numDistinctVertices].Color.set(buf->Vertices[x + y*width].Color.color);
			}
		}
	}
	else
	{
		for (int y = 0; y < height; y++)
		{
			float ratio = (float)y / (float)height;
			for (int x = 0; x < width; x++)
			{
				buf->Vertices[x + y*width].Color.set(255, colorDifferenceRed*ratio + lowColorRed, colorDifferenceGreen*ratio + lowColorGreen, colorDifferenceBlue*ratio + lowColorBlue);
				buf->Vertices[x + y*width + numDistinctVertices].Color.set(buf->Vertices[x + y*width].Color.color);
			}
		}
	}
}

void ThreeDGraph::SetupGridIndices(int width, int height)
{
	u32 numDistinctVertices = (u32)(width * height);
	u32 numDistinctIndices = (u32)((width-1) * (height-1) * 6);
	u32 size = buf->Indices.size();
	//Setup indices
	int i = 0;
    for (int y = 0; y < height -1; y++)
    {
		for (int x = 0; x < width -1; x++)
        {
            u32 lowerLeft = (u32)(x + y * width);
            u32 lowerRight = (u32)((x + 1) + y * width);
            u32 topLeft = (u32)(x + (y + 1) * width);
            u32 topRight = (u32)((x + 1) + (y + 1) * width);

			buf->Indices[i + numDistinctIndices] = lowerLeft + numDistinctVertices;
			buf->Indices[i++] = lowerLeft;
			buf->Indices[i + numDistinctIndices] = topRight + numDistinctVertices;
			buf->Indices[i++] = topLeft;
			buf->Indices[i + numDistinctIndices] = topLeft + numDistinctVertices;
            buf->Indices[i++] = topRight;

			buf->Indices[i + numDistinctIndices] = lowerLeft + numDistinctVertices;
			buf->Indices[i++] = lowerLeft;
			buf->Indices[i + numDistinctIndices] = lowerRight + numDistinctVertices;
            buf->Indices[i++] = topRight;
			buf->Indices[i + numDistinctIndices] = topRight + numDistinctVertices;
			buf->Indices[i++] = lowerRight;
        }
    }
}

void ThreeDGraph::CalculateGridNormals()
{
	for (unsigned int i = 0; i < buf->Vertices.size(); i++)
	{
		buf->Vertices[i].Normal = Vector3_Zero;
	}

	u32 size = buf->Indices.size();
	for (unsigned int i = 0; i < size / 3; i++)
	{
		int index1 = buf->Indices[i * 3];
        int index2 = buf->Indices[i * 3 + 1];
        int index3 = buf->Indices[i * 3 + 2];

		Vector3 side1 = buf->Vertices[index1].Pos - buf->Vertices[index3].Pos;
        Vector3 side2 = buf->Vertices[index1].Pos - buf->Vertices[index2].Pos;
		Vector3 normal = side2.crossProduct(side1);

        buf->Vertices[index1].Normal += normal;
        buf->Vertices[index2].Normal += normal;
        buf->Vertices[index3].Normal += normal;
	}

	u32 vertHalfSize = buf->Vertices.size() / 2;

	for (unsigned int i = 0; i < vertHalfSize; i++)
	{
		buf->Vertices[i].Normal.normalize();
		buf->Vertices[i + vertHalfSize].Normal = -1.0f * buf->Vertices[i].Normal;
	}
}

void ThreeDGraph::SerializeIn(istream& is)
{
	name = SerializeInWxString(is);

	is >> enableLighting;
	is >> enableSpecular;
	is >> bothSides;
	is >> showWireframe;

	lowColor = SerializeInSColor(is);
	highColor = SerializeInSColor(is);

	equationString = SerializeInWxString(is);

	is >> scale;

	is >> enabled;
}
void ThreeDGraph::SerializeOut(ostream& os)
{
	os << graphType << endl;

	SerializeOutWxString(os, name);

	os << enableLighting << endl;
	os << enableSpecular << endl;
	os << bothSides << endl;
	os << showWireframe << endl;

	SerializeOutSColor(os, lowColor);	
	SerializeOutSColor(os, highColor);

	SerializeOutWxString(os, equationString);
	//os << equationString << endl;

	os << scale << endl;

	os << enabled << endl;
}

ostream& operator<<(ostream& os, ThreeDGraph& graph)
{
	graph.SerializeOut(os);

	return os;
}



///Rectangular3D

RectangularThreeDGraph::RectangularThreeDGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device, RectangularAxis _colorAxis, RectangularAxis _axis,
	int _graphWidthResolution, double _widthStart, double _widthEnd, int _graphHeightResolution, double _heightStart, double _heightEnd, bool _solid, bool _enabled)
	: ThreeDGraph(_name, _equationString, ThreeDGraph_Rectangular, Scale, _lowColor, _highColor, device, _enabled)
{
	colorAxis = _colorAxis;
	axis = _axis;
	
	graphWidth = _graphWidthResolution;
	widthStart = _widthStart;
	widthEnd =_widthEnd;
	graphHeight = _graphHeightResolution;
	heightStart = _heightStart;
	heightEnd =_heightEnd;

	solid = _solid;

	valueMinimum = HUGE_VAL;
	valueMaximum = -HUGE_VAL;

	
	mesh = new SMesh();
	buf = new SMeshBuffer();//IMeshBuffer.Create(VertexType.Standard, IndexType._32Bit);
    mesh->addMeshBuffer(buf);
	buf->MappingHint_Vertex = EHM_STATIC;
	buf->MappingHint_Index = EHM_STATIC;
	buf->drop();

	buf->Vertices.set_used(graphWidth * graphHeight * 2);
	buf->Indices.set_used((graphWidth-1) * (graphHeight-1) * 12);	
}

void RectangularThreeDGraph::GetXVertexColors(double min, double max)
{
	float minFloat = (float)min;
	float maxFloat = (float)max;
	float difference = maxFloat - minFloat;

	int lowColorRed = lowColor.getRed();
	int lowColorGreen = lowColor.getGreen();
	int lowColorBlue = lowColor.getBlue();

	unsigned int i = 0;
	for (i ; i < buf->Vertices.size(); i++)
	{
		float ratio = (buf->Vertices[i].Pos.X - minFloat) / difference;
		if (difference == 0.0f)
			ratio = 0.0f;

		buf->Vertices[i].Color.set(255, colorDifferenceRed*ratio + lowColorRed, colorDifferenceGreen*ratio + lowColorGreen, colorDifferenceBlue*ratio + lowColorBlue);
	}		
}

void RectangularThreeDGraph::GetYVertexColors(double min, double max)
{
	float minFloat = (float)min;
	float maxFloat = (float)max;
	float difference = maxFloat - minFloat;

	int lowColorRed = lowColor.getRed();
	int lowColorGreen = lowColor.getGreen();
	int lowColorBlue = lowColor.getBlue();

	unsigned int i = 0;
	for (i ; i < buf->Vertices.size(); i++)
	{
		float ratio = (buf->Vertices[i].Pos.Y - minFloat) / difference;
		if (difference == 0.0f)
			ratio = 0.0f;

		buf->Vertices[i].Color.set(255, colorDifferenceRed*ratio + lowColorRed, colorDifferenceGreen*ratio + lowColorGreen, colorDifferenceBlue*ratio + lowColorBlue);
	}	
}

void RectangularThreeDGraph::GetZVertexColors(double min, double max)
{
	float minFloat = (float)min;
	float maxFloat = (float)max;
	float difference = maxFloat - minFloat;

	int lowColorRed = lowColor.getRed();
	int lowColorGreen = lowColor.getGreen();
	int lowColorBlue = lowColor.getBlue();

	unsigned int i = 0;
	for (i ; i < buf->Vertices.size(); i++)
	{
		float ratio = (buf->Vertices[i].Pos.Z - minFloat) / difference;
		if (difference == 0.0f)
			ratio = 0.0f;

		buf->Vertices[i].Color.set(255, colorDifferenceRed*ratio + lowColorRed, colorDifferenceGreen*ratio + lowColorGreen, colorDifferenceBlue*ratio + lowColorBlue);
	}		
}

bool RectangularThreeDGraph::CalculateGraph()
{
	int numDistinctVerts = graphWidth * graphHeight;

	std::string validVars[2];
	switch (axis)
	{
	case ThreeDGraph_X:
		validVars[0] = "y";
		validVars[1] = "z";
		break;
	case ThreeDGraph_Y:
		validVars[0] = "x";
		validVars[1] = "z";
		break;
	case ThreeDGraph_Z:
		validVars[0] = "x";
		validVars[1] = "y";
		break;
	}
	MathExpression mathExpr = MathExpression(equationString, validVars, 2);
	double validVarsValue[2] = {0,0};


	double currentWidth = widthStart;
	double currentHeight = heightStart;

	double widthInterval = (widthEnd - widthStart) / (double)(graphWidth - 1);
	double heightInterval = (heightEnd - heightStart) / (double)(graphHeight - 1);

	validVarsValue[0] = currentWidth;
	validVarsValue[1] = currentHeight;

	//Setup vertex positions
	int i = 0;
	for (int height = 0; height < graphHeight; height++)
	{
		for (int width = 0; width < graphWidth; width++)
		{
			double value = mathExpr.GetValue(validVarsValue);

			if (value > valueMaximum)
				valueMaximum = value;
			if (value < valueMinimum)
				valueMinimum = value;

			S3DVertex& v = buf->Vertices[i];
			S3DVertex& v2 = buf->Vertices[i + numDistinctVerts];

			float currentWidthFloat = (float)currentWidth;
			float currentHeightFloat = (float)currentHeight;
			float valueFloat = (float)value;

			switch (axis)
			{
			case ThreeDGraph_X:
				v.Pos.set(valueFloat, currentWidthFloat,currentHeightFloat);
				v2.Pos.set(valueFloat, currentWidthFloat,currentHeightFloat);
				break;
			case ThreeDGraph_Y:
				v.Pos.set(currentWidthFloat, valueFloat, currentHeightFloat);
				v2.Pos.set(currentWidthFloat, valueFloat, currentHeightFloat);
				break;
			case ThreeDGraph_Z:
				v.Pos.set(currentHeightFloat, currentWidthFloat, valueFloat);
				v2.Pos.set(currentHeightFloat, currentWidthFloat, valueFloat);
				break;
			}

			v.Normal.set(0, 1, 0);
			//v.Color.set(255, 255, 0, 0);
			v.TCoords.set(width, height);
			v2.TCoords.set(width, height);

			currentWidth += widthInterval;
			validVarsValue[0] = currentWidth;
			i++;
		}

		currentWidth = widthStart;
		validVarsValue[0] = currentWidth;
		currentHeight += heightInterval;
		validVarsValue[1] = currentHeight;
	}

	//Setup Vertex colors
	if (!solid)
	{
		colorDifferenceRed = highColor.getRed() - lowColor.getRed();
		colorDifferenceGreen = highColor.getGreen() - lowColor.getGreen();
		colorDifferenceBlue = highColor.getBlue() - lowColor.getBlue();
	}
	else
	{
		colorDifferenceRed = 0;
		colorDifferenceGreen = 0;
		colorDifferenceBlue = 0;
	}


	if (colorAxis == axis)
	{
		switch (colorAxis)
		{
		case ThreeDGraph_X:
			GetXVertexColors(valueMinimum, valueMaximum);
			break;
		case ThreeDGraph_Y:
			GetYVertexColors(valueMinimum, valueMaximum);
			break;
		case ThreeDGraph_Z:
			GetZVertexColors(valueMinimum, valueMaximum);
			break;
		}
	}
	else
	{
		switch (axis)
		{
		case ThreeDGraph_X:
			if (colorAxis == ThreeDGraph_Y)
			{
				GetYVertexColors(widthStart, widthStart + widthInterval*(graphWidth-1));
			}
			else
			{
				GetZVertexColors(heightStart, heightStart + heightInterval*(graphWidth-1));
			}
			break;
		case ThreeDGraph_Y:
			if (colorAxis == ThreeDGraph_X)
			{
				GetXVertexColors(widthStart, widthStart + widthInterval*(graphWidth-1));
			}
			else
			{
				GetZVertexColors(heightStart, heightStart + heightInterval*(graphWidth-1));
			}
			break;
		case ThreeDGraph_Z:
			if (colorAxis == ThreeDGraph_X)
			{
				GetXVertexColors(widthStart, widthStart + widthInterval*(graphWidth-1));
			}
			else
			{
				GetYVertexColors(heightStart, heightStart + heightInterval*(graphWidth-1));
			}
			break;
		}		
	}

	SetupGridIndices(graphWidth, graphHeight);

	CalculateGridNormals();

	buf->recalculateBoundingBox();
	mesh->recalculateBoundingBox();

	return true;
}

void RectangularThreeDGraph::SerializeIn(istream& is)
{
	ThreeDGraph::SerializeIn(is);

	int tempColorAxis = 0;
	is >> tempColorAxis;
	if (tempColorAxis == ThreeDGraph_X)
	{
		colorAxis = ThreeDGraph_X;
	}
	else if (tempColorAxis == ThreeDGraph_Y)
	{
		colorAxis = ThreeDGraph_Y;
	}
	else if (tempColorAxis == ThreeDGraph_Z)
	{
		colorAxis = ThreeDGraph_Z;
	}

	int tempAxis = 0;
	is >> tempAxis;
	if (tempAxis == ThreeDGraph_X)
	{
		axis = ThreeDGraph_X;
	}
	else if (tempAxis == ThreeDGraph_Y)
	{
		axis = ThreeDGraph_Y;
	}
	else if (tempAxis == ThreeDGraph_Z)
	{
		axis = ThreeDGraph_Z;
	}

	is >> graphWidth;
	is >> widthStart;
	is >> widthEnd;
	is >> graphHeight;
	is >> heightStart;
	is >> heightEnd;

	is >> solid;

	is >> valueMinimum;
	is >> valueMaximum;
}
void RectangularThreeDGraph::SerializeOut(ostream& os)
{
	ThreeDGraph::SerializeOut(os);

	os << colorAxis << endl;
	os << axis << endl;

	os << graphWidth << endl;
	os << widthStart << endl;
	os << widthEnd << endl;
	os << graphHeight << endl;
	os << heightStart << endl;
	os << heightEnd << endl;

	os << solid << endl;

	os << valueMinimum << endl;
	os << valueMaximum << endl;
}

istream& operator>>(istream& is, RectangularThreeDGraph& graph)
{
	graph.SerializeIn(is);

	return is;
}


///Spherical3D

SphericalThreeDGraph::SphericalThreeDGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device, SphericalAxis _colorAxis,
	int _thetaResolution, double _thetaStart, double _thetaEnd, int _phiResolution, double _phiStart, double _phiEnd, bool _solid, bool _enabled)
	: ThreeDGraph(_name, _equationString, ThreeDGraph_Spherical, Scale, _lowColor, _highColor, device, _enabled)
{
	colorAxis = _colorAxis;
	
	thetaResolution = _thetaResolution;
	thetaStart = _thetaStart;
	thetaEnd =_thetaEnd;
	phiResolution = _phiResolution;
	phiStart = _phiStart;
	phiEnd =_phiEnd;

	radiusMinimum = HUGE_VAL;
	radiusMaximum = -HUGE_VAL;

	solid = _solid;
	
	mesh = new SMesh();
	buf = new SMeshBuffer();
    mesh->addMeshBuffer(buf);
	buf->MappingHint_Vertex = EHM_STATIC;
	buf->MappingHint_Index = EHM_STATIC;
	buf->drop();

	buf->Vertices.set_used(thetaResolution * phiResolution * 2);
	buf->Indices.set_used((thetaResolution-1) * (phiResolution-1) * 12);	
}

bool SphericalThreeDGraph::CalculateGraph()
{
	int numDistinctVerts = thetaResolution * phiResolution;

	std::string validVars[2] = { "theta", "phi" };
	MathExpression mathExpr = MathExpression(equationString, validVars, 2);
	MathExpression xSphericalMathExpr = MathExpression("sin(phi)*cos(theta)", validVars, 2);
	MathExpression ySphericalMathExpr = MathExpression("sin(phi)*sin(theta)", validVars, 2);
	MathExpression zSphericalMathExpr = MathExpression("cos(phi)", validVars, 2);
	double validVarsValue[2] = {0,0};

	double currentTheta = thetaStart;
	double currentPhi = phiStart;

	double thetaInterval = (thetaEnd - thetaStart) / (double)(thetaResolution - 1);
	double phiInterval = (phiEnd - phiStart) / (double)(phiResolution - 1);

	validVarsValue[0] = currentTheta;
	validVarsValue[1] = currentPhi;

	//Setup vertex positions
	int i = 0;
	for (int height = 0; height < phiResolution; height++)
	{
		for (int width = 0; width < thetaResolution; width++)
		{
			double radius = mathExpr.GetValue(validVarsValue);
			double xSpherical = xSphericalMathExpr.GetValue(validVarsValue);
			double ySpherical = ySphericalMathExpr.GetValue(validVarsValue);
			double zSpherical = zSphericalMathExpr.GetValue(validVarsValue);

			if (radius > radiusMaximum)
				radiusMaximum = radius;
			if (radius < radiusMinimum)
				radiusMinimum = radius;

			S3DVertex& v = buf->Vertices[i];
			S3DVertex& v2 = buf->Vertices[i + numDistinctVerts];

			float currentThetaFloat = (float)currentTheta;
			float currentPhiFloat = (float)currentPhi;
			float radiusFloat = (float)radius;
			float xSphericalFloat = (float)xSpherical;
			float ySphericalFloat = (float)ySpherical;
			float zSphericalFloat = (float)zSpherical;

			v.Pos.set(radiusFloat*xSphericalFloat, radiusFloat*ySphericalFloat,radiusFloat*zSphericalFloat);
			v2.Pos.set(radiusFloat*xSphericalFloat, radiusFloat*ySphericalFloat,radiusFloat*zSphericalFloat);
			v.TCoords.set(width, height);
			v2.TCoords.set(width, height);

			currentTheta += thetaInterval;
			validVarsValue[0] = currentTheta;
			i++;
		}

		currentTheta = thetaStart;
		validVarsValue[0] = currentTheta;
		currentPhi += phiInterval;
		validVarsValue[1] = currentPhi;
	}

	//Setup Vertex colors
	if (!solid)
	{
		colorDifferenceRed = highColor.getRed() - lowColor.getRed();
		colorDifferenceGreen = highColor.getGreen() - lowColor.getGreen();
		colorDifferenceBlue = highColor.getBlue() - lowColor.getBlue();
	}
	else
	{
		colorDifferenceRed = 0;
		colorDifferenceGreen = 0;
		colorDifferenceBlue = 0;
	}


	if (colorAxis == ThreeDGraphSpherical_Radius)
	{
		float difference = (float)radiusMaximum - (float)radiusMinimum;

		int lowColorRed = lowColor.getRed();
		int lowColorGreen = lowColor.getGreen();
		int lowColorBlue = lowColor.getBlue();

		for(unsigned int i = 0; i < buf->Vertices.size(); i++)
		{
			S3DVertex& vert = buf->Vertices[i];

			float distance = vert.Pos.getDistanceFrom(Vector3_Zero);

			float ratio = distance / difference;
			if (difference == 0.0f)
				ratio = 0.0f;

			buf->Vertices[i].Color.set(255, colorDifferenceRed*ratio + lowColorRed, colorDifferenceGreen*ratio + lowColorGreen, colorDifferenceBlue*ratio + lowColorBlue);
		}
	}
	else
	{
		switch (colorAxis)
		{
		case ThreeDGraphSpherical_Theta:
			ColorAcrossGridAxis(true, thetaResolution, phiResolution);
			break;
		case ThreeDGraphSpherical_Phi:
			ColorAcrossGridAxis(false, thetaResolution, phiResolution);
			break;
		}
	}

	SetupGridIndices(thetaResolution, phiResolution);

	CalculateGridNormals();

	buf->recalculateBoundingBox();
	mesh->recalculateBoundingBox();

	return true;
}

void SphericalThreeDGraph::SerializeIn(istream& is)
{
	ThreeDGraph::SerializeIn(is);

	int tempColorAxis = 0;
	is >> tempColorAxis;
	if (tempColorAxis == ThreeDGraphSpherical_Theta)
	{
		colorAxis = ThreeDGraphSpherical_Theta;
	}
	else if (tempColorAxis == ThreeDGraphSpherical_Phi)
	{
		colorAxis = ThreeDGraphSpherical_Phi;
	}
	else if (tempColorAxis == ThreeDGraphSpherical_Radius)
	{
		colorAxis = ThreeDGraphSpherical_Radius;
	}

	is  >> thetaResolution;
	is  >> thetaStart;
	is  >> thetaEnd;
	is  >> phiResolution;
	is  >> phiStart;
	is  >> phiEnd;

	is  >> solid;

	is  >> radiusMinimum;
	is  >> radiusMaximum;
}
void SphericalThreeDGraph::SerializeOut(ostream& os)
{
	ThreeDGraph::SerializeOut(os);

	os << colorAxis << endl;

	os << thetaResolution << endl;
	os << thetaStart << endl;
	os << thetaEnd << endl;
	os << phiResolution << endl;
	os << phiStart << endl;
	os << phiEnd << endl;

	os << solid << endl;

	os << radiusMinimum << endl;
	os << radiusMaximum << endl;
}

istream& operator>>(istream& is, SphericalThreeDGraph& graph)
{
	graph.SerializeIn(is);

	return is;
}



///Cylindrical3D

CylindricalThreeDGraph::CylindricalThreeDGraph(wxString _name, const char* _equationString, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device, CylindricalAxis _colorAxis,
	int _thetaResolution, double _thetaStart, double _thetaEnd, int _radiusResolution, double _radiusStart, double _radiusEnd, bool _solid, bool _enabled)
	: ThreeDGraph(_name, _equationString, ThreeDGraph_Cylindrical, Scale, _lowColor, _highColor, device, _enabled)
{
	colorAxis = _colorAxis;
	
	thetaResolution = _thetaResolution;
	thetaStart = _thetaStart;
	thetaEnd =_thetaEnd;
	radiusResolution = _radiusResolution;
	radiusStart = _radiusStart;
	radiusEnd =_radiusEnd;

	zMinimum = HUGE_VAL;
	zMaximum = -HUGE_VAL;

	solid = _solid;
	
	mesh = new SMesh();
	buf = new SMeshBuffer();
    mesh->addMeshBuffer(buf);
	buf->MappingHint_Vertex = EHM_STATIC;
	buf->MappingHint_Index = EHM_STATIC;
	buf->drop();

	buf->Vertices.set_used(thetaResolution * radiusResolution * 2);
	buf->Indices.set_used((thetaResolution-1) * (radiusResolution-1) * 12);	
}

bool CylindricalThreeDGraph::CalculateGraph()
{
	int numDistinctVerts = thetaResolution * radiusResolution;

	std::string validVars[2] = { "theta", "r" };
	MathExpression mathExpr = MathExpression(equationString, validVars, 2);
	MathExpression xCylindricalMathExpr = MathExpression("r*cos(theta)", validVars, 2);
	MathExpression yCylindricalMathExpr = MathExpression("r*sin(theta)", validVars, 2);
	double validVarsValue[2] = {0,0};

	double currentTheta = thetaStart;
	double currentRadius = radiusStart;

	double thetaInterval = (thetaEnd - thetaStart) / (double)(thetaResolution - 1);
	double radiusInterval = (radiusEnd - radiusStart) / (double)(radiusResolution - 1);

	validVarsValue[0] = currentTheta;
	validVarsValue[1] = currentRadius;

	//Setup vertex positions
	int i = 0;
	for (int height = 0; height < radiusResolution; height++)
	{
		for (int width = 0; width < thetaResolution; width++)
		{
			double z = mathExpr.GetValue(validVarsValue);
			double xCylindrical = xCylindricalMathExpr.GetValue(validVarsValue);
			double yCylindrical = yCylindricalMathExpr.GetValue(validVarsValue);

			if (z > zMaximum)
				zMaximum = z;
			if (z < zMinimum)
				zMinimum = z;

			S3DVertex& v = buf->Vertices[i];
			S3DVertex& v2 = buf->Vertices[i + numDistinctVerts];

			float currentThetaFloat = (float)currentTheta;
			float currentRadiusFloat = (float)currentRadius;
			float zFloat = (float)z;
			float xFloat = (float)xCylindrical;
			float yFloat = (float)yCylindrical;

			v.Pos.set(xFloat, yFloat, zFloat);
			v2.Pos.set(xFloat, yFloat, zFloat);
			v.TCoords.set(width, height);
			v2.TCoords.set(width, height);

			currentTheta += thetaInterval;
			validVarsValue[0] = currentTheta;
			i++;
		}

		currentTheta = thetaStart;
		validVarsValue[0] = currentTheta;
		currentRadius += radiusInterval;
		validVarsValue[1] = currentRadius;
	}

	//Setup Vertex colors
	if (!solid)
	{
		colorDifferenceRed = highColor.getRed() - lowColor.getRed();
		colorDifferenceGreen = highColor.getGreen() - lowColor.getGreen();
		colorDifferenceBlue = highColor.getBlue() - lowColor.getBlue();
	}
	else
	{
		colorDifferenceRed = 0;
		colorDifferenceGreen = 0;
		colorDifferenceBlue = 0;
	}


	if (colorAxis == ThreeDGraphCylindrical_Z)
	{
		float zMinimumFloat = (float)zMinimum;
		float difference = (float)zMaximum - zMinimumFloat;

		int lowColorRed = lowColor.getRed();
		int lowColorGreen = lowColor.getGreen();
		int lowColorBlue = lowColor.getBlue();

		for(unsigned int i = 0; i < buf->Vertices.size(); i++)
		{
			S3DVertex& vert = buf->Vertices[i];

			float distance = vert.Pos.Z;

			float ratio = (distance - zMinimumFloat) / difference;
			if (difference == 0.0f)
				ratio = 0.0f;

			buf->Vertices[i].Color.set(255, colorDifferenceRed*ratio + lowColorRed, colorDifferenceGreen*ratio + lowColorGreen, colorDifferenceBlue*ratio + lowColorBlue);
		}
	}
	else
	{
		switch (colorAxis)
		{
		case ThreeDGraphCylindrical_Theta:
			ColorAcrossGridAxis(true, thetaResolution, radiusResolution);
			break;
		case ThreeDGraphCylindrical_Radius:
			ColorAcrossGridAxis(false, thetaResolution, radiusResolution);
			break;
		}
	}

	SetupGridIndices(thetaResolution, radiusResolution);

	CalculateGridNormals();

	buf->recalculateBoundingBox();
	mesh->recalculateBoundingBox();

	return true;
}

void CylindricalThreeDGraph::SerializeIn(istream& is)
{
	ThreeDGraph::SerializeIn(is);

	int tempColorAxis = 0;
	is >> tempColorAxis;
	if (tempColorAxis == ThreeDGraphCylindrical_Theta)
	{
		colorAxis = ThreeDGraphCylindrical_Theta;
	}
	else if (tempColorAxis == ThreeDGraphCylindrical_Radius)
	{
		colorAxis = ThreeDGraphCylindrical_Radius;
	}
	else if (tempColorAxis == ThreeDGraphCylindrical_Z)
	{
		colorAxis = ThreeDGraphCylindrical_Z;
	}

	is  >> thetaResolution;
	is  >> thetaStart;
	is  >> thetaEnd;
	is  >> radiusResolution;
	is  >> radiusStart;
	is  >> radiusEnd;

	is  >> solid;

	is  >> zMinimum;
	is  >> zMaximum;
}
void CylindricalThreeDGraph::SerializeOut(ostream& os)
{
	ThreeDGraph::SerializeOut(os);

	os << colorAxis << endl;

	os << thetaResolution << endl;
	os << thetaStart << endl;
	os << thetaEnd << endl;
	os << radiusResolution << endl;
	os << radiusStart << endl;
	os << radiusEnd << endl;

	os << solid << endl;

	os << zMinimum << endl;
	os << zMaximum << endl;
}

istream& operator>>(istream& is, CylindricalThreeDGraph& graph)
{
	graph.SerializeIn(is);

	return is;
}



///Parametric3D

ParametricThreeDGraph::ParametricThreeDGraph(wxString _name, const char* _xEquationString, const char* _yEquationString, const char* _zEquationString, float Scale, SColor _lowColor, SColor _highColor, IrrlichtDevice* device, ParametricAxis _colorAxis,
	int _uResolution, double _uStart, double _uEnd, int _vResolution, double _vStart, double _vEnd, bool _solid, bool _enabled)
	: ThreeDGraph(_name, "", ThreeDGraph_Parametric, Scale, _lowColor, _highColor, device, _enabled)
{
	xEquationString = _(_xEquationString);
	yEquationString = _(_yEquationString);
	zEquationString = _(_zEquationString);

	colorAxis = _colorAxis;
	
	uResolution = _uResolution;
	uStart = _uStart;
	uEnd =_uEnd;
	vResolution = _vResolution;
	vStart = _vStart;
	vEnd =_vEnd;

	solid = _solid;
	
	mesh = new SMesh();
	buf = new SMeshBuffer();
    mesh->addMeshBuffer(buf);
	buf->MappingHint_Vertex = EHM_STATIC;
	buf->MappingHint_Index = EHM_STATIC;
	buf->drop();

	buf->Vertices.set_used(uResolution * vResolution * 2);
	buf->Indices.set_used((uResolution-1) * (vResolution-1) * 12);	
}

bool ParametricThreeDGraph::CalculateGraph()
{
	int numDistinctVerts = uResolution * vResolution;

	std::string validVars[2] = { "u", "v" };
	MathExpression xParametricMathExpr = MathExpression(xEquationString, validVars, 2);
	MathExpression yParametricMathExpr = MathExpression(yEquationString, validVars, 2);
	MathExpression zParametricMathExpr = MathExpression(zEquationString, validVars, 2);
	double validVarsValue[2] = {0,0};

	double currentU = uStart;
	double currentV = vStart;

	double uInterval = (uEnd - uStart) / (double)(uResolution - 1);
	double vInterval = (vEnd - vStart) / (double)(vResolution - 1);

	validVarsValue[0] = currentU;
	validVarsValue[1] = currentV;

	//Setup vertex positions
	int i = 0;
	for (int height = 0; height < vResolution; height++)
	{
		for (int width = 0; width < uResolution; width++)
		{
			double xParametric = xParametricMathExpr.GetValue(validVarsValue);
			double yParametric = yParametricMathExpr.GetValue(validVarsValue);
			double zParametric = zParametricMathExpr.GetValue(validVarsValue);

			S3DVertex& v = buf->Vertices[i];
			S3DVertex& v2 = buf->Vertices[i + numDistinctVerts];

			float currentUFloat = (float)currentU;
			float currentVFloat = (float)currentV;
			float xFloat = (float)xParametric;
			float yFloat = (float)yParametric;
			float zFloat = (float)zParametric;

			v.Pos.set(xFloat, yFloat, zFloat);
			v2.Pos.set(xFloat, yFloat, zFloat);
			v.TCoords.set(width, height);
			v2.TCoords.set(width, height);

			currentU += uInterval;
			validVarsValue[0] = currentU;
			i++;
		}

		currentU = uStart;
		validVarsValue[0] = currentU;
		currentV += vInterval;
		validVarsValue[1] = currentV;
	}

	//Setup Vertex colors
	if (!solid)
	{
		colorDifferenceRed = highColor.getRed() - lowColor.getRed();
		colorDifferenceGreen = highColor.getGreen() - lowColor.getGreen();
		colorDifferenceBlue = highColor.getBlue() - lowColor.getBlue();
	}
	else
	{
		colorDifferenceRed = 0;
		colorDifferenceGreen = 0;
		colorDifferenceBlue = 0;
	}

	if (colorAxis == ThreeDGraphParametric_U)
	{
		ColorAcrossGridAxis(true, uResolution, vResolution);
	}
	else
	{
		ColorAcrossGridAxis(false, uResolution, vResolution);
	}

	SetupGridIndices(uResolution, vResolution);

	CalculateGridNormals();

	buf->recalculateBoundingBox();
	mesh->recalculateBoundingBox();

	return true;
}

void ParametricThreeDGraph::SerializeIn(istream& is)
{
	ThreeDGraph::SerializeIn(is);

	int tempColorAxis = 0;
	is >> tempColorAxis;
	if (tempColorAxis == ThreeDGraphParametric_U)
	{
		colorAxis = ThreeDGraphParametric_U;
	}
	else if (tempColorAxis == ThreeDGraphParametric_V)
	{
		colorAxis = ThreeDGraphParametric_V;
	}
	else if (tempColorAxis == ThreeDGraphParametric_X)
	{
		colorAxis = ThreeDGraphParametric_X;
	}
	else if (tempColorAxis == ThreeDGraphParametric_Y)
	{
		colorAxis = ThreeDGraphParametric_Y;
	}
	else if (tempColorAxis == ThreeDGraphParametric_Z)
	{
		colorAxis = ThreeDGraphParametric_Z;
	}


	is >> uResolution;
	is >> uStart;
	is >> uEnd;
	is >> vResolution;
	is >> vStart;
	is >> vEnd;

	is >> solid;

	xEquationString = SerializeInWxString(is);
	yEquationString = SerializeInWxString(is);
	zEquationString = SerializeInWxString(is);
}
void ParametricThreeDGraph::SerializeOut(ostream& os)
{
	ThreeDGraph::SerializeOut(os);

	os << colorAxis << endl;

	os << uResolution << endl;
	os << uStart << endl;
	os << uEnd << endl;
	os << vResolution << endl;
	os << vStart << endl;
	os << vEnd << endl;

	os << solid << endl;

	SerializeOutWxString(os, xEquationString);
	SerializeOutWxString(os, yEquationString);
	SerializeOutWxString(os, zEquationString);
}

istream& operator>>(istream& is, ParametricThreeDGraph& graph)
{
	graph.SerializeIn(is);

	return is;
}