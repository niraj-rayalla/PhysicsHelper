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

#ifndef WX_IRR_EVENT_RECEIVER
#define WX_IRR_EVENT_RECEIVER

#include "IrrlichtInclude.h"
#include "GUI Enviornment/PhysicsHelperGUIEnviornment.h"

enum PhysicsHelperEventType
{
	PHEventType_None,
	PHEventType_Mouse,
	PHEventType_Keyboard
};

class PhysicsHeplerEventHandler : public IEventReceiver
{
private:
	PhysicsHelperGUIEnviornment* physicsHelperGUIEnviornment;
	PhysicsHelperEventType eventType;

public:
	int mouseXMove;
	int mouseYMove;
	bool mouseLeftDown;

	PhysicsHelperEventType GetEventType()
	{
		PhysicsHelperEventType tempEventType = eventType;
		eventType = PHEventType_None;

		return tempEventType;
	}

    virtual bool OnEvent(const SEvent& event)
    {
		switch(event.EventType)
		{

		case EET_MOUSE_INPUT_EVENT:

			switch(event.MouseInput.Event)
			{

			case EMIE_MOUSE_MOVED:
				
				eventType = PHEventType_Mouse;
				mouseXMove = event.MouseInput.X;
				mouseYMove = event.MouseInput.Y;

				return true;

				break;

			case EMIE_LMOUSE_PRESSED_DOWN:
				
				mouseLeftDown = true;

				return false;

				break;

			case EMIE_LMOUSE_LEFT_UP:
				
				mouseLeftDown = false;

				return false;

				break;
			}

			break;

		// Remember whether each key is down or up
		case EET_KEY_INPUT_EVENT:

			eventType = PHEventType_Keyboard;
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			isShiftDown = event.KeyInput.Shift;

			break;

		case EET_GUI_EVENT:
			IGUIElement* elem;

			switch(event.GUIEvent.EventType)
			{

			case EGET_ELEMENT_FOCUSED:

				elem = event.GUIEvent.Caller;
				//if (elem->getType() == EGUIET_STATIC_TEXT)
				if (elem)
				{
					if (elem->getType() != EGUIET_WINDOW)
					{
						IGUIElement* parentElem = elem->getParent();
						if (parentElem && parentElem->getType() == EGUIET_WINDOW)
						{
							elem = parentElem;
						}
						else
						{
							elem = NULL;
						}
					}
				}

				PhysicsHelperGUIEnviornment::focusedGUIElement = elem;
				return true;

				break;

			case EGET_ELEMENT_FOCUS_LOST:

				elem = event.GUIEvent.Element;
				//if (elem->getType() == EGUIET_STATIC_TEXT)
				if (elem)
				{
					if (elem->getType() != EGUIET_WINDOW)
					{
						IGUIElement* parentElem = elem->getParent();
						if (parentElem && parentElem->getType() == EGUIET_WINDOW)
						{
							elem = parentElem;
						}
						else
						{
							elem = NULL;
						}
					}
				}

				PhysicsHelperGUIEnviornment::focusedGUIElement = elem;
				return true;

				break;
				
			case EGET_ELEMENT_CLOSED:
				
				elem = event.GUIEvent.Caller;
				physicsHelperGUIEnviornment->RemoveGUIElement(elem);
				elem->remove();
				return true;

				break;					
			}

			break;
		}

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
            return KeyIsDown[keyCode];
    }
    
	PhysicsHeplerEventHandler(IGUIEnvironment* guiEnv)
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                KeyIsDown[i] = false;

		isShiftDown = false;

		physicsHelperGUIEnviornment = new PhysicsHelperGUIEnviornment(guiEnv);

		eventType = PHEventType_None;
    }

	~PhysicsHeplerEventHandler()
	{
		delete physicsHelperGUIEnviornment;
	}

	PhysicsHelperGUIEnviornment* GetGUIEnvironment()
	{
		return physicsHelperGUIEnviornment;
	}

private:
    //holds the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool isShiftDown;
};

#endif