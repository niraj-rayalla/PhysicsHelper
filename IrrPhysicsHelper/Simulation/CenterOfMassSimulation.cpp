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

#include "CenterOfMassSimulation.h"

CenterOfMassSimulation::CenterOfMassSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine,
		void (*addObjectToListBox)(wxString str, bool enabled),
		void (*changeCOMLabels)(float COMX, float COMY, float COMZ, 
		float totalMass, int numObjects)) : Simulation(dev, _driver, _physicsEngine, SimulationType_CenterOfMass)
{
	centerOfMass = Vector3(0.0f, 0.0f, 0.0f);
	numObjects = 0;
	totalMass = 0.0f;

	objectList = new List<COMSimulationObject*>();
	selectedObjectsIndexes = new List<int>();

	COMPointLeft = Vector3_Zero;
	COMPointRight = Vector3_Zero;
	COMPointTop = Vector3_Zero;
	COMPointBottom = Vector3_Zero;
	COMPointForward = Vector3_Zero;
	COMPointBackward = Vector3_Zero;

	UpdateCOMPoint();

	AddObjectToListBox = addObjectToListBox;
	ChangeCOMLabels = changeCOMLabels;
}

CenterOfMassSimulation::~CenterOfMassSimulation()
{
	delete objectList;
	delete selectedObjectsIndexes;
}

wxString* CenterOfMassSimulation::GetOutputStrings()
{
	wxString* retStrings = new wxString[3];
	
	retStrings[0] = _("{") + wxString::Format("%f", centerOfMass.X) + _(", ") + wxString::Format("%f", centerOfMass.Y) + _(", ") + wxString::Format("%f", centerOfMass.Z) + _("}");
	retStrings[1] = wxString::Format("%f", totalMass);
	retStrings[2] = wxString::Format("%i", numObjects);

	UpdateCOMPoint();

	return retStrings;
}

wxString* CenterOfMassSimulation::AddObject(wxString _name, Vector3 pos, float mass, float radius, bool isRelative, int relativeIndex, bool enabled)
{
	if (isRelative)
	{
		COMSimulationObject* obj = objectList->GetAt(relativeIndex)->GetData();

		pos += obj->position;
	}

	centerOfMass *= totalMass;

	totalMass += mass;

	centerOfMass += pos*mass;
	centerOfMass /= totalMass;

	objectList->Add(new COMSimulationObject(device->getSceneManager()->addSphereSceneNode(radius, 16, 0, numObjects++, pos), _name, pos, mass, radius, enabled), true); 

	UpdateCOMPoint();

	SetUnSaved();

	return GetOutputStrings();
}

wxString* CenterOfMassSimulation::AddObjectUsingEquation(wxString _name, vector3d<std::string> posStrings, std::string mass, std::string radius, Vector3 posBegins, Vector3 posEnds, Vector3 posResolutions, bool isRelative, int relativeIndex)
{
	MathExpression massExpr = MathExpression(mass.c_str(), MathExpression::cartesianMathExpr, 3);
	MathExpression radiusExpr = MathExpression(radius.c_str(), MathExpression::cartesianMathExpr, 3);

	MathExpression posXExpr = MathExpression(posStrings.X.c_str(), MathExpression::cartesianMathExpr, 3);
	MathExpression posYExpr = MathExpression(posStrings.Y.c_str(), MathExpression::cartesianMathExpr, 3);
	MathExpression posZExpr = MathExpression(posStrings.Z.c_str(), MathExpression::cartesianMathExpr, 3);

	//Make sure no errors happen if an axis has a resolution of only 1.
	bool onceXInterval = false;
	bool onceYInterval = false;
	bool onceZInterval = false;

	double posXInterval = 0.0;
	if(posResolutions.X == 1.0)
	{
		posXInterval = 1.0;
		onceXInterval = true;
	}
	else
	{
		posXInterval = (posEnds.X - posBegins.X)/ (posResolutions.X - 1.0);
	}			
	
	double posYInterval = 0.0;
	if(posResolutions.Y == 1.0)
	{
		posYInterval = 1.0;
		onceYInterval = true;
	}
	else
	{
		posYInterval = (posEnds.Y - posBegins.Y)/ (posResolutions.Y - 1.0);
	}

	double posZInterval = 0.0;
	if(posResolutions.Z == 1.0)
	{
		posZInterval = 1.0;
		onceZInterval = true;
	}
	else
	{
		posZInterval = (posEnds.Z - posBegins.Z)/ (posResolutions.Z - 1.0);
	}

	Vector3 relativePos = Vector3_Zero;

	if (isRelative)
	{
		COMSimulationObject* obj = objectList->GetAt(relativeIndex)->GetData();

		relativePos = obj->position;
	}

	double validVarsValue[3] = {0,0,0};

	centerOfMass *= totalMass;

	int tempNumObjects = 1;

	for (float currentX = posBegins.X; currentX <= posEnds.X; currentX += posXInterval)
	{
		validVarsValue[0] = (double)currentX;
		for (float currentY = posBegins.Y; currentY <= posEnds.Y; currentY += posYInterval)
		{
			validVarsValue[1] = (double)currentY;
			for (float currentZ = posBegins.Z; currentZ <= posEnds.Z; currentZ += posZInterval)
			{
				validVarsValue[2] = (double)currentZ;

				double massValue = massExpr.GetValue(validVarsValue);
				double radiusValue = radiusExpr.GetValue(validVarsValue);

				double posXValue = posXExpr.GetValue(validVarsValue);
				double posYValue = posYExpr.GetValue(validVarsValue);
				double posZValue = posZExpr.GetValue(validVarsValue);

				Vector3 posVector = Vector3((float)posXValue, (float)posYValue, (float)posZValue) + relativePos;

				totalMass += (float)massValue;
				centerOfMass += posVector*(float)massValue;

				wxString name = _name + wxString::Format("%i", tempNumObjects++);

				objectList->Add(new COMSimulationObject(device->getSceneManager()->addSphereSceneNode((float)radiusValue, 16, 0, numObjects, posVector), name, posVector, (float)massValue, (float)radiusValue), true); 

				if (onceZInterval)
					break;
			}

			if (onceYInterval)
				break;
		}

		if (onceXInterval)
			break;
	}

	centerOfMass /= totalMass;

	UpdateCOMPoint();

	SetUnSaved();

	return GetOutputStrings();
}

wxString* CenterOfMassSimulation::RemoveObject(int listIndex)
{
	if (numObjects > 1)
	{
		Node<COMSimulationObject*>* objHolder = objectList->GetAt(listIndex);
		COMSimulationObject* objPointer = objHolder->GetData();

		centerOfMass *= totalMass;
		totalMass -= objPointer->mass;
		centerOfMass -= objPointer->mass*objPointer->position;
		centerOfMass /= totalMass;

		//objPointer->node->remove();
		objectList->Remove(objHolder);

		numObjects--;

		UpdateCOMPoint();
	}
	else
	{
		Reset();
	}

	SetUnSaved();

	return GetOutputStrings();
}

void CenterOfMassSimulation::ChangeSelected(wxArrayInt intArray)
{
	foreach(int, intIt, selectedObjectsIndexes)
	{
		objectList->GetAt(intIt->GetData())->GetData()->ChangeColor();
	}
	selectedObjectsIndexes->Clear();

	for(unsigned int i = 0; i < intArray.size(); i++)
	{
		objectList->GetAt(intArray[i])->GetData()->ChangeColor(SColor(255, 255, 255, 0));
		selectedObjectsIndexes->Add(intArray[i]);
	}
}

wxString* CenterOfMassSimulation::ChangeEnabled(int index)
{
	COMSimulationObject* obj = objectList->GetAt(index)->GetData();

	if(obj->enabled)
	{
		if (numObjects > 1)
		{
			//Remove object from calculation
			centerOfMass *= totalMass;
			totalMass -= obj->mass;
			centerOfMass -= obj->mass*obj->position;
			centerOfMass /= totalMass;

			numObjects--;
		}
		else
		{
			centerOfMass = Vector3_Zero;
			numObjects = 0;
			totalMass = 0.0f;

			UpdateCOMPoint();
		}
	}
	else
	{
		//Add object to calculation
		centerOfMass *= totalMass;
		totalMass += obj->mass;
		centerOfMass += obj->mass*obj->position;
		centerOfMass /= totalMass;

		numObjects++;
	}

	obj->ChangeEnabled();

	UpdateCOMPoint();

	SetUnSaved();

	return GetOutputStrings();
}

wxString* CenterOfMassSimulation::ClearCenterOfMassObjects()
{
	Reset();
	UpdateCOMPoint();
	
	SetUnSaved();

	return GetOutputStrings();
}

void CenterOfMassSimulation::Reset()
{
	/*while (List<COMSimulationObject*>::iterator currentElem = objectList->GetHead())
	{
		currentElem->GetData()->node->remove();
		objectList->Remove(currentElem);
	}*/
	objectList->Clear();
	selectedObjectsIndexes->Clear();

	centerOfMass = Vector3_Zero;
	numObjects = 0;
	totalMass = 0.0f;

	COMPointLeft = Vector3_Zero;
	COMPointRight = Vector3_Zero;
	COMPointTop = Vector3_Zero;
	COMPointBottom = Vector3_Zero;
	COMPointForward = Vector3_Zero;
	COMPointBackward = Vector3_Zero;

	SetSaved();
}

void CenterOfMassSimulation::Draw(WxIrrViewport* currentViewport)
{
	Simulation::Draw(currentViewport);

	//Draw center of mass point

	SColor pointColor = SColor(255, 255, 255, 255);

	driver->draw3DLine(COMPointLeft, COMPointRight, pointColor);
	driver->draw3DLine(COMPointTop, COMPointBottom, pointColor);
	driver->draw3DLine(COMPointForward, COMPointBackward, pointColor);
}

void CenterOfMassSimulation::UpdateCOMPoint()
{
	COMPointLeft = centerOfMass - Vector3(2.0f, 0.0f, 0.0f);
	COMPointRight = centerOfMass + Vector3(2.0f, 0.0f, 0.0f);
	COMPointTop = centerOfMass - Vector3(0.0f, 2.0f, 0.0f);
	COMPointBottom = centerOfMass + Vector3(0.0f, 2.0f, 0.0f);
	COMPointForward = centerOfMass - Vector3(0.0f, 0.0f, 2.0f);
	COMPointBackward = centerOfMass + Vector3(0.0f, 0.0f, 2.0f);
}

void CenterOfMassSimulation::SerializeIn(istream &is)
{
	Simulation::SerializeIn(is);

	List<COMSimulationObject*>* tempObjectList = SerializeInListPointer<COMSimulationObject>(is);
	foreach(COMSimulationObject*, objIt, tempObjectList)
	{
		COMSimulationObject* obj = objIt->GetData();
		wxString* tempStrings = AddObject(obj->name, obj->position, obj->mass, obj->radius, false, 0, obj->enabled);
		delete [] tempStrings;
		AddObjectToListBox(obj->name, obj->enabled);
	}

	ChangeCOMLabels(centerOfMass.X, centerOfMass.Y, centerOfMass.Z, totalMass, numObjects);


	delete tempObjectList;
}

void CenterOfMassSimulation::SerializeOut(ostream &os)
{
	Simulation::SerializeOut(os);

	SerializeOutListPointer(os, objectList);
}