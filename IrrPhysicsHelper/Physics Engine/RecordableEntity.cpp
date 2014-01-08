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

#include "RecordableEntity.h"

RecordableEntityPointer::RecordableEntityPointer(wxString& _typeName, List<wxString>* _yNames)
{
	typeName = _typeName;

	foreach(wxString, nameIt, _yNames)
	{
		yNames.Add(nameIt->GetData());
	}
	//yNames = _yNames;
}
RecordableEntityPointer::~RecordableEntityPointer()
{
	Reset();
}

void RecordableEntityPointer::Record(double time)
{
	timeList.Add(time);
}

ObjectPropertyTabStructure* RecordableEntityPointer::GetChartObjectPropertyStructure(wxString& objectName)
{
	return NULL;
}

void RecordableEntityPointer::Reset()
{
	timeList.Clear();
	yNames.Clear();
}


RecordableEntityFloatPointer::RecordableEntityFloatPointer(wxString& _typeName, List<wxString>* _yNames, float* _dataPointer)
	: RecordableEntityPointer(_typeName, _yNames)
{
	dataPointer = _dataPointer;
}
RecordableEntityFloatPointer::~RecordableEntityFloatPointer()
{
	Reset();
}

void RecordableEntityFloatPointer::Record(double time)
{
	RecordableEntityPointer::Record(time);

	dataList.Add(*dataPointer);
}

List<double>* RecordableEntityFloatPointer::GetPointerToDataList()
{
	return &dataList;
}

ObjectPropertyTabStructure* RecordableEntityFloatPointer::GetChartObjectPropertyStructure(wxString& objectName)
{
	wxString xAxis = _("Time(s)");
	return new ObjectPropertyTabStructure(objectName + typeName, xAxis, typeName, &timeList, &dataList, &yNames);
}

void RecordableEntityFloatPointer::Reset()
{
	RecordableEntityPointer::Reset();

	dataList.Clear();
}


RecordableEntityVector3Pointer::RecordableEntityVector3Pointer(wxString& _typeName, List<wxString>* _yNames, Vector3* _dataPointer)
	: RecordableEntityPointer(_typeName, _yNames)
{
	dataPointer = _dataPointer;
}
RecordableEntityVector3Pointer::~RecordableEntityVector3Pointer()
{
	Reset();
}

void RecordableEntityVector3Pointer::Record(double time)
{
	RecordableEntityPointer::Record(time);

	dataList.Add(*dataPointer);
}

List<Vector3>* RecordableEntityVector3Pointer::GetPointerToDataList()
{
	return &dataList;
}

ObjectPropertyTabStructure* RecordableEntityVector3Pointer::GetChartObjectPropertyStructure(wxString& objectName)
{
	wxString xAxis = _("Time(s)");
	return new ObjectPropertyTabStructure(objectName + typeName, xAxis, typeName, &timeList, &dataList, &yNames);
}

void RecordableEntityVector3Pointer::Reset()
{
	RecordableEntityPointer::Reset();

	dataList.Clear();
}





RecordableEntity::RecordableEntity()
{
	entityPointerList = new List<RecordableEntityPointer*>();
}
RecordableEntity::~RecordableEntity()
{
	delete entityPointerList;
	objPropertyList.Clear();
}

void RecordableEntity::Record(double time)
{
	foreach(RecordableEntityPointer*, dataPointerIt, entityPointerList)
	{
		dataPointerIt->GetData()->Record(time);
	}
}

void RecordableEntity::AddDataToRecord(wxString& typeName, List<wxString>* _yNames, float* dataPointer)
{
	entityPointerList->Add(new RecordableEntityFloatPointer(typeName, _yNames, dataPointer));
}

void RecordableEntity::AddDataToRecord(wxString& typeName, List<wxString>* _yNames, Vector3* dataPointer)
{
	entityPointerList->Add(new RecordableEntityVector3Pointer(typeName, _yNames, dataPointer));
}

void RecordableEntity::ClearRecordings()
{
	foreach(RecordableEntityPointer*, entityIt, entityPointerList)
	{
		entityIt->GetData()->Reset();
	}
	entityPointerList->Clear();
	objPropertyList.Clear();
}

ObjectTabStructure* RecordableEntity::GetObjectTabStructure(wxString& objectName)
{
	if (entityPointerList->GetSize() > 0)
	{
		foreach(RecordableEntityPointer*, entityIt, entityPointerList)
		{
			objPropertyList.Add(entityIt->GetData()->GetChartObjectPropertyStructure(objectName));
		}

		return new ObjectTabStructure(objectName, &objPropertyList);
	}

	return NULL;
}