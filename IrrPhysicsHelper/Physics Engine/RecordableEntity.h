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

#ifndef WX_IRR_RECORDABLE_ENTITY
#define WX_IRR_RECORDABLE_ENTITY

#include "../Include.h"
#include "../UI/ChartFrame/ChartFrame.h"

class RecordableEntityPointer
{
protected:
	wxString typeName;
	List<double> timeList;
	List<wxString> yNames;
public:
	RecordableEntityPointer(wxString& _typeName, List<wxString>* _yNames);
	~RecordableEntityPointer();

	virtual void Record(double time);

	virtual ObjectPropertyTabStructure* GetChartObjectPropertyStructure(wxString& objectName);

	virtual void Reset();
};

class RecordableEntityFloatPointer : public RecordableEntityPointer
{
private:
	float* dataPointer;
	List<double> dataList;
public:
	RecordableEntityFloatPointer(wxString& _typeName, List<wxString>* _yNames, float* _dataPointer);
	~RecordableEntityFloatPointer();

	void Record(double time);

	List<double>* GetPointerToDataList();

	ObjectPropertyTabStructure* GetChartObjectPropertyStructure(wxString& objectName);

	void Reset();
};

class RecordableEntityVector3Pointer : public RecordableEntityPointer
{
private:
	Vector3* dataPointer;
	List<Vector3> dataList;
public:
	RecordableEntityVector3Pointer(wxString& _typeName, List<wxString>* _yNames, Vector3* _dataPointer);
	~RecordableEntityVector3Pointer();
	void Record(double time);
	
	List<Vector3>* GetPointerToDataList();
	ObjectPropertyTabStructure* GetChartObjectPropertyStructure(wxString& objectName);

	void Reset();
};


//Uses pointer to the data and whenever record function is called stores the value of the
//pointer in a list.
class RecordableEntity
{
public:
	List<RecordableEntityPointer*>* entityPointerList;
	List<ObjectPropertyTabStructure*> objPropertyList;

	RecordableEntity();
	~RecordableEntity();

	void Record(double time);

	void AddDataToRecord(wxString& typeName, List<wxString>* _yNames, float* dataPointer);

	void AddDataToRecord(wxString& typeName, List<wxString>* _yNames, Vector3* dataPointer);

	void ClearRecordings();

	ObjectTabStructure* GetObjectTabStructure(wxString& objectName);

};

#endif