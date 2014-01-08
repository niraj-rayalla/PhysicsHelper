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

#ifndef WX_IRR_IRRLICHT_TO_BULLET_OBJECTS
#define WX_IRR_IRRLICHT_TO_BULLET_OBJECTS

#include "../IrrlichtInclude.h"
#include "PhysicsEngineInclude.h"
#include "../General/GeneralClasses.h"
#include "btBulletDynamicsCommon.h"
#include "../Serialization/Serialization.h"

#include "../GUI Enviornment/BasicDynamicObjectIrrlichtGUI.h"

using namespace Physics_Engine;

//Functions to help conversion from irrlicht to bullet.
btVector3 IrrlichtToBulletVector3(Vector3& input);
Vector3 BulletToIrrlichtVector3(btVector3& input);
Vector3 BulletToIrrlichtVector3(const btVector3& input);

enum ArrowType
{
	ArrowType_Velocity,
	ArrowType_AngularVelocity,
	ArrowType_Acceleration,
	ArrowType_Force
};

enum IrrlichtBulletObjectGenericType
{
	IrrlichtBulletObjectType_None,
	IrrlichtBulletObjectType_Static,
	IrrlichtBulletObjectType_Dynamic
};

enum IrrlichtBulletObjectSpecificType
{
	IrrlichtBulletObjectSpecificType_None = 0,
	IrrlichtBulletObjectSpecificType_Sphere = 1,
	IrrlichtBulletObjectSpecificType_Box = 2,
	IrrlichtBulletObjectSpecificType_Capsule = 3,
	IrrlichtBulletObjectSpecificType_Cone = 4,
	IrrlichtBulletObjectSpecificType_Cylinder = 5,
	IrrlichtBulletObjectSpecificType_StaticGraph = 6
};

class IrrlichtToBulletObjectStorage
{	
public:
	static btDiscreteDynamicsWorld* dynamicsWorld;

	IrrlichtBulletObjectGenericType objType;
	IrrlichtBulletObjectSpecificType specificObjType;

	wxString name;
	ISceneNode* node;

	Vector3 nodePos;
	Vector3 nodeRot;

	List<IrrlichtToBulletObjectStorage*>::iterator listNodePointer;

	List<PhysicsObjectTrackerType*>::iterator physicsObjectTrackerListIt;

	IrrlichtToBulletObjectStorage()
	{
		node = NULL;
		listNodePointer = NULL;
		physicsObjectTrackerListIt = NULL;
	}
	IrrlichtToBulletObjectStorage(wxString _name, ISceneNode* _node = 0)
	{
		objType = IrrlichtBulletObjectType_None;
		specificObjType = IrrlichtBulletObjectSpecificType_None;

		name = _name;
		node = _node;

		listNodePointer = NULL;
		physicsObjectTrackerListIt = NULL;
	}

	virtual ~IrrlichtToBulletObjectStorage()
	{
		if (node)
			node->remove();
	}

	virtual void Update()
	{
	}
	
	virtual void Draw(IVideoDriver* driver)
	{
	}

	wxString GetIrrBullName()
	{
		return name;
	}

	static void SetDynamicWorld(btDiscreteDynamicsWorld* world)
	{
		dynamicsWorld = world;
	}

	virtual void SerializeOut(ostream& os);
	virtual void SerializeIn(istream& is);

	friend ostream& operator<<(ostream& os, IrrlichtToBulletObjectStorage& obj)
	{
		obj.SerializeOut(os);

		return os;
	}
	friend istream& operator>>(istream& is, IrrlichtToBulletObjectStorage& obj)
	{
		obj.SerializeIn(is);

		return is;
	}
};

class IrrlichtToBulletStaticObject : public IrrlichtToBulletObjectStorage
{
public:
	btRigidBody* body;

	IrrlichtToBulletStaticObject()
		: IrrlichtToBulletObjectStorage()
	{
		body = NULL;
	}
	IrrlichtToBulletStaticObject(wxString _name, btRigidBody* _body, ISceneNode* _node)
		: IrrlichtToBulletObjectStorage(_name, _node)
	{
		objType = IrrlichtBulletObjectType_Static;
		specificObjType = IrrlichtBulletObjectSpecificType_None;

		body = _body;
	}

	virtual ~IrrlichtToBulletStaticObject()
	{
		if (body)
		{
			if (body->getMotionState())
			{
				delete body->getMotionState();
			}
			if (dynamicsWorld)
			{
				dynamicsWorld->removeRigidBody(body);
			}
			delete body;
		}
	}
};

class IrrlichtToBulletStaticGraphObject : public IrrlichtToBulletStaticObject
{
public:
	btRigidBody* body;
	ThreeDGraph* graph;

	btTriangleIndexVertexArray* meshInterface;
	int* indexBulletArray;
	btScalar* vertexBulletArray;

	IrrlichtToBulletStaticGraphObject()
		: IrrlichtToBulletStaticObject()
	{
		graph = NULL;
		meshInterface = NULL;
		indexBulletArray = NULL;
		vertexBulletArray = NULL;
	}
	IrrlichtToBulletStaticGraphObject(wxString _name, btRigidBody* _body, ThreeDGraph* _graph, btTriangleIndexVertexArray* _meshInterface, int* _indexBulletArray, btScalar* _vertexBulletArray)
		: IrrlichtToBulletStaticObject(_name, _body, NULL)
	{
		specificObjType = IrrlichtBulletObjectSpecificType_StaticGraph;

		body = _body;
		graph = _graph;

		meshInterface = _meshInterface;
		indexBulletArray = _indexBulletArray;
		vertexBulletArray = _vertexBulletArray;
	}

	virtual ~IrrlichtToBulletStaticGraphObject()
	{
		delete graph;
		node = NULL;

		delete meshInterface;
		delete [] indexBulletArray;
		delete [] vertexBulletArray;
	}

	virtual void SerializeOut(ostream& os)
	{
		IrrlichtToBulletStaticObject::SerializeOut(os);

		os << *graph;
	}
	virtual void SerializeIn(istream& is, IrrlichtDevice* device)
	{
		IrrlichtToBulletStaticObject::SerializeIn(is);

		int graphType = 0;
		is >> graphType;
	
		if (graphType == ThreeDGraph_Rectangular)
		{
			RectangularThreeDGraph rectangularGraph;
			is >> rectangularGraph;
			graph = new RectangularThreeDGraph(rectangularGraph.name, rectangularGraph.equationString.ToAscii(), rectangularGraph.scale, rectangularGraph.lowColor, rectangularGraph.highColor,
				device, rectangularGraph.colorAxis, rectangularGraph.axis, rectangularGraph.graphWidth, rectangularGraph.widthStart, rectangularGraph.widthEnd, 
				rectangularGraph.graphHeight, rectangularGraph.heightStart, rectangularGraph.heightEnd, rectangularGraph.solid, rectangularGraph.enabled);			
		}
		else if (graphType == ThreeDGraph_Cylindrical)
		{
			CylindricalThreeDGraph cylindricalGraph;
			is >> cylindricalGraph;
			graph = new CylindricalThreeDGraph(cylindricalGraph.name, cylindricalGraph.equationString.ToAscii(), cylindricalGraph.scale, cylindricalGraph.lowColor, cylindricalGraph.highColor,
				device, cylindricalGraph.colorAxis,	cylindricalGraph.thetaResolution, cylindricalGraph.thetaStart, cylindricalGraph.thetaEnd, cylindricalGraph.radiusResolution,
				cylindricalGraph.radiusStart, cylindricalGraph.radiusEnd, cylindricalGraph.solid, cylindricalGraph.enabled);
		}
		else if (graphType == ThreeDGraph_Spherical)
		{
			SphericalThreeDGraph sphericalGraph;
			is >> sphericalGraph;
			graph = new SphericalThreeDGraph(sphericalGraph.name, sphericalGraph.equationString.ToAscii(), sphericalGraph.scale, sphericalGraph.lowColor, sphericalGraph.highColor, device,
				sphericalGraph.colorAxis, sphericalGraph.thetaResolution, sphericalGraph.thetaStart, sphericalGraph.thetaEnd, sphericalGraph.phiResolution, sphericalGraph.phiStart,
				sphericalGraph.phiEnd, sphericalGraph.solid, sphericalGraph.enabled);
		}
		else if (graphType == ThreeDGraph_Parametric)
		{
			ParametricThreeDGraph parametricGraph;
			is >> parametricGraph;
			graph = new ParametricThreeDGraph(parametricGraph.name, parametricGraph.xEquationString.ToAscii(), parametricGraph.yEquationString.ToAscii(), parametricGraph.zEquationString.ToAscii(), parametricGraph.scale, 
				parametricGraph.lowColor, parametricGraph.highColor, device, parametricGraph.colorAxis,
				parametricGraph.uResolution, parametricGraph.uStart, parametricGraph.uEnd, parametricGraph.vResolution, parametricGraph.vStart, parametricGraph.vEnd, parametricGraph.solid, parametricGraph.enabled);
		}
	}
};

class IrrlichtToBulletDynamicObject : public IrrlichtToBulletObjectStorage, public PhysicsObject
{
public:
	static bool showVelocity;
	static bool showAngularVelocity;
    static bool showNetAcceleration;
    static bool showNetForce;
	static SColor velocityArrowColor;
	static SColor angularVelocityArrowColor;
	static SColor accelerationArrowColor;
	static SColor forceArrowColor;

	btRigidBody* body;
	
	ThreeDArrow* angularVelocityArrow;
	ThreeDArrow* accelerationArrow;
	ThreeDArrow* forceArrow;

	Vector3 BulletVelocity;
	Vector3 BulletAngularVelocity;

	BasicDynamicObjectIrrlichtGUI* objectGUI;

	IrrlichtToBulletDynamicObject()
		: IrrlichtToBulletObjectStorage(), PhysicsObject()
	{
		body = NULL;
		velocityArrow = NULL;
		angularVelocityArrow = NULL;
		accelerationArrow = NULL;
		forceArrow = NULL;

		objectGUI = NULL;
	}
	IrrlichtToBulletDynamicObject(wxString _name, btRigidBody* _body, ISceneNode* _node, float _mass)
		: IrrlichtToBulletObjectStorage(_name, _node), PhysicsObject()
	{
		objType = IrrlichtBulletObjectType_Dynamic;
		specificObjType = IrrlichtBulletObjectSpecificType_None;

		body = _body;

		if (node)
			position = _node->getPosition();
		mass = _mass;

		delete velocityArrow;

		velocityArrow = NULL;
		angularVelocityArrow = NULL;
		accelerationArrow = NULL;
		forceArrow = NULL;

		if (node)
		{
			SetVelocityArrowVisibility(showVelocity);
			SetAngularVelocityArrowVisibility(showAngularVelocity);
			SetAccelerationArrowVisibility(showNetAcceleration);
			SetForceArrowVisibility(showNetForce);
		}

		objectGUI = NULL;
	}

	virtual ~IrrlichtToBulletDynamicObject()
	{
		if (body)
		{
			if (body->getMotionState())
			{
				delete body->getMotionState();
			}
			if (dynamicsWorld)
			{
				dynamicsWorld->removeRigidBody(body);
			}
			delete body;
		}

		delete angularVelocityArrow;
		delete accelerationArrow;
		delete forceArrow;

		if (objectGUI)
			delete objectGUI;
	}

	virtual void UpdateBulletBody()
	{
		body->applyCentralForce(IrrlichtToBulletVector3(force));
	}

	virtual void Update();
	
	virtual void Draw(IVideoDriver* driver)
	{
		IrrlichtToBulletObjectStorage::Draw(driver);

		if (showVelocity && velocityArrow)
			velocityArrow->Draw(driver);

		if (showAngularVelocity && angularVelocityArrow)
			angularVelocityArrow->Draw(driver);

		if (showNetAcceleration && accelerationArrow)
			accelerationArrow->Draw(driver);

		if (showNetForce && forceArrow)
			forceArrow->Draw(driver);
	}

	void MakeVelocityArrow()
	{
		if (!velocityArrow)
			velocityArrow = new ThreeDArrow(IrrlichtToBulletDynamicObject::velocityArrowColor);
	}

	void MakeAngularVelocityArrow()
	{
		if (!angularVelocityArrow)
			angularVelocityArrow = new ThreeDArrow(IrrlichtToBulletDynamicObject::angularVelocityArrowColor);
	}

	void MakeAccelerationArrow()
	{
		if (!accelerationArrow)
			accelerationArrow = new ThreeDArrow(IrrlichtToBulletDynamicObject::accelerationArrowColor);
	}

	void MakeForceArrow()
	{
		if (!forceArrow)
			forceArrow = new ThreeDArrow(IrrlichtToBulletDynamicObject::forceArrowColor);
	}

	void SetVelocityArrowVisibility(bool visibility)
	{
		showVelocity = visibility;

		if (visibility)
			MakeVelocityArrow();
	}

	void SetAngularVelocityArrowVisibility(bool visibility)
	{
		showAngularVelocity = visibility;

		if (visibility)
			MakeAngularVelocityArrow();
	}

	void SetAccelerationArrowVisibility(bool visibility)
	{
		showNetAcceleration = visibility;

		if (visibility)
			MakeAccelerationArrow();
	}

	void SetForceArrowVisibility(bool visibility)
	{
		showNetForce = visibility;

		if (visibility)
			MakeForceArrow();
	}

	ThreeDArrow* GetVelocityArrow()
	{
		return velocityArrow;
	}

	static void ChangeArrowColors(ArrowType arrowType, SColor& color)
	{
		switch(arrowType)
		{
		case ArrowType_Velocity:
			velocityArrowColor = color;
			break;
		case ArrowType_AngularVelocity:
			angularVelocityArrowColor = color;
			break;
		case ArrowType_Acceleration:
			accelerationArrowColor = color;
			break;
		case ArrowType_Force:
			forceArrowColor = color;
			break;
		}
	}

	void SetObjectGUI(BasicDynamicObjectIrrlichtGUI* _objectGUI)
	{
		objectGUI = _objectGUI;
	}

	virtual void SerializeOut(ostream& os)
	{
		IrrlichtToBulletObjectStorage::SerializeOut(os);
		os << mass << endl;

		BulletVelocity = BulletToIrrlichtVector3(body->getLinearVelocity());
		SerializeOutVector3(os, BulletVelocity);

		BulletAngularVelocity = BulletToIrrlichtVector3(body->getAngularVelocity());
		SerializeOutVector3(os, BulletAngularVelocity);
	}
	virtual void SerializeIn(istream& is)
	{
		IrrlichtToBulletObjectStorage::SerializeIn(is);
		is >> mass;

		BulletVelocity = SerializeInVector3(is);
		BulletAngularVelocity = SerializeInVector3(is);
	}
};

IrrlichtToBulletDynamicObject* CastToDynamicObject(IrrlichtToBulletObjectStorage* obj);

class IrrlichtToBulletDynamicSphereObject : public IrrlichtToBulletDynamicObject
{
public:
	float radius;

	IrrlichtToBulletDynamicSphereObject()
		: IrrlichtToBulletDynamicObject()
	{
	}
	IrrlichtToBulletDynamicSphereObject(wxString _name, btRigidBody* _body, ISceneNode* _node, float _radius, float _mass)
		: IrrlichtToBulletDynamicObject(_name, _body, _node, _mass)
	{
		specificObjType = IrrlichtBulletObjectSpecificType_Sphere;

		radius = _radius;
	}

	virtual void SerializeOut(ostream& os)
	{
		IrrlichtToBulletDynamicObject::SerializeOut(os);
		os << radius << endl;
	}
	virtual void SerializeIn(istream& is)
	{
		IrrlichtToBulletDynamicObject::SerializeIn(is);
		is >> radius;
	}
};

class IrrlichtToBulletDynamicBoxObject : public IrrlichtToBulletDynamicObject
{
public:
	Vector3 scale;

	IrrlichtToBulletDynamicBoxObject()
		: IrrlichtToBulletDynamicObject()
	{
	}
	IrrlichtToBulletDynamicBoxObject(wxString _name, btRigidBody* _body, ISceneNode* _node, Vector3 _scale, float _mass)
		: IrrlichtToBulletDynamicObject(_name, _body, _node, _mass)
	{
		specificObjType = IrrlichtBulletObjectSpecificType_Box;

		scale = _scale;
	}

	virtual void SerializeOut(ostream& os)
	{
		IrrlichtToBulletDynamicObject::SerializeOut(os);
		SerializeOutVector3(os, scale);
	}
	virtual void SerializeIn(istream& is)
	{
		IrrlichtToBulletDynamicObject::SerializeIn(is);
		scale = SerializeInVector3(is);
	}
};

class IrrlichtToBulletDynamicCapsuleObject : public IrrlichtToBulletDynamicObject
{
public:
	float heightFromSphereCenters;
	float radius;

	IrrlichtToBulletDynamicCapsuleObject()
		: IrrlichtToBulletDynamicObject()
	{
	}
	IrrlichtToBulletDynamicCapsuleObject(wxString _name, btRigidBody* _body, ISceneNode* _node, float _heightFromSphereCenters, float _radius, float _mass)
		: IrrlichtToBulletDynamicObject(_name, _body, _node, _mass)
	{
		specificObjType = IrrlichtBulletObjectSpecificType_Capsule;

		heightFromSphereCenters = _heightFromSphereCenters;
		radius = _radius;
	}

	virtual void SerializeOut(ostream& os)
	{
		IrrlichtToBulletDynamicObject::SerializeOut(os);
		os << heightFromSphereCenters << endl;
		os << radius << endl;
	}
	virtual void SerializeIn(istream& is)
	{
		IrrlichtToBulletDynamicObject::SerializeIn(is);
		is >> heightFromSphereCenters;
		is >> radius;
	}
};

class IrrlichtToBulletDynamicConeObject : public IrrlichtToBulletDynamicObject
{
public:
	float height;
	float radius;

	IrrlichtToBulletDynamicConeObject()
		: IrrlichtToBulletDynamicObject()
	{
	}
	IrrlichtToBulletDynamicConeObject(wxString _name, btRigidBody* _body, ISceneNode* _node, float _height, float _radius, float _mass)
		: IrrlichtToBulletDynamicObject(_name, _body, _node, _mass)
	{
		specificObjType = IrrlichtBulletObjectSpecificType_Cone;

		height = _height;
		radius = _radius;
	}

	virtual void SerializeOut(ostream& os)
	{
		IrrlichtToBulletDynamicObject::SerializeOut(os);
		os << height << endl;
		os << radius << endl;
	}
	virtual void SerializeIn(istream& is)
	{
		IrrlichtToBulletDynamicObject::SerializeIn(is);
		is >> height;
		is >> radius;
	}
};

class IrrlichtToBulletDynamicCylinderObject : public IrrlichtToBulletDynamicObject
{
public:
	float height;
	float radius;

	IrrlichtToBulletDynamicCylinderObject()
		: IrrlichtToBulletDynamicObject()
	{
	}
	IrrlichtToBulletDynamicCylinderObject(wxString _name, btRigidBody* _body, ISceneNode* _node, float _height, float _radius, float _mass)
		: IrrlichtToBulletDynamicObject(_name, _body, _node, _mass)
	{
		specificObjType = IrrlichtBulletObjectSpecificType_Cylinder;

		height = _height;
		radius = _radius;
	}

	virtual void SerializeOut(ostream& os)
	{
		IrrlichtToBulletDynamicObject::SerializeOut(os);
		os << height << endl;
		os << radius << endl;
	}
	virtual void SerializeIn(istream& is)
	{
		IrrlichtToBulletDynamicObject::SerializeIn(is);
		is >> height;
		is >> radius;
	}
};






class IrrlichtBulletConstraint
{
protected:
	ISceneNode* node1;
	ISceneNode* node2;

	btTypedConstraint* constraint;

	Vector3 pos1;
	Vector3 pos2;
public:
	List<IrrlichtBulletConstraint*>::iterator listNodePointer;

	IrrlichtBulletConstraint(ISceneNode* _node1 = 0, ISceneNode* _node2 = 0, btTypedConstraint* _constraint = 0)
	{
		node1 = _node1;
		node2 = _node2;

		constraint = _constraint;

		listNodePointer = NULL;
	}

	~IrrlichtBulletConstraint()
	{
		delete constraint;
	}

	virtual void Draw(IVideoDriver* driver)
	{
		if (node1)
			pos1 = node1->getPosition();

		if (node2)
			pos2 = node2->getPosition();

		driver->draw3DLine(pos1, pos2, SColor(255, 0, 0, 0));
	}

	virtual ISceneNode* GetNode1()
	{
		return node1;
	}

	virtual ISceneNode* GetNode2()
	{
		return node2;
	}

	virtual void SetNode2(ISceneNode* _node2)
	{
		node2 = _node2;
	}

	virtual void SetPosition1(Vector3& position)
	{
		pos1 = position;
	}

	virtual void SetPosition2(Vector3& position)
	{
		pos2 = position;
	}

	Vector3 GetPosition1()
	{
		return pos1;
	}

	Vector3 GetPosition2()
	{
		return pos2;
	}

	virtual void SetConstraint(btTypedConstraint* _constraint)
	{
		constraint = _constraint;
	}

	btTypedConstraint* GetConstraint()
	{
		return constraint;
	}
};

class IrrlichtBulletHingeConstraint : public IrrlichtBulletConstraint
{
private:
	Vector3 axis;

public:
	IrrlichtBulletHingeConstraint(ISceneNode* _node1 = 0, ISceneNode* _node2 = 0, btTypedConstraint* _constraint = 0)
		: IrrlichtBulletConstraint(_node1, _node2, _constraint)
	{
		axis = Vector3_Zero;
	}

	void Draw(IVideoDriver* driver)
	{
		driver->draw3DLine(pos1, pos2, SColor(255, 0, 0, 0));
		driver->draw3DLine(pos2 - axis, pos2 + axis, SColor(255, 255, 255, 255));
	}

	void SetAxis(Vector3& _axis)
	{
		axis = _axis;
	}
};

class IrrlichtBulletSpring
{
public:
	SpringSceneNode* node;
	List<Physics_Engine::Spring*>::iterator springListElem;
	float k;

	IrrlichtBulletSpring(SpringSceneNode* _node, float _k, List<Physics_Engine::Spring*>::iterator _springListElem)
	{
		node = _node;
		k = _k;

		springListElem = _springListElem;
	}

	~IrrlichtBulletSpring()
	{
		if(node)
			node->remove();
	}
};


#endif