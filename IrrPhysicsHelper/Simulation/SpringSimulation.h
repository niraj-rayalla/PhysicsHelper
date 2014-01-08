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

#ifndef _WX_IRR_SPRING_SIMULATION
#define _WX_IRR_SPRING_SIMULATION

#include "Simulation.h"

class SpringSimulation: public Simulation
{
private:
	const char* uniformalAcceleration;
	MathExpression* uniformalAccelerationExpr;

	int lastNodeIndex;

	List<SpringSceneNode*> springSceneNodeList;

public:
	SpringSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, const char* _uniformalAcceleration = "0");
	~SpringSimulation();

	void AddSpringSimulationNode(wxString _name, double kConstant, float length, float equilibriumLength, float mass);
	void LoadSpringSimulationNode(wxString _name, double kConstant, float length, float equilibriumLength, float mass, Vector3& oldPos, Vector3& vel);

	void RemoveLastSpringSimulationNode();

	void ChangeEquations(const char* _uniformalAcceleration);

	void Reset();

	void Update(float timeInSecondsSinceLastFrame, bool ignorePaused = false);
	void UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport);

	void Draw(WxIrrViewport* currentViewport = 0);

	void StartRecording();
	void StopRecording();

	void SerializeIn(istream& is);
	void SerializeOut(ostream& os);
};

#endif