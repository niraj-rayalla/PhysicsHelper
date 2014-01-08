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

#ifndef _WX_IRR_KEYBOARD_MANAGER
#define _WX_IRR_KEYBOARD_MANAGER

class WxIrrKeyboardManager
{
public:
	bool upKey;
	bool downKey;
	bool leftKey;
	bool rightKey;

	int count;

	void Reset()
	{
		upKey = false;
		downKey = false;
		leftKey = false;
		rightKey = false;

		count = 0;
	}

	void IncrementCount()
	{
		count++;
	}

	void DecrementCount()
	{
		count--;
	}
};

class WxIrrMouseManager
{
public:
	bool mouseMovedFlag;
	int moveXAmount;
	int moveYAmount;

	void Reset()
	{
		mouseMovedFlag = false;
	}
};

#endif