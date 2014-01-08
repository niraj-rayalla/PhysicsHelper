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

#ifndef _WX_IRR_CHART_WINDOW
#define _WX_IRR_CHART_WINDOW

#include "../../Include.h"
#include "../../WxIrrViewport.h"
#include "../UIInclude.h"
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/filedlg.h>
#include <wx/grid.h>

#include <chart.h>
#include "wx/wxfreechartdefs.h"
#include "wx/chartpanel.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/axis/logarithmicnumberaxis.h>

// for histogram demo
#include <wx/xy/xyhistorenderer.h>

// for area demo
#include <wx/xy/xyarearenderer.h>

// for dynamic dataset
#include <wx/xy/vectordataset.h>

#include <wx/xy/functions/sinefunction.h>

#include <legend.h>

#include <wx/clipbrd.h>

class ObjectPropertyTabStructure
{
public:
	wxString propertyName;
	wxString xAxisTitle;
	wxString yAxisTitle;
	double* dataX;
	double* dataY;
	int dataSize;
	int numDataPerValue;
	List<wxString>* yNames;

	ObjectPropertyTabStructure()
	{
		propertyName = _("");
		xAxisTitle = _("");
		yAxisTitle = _("");
		dataX = NULL;
		dataY = NULL;
		dataSize = 0;
		numDataPerValue = 0;
	}

	ObjectPropertyTabStructure(wxString& _propertyName, wxString& _xAxisTitle, wxString& _yAxisTitle, List<double>* _dataX, List<double>* _dataY, List<wxString>* _yNames)
	{
		propertyName = _propertyName;
		xAxisTitle = _xAxisTitle;
		yAxisTitle = _yAxisTitle;
		yNames = _yNames;
		numDataPerValue = 1;

		dataSize = _dataX->GetSize();
		dataX = new double[dataSize];
		dataY = new double[dataSize];

		int i = 0;
		foreach(double, dataIt, _dataX)
		{
			dataX[i] = dataIt->GetData();
			i++;
		}

		i = 0;
		foreach(double, dataIt, _dataY)
		{
			dataY[i] = dataIt->GetData();
			i++;
		}
	}

	ObjectPropertyTabStructure(wxString& _propertyName, wxString& _xAxisTitle, wxString& _yAxisTitle, List<double>* _dataX, List<Vector3>* _dataY, List<wxString>* _yNames)
	{
		propertyName = _propertyName;
		xAxisTitle = _xAxisTitle;
		yAxisTitle = _yAxisTitle;
		yNames = _yNames;
		numDataPerValue = 3;

		dataSize = _dataX->GetSize();
		dataX = new double[dataSize];
		dataY = new double[dataSize*3];

		int i = 0;
		foreach(double, dataIt, _dataX)
		{
			dataX[i] = dataIt->GetData();
			i++;
		}

		i = 0;
		foreach(Vector3, dataIt, _dataY)
		{
			dataY[i++] = dataIt->GetData().X;
			dataY[i++] = dataIt->GetData().Y;
			dataY[i++] = dataIt->GetData().Z;
		}
	}

	~ObjectPropertyTabStructure()
	{
		delete [] dataX;
		delete [] dataY;
	}
};

class ObjectTabStructure
{
public:
	wxString objectName;
	List<ObjectPropertyTabStructure*>* objectPropertyList;	

	ObjectTabStructure()
	{
		objectName = _("");
		objectPropertyList = NULL;
	}
	~ObjectTabStructure()
	{
	}
	//Uses pointers to the names but doesn't delete them if they were dynamially created.
	ObjectTabStructure(wxString& _objectName, List<ObjectPropertyTabStructure*>* _objectPropertyList)
	{
		objectName = _objectName;
		objectPropertyList = _objectPropertyList;
	}
};

class ChartAndDataControl : wxPanel
{
private:
	wxAuiManager m_mgr;
	Chart* chart;
	wxChartPanel* chartPanel;
	wxGrid* dataGrid;
public:
	//ChartAndDataControl();
	ChartAndDataControl(wxWindow* parent, wxString& title, Chart* _chart, wxString& xAxisTitle, wxString& yAxisTitle, double* dataX, double* dataY,
		List<wxString>* yNames, int numOfData, int numCols, List<wxChartPanel*>* chartList);
	~ChartAndDataControl();

	Chart* GetChart()
	{
		return chart;
	}
	wxChartPanel* GetChartPanel()
	{
		return chartPanel;
	}
	void CopyGridData(wxKeyEvent& event);

	void ChangeChartTitle(wxString& str)
	{
		chart->SetTitle(str);
	}

	void OnResize(wxSizeEvent& event);

	DECLARE_EVENT_TABLE()
};

class WxIrrChartWindow: public wxFrame
{
private:
	wxMenuBar *menuBar;
	wxAuiManager m_mgr;

	wxNotebook* mainTab;
	List<List<wxChartPanel*>*>* chartList;

public:
	WxIrrChartWindow(List<ObjectTabStructure*>* tabStructure);
	~WxIrrChartWindow();

	void SetupTabStructure(List<ObjectTabStructure*>* tabStructure);

	void OnExit(wxCommandEvent& event)
	{
		this->Close(true);
	}
	void OnSaveActiveChart(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

#endif 
