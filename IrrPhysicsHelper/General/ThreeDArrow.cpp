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

#include "ThreeDArrow.h"

matrix4 ThreeDArrow::mat = matrix4();

void Get3DArrowPositions(Vector3 tail, Vector3 dirWithLength, Vector3& head, Vector3& arrowHead1, Vector3& arrowHead2)
{
	head = tail + dirWithLength;
	
	Vector3 normBackwards = tail - head;
	float length = normBackwards.getLength();
	normBackwards /= length;

	Vector3 arrowHeadDir = length * 0.1f * Vector3(Ceiling(1.0f-abs_(normBackwards.X), 1.0f), Ceiling(1.0f-abs_(normBackwards.Y), 1.0f), Ceiling(1.0f-abs_(normBackwards.Z), 1.0f));
	arrowHead1 = head + arrowHeadDir + normBackwards;
	arrowHead2 = head - arrowHeadDir + normBackwards;
}