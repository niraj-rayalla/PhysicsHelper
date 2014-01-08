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

#ifndef _WX_IRR_FORCE
#define _WX_IRR_FORCE

#include "../../IrrlichtInclude.h"
#include "../Physics Object/PhysicsObject.h"

namespace Physics_Engine
{
	enum Force_Types
	{
		Directional,
		Radial,
		Uniformal
	};

	class Force
	{
	private:	
		Force_Types type;
	public:
		Force(Force_Types type_in)
		{
			type = type_in;
		}

		virtual void AddForcetoObject(PhysicsObject& obj) {};
	};

	class DirectionalForce: public Force
    {
	private:
        Vector3 direction;
	public:
		DirectionalForce(Vector3 dir): Force(Directional)
        {
            direction = dir;
        }

        virtual void AddForcetoObject(PhysicsObject& obj)
        {
            obj.AddForce(direction);
        }

		void ChangeDirection(Vector3 dir)
		{
			direction = dir;
		}

		Vector3 GetDirection()
		{
			return direction;
		}
    };

    class RadialForce : public Force
    {
	private:
        Vector3 center;
        float radius;
        float forceMagnitude;
	public:
        RadialForce(Vector3 center_in, float radius_in, float forceMagnitude_in)
            : Force(Radial)
        {
            center = center_in;
            radius = radius_in;
            forceMagnitude = forceMagnitude_in;
        }

        virtual void AddForcetoObject(PhysicsObject& obj)
        {
			if (obj.GetPosition().getDistanceFrom(center) <= radius)
            {
                Vector3 frc = obj.GetPosition() - center;
				frc = frc.normalize();
                frc *= forceMagnitude;

                obj.AddForce(frc);
            }
        }
    };

    class UniformalForce : public Force
    {
	private:
        Vector3 acceleration;
	public:
        UniformalForce(Vector3 acc)
            : Force(Uniformal)
        {
            acceleration = acc;
        }

        virtual void AddForcetoObject(PhysicsObject& obj)
        {
			obj.AddForce(acceleration * obj.GetMass());
        }
    };
	
	class ForceAfter
	{
	public:
		Force* force;
		PhysicsObject* obj;

		ForceAfter()
		{
			force = NULL;
			obj = NULL;
		}
		ForceAfter(Force* _force, PhysicsObject* _obj)
		{
			force = _force;
			obj = _obj;
		}

		~ForceAfter()
		{
			delete force;
		}
	};
}

#endif