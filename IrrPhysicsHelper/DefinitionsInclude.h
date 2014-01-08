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

#ifndef _WX_IRR_DEFINITIONSINCLUDE
#define _WX_IRR_DEFINITIONSINCLUDE

//Defined Variables

//Platform
#define _WX_IRR_WINDOWS 1
//#define _WX_IRR_LINUX 1
//#define _WX_IRR_MACOS 1

#ifdef _WX_IRR_WINDOWS
	//Link the Irrlicht library.
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(lib, "wxcode_msw28ud_freechart.lib")
	//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifdef _WX_IRR_LINUX
	//Include GTK files
	#include <gtk/gtk.h>
	#include <gtk/gtkwidget.h>
	#include <gdk/gdk.h>
	#include <gdk/gdkx.h>
#endif

#ifdef _WX_IRR_MACOS	
#endif


#endif
