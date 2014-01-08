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

#ifndef _WX_IRR_BASIC_MOTION_SIMULATION
#define _WX_IRR_BASIC_MOTION_SIMULATION

#include "Simulation.h"

enum BasicMotionEquationType
{
	BasicMotionEquationType_Position,
	BasicMotionEquationType_Velocity,
	BasicMotionEquationType_Acceleration
};

class BasicMotionTimedEquation
{
private:
	BasicMotionEquationType equationType;
	MathExpression* equationExprX;
	MathExpression* equationExprY;
	MathExpression* equationExprZ; 
	static std::string validVariables[1];

	friend class BasicMotionObject;

public:
	float startTime;
	float endTime;
	char* equationX;
	char* equationY;
	char* equationZ;

	BasicMotionTimedEquation(float _startTime, float _endTime, char* _equationX, char* _equationY, char* _equationZ, BasicMotionEquationType _equationType = BasicMotionEquationType_Acceleration);
	~BasicMotionTimedEquation();

	Vector3 GetValue(double* validVarValues);
};

class BasicMotionObject : public VisiblePhysicsObject
{
public:
	bool global;
	List<BasicMotionTimedEquation*>* motionEquationList;

	BasicMotionObject(wxString _name, float _mass = 1.0f, Vector3 pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 vel = Vector3(0.0f, 0.0f, 0.0f));
	~BasicMotionObject();

	//Add the equation if the time range is distinct.
	bool AddEquation(BasicMotionTimedEquation* eqn);
	void RemoveEquation(int index);

	virtual void Update(float timeInSecondsSinceLastFrame);
	void UpdateEquationValues(double* validVarValues, float totalTime);
};

class BasicMotionObjectSphere : public BasicMotionObject
{
private:
	float radius;

public:
	BasicMotionObjectSphere(irr::scene::ISceneManager *smgr, wxString _name, float _mass, Vector3 pos, Vector3 vel, float _radius);
	~BasicMotionObjectSphere();

	void Update(float timeInSecondsSinceLastFrame);
};

class BasicMotionSimulation : public Simulation
{
private:
	List<BasicMotionTimedEquation*>* globalAccelerationList;
	List<BasicMotionTimedEquation*>* currentGlobalAccelerationList;

public:
	List<BasicMotionObject*>* basicMotionObjectList;

	BasicMotionSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine);
	~BasicMotionSimulation();

	void AddObject(wxString _name, Vector3 pos, Vector3 intVel, float mass);
	void AddObjectUsingEquation(wxString _name, Vector3 pos, Vector3 intVel, float mass);

	void RemoveObject(int listIndex);

	void AddGlobalAcceleration(float startTime, float endTime, char* equationX, char* equationY, char* equationZ);

	void Reset();

	void Update(float timePassedSeconds, bool ignorePaused = false);

	void Draw(WxIrrViewport* currentViewport = 0);
};

#endif