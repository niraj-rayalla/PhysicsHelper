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

#include "ChartFrame.h"

BEGIN_EVENT_TABLE(ChartAndDataControl, wxPanel)

	EVT_SIZE(ChartAndDataControl::OnResize)

END_EVENT_TABLE()
//ChartAndDataControl::ChartAndDataControl()
//{
//	chart = NULL;
//	
//	dataGrid = new wxGrid(this, wxID_ANY,wxDefaultPosition, wxSize(150, 450));
//	dataGrid->CreateGrid(0, 0);
//
//	m_mgr.SetManagedWindow(this);
//
//	m_mgr.AddPane(dataGrid, wxAuiPaneInfo().CloseButton(false).Left().PinButton(true).MinimizeButton(true).Name(wxT("dataGrid")));
//	m_mgr.AddPane(new wxWindow(this, wxID_ANY), wxAuiPaneInfo().CenterPane().Name(wxT("chart")));
//
//	m_mgr.Update();
//}
ChartAndDataControl::ChartAndDataControl(wxWindow* parent, wxString& title, Chart* _chart, wxString& xAxisTitle, wxString& yAxisTitle, double* dataX, double* dataY,
	List<wxString>* yNames, int numOfData, int numCols, List<wxChartPanel*>* chartList)
	: wxPanel(parent, wxID_ANY)
{
	chart = _chart;

	dataGrid = new wxGrid(this, wxID_ANY,wxDefaultPosition, wxSize(200, 600));
	dataGrid->SetDefaultColSize(30);
	dataGrid->SetDefaultRowSize(20);
	dataGrid->SetRowLabelSize(60);
	dataGrid->SetEditable(false);
	dataGrid->CreateGrid(numOfData, numCols);
	if (dataX && dataY)
	{
		for(int i = 0; i < numOfData; i++)
		{
			wxString rowString = wxString::Format(wxT("%f"), dataX[i]);
			dataGrid->SetRowLabelValue(i, rowString);
			for(int j = 0; j < numCols; j++)
			{
				wxString cellValue = wxString::Format(wxT("%f"), dataY[i*numCols + j]);
				dataGrid->SetCellValue(i, j, cellValue);
			}
		}
	}

	dataGrid->Connect(wxID_ANY, wxEVT_KEY_DOWN, wxKeyEventHandler(ChartAndDataControl::CopyGridData), (wxObject*) NULL, this);

	m_mgr.SetManagedWindow(this);

	m_mgr.AddPane(dataGrid, wxAuiPaneInfo().CloseButton(false).Left().PinButton(true).MinimizeButton(true).MinSize(150, 150).Name(wxT("dataGrid")));

	if(!chart)
	{
		// first step: create plot
		XYPlot *plot = new XYPlot();

		// create dataset
		XYSimpleDataset *dataset = new XYSimpleDataset();

		int currentSkip = 0;
		double* data = new double[numOfData*2];
		for (int j = 0; j < numOfData; j++)
		{
			data[j*2] = dataX[j];
		}
		for (int i = 0; i < numCols; i++)
		{
			for (int j = 0; j < numOfData; j++)
			{
				data[j*2 + 1] = dataY[j*numCols + currentSkip];
			}

			// and add serie to it
			dataset->AddSerie((double*) data, numOfData);
			dataset->SetSerieName(i, yNames->GetAt(i)->GetData());
			currentSkip++;
		}

		// set line renderer to dataset
		dataset->SetRenderer(new XYLineRenderer());

		// create left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// optional: set axis titles
		leftAxis->SetTitle(yAxisTitle);
		bottomAxis->SetTitle(xAxisTitle);

		// add axes and dataset to plot
		plot->AddObjects(dataset, leftAxis, bottomAxis);

		plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

		// and finally create chart
		chart = new Chart(plot, title);

		delete[] data;

	}
	chartPanel = new wxChartPanel(this, wxID_ANY, chart);
	m_mgr.AddPane(chartPanel, wxAuiPaneInfo().CenterPane().Name(wxT("chart")));
	//m_mgr.AddPane(new wxWindow(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100)), wxAuiPaneInfo().CenterPane().Name(wxT("chart")));

	chartList->Add(chartPanel);

	m_mgr.Update();
}

ChartAndDataControl::~ChartAndDataControl()
{
	m_mgr.UnInit();
}

void ChartAndDataControl::CopyGridData(wxKeyEvent& event)
{
	if ((event.GetUnicodeKey() == 'C') && (event.ControlDown() == true)) 
	{
		wxString copy_data;
		bool something_in_this_line;

		copy_data.Clear();

		for (int i=0; i < dataGrid->GetRows();i++)
		{     
			something_in_this_line = false;   
			for (int j=0; j < dataGrid->GetCols(); j++)
			{ 
				if (dataGrid->IsInSelection(i,j))
				{
					if (something_in_this_line == false)
					{ 
						if (copy_data.IsEmpty() == false)
						{   
							copy_data.Append(wxT("\n")); 
						}
						something_in_this_line = true;
					}
					else
					{                               
						copy_data.Append(wxT("\t")); 
					}
					copy_data = copy_data + dataGrid->GetCellValue(i,j);   
				}
			}
		}

		wxOpenClipboard();         
		wxEmptyClipboard();
		wxSetClipboardData(wxDF_TEXT,copy_data.c_str(),0,0);
		wxCloseClipboard();
	}	
}

void ChartAndDataControl::OnResize(wxSizeEvent& event)
{
	wxSize newSize = event.GetSize();
}





enum
{
    ID_Chart_Exit = 3000,
    ID_Chart_SaveAsImage,
	ID_Chart_Print,
	ID_Chart_ChangeTitle
};

BEGIN_EVENT_TABLE(WxIrrChartWindow, wxFrame)

	EVT_MENU(ID_Chart_Exit, WxIrrChartWindow::OnExit)
	EVT_MENU(ID_Chart_SaveAsImage, WxIrrChartWindow::OnSaveActiveChart)

END_EVENT_TABLE()

WxIrrChartWindow::WxIrrChartWindow(List<ObjectTabStructure*>* tabStructure)
: wxFrame(NULL, wxID_ANY, _("Chart Results"), wxDefaultPosition, wxSize(800, 600))
{
	chartList = new List<List<wxChartPanel*>*>();

	menuBar = new wxMenuBar();

	//File menu
	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(ID_Chart_SaveAsImage, wxT("&Save As Image..."));
	fileMenu->Append(ID_Chart_Print, wxT("&Print Graph"));
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_Chart_Exit, _("E&xit"));
	menuBar->Append(fileMenu, wxT("&File"));

	//Edit menu
	wxMenu* editMenu = new wxMenu();
	editMenu->Append(ID_Chart_ChangeTitle, wxT("Change Graph Title"));
	menuBar->Append(editMenu, wxT("&Edit"));

    SetMenuBar( menuBar );

	m_mgr.SetManagedWindow(this);

	/*List<ObjectTabStructure> objList;

	List<double> timeList;
	timeList.Add(0);
	timeList.Add(1);
	timeList.Add(2);
	timeList.Add(3);
	timeList.Add(4);
	List<double> doubleList;
	doubleList.Add(243);
	doubleList.Add(23);
	doubleList.Add(43);
	doubleList.Add(2342);
	doubleList.Add(12);

	List<wxString> yNames;
	yNames.Add(_("X"));
	yNames.Add(_("Y"));
	yNames.Add(_("Z"));

	List<ObjectPropertyTabStructure*> objPropertyList;
	wxString propName = _("Pos");
	wxString xAxisTitle = _("Time(s)");
	wxString yAxisTitle = _("Position(m)");
	objPropertyList.Add(new ObjectPropertyTabStructure(propName, xAxisTitle, yAxisTitle, &timeList, &doubleList, &yNames));
	yAxisTitle = _("Velocity(m/s)");
	objPropertyList.Add(new ObjectPropertyTabStructure(propName, xAxisTitle, yAxisTitle, &timeList, &doubleList, &yNames));

	List<wxString> stringList;
	stringList.Add(_("Pos"));
	stringList.Add(_("Vel"));

	wxString name = _("Obj1");
	ObjectTabStructure temp(name, &objPropertyList);
	objList.Add(temp);

	temp.objectName = _("Obj2");
	objList.Add(temp);

	temp.objectName = _("Obj3");

	List<Vector3> vectorList;
	vectorList.Add(Vector3(0.0f, 1.0f, 3.0f));
	vectorList.Add(Vector3(2.0f, 12.0f, 3.0f));
	vectorList.Add(Vector3(34.0f, 1.0f, 23.0f));
	vectorList.Add(Vector3(0.0f, 1.0f, 3.0f));
	vectorList.Add(Vector3(0.0f, 1.0f, 3.0f));

	yAxisTitle = _("Force(N)");
	objPropertyList.Add(new ObjectPropertyTabStructure(propName, xAxisTitle, yAxisTitle, &timeList, &vectorList, &yNames));

	objList.Add(temp);

	SetupTabStructure(&objList);*/

	SetupTabStructure(tabStructure);
}

