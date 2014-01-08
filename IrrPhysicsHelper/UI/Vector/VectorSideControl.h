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

///-----------------------------------------------------------------
///
/// @file      VectorAdditionPanel.h
/// @author    niraj
/// Created:   7/5/2012 10:11:22 PM
/// @section   DESCRIPTION
///            VectorAdditionPanel class declaration
///
///------------------------------------------------------------------

#ifndef WX_IRR_VECTOR_PANEL
#define WX_IRR_VECTOR_PANEL

#include <wx/wx.h>
#include "../SimulationSideControl.h"
#include "VectorAddDialog.h"


class VectorPanel : public SimulationPanel
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		VectorPanel(wxWindow *parent, void (*addPolarVector)(float length, float theta, float phi),
			void (*addRectangularVector)(float X, float Y, float Z),
			void (*removeVector)(int index),
			void (*clearVectors)(void),
			void (*changeLineUpOrientation)(void),
			void (*changeSelection)(wxArrayInt intArray),
			wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(305,357));
		virtual ~VectorPanel();
		void AddVectorClick(wxCommandEvent& event);
		void RemoveVectorClick(wxCommandEvent& event);
		void ClearVectorsClick(wxCommandEvent& event);
		void LineUpVectorsClick(wxCommandEvent& event);
		void VectorListBoxSelected(wxCommandEvent& event);

		void (*AddPolarVector)(float length, float theta, float phi);
		void (*AddRectangularVector)(float X, float Y, float Z);
		void (*RemoveVectorFunction)(int index);
		void (*ClearVectorsFunction)(void);
		void (*ChangeLineUpOrientation)(void);
		void (*ChangeSelection)(wxArrayInt intArray);

		void AddObjectToListBox(wxString str);
		void Reset();
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxListBox *VectorListBox;
		wxCheckBox *LineUpVectors;
		wxButton *ClearVectors;
		wxButton *RemoveVector;
		wxButton *AddVector;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_LINEUPVECTORS = 1029,
			ID_CLEARVECTORS = 1028,
			ID_VECTORLISTBOX = 1027,
			ID_REMOVEVECTOR = 1026,
			ID_ADDVECTOR = 1025
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		int vectorListBoxCount;
};

#endif
