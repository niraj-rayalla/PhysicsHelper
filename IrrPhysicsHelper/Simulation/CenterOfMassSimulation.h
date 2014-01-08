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

#ifndef _WX_IRR_CENTER_OF_MASS_SIMULATION
#define _WX_IRR_CENTER_OF_MASS_SIMULATION

#include "Simulation.h"

class COMSimulationObject
{
public:
	ISceneNode* node;
	wxString name;
	Vector3 position;
	float mass;
	float radius;
	bool enabled;

	COMSimulationObject()
	{
		node = NULL;
	}

	COMSimulationObject(ISceneNode* _node, wxString _name, Vector3 pos, float _mass, float _radius, bool _enabled = true)
	{
		node = _node;
		name = _name;
		position = pos;
		mass = _mass;
		radius = _radius;
		enabled = _enabled;
	}

	~COMSimulationObject()
	{
		if (node)
			node->remove();
	}

	void ChangeColor(SColor color = SColor(255, 255, 255, 255))
	{
		node->getSceneManager()->getMeshManipulator()->setVertexColors(((IMeshSceneNode*)node)->getMesh(), color);
	}

	void ChangeEnabled()
	{
		if (enabled)
		{
			enabled = false;
			ChangeColor(SColor(255, 100, 100, 100));
			node->setMaterialFlag(EMF_LIGHTING, false);
		}
		else
		{
			enabled = true;
			ChangeColor();
			node->setMaterialFlag(EMF_LIGHTING, true);
		}
	}

	friend ostream& operator<<(ostream& os, COMSimulationObject& obj)
	{
		SerializeOutVector3(os, obj.position);
		SerializeOutWxString(os, obj.name);
		os << obj.mass << endl << obj.radius << endl << obj.enabled << endl;

		return os;
	}

	friend istream& operator>>(istream& is, COMSimulationObject& obj)
	{
		obj.position = SerializeInVector3(is);
		obj.name = SerializeInWxString(is);
		is >> obj.mass;
		is >> obj.radius;
		is >> obj.enabled;

		return is;
	}
};

class CenterOfMassSimulation : public Simulation
{
private:
	Vector3 centerOfMass;
	int numObjects;
	float totalMass;

	List<COMSimulationObject*>* objectList;
	List<int>* selectedObjectsIndexes;

	Vector3 COMPointLeft;
	Vector3 COMPointRight;
	Vector3 COMPointTop;
	Vector3 COMPointBottom;
	Vector3 COMPointForward;
	Vector3 COMPointBackward;

	
	void (*AddObjectToListBox)(wxString str, bool enabled);
	void (*ChangeCOMLabels)(float COMX, float COMY, float COMZ, float totalMass, int numObjects);

public:
	CenterOfMassSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine,
		void (*AddObjectToListBox)(wxString str, bool enabled),
		void (*ChangeCOMLabels)(float COMX, float COMY, float COMZ, 
		float totalMass, int numObjects));
	~CenterOfMassSimulation();

	wxString* GetOutputStrings();

	wxString* AddObject(wxString _name, Vector3 pos, float mass, float radius, bool isRelative, int relativeIndex, bool enabled = true);
	wxString* AddObjectUsingEquation(wxString _name, vector3d<std::string> pos, std::string mass, std::string radius, Vector3 posBegin, Vector3 posEnd, Vector3 posRes, bool isRelative, int relativeIndex);

	wxString* RemoveObject(int listIndex);

	void ChangeSelected(wxArrayInt intArray);
	wxString* ChangeEnabled(int index);

	wxString* ClearCenterOfMassObjects();

	void Reset();

	void Draw(WxIrrViewport* currentViewport = 0);

	void UpdateCOMPoint();

	void SerializeIn(istream &is);
	void SerializeOut(ostream &os);
};

#endif