WxIrrChartWindow::~WxIrrChartWindow()
{
	/*delete leftPanel;
	delete rightPanel;*/

	delete chartList;

	m_mgr.UnInit();
}

void WxIrrChartWindow::SetupTabStructure(List<ObjectTabStructure*>* tabStructure)
{
	//m_mgr.DetachPane(leftPanel);
	//leftPanel->GetParent()->RemoveChild(leftPanel);
	//leftPanel->Destroy();

	//m_mgr.AddPane(leftPanel, wxAuiPaneInfo().CloseButton(false).Right().PinButton(true).MinimizeButton(true).Name(wxT("rightPanel")));	
	//m_mgr.GetPane("rightPanel").MinSize(rightPanel->GetSize());
	//m_mgr.GetPane("rightPanel").MaxSize(rightPanel->GetSize());
	////m_mgr.GetPane("rightPanel").MinimizeButton(true).Maximize();
	//m_mgr.Update();
	

	mainTab = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(600, 200), wxNB_DEFAULT);

	foreach(ObjectTabStructure*, structureIt, tabStructure)
	{
		ObjectTabStructure* objectStructure = structureIt->GetData();

		wxNotebook* objectPage = new wxNotebook(mainTab, wxID_ANY, wxDefaultPosition, mainTab->GetClientSize(), wxNB_DEFAULT);
		mainTab->AddPage(objectPage, objectStructure->objectName);

		List<wxChartPanel*>* objectChartList = new List<wxChartPanel*>();

		foreach(ObjectPropertyTabStructure*, structIt, objectStructure->objectPropertyList)
		{
			ObjectPropertyTabStructure* structure = structIt->GetData();
			
			wxString chartTitle = objectStructure->objectName + _(" ") + structure->propertyName;
			objectPage->AddPage((wxWindow*)new ChartAndDataControl(objectPage, chartTitle, NULL, structure->xAxisTitle, structure->yAxisTitle,
				structure->dataX, structure->dataY, structure->yNames, structure->dataSize, structure->numDataPerValue, objectChartList), structure->propertyName);
		}

		chartList->Add(objectChartList);
	}

	m_mgr.AddPane(mainTab, wxAuiPaneInfo().CenterPane().Name(wxT("mainTab")));

	m_mgr.Update();	
}

void WxIrrChartWindow::OnSaveActiveChart(wxCommandEvent& event)
{	
	wxFileDialog dlg(this, wxT("Choose file..."), wxEmptyString, wxEmptyString,
				wxString(wxT("Bitmap (*.bmp)|*.bmp|GIF (*.gif)|*.gif|JPEG (*.jpeg)|*.jpeg|PNG files (*.png)|*.png|TGA (*.tga)|*.tga|TIFF (*.tiff)|*.tiff|XPM (*.xpm)|*.xpm")),
				wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	

	if (dlg.ShowModal()== wxID_OK)
	{
		ChartAndDataControl* selectedChartAndDataPage = (ChartAndDataControl*)((wxNotebook*)mainTab->GetCurrentPage())->GetCurrentPage();
		wxBitmap bitmap = (selectedChartAndDataPage->GetChartPanel())->CopyBackbuffer();

		int fileTypeIndex = dlg.GetFilterIndex();

		switch(fileTypeIndex)
		{
		case 0:
			bitmap.ConvertToImage().SaveFile(dlg.GetPath(), wxBITMAP_TYPE_BMP);
			break;

		case 1:
			bitmap.ConvertToImage().SaveFile(dlg.GetPath(), wxBITMAP_TYPE_GIF);
			break;

		case 2:
			bitmap.ConvertToImage().SaveFile(dlg.GetPath(), wxBITMAP_TYPE_JPEG);
			break;

		case 3:
			bitmap.ConvertToImage().SaveFile(dlg.GetPath(), wxBITMAP_TYPE_PNG);
			break;

		case 4:
			bitmap.ConvertToImage().SaveFile(dlg.GetPath(), wxBITMAP_TYPE_TGA);
			break;

		case 5:
			bitmap.ConvertToImage().SaveFile(dlg.GetPath(), wxBITMAP_TYPE_TIFF);
			break;

		case 6:
			bitmap.ConvertToImage().SaveFile(dlg.GetPath(), wxBITMAP_TYPE_XPM);
			break;
		}
		
	}
}