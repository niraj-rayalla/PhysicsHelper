Sourceforge Link:
	https://sourceforge.net/projects/t-dphysicssim/
Contact:
	Name: Niraj Rayalla
	email: niraj.rayalla@gmail.com

License of 3-DPhysicsSim is GPLv3 and its contents can be seen in included license.txt

To compile you will have to link 
	Irrlicht (currently using 1.7.3)
	IrrFreeType (2.1.9)
	Bullet (2.8)
	wxWidgets (2.9.3)
	wxFreeChart (1.6)

For example, the way I linked these on the IDE I'm using (Visual C++ Express 2010), is by adding the following
"Include Directories":

C:\Niraj\IrrPhysicsHelper\IrrFreeType\ft219\freetype-2.1.9\include;
C:\Niraj\IrrPhysicsHelper\wxFreeChart\freechart-1.6\freechart\include;
C:\Niraj\IrrPhysicsHelper\wxFreeChart\freechart-1.6\freechart\include\wx;
C:\Niraj\IrrPhysicsHelper\Bullet Physics\bullet-2.80-rev2531\bullet-2.80-rev2531\src;
C:\wxWidgets-2.9.3\include;
C:\wxWidgets-2.9.3\lib\vc_lib\mswud;
C:\Niraj\irrlicht-1.7.3\irrlicht-1.7.3\include;


The following libraries have to be linked:

freetype219.lib
wxcode_msw28ud_freechart.lib
BulletDynamics.lib
BulletCollision.lib
LinearMath.lib
wxmsw29ud_aui.lib
wxmsw29ud_html.lib
wxmsw29ud_adv.lib
wxmsw29ud_core.lib
wxbase29ud_xml.lib
wxbase29ud.lib
wxtiffd.lib
wxjpegd.lib
wxpngd.lib

These libraries are located in the distributions that are downloaded and for Visual C++ to reference them,
I had to add the following "Library Directories":

C:\Niraj\irrlicht-1.7.3\irrlicht-1.7.3\lib\Win32-visualstudio;
C:\Niraj\irrlicht-1.7.3\irrlicht-1.7.3\lib;
C:\Niraj\IrrPhysicsHelper\IrrFreeType\ft219\freetype-2.1.9\objs;
C:\Niraj\rrPhysicsHelper\wxFreeChart\freechart-1.6\freechart\lib\vc_lib;
C:\Niraj\IrrPhysicsHelper\Bullet Physics\bullet-2.80-rev2531\bullet-2.80-rev2531\lib;
C:\wxWidgets-2.9.3\lib\vc_lib




General Info:

There are still quite a lot of bugs and features to implement, so don't be surprised by crashes that occur often depending on
what you're doing. All features that are planned and currently implemented are shown in the sourceforge project page or its wiki page.

There is also very little in the way of documentation and a lot of cleaning needs to be done. I will most likely fix this in
the future, but as of now I'm a little busy and so it won't happen anytime soon.

When the program is setup in a way that movement is done by the WASD controls. Left click dragging for rotating the camera.
Holding down the control button and left clicking on an object allows you to see the object's descriptive values, such as it mass, position and velocity.