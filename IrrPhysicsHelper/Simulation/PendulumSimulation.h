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

#ifndef _WX_IRR_PENDULUM_SIMULATION
#define _WX_IRR_PENDULUM_SIMULATION

#include "Simulation.h"

class PendulumSimulation : public Simulation
{
private:
	std::string uniformalAccelerationX;
	std::string uniformalAccelerationY;
	std::string uniformalAccelerationZ;
	MathExpression* uniformalAccelerationExprX;
	MathExpression* uniformalAccelerationExprY;
	MathExpression* uniformalAccelerationExprZ;

	int lastNodeIndex;

	void (*ChangeCurrentAccelerationLabel)(float X, float Y, float Z);

public:
	PendulumSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*changeCurrentAccelerationLabel)(float x, float y, float z),
		const char* _uniformalAccelerationX = "0", const char* _uniformalAccelerationY = "-9.8", const char* _uniformalAccelerationZ = "0");
	~PendulumSimulation();

	void AddPendulumSimulationNode(wxString _name, double theta, double phi, double length, float mass);
	void AddPendulumSimulationNode(wxString _name, Vector3 pointer, float mass);
	void AddPendulumSimulationNodeComponents(wxString _name, double X, double Y, double Z, float mass);

	void RemovePendulumSimulationNode(int index);

	void ChangeSelectedColor(wxArrayInt indices);

	void ChangeEquations(std::string _uniformalAccelerationX, std::string _uniformalAccelerationY, std::string _uniformalAccelerationZ);

	void Reset();

	void Update(float timeInSecondsSinceLastFrame, bool ignorePaused = false);
	void UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport);

	void Draw(WxIrrViewport* currentViewport = 0);

	void StartRecording();
	void StopRecording();
};

#endif