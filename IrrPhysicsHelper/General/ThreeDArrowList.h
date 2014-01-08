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

#ifndef _WX_IRR_3DArrow_LIST
#define _WX_IRR_3DArrow_LIST

#include "ThreeDArrow.h"
#include "GeneralClasses.h"

class ThreeDArrowList
{
private:
	List<irr::core::array<S3DVertex>*> vertices;
	List<irr::core::array<u16>*> indices;

	int verticesSize;

	List<ThreeDArrow*>* arrowList;

public:
	ThreeDArrowList();

	~ThreeDArrowList();

	void ChangeColor(SColor& color);

	void Update();

	void Draw(IVideoDriver* driver);

	//keep the pointer to the arrow stored so that it can be updated.
	List<ThreeDArrow*>::iterator Add(ThreeDArrow* arrow);
	//keep the pointer to the list of arrows stored so that they can be updated.
	List<ThreeDArrow*>::iterator Add(List<ThreeDArrow*>* _arrowList);
	
	void Remove(List<ThreeDArrow*>::iterator elem, int numToDelete = 1);

	S3DVertex* GetVerticesPointer(List<irr::core::array<S3DVertex>*>::iterator vertexList);
	u16* GetIndicesPointer(List<irr::core::array<u16>*>::iterator indexList);
};

#endif