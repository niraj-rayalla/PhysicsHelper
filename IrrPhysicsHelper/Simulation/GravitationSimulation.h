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

#ifndef _WX_IRR_GRAVITATION_SIMULATION
#define _WX_IRR_GRAVITATION_SIMULATION

#include "Simulation.h"

class GravitationSimulation : public Simulation
{
private:
	List<int>* selectedObjectsIndexes;

	void (*AddObjectToListBox)(wxString str, bool enabled);
public:
	GravitationSimulation(IrrlichtDevice* dev, IVideoDriver* _driver, PhysicsEngine* _physicsEngine, void (*addObjectToListBox)(wxString str, bool enabled));
	~GravitationSimulation();

	void AddObject(wxString _name, Vector3 pos, Vector3 intVel, float mass, bool isRelative, int relativeIndex, float radius = 1.0f, bool enabled = true);
	void AddObject(wxString _name, std::string mass, std::string radius, vector3d<std::string> posStrings, Vector3 posBegins, Vector3 posEnds, Vector3 posResolutions,
		vector3d<std::string> velStrings, bool isRelative, int relativeIndex, bool enabled = true);
	void RemoveObject(int index);
	void ChangeEnabledState(int index);
	void ChangeSelections(wxArrayInt indices);

	void Reset();

	void Update(float timeInSecondsSinceLastFrame, bool ignorePaused = false);
	void UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport);

	void Draw(WxIrrViewport* currentViewport = 0);

	void StartRecording();
	void StopRecording();

	void SerializeIn(istream &is);
	/*void SerializeOut(ostream &os);*/
};

#endif