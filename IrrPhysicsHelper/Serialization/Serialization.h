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

#ifndef WX_IRR_PHYSICS_HELPER_SERIALIZATION
#define WX_IRR_PHYSICS_HELPER_SERIALIZATION

#include <wx/wx.h>
#include "../IrrlichtInclude.h"

#include "../General/GeneralClasses.h"

#include <iostream>
#include <fstream>
using namespace std;

void SerializeOutWxString(ostream& os, wxString& str);
wxString SerializeInWxString(istream& is);

void SerializeOutSColor(ostream& os, SColor& color);
SColor SerializeInSColor(istream& is);

void SerializeOutVector3(ostream& os, Vector3& vec);
Vector3 SerializeInVector3(istream& is);

template <typename  T>
void SerializeOutList(ostream& os, List<T>* list)
{
	os << list->GetSize();
	os << endl;

	//foreach(T, It, list)
	for(typename List<T>::iterator It = list->begin(); It != NULL; It->advance(It))
	{
		T temp = It->GetData();
		os << temp << endl;
	}
}
template <typename  T>
List<T>* SerializeInList(istream& is)
{
	List<T>* list = new List<T>();

	int size = 0;
	is >> size;

	for(int i = 0; i < size; i++)
	{
		T elem;
		is >> elem;

		list->Add(elem);
	}

	return list;
}
template <typename  T>
void SerializeOutListPointer(ostream& os, List<T*>* list)
{
	os << list->GetSize();
	os << endl;

	//foreach(T*, ListIt, list)
	for(typename List<T*>::iterator ListIt = list->begin(); ListIt != NULL; ListIt->advance(ListIt))
	{
		T* temp = ListIt->GetData();
		os << *temp << endl;
	}
}
template <typename  T>
List<T*>* SerializeInListPointer(istream& is)
{
	List<T*>* list = new List<T*>();

	int size = 0;
	is >> size;

	for(int i = 0; i < size; i++)
	{
		T elem;
		is >> elem;
		T* ptrElem = new T(elem);

		list->Add(ptrElem);
	}

	return list;
}


#endif
