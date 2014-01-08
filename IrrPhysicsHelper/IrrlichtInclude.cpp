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

#include "IrrlichtInclude.h"

SColor operator/(SColor& color, int num)
{
	SColor newSColor = color;
	newSColor.setRed(newSColor.getRed() / 2);
	newSColor.setGreen(newSColor.getGreen() / 2);
	newSColor.setBlue(newSColor.getBlue() / 2);

	return newSColor;
}

void DrawTextOnScreenFrom3DPos(Vector3& point, int currentViewportWidth, int currentViewportHeight, rect<s32>& viewportClientArea,
	ISceneManager* customSmgr, IGUIEnvironment* guiEnv, ICameraSceneNode* camera, stringw& text, SColor& color)
{
	vector2d<s32> screenPos = customSmgr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(point, camera);
	dimension2d<u32> textArea = guiEnv->getSkin()->getFont()->getDimension(text.c_str());
	screenPos.X -= textArea.Width / 2;
	screenPos.Y -= textArea.Height / 2;

	screenPos.X *= (float)viewportClientArea.getWidth() / (float)currentViewportWidth;
	screenPos.Y *= (float)viewportClientArea.getHeight() / (float)currentViewportHeight;
	screenPos += viewportClientArea.UpperLeftCorner;

	rect<s32> textRect(screenPos, screenPos + vector2d<s32>(textArea.Width, textArea.Height));

	guiEnv->getSkin()->getFont()->draw(text, textRect, color, false, false, &viewportClientArea);
}