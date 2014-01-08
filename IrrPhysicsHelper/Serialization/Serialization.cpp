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

#include "Serialization.h"

void SerializeOutWxString(ostream& os, wxString& str)
{
	os << str.size() << endl;
	os << str << endl;
}

wxString SerializeInWxString(istream& is)
{
	int size = 0;
	is >> size;
	
	if (size == 0)
		return _("");

	char* str = new char[size+1];
	is >> str;

	wxString retString = wxString(str);
	delete [] str;

	return retString;
}

void SerializeOutSColor(ostream& os, SColor& color)
{
	os << color.getAlpha()<< endl << color.getRed() << endl << color.getGreen() << endl << color.getBlue() << endl;
}
SColor SerializeInSColor(istream& is)
{
	int alpha = 0;
	int red = 0;
	int green = 0;
	int blue = 0;

	is >> alpha;
	is >> red;
	is >> green;
	is >> blue;

	return SColor(alpha, red, green, blue);
}

void SerializeOutVector3(ostream& os, Vector3& vec)
{
	os << vec.X << endl << vec.Y << endl << vec.Z << endl;
}
Vector3 SerializeInVector3(istream& is)
{
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;

	is >> X;
	is >> Y;
	is >> Z;

	return Vector3(X, Y, Z);
}