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

#include "ThreeDArrowList.h"

ThreeDArrowList::ThreeDArrowList()
{
	arrowList = new List<ThreeDArrow*>();
	verticesSize = 0;
}

ThreeDArrowList::~ThreeDArrowList()
{
	delete arrowList;
	vertices.Clear();
	indices.Clear();
}

void ThreeDArrowList::ChangeColor(SColor& color)
{
	
}

void ThreeDArrowList::Update()
{	
	if (verticesSize / 4 == arrowList->GetSize())
	{
		int j = 0;
		List<irr::core::array<S3DVertex>*>::iterator currentVerticesList = vertices.begin();
		
		irr::core::array<S3DVertex>* currentVerticesArray = currentVerticesList->GetData();
		S3DVertex* currentVerticesArrayPointer = currentVerticesArray->pointer();

		foreach(ThreeDArrow*, arrowIt, arrowList)
		{				
			S3DVertex* vertexPointer = arrowIt->GetData()->GetVerticesPointer();

			int size = currentVerticesArray->size();

			for(int i = 0; i < 4; i++)
			{
				currentVerticesArrayPointer[j++].Pos = vertexPointer[i].Pos;
			}

			if(j == size - 1)
			{
				currentVerticesList->advance(currentVerticesList);

				currentVerticesArray = currentVerticesList->GetData();
				currentVerticesArrayPointer = currentVerticesArray->pointer();

				j = 0;
			}
		}
	}	
}

void ThreeDArrowList::Draw(IVideoDriver* driver)
{
	if (verticesSize / 4 != arrowList->GetSize())
	{
		vertices.Clear();
		indices.Clear();

		verticesSize = arrowList->GetSize() * 4;

		int tempSize = verticesSize;

		List<ThreeDArrow*>::iterator currentArrowIt = arrowList->begin();
		while(tempSize > 65532)
		{
			irr::core::array<S3DVertex>* tempVerticesArray = new irr::core::array<S3DVertex>();
			irr::core::array<u16>* tempIndicesArray = new irr::core::array<u16>();

			tempVerticesArray->reallocate(65532);
			tempIndicesArray->reallocate(65532 / 4 * 6);

			int j = 0;
			int k = 0;
			for(int i = 0; i < 16383; i++)
			{				
				S3DVertex* vertexPointer = currentArrowIt->GetData()->GetVerticesPointer();
				u16* indexPointer = currentArrowIt->GetData()->GetIndicesPointer();

				int size = tempVerticesArray->size();

				for(int l = 0; l < 4; l++)
				{
					tempVerticesArray->push_back(vertexPointer[l]);
				}

				for(int l = 0; l < 6; l++)
				{
					tempIndicesArray->push_back(indexPointer[l] + size);
				}

				currentArrowIt->advance(currentArrowIt);
			}

			vertices.Add(tempVerticesArray);
			indices.Add(tempIndicesArray);

			tempSize -= 65532;
		}

		irr::core::array<S3DVertex>* tempVerticesArray = new irr::core::array<S3DVertex>();
		irr::core::array<u16>* tempIndicesArray = new irr::core::array<u16>();

		tempVerticesArray->reallocate(tempSize);
		tempIndicesArray->reallocate(tempSize / 4 * 6);

		int j = 0;
		int k = 0;
		for(int i = 0; i < tempSize / 4; i++)
		{				
			S3DVertex* vertexPointer = currentArrowIt->GetData()->GetVerticesPointer();
			u16* indexPointer = currentArrowIt->GetData()->GetIndicesPointer();

			int size = tempVerticesArray->size();

			for(int l = 0; l < 4; l++)
			{
				tempVerticesArray->push_back(vertexPointer[l]);
			}

			for(int l = 0; l < 6; l++)
			{
				tempIndicesArray->push_back(indexPointer[l] + size);
			}

			currentArrowIt->advance(currentArrowIt);
		}

		vertices.Add(tempVerticesArray);
		indices.Add(tempIndicesArray);
	}

	List<irr::core::array<u16>*>::iterator currentIndicesList = indices.begin();
	List<irr::core::array<S3DVertex>*>* verticesPointer = &vertices;
	foreach(irr::core::array<S3DVertex>*, vertexArrayIt, verticesPointer)
	{
		S3DVertex* vertexPointer = GetVerticesPointer(vertexArrayIt);
		u16* indexPointer = GetIndicesPointer(currentIndicesList);

		driver->setTransform(video::ETS_WORLD, ThreeDArrow::mat);
		driver->drawVertexPrimitiveList(vertexPointer, vertexArrayIt->GetData()->size(),
			indexPointer, currentIndicesList->GetData()->size() / 2, EVT_STANDARD, EPT_LINES, EIT_16BIT);
		
		currentIndicesList->advance(currentIndicesList);
	}
}

List<ThreeDArrow*>::iterator ThreeDArrowList::Add(ThreeDArrow* arrow)
{
	if(arrow)
	{
		return arrowList->Add(arrow);
	}

	return NULL;
}
List<ThreeDArrow*>::iterator ThreeDArrowList::Add(List<ThreeDArrow*>* _arrowList)
{
	if(_arrowList)
	{
		return arrowList->Append(_arrowList);
	}

	return NULL;
}

void ThreeDArrowList::Remove(List<ThreeDArrow*>::iterator elem, int numToDelete)
{
	arrowList->Remove(elem, numToDelete);
}

S3DVertex* ThreeDArrowList::GetVerticesPointer(List<irr::core::array<S3DVertex>*>::iterator vertexList)
{
	return vertexList->GetData()->pointer();
}

u16* ThreeDArrowList::GetIndicesPointer(List<irr::core::array<u16>*>::iterator indexList)
{
	return indexList->GetData()->pointer();
}