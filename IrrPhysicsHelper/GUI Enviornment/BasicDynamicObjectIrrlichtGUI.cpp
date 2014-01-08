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

#include "BasicDynamicObjectIrrlichtGUI.h"
#include <wx/wx.h>

BasicDynamicObjectIrrlichtGUI::BasicDynamicObjectIrrlichtGUI(IGUIEnvironment* guiEnv, const wchar_t* title, float mass, const Vector3& pos, const Vector3& vel, const Vector3& frc)
{
	window = guiEnv->addWindow(irr::core::rect<s32>(0, 0, 105, 160), false, title, 0, 1);

	wxString massStr = wxString::Format(_("%f"), mass);
	wxCStrData data = massStr.c_str();	

	massLabel =	guiEnv->addStaticText(L"Mass:", rect<s32>(5, 20, 35, 40), false, true, window, 10);
	massValue =	guiEnv->addStaticText(data.AsWChar(), rect<s32>(35, 20, 75, 40), false, true, window, 11);

	//Position
	posLabel = guiEnv->addStaticText(L"Pos:", rect<s32>(5, 40, 35, 60), false, true, window, 12);

	posXLabel = guiEnv->addStaticText(L"X:", rect<s32>(35, 40, 45, 60), false, true, window, 13);
	wxString posXStr = wxString::Format(_("%f"), pos.X);
	wxCStrData posXStrData = posXStr.c_str();
	posXValue = guiEnv->addStaticText(posXStrData.AsWChar(), rect<s32>(55, 40, 125, 60), false, true, window, 14);

	posYLabel = guiEnv->addStaticText(L"Y:", rect<s32>(35, 50, 45, 70), false, true, window, 15);
	wxString posYStr = wxString::Format(_("%f"), pos.Y);
	wxCStrData posYStrData = posYStr.c_str();
	posYValue = guiEnv->addStaticText(posYStrData.AsWChar(), rect<s32>(55, 50, 125, 70), false, true, window, 16);

	posZLabel = guiEnv->addStaticText(L"Z:", rect<s32>(35, 60, 45, 80), false, true, window, 17);
	wxString posZStr = wxString::Format(_("%f"), pos.Z);
	wxCStrData posZStrData = posZStr.c_str();
	posZValue = guiEnv->addStaticText(posZStrData.AsWChar(), rect<s32>(55, 60, 125, 80), false, true, window, 18);

	//Velocity
	velLabel = guiEnv->addStaticText(L"Vel:", rect<s32>(5, 80, 35, 100), false, true, window, 19);

	velXLabel = guiEnv->addStaticText(L"X:", rect<s32>(35, 80, 45, 100), false, true, window, 20);
	wxString velXStr = wxString::Format(_("%f"), vel.X);
	wxCStrData velXStrData = velXStr.c_str();
	velXValue = guiEnv->addStaticText(velXStrData.AsWChar(), rect<s32>(55, 80, 125, 100), false, true, window, 21);

	velYLabel = guiEnv->addStaticText(L"Y:", rect<s32>(35, 90, 45, 110), false, true, window, 22);
	wxString velYStr = wxString::Format(_("%f"), vel.Y);
	wxCStrData velYStrData = velYStr.c_str();
	velYValue = guiEnv->addStaticText(velYStrData.AsWChar(), rect<s32>(55, 90, 125, 110), false, true, window, 23);

	velZLabel = guiEnv->addStaticText(L"Z:", rect<s32>(35, 100, 45, 120), false, true, window, 24);
	wxString velZStr = wxString::Format(_("%f"), vel.Z);
	wxCStrData velZStrData = velZStr.c_str();
	velZValue = guiEnv->addStaticText(velZStrData.AsWChar(), rect<s32>(55, 100, 125, 120), false, true, window, 25);

	//Force
	frcLabel = guiEnv->addStaticText(L"Force:", rect<s32>(5, 120, 35, 130), false, true, window, 26);

	frcXLabel = guiEnv->addStaticText(L"X:", rect<s32>(35, 120, 45, 130), false, true, window, 27);
	wxString frcXStr = wxString::Format(_("%f"), frc.X);
	wxCStrData frcXStrData = frcXStr.c_str();
	frcXValue = guiEnv->addStaticText(frcXStrData.AsWChar(), rect<s32>(55, 120, 125, 130), false, true, window, 28);

	frcYLabel = guiEnv->addStaticText(L"Y:", rect<s32>(35, 130, 45, 140), false, true, window, 29);
	wxString frcYStr = wxString::Format(_("%f"), frc.Y);
	wxCStrData frcYStrData = frcYStr.c_str();
	frcYValue = guiEnv->addStaticText(frcYStrData.AsWChar(), rect<s32>(55, 130, 125, 140), false, true, window, 30);

	frcZLabel = guiEnv->addStaticText(L"Z:", rect<s32>(35, 140, 45, 150), false, true, window, 31);
	wxString frcZStr = wxString::Format(_("%f"), frc.Z);
	wxCStrData frcZStrData = frcZStr.c_str();
	frcZValue = guiEnv->addStaticText(frcZStrData.AsWChar(), rect<s32>(55, 140, 125, 150), false, true, window, 32);
}

BasicDynamicObjectIrrlichtGUI::~BasicDynamicObjectIrrlichtGUI()
{
	window->remove();
}

void BasicDynamicObjectIrrlichtGUI::UpdatePosition(Vector3& pos)
{
	wxString posXStr = wxString::Format(_("%f"), pos.X);
	wxCStrData posXStrData = posXStr.c_str();

	wxString posYStr = wxString::Format(_("%f"), pos.Y);
	wxCStrData posYStrData = posYStr.c_str();

	wxString posZStr = wxString::Format(_("%f"), pos.Z);
	wxCStrData posZStrData = posZStr.c_str();

	posXValue->setText(posXStrData.AsWChar());
	posYValue->setText(posYStrData.AsWChar());
	posZValue->setText(posZStrData.AsWChar());
}
void BasicDynamicObjectIrrlichtGUI::UpdateVelocity(Vector3& vel)
{
	wxString velXStr = wxString::Format(_("%f"), vel.X);
	wxCStrData velXStrData = velXStr.c_str();

	wxString velYStr = wxString::Format(_("%f"), vel.Y);
	wxCStrData velYStrData = velYStr.c_str();

	wxString velZStr = wxString::Format(_("%f"), vel.Z);
	wxCStrData velZStrData = velZStr.c_str();

	velXValue->setText(velXStrData.AsWChar());
	velYValue->setText(velYStrData.AsWChar());
	velZValue->setText(velZStrData.AsWChar());
}
void BasicDynamicObjectIrrlichtGUI::UpdateForce(Vector3& frc)
{
	wxString frcXStr = wxString::Format(_("%f"), frc.X);
	wxCStrData frcXStrData = frcXStr.c_str();

	wxString frcYStr = wxString::Format(_("%f"), frc.Y);
	wxCStrData frcYStrData = frcYStr.c_str();

	wxString frcZStr = wxString::Format(_("%f"), frc.Z);
	wxCStrData frcZStrData = frcZStr.c_str();

	frcXValue->setText(frcXStrData.AsWChar());
	frcYValue->setText(frcYStrData.AsWChar());
	frcZValue->setText(frcZStrData.AsWChar());
}