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

#include "PlaygroundSimulation.h"

PlaygroundSimulation::PlaygroundSimulation(irr::IrrlichtDevice *dev, irr::video::IVideoDriver *_driver, Physics_Engine::PhysicsEngine *_physicsEngine, void (*addObjectToListBox)(wxString& str))
	:Simulation(dev, _driver, _physicsEngine, SimulationType_Playground)
{
	physicsEngine->DisablePositionUpdating();
	physicsEngine->DisableSerialization();

	irrToBullConnector = new IrrlichtToBulletConnector();
	mouseAddObjectType = MouseAddObjectType_CapsuleOrSphere;

	AddObjectToListBox = addObjectToListBox;

	showXZGrid();
	/*showXYGrid();
	showYZGrid();*/

	objectCount = 0;
	springCount = 0;
	constraintCount = 0;

	AddBoxObject(_("TSE2"), Vector3(0, -15, 0), Vector3_Zero, Vector3_Zero, Vector3_Zero, Vector3(90.0f, 5.0f, 90.0f), 0.0f);
	//AddSphereObject(_("TSE2"), Vector3(0, 65, 0), Vector3_Zero, Vector3_Zero, Vector3_Zero, 5.0f, 1.0f);
	//AddSphereObject(_("TSE"), Vector3(0, 60, 0), Vector3_Zero, 5.0f, 0.0f);
	/*AddSphereObject(_("TSE"), Vector3(-16, 10, 0), Vector3_Zero, 5.0f, 1.0f);
	AddSphereObject(_("TSE"), Vector3(20, 10, 0), Vector3_Zero, 5.0f, 1.0f);*/

	//AddCylinderObject(_("ASDF"), Vector3(-8, 30, 0), Vector3_Zero, 5.0f, 10.0f, 1.0f);

	//btTransform trans = btTransform();
	//trans.setIdentity();
	//trans.setOrigin(btVector3(0,0,0));
	//btRigidBody* bod = irrToBullConnector->objectList->GetTail()->GetData()->body;
	//btRigidBody* bod2 = irrToBullConnector->objectList->GetTail()->prev->GetData()->body;
	//trans.setOrigin(bod->getWorldTransform().getOrigin());
	//btGeneric6DofConstraint* constraintGeneric = new btGeneric6DofConstraint((*bod), (*bod2), trans, trans, true);
	//constraintGeneric->setLimit(0, 0.0f, 0.0f);
	//constraintGeneric->setLimit(1, 0.0f, 0.0f);
	//constraintGeneric->setLimit(2, 0.0f, 0.0f);
	////irrToBullConnector->AddConstraint(constraintGeneric);

	//btHingeConstraint* hinge = new btHingeConstraint((*bod), *(bod2), btVector3(-20,0,0), btVector3(0,0,0), btVector3(1, 0, 0), btVector3(1, 0, 0), true);
	//hinge->setLimit(0.0f, 3.14f);
	//hinge->enableAngularMotor(true, 1.0f, 5.0f);
	///*hinge->setMotorTarget(3.14f, 5.0f);
	//hinge->enableMotor(true);*/

	//irrToBullConnector->AddConstraint(hinge);

	/*AddConeObject(_("TSE2"), Vector3(0.0f, 30.0f, 0.0f), Vector3_Zero, 5.0f, 5.0f, 1.0f);

	AddCapsuleObject(_("TSE2"), Vector3(20.0f, 30.0f, 0.0f), Vector3_Zero, 5.0f, 5.0f, 1.0f);*/


	//wxString yequation = _("y");
	//MathExpression mathExpr = MathExpression("y", MathExpression::cartesianMathExpr, 3);
	//double validVarsValue[3] = {0,0,0};

	//double yValue;
	//for (double y = 0.0; y <= 30.0; y+=3.0)
	//{
	//	validVarsValue[1] = y;
	//	for (double x = 0.0; x <= 15.0; x+=3.0)
	//	{
	//		validVarsValue[0] = x;
	//		//for (double z = 0.0; z <= 15.0; z+=3)
	//		{
	//			validVarsValue[2] = 1.0;
	//			//yValue = mathExpr.GetValue(validVarsValue);

	//			AddCubeObject(_("asdfasd"), Vector3((float)x, (float)y, (float)10.0f), Vector3_Zero, Vector3_Zero, 1.0f, 1.0f);
	//		}
	//	}
	//}

	/*AddBoxObject(_("SDF"), Vector3(0.0f, 50.0f, 0.0f), Vector3_Zero, Vector3_Zero, Vector3(3.0f, 10.0f, 4.0f), 1.0f);
	AddBoxObject(_("SDF"), Vector3(10.0f, 35.0f, 0.0f), Vector3_Zero, Vector3_Zero, Vector3(3.0f, 10.0f, 4.0f), 1.0f);
	btHingeConstraint* hinge = new btHingeConstraint(*(irrToBullConnector->objectList->GetTail()->prev->GetData()->body), *(irrToBullConnector->objectList->GetTail()->GetData()->body),
		btVector3(6.5f, -7.5f, 0.0f), btVector3(-3.5f, 7.5f, 0.0f), btVector3(1.0f, 0.0f, 0.0f), btVector3(1.0f, 0.0f, 0.0f));
	btHingeConstraint* hinge2 = new btHingeConstraint(*(irrToBullConnector->objectList->GetTail()->prev->GetData()->body),
		btVector3(0.0f, 7.5f, 0.0f), btVector3(1.0f, 0.0f, 0.0f));*/

	/*irrToBullConnector->AddConstraint(hinge);
	irrToBullConnector->AddConstraint(hinge2);*/

	ShowVelocityArrow();
	ShowForceArrow();

	tempSpringSceneNode = NULL;
	tempConstraint = NULL;

	recordingObjects = new List<IrrlichtToBulletDynamicObject*>();
}

PlaygroundSimulation::~PlaygroundSimulation()
{
	physicsEngine->EnablePositionUpdating();
	physicsEngine->EnableSerialization();

	delete irrToBullConnector;
	if (tempSpringSceneNode)
		tempSpringSceneNode->remove();

	delete recordingObjects;
}

void PlaygroundSimulation::Reset()
{
	Simulation::Reset();

	device->getSceneManager()->clear();
	irrToBullConnector->Reset();

	tempSpringSceneNode = NULL;
	tempConstraint = NULL;

	if (tempSpringSceneNode)
		tempSpringSceneNode->remove();

	recordingObjects->Clear();

	objectCount = 0;
	springCount = 0;
	constraintCount = 0;
}

void PlaygroundSimulation::AddSphereObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float radius, float mass)
{
	if (name == _(""))
	{
		objectCount++;
		name = _("Object")+wxString::Format(_("%i"), objectCount);
	}

	btVector3 localInertia(0,0,0);
	btCollisionShape* sphereShape = new btSphereShape(radius);
	irrToBullConnector->AddCustomCollisionShape(sphereShape);
	if (mass > 0.0f)
		sphereShape->calculateLocalInertia(mass, localInertia);

	btTransform startTransform;
	startTransform.setIdentity();

	startTransform.setOrigin(IrrlichtToBulletVector3(pos));

	btDefaultMotionState* objMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, objMotionState, sphereShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	body->setLinearVelocity(IrrlichtToBulletVector3(vel));
	body->setAngularVelocity(IrrlichtToBulletVector3(angVel));
	
	IMeshSceneNode* sphereNode = device->getSceneManager()->addSphereSceneNode(radius);
	sphereNode->setPosition(pos);
	sphereNode->setRotation(rot*RADTODEG);

	ITriangleSelector* selector = device->getSceneManager()->createTriangleSelector(sphereNode->getMesh(), sphereNode);
	sphereNode->setTriangleSelector(selector);
	selector->drop();

	IrrlichtToBulletDynamicSphereObject* sphereObj = new IrrlichtToBulletDynamicSphereObject(name, body, sphereNode, radius, mass);

	irrToBullConnector->AddRigidBody(sphereObj, physicsEngine);

	AddObjectToListBox(name);
}

void PlaygroundSimulation::AddBoxObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, Vector3 scale, float mass)
{
	if (name == _(""))
	{
		objectCount++;
		name = _("Object")+wxString::Format(_("%i"), objectCount);
	}

	btVector3 localInertia(0,0,0);
	btCollisionShape* cubeShape = new btBoxShape(btVector3(scale.X, scale.Y, scale.Z));
	irrToBullConnector->AddCustomCollisionShape(cubeShape);
	if (mass > 0.0f)
		cubeShape->calculateLocalInertia(mass, localInertia);

	btTransform startTransform;
	startTransform.setIdentity();

	startTransform.setOrigin(IrrlichtToBulletVector3(pos));
	btQuaternion quat;
	quat.setEulerZYX(rot.Z, rot.Y, rot.X);
	startTransform.setRotation(quat);

	btDefaultMotionState* objMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, objMotionState, cubeShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	body->setLinearVelocity(IrrlichtToBulletVector3(vel));
	body->setAngularVelocity(IrrlichtToBulletVector3(angVel));
	
	IMeshSceneNode* cubeNode = device->getSceneManager()->addCubeSceneNode(1.0f);
	cubeNode->setScale(Vector3(2.0f*scale.X, 2.0f*scale.Y, 2.0f*scale.Z));
	cubeNode->setPosition(pos);
	cubeNode->setRotation(rot*RADTODEG);
	cubeNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	ITriangleSelector* selector = device->getSceneManager()->createTriangleSelector(cubeNode->getMesh(), cubeNode);
	cubeNode->setTriangleSelector(selector);
	selector->drop();

	IrrlichtToBulletDynamicBoxObject* boxObj = new IrrlichtToBulletDynamicBoxObject(name, body, cubeNode, scale, mass);

	irrToBullConnector->AddRigidBody(boxObj, physicsEngine);

	AddObjectToListBox(name);
}


void PlaygroundSimulation::AddCubeObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float scale, float mass)
{
	AddBoxObject(name, pos, rot, vel, angVel, Vector3(scale, scale, scale), mass);
}

void PlaygroundSimulation::AddCapsuleObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float radius, float heightFromSphereCenters, float mass)
{
	btVector3 localInertia(0,0,0);
	btCollisionShape* capsuleShape = new btCapsuleShape(radius, heightFromSphereCenters);
	irrToBullConnector->AddCustomCollisionShape(capsuleShape);
	if (mass > 0.0f)
		capsuleShape->calculateLocalInertia(mass, localInertia);

	btTransform startTransform;
	startTransform.setIdentity();

	startTransform.setOrigin(IrrlichtToBulletVector3(pos));

	btDefaultMotionState* objMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, objMotionState, capsuleShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	body->setLinearVelocity(IrrlichtToBulletVector3(vel));
	body->setAngularVelocity(IrrlichtToBulletVector3(angVel));
	
	IMeshSceneNode* capsuleNode = customSceneNodeManager->CreateCapsuleSceneNode(device->getSceneManager(), -1, SColor(255, 255, 255, 255), 10, radius, heightFromSphereCenters);
	capsuleNode->setPosition(pos);
	capsuleNode->setRotation(rot*RADTODEG);

	ITriangleSelector* selector = device->getSceneManager()->createTriangleSelector(capsuleNode->getMesh(), capsuleNode);
	capsuleNode->setTriangleSelector(selector);
	selector->drop();

	IrrlichtToBulletDynamicCapsuleObject* capsuleObj = new IrrlichtToBulletDynamicCapsuleObject(name, body, capsuleNode, heightFromSphereCenters, radius, mass);

	irrToBullConnector->AddRigidBody(capsuleObj, physicsEngine);

	objectCount++;
	AddObjectToListBox(_("Object")+wxString::Format(_("%i"), objectCount));
}

void PlaygroundSimulation::AddConeObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float radius, float height, float mass)
{
	if (name == _(""))
	{
		objectCount++;
		name = _("Object")+wxString::Format(_("%i"), objectCount);
	}

	btVector3 localInertia(0,0,0);
	btCollisionShape* coneShape = new btConeShape(radius, height);
	irrToBullConnector->AddCustomCollisionShape(coneShape);
	if (mass > 0.0f)
		coneShape->calculateLocalInertia(mass, localInertia);

	btTransform startTransform;
	startTransform.setIdentity();

	startTransform.setOrigin(IrrlichtToBulletVector3(pos));

	btDefaultMotionState* objMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, objMotionState, coneShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	body->setLinearVelocity(IrrlichtToBulletVector3(vel));
	body->setAngularVelocity(IrrlichtToBulletVector3(angVel));
	
	IMeshSceneNode* coneNode = customSceneNodeManager->CreateConeSceneNode(device->getSceneManager(), -1, SColor(255, 255, 255, 255), 10, radius, height);
	coneNode->setPosition(pos);
	coneNode->setRotation(rot*RADTODEG);
	coneNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	ITriangleSelector* selector = device->getSceneManager()->createTriangleSelector(coneNode->getMesh(), coneNode);
	coneNode->setTriangleSelector(selector);
	selector->drop();

	IrrlichtToBulletDynamicConeObject* coneObj = new IrrlichtToBulletDynamicConeObject(name, body, coneNode, height, radius, mass);

	irrToBullConnector->AddRigidBody(coneObj, physicsEngine);

	AddObjectToListBox(name);
}

void PlaygroundSimulation::AddCylinderObject(wxString name, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float radius, float height, float mass)
{
	if (name == _(""))
	{
		objectCount++;
		name = _("Object")+wxString::Format(_("%i"), objectCount);
	}

	btVector3 localInertia(0,0,0);
	btCollisionShape* cylinderShape = new btCylinderShape(btVector3(radius, height / 2.0f, radius));
	irrToBullConnector->AddCustomCollisionShape(cylinderShape);
	if (mass > 0.0f)
		cylinderShape->calculateLocalInertia(mass, localInertia);

	btTransform startTransform;
	startTransform.setIdentity();

	startTransform.setOrigin(IrrlichtToBulletVector3(pos));

	btDefaultMotionState* objMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, objMotionState, cylinderShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	body->setLinearVelocity(IrrlichtToBulletVector3(vel));
	body->setAngularVelocity(IrrlichtToBulletVector3(angVel));
	
	//ISceneNode* cylinderNode = new CylinderSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), -1, SColor(255, 255, 255, 255), 10, radius, height);
	IMeshSceneNode* cylinderNode = customSceneNodeManager->CreateCylinderSceneNode(device->getSceneManager(), -1, SColor(255, 255, 255, 255), 10, radius, height);
	cylinderNode->setPosition(pos);
	cylinderNode->setRotation(rot*RADTODEG);

	ITriangleSelector* selector = device->getSceneManager()->createTriangleSelector(cylinderNode->getMesh(), cylinderNode);
	cylinderNode->setTriangleSelector(selector);
	selector->drop();

	IrrlichtToBulletDynamicCylinderObject* cylinderObj = new IrrlichtToBulletDynamicCylinderObject(name, body, cylinderNode, height, radius, mass);

	irrToBullConnector->AddRigidBody(cylinderObj, physicsEngine);

	AddObjectToListBox(name);
}

void PlaygroundSimulation::AddFromFileObject(wxString name, wxString filename, Vector3 pos, Vector3 rot, Vector3 vel, Vector3 angVel, float scale, float mass)
{

}

void PlaygroundSimulation::Update(float timeInSecondsSinceLastFrame, bool ignorePaused)
{
	if (isRecording && isRecordingFirstFrame)
	{
		irrToBullConnector->Record(totalTime, isRecording, recordingObjects);
		isRecordingFirstFrame = false;
	}

	Simulation::Update(timeInSecondsSinceLastFrame, ignorePaused);
}

void PlaygroundSimulation::UpdateAfter(float timeInSecondsSinceLastFrame, WxIrrViewport* viewport)
{
	if (!simulationPaused)
	{
		irrToBullConnector->Update(totalTime, timeInSecondsSinceLastFrame, isRecording, recordingObjects);

		Simulation::UpdateAfter(timeInSecondsSinceLastFrame, viewport);
	}
}

void PlaygroundSimulation::Draw(WxIrrViewport* currentViewport)
{
	Simulation::Draw(currentViewport);

	driver->setMaterial(basicMaterial);
	irrToBullConnector->Draw(driver);

	if (tempConstraint)
		tempConstraint->Draw(driver);
}

void PlaygroundSimulation::DrawNames(WxIrrViewport* currentViewport)
{
	rect<irr::s32> currentViewportWholeArea = viewportManager->GetRootViewport()->GetIrrArea();
	rect<irr::s32> currentViewportClientArea = currentViewport->GetIrrClientArea();

	driver->setViewPort(currentViewportWholeArea);

	stringw text = L"";
	foreach(IrrlichtToBulletObjectStorage*, objIt, irrToBullConnector->objectList)
	{
		IrrlichtToBulletObjectStorage* currentObj = objIt->GetData();
		text = currentObj->GetIrrBullName().ToStdWstring().c_str();

		Vector3 nodePos = currentObj->node->getPosition();
		
		DrawTextOnScreenFrom3DPos(nodePos, currentViewportWholeArea.getWidth(), currentViewportWholeArea.getHeight(), currentViewportClientArea, device->getSceneManager(),
			guiEnv, currentViewport->GetCamera(), text, SColor(255, 0, 0, 255));
	}	

	driver->setViewPort(currentViewportClientArea);
}

void PlaygroundSimulation::ShowVelocityArrow()
{
	Simulation::ShowVelocityArrow();
	irrToBullConnector->SetVisibilityVelocityArrow(true);
}
void PlaygroundSimulation::ShowAngularVelocityArrow()
{
	Simulation::ShowAngularVelocityArrow();
	irrToBullConnector->SetVisibilityAngularVelocityArrow(true);
}
void PlaygroundSimulation::ShowAccelerationArrow()
{
	Simulation::ShowAccelerationArrow();
	irrToBullConnector->SetVisibilityAccelerationArrow(true);
}
void PlaygroundSimulation::ShowForceArrow()
{
	Simulation::ShowForceArrow();
	irrToBullConnector->SetVisibilityForceArrow(true);
}

void PlaygroundSimulation::HideVelocityArrow()
{
	Simulation::HideVelocityArrow();
	irrToBullConnector->SetVisibilityVelocityArrow(false);
}
void PlaygroundSimulation::HideAngularVelocityArrow()
{
	Simulation::HideAngularVelocityArrow();
	irrToBullConnector->SetVisibilityAngularVelocityArrow(false);
}
void PlaygroundSimulation::HideAccelerationArrow()
{
	Simulation::HideAccelerationArrow();
	irrToBullConnector->SetVisibilityAccelerationArrow(false);
}
void PlaygroundSimulation::HideForceArrow()
{
	Simulation::HideForceArrow();
	irrToBullConnector->SetVisibilityForceArrow(false);
}

void PlaygroundSimulation::ChangeVelocityArrowColor(SColor& color)
{
	Simulation::ChangeVelocityArrowColor(color);
	irrToBullConnector->ChangeVelocityArrowColor(color);
}
void PlaygroundSimulation::ChangeAngularVelocityArrowColor(SColor& color)
{
	Simulation::ChangeAngularVelocityArrowColor(color);
	irrToBullConnector->ChangeAngularVelocityArrowColor(color);
}
void PlaygroundSimulation::ChangeAccelerationArrowColor(SColor& color)
{
	Simulation::ChangeAccelerationArrowColor(color);
	irrToBullConnector->ChangeAccelerationArrowColor(color);
}
void PlaygroundSimulation::ChangeForceArrowColor(SColor& color)
{
	Simulation::ChangeForceArrowColor(color);
	irrToBullConnector->ChangeForceArrowColor(color);
}

void PlaygroundSimulation::StartSphereMouseAdd() 
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_CapsuleOrSphere;
		StartMouseCheck();
	}
}
void PlaygroundSimulation::StartCubeMouseAdd()
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_BoxOrCube;
		StartMouseCheck();
	}
}
void PlaygroundSimulation::StartCylinderMouseAdd()
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_Cylinder;
		StartMouseCheck();
	}
}
void PlaygroundSimulation::StartConeMouseAdd()
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_Cone;
		StartMouseCheck();
	}
}
void PlaygroundSimulation::StartCapsuleMouseAdd()
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_Capsule;
		StartMouseCheck();
	}
}
void PlaygroundSimulation::StartFromFileMouseAdd(wxString filename)
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_FromFile;
		StartMouseCheck();
	}
}

void PlaygroundSimulation::StartSpringMouseAdd()
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_Spring;
		StartMouseCheck();
	}
}

void PlaygroundSimulation::StartPointToPointJointMouseAdd()
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_PointToPointJoint;
		StartMouseCheck();
	}
}

void PlaygroundSimulation::StartHingeJointMouseAdd()
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_HingeJoint;
		StartMouseCheck();
	}
}

void PlaygroundSimulation::StartSliderJointMouseAdd()
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_Slider;
		StartMouseCheck();
	}
}

void PlaygroundSimulation::StartGenericJointMouseAdd()
{
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_GenericConstraint;
		StartMouseCheck();
	}
}
void QuaternionToEuler2(const btQuaternion &TQuat, btVector3 &TEuler)
{
   btScalar W = TQuat.getW();
   btScalar X = TQuat.getX();
   btScalar Y = TQuat.getY();
   btScalar Z = TQuat.getZ();
   float WSquared = W * W;
   float XSquared = X * X;
   float YSquared = Y * Y;
   float ZSquared = Z * Z;
   TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
   TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
   TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
   TEuler *= RADTODEG;
};

void PlaygroundSimulation::AddStaticGraphToBullet(ThreeDGraph* graph)
{
	IMeshBuffer* tempBuffer = graph->GetMesh()->getMeshBuffer(0);
	int* indexBulletArray = new int[tempBuffer->getIndexCount()];
	btScalar* vertexBulletArray = new btScalar[tempBuffer->getVertexCount()*3];
	u16* indexIrrArray = tempBuffer->getIndices();
	S3DVertex* vertexIrrArray = (S3DVertex*)tempBuffer->getVertices();

	int j = 0;
	for(unsigned int i = 0; i < tempBuffer->getIndexCount(); i++)
	{
		indexBulletArray[j++] = indexIrrArray[i];
	}

	j = 0;
	for(unsigned int i = 0; i < tempBuffer->getVertexCount(); i++)
	{
		vertexBulletArray[j++] = vertexIrrArray[i].Pos.X;
		vertexBulletArray[j++] = vertexIrrArray[i].Pos.Y;
		vertexBulletArray[j++] = vertexIrrArray[i].Pos.Z;
	}

	btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray(tempBuffer->getIndexCount() / 3, indexBulletArray, 12,
		tempBuffer->getVertexCount(), vertexBulletArray, sizeof(btScalar)*3);

	btBvhTriangleMeshShape* meshShape = new btBvhTriangleMeshShape(meshInterface, true);
	irrToBullConnector->AddCustomCollisionShape(meshShape);

	btTransform startTransform;
	startTransform.setIdentity();

	startTransform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));

	btDefaultMotionState* objMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, objMotionState, meshShape);
	btRigidBody* body = new btRigidBody(rbInfo);

	ITriangleSelector* selector = device->getSceneManager()->createTriangleSelector(graph->GetMesh(), graph->GetNode());
	graph->GetNode()->setTriangleSelector(selector);
	selector->drop();

	IrrlichtToBulletStaticGraphObject* graphObj = new IrrlichtToBulletStaticGraphObject(_("Graph"), body, graph, meshInterface, indexBulletArray, vertexBulletArray);
	irrToBullConnector->AddRigidBody(graphObj, physicsEngine);
}

void PlaygroundSimulation::AddMultipleObjectsCylindrical(bool singleSurface, wxString zEquation, double thetaRes, double rRes, double minTheta, double maxTheta, double minR, double maxR,
	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation)
{
	if(singleSurface)
	{
		CylindricalThreeDGraph* graph = new CylindricalThreeDGraph(_("Graph"), zEquation, 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), device, ThreeDGraphCylindrical_Theta,
			thetaRes, minTheta, maxTheta, rRes, minR, maxR);

		graph->CalculateGraph();
		graph->AddToSceneManager(device, device->getSceneManager());		
		
		AddStaticGraphToBullet(graph);
	}
	else
	{
		std::string validVars[2] = { "theta", "r" };
		MathExpression zEquationExpr = MathExpression(zEquation, validVars, 2);
		MathExpression xCylindricalMathExpr = MathExpression("r*cos(theta)", validVars, 2);
		MathExpression yCylindricalMathExpr = MathExpression("r*sin(theta)", validVars, 2);
		MathExpression massEquationExpr = MathExpression(massEquation, validVars, 2);
		MathExpression xRotEquationExpr = MathExpression(xRotEquation, validVars, 2);
		MathExpression yRotEquationExpr = MathExpression(yRotEquation, validVars, 2);
		MathExpression zRotEquationExpr = MathExpression(zRotEquation, validVars, 2);
		double validVarsValue[2] = {0,0};

		double currentTheta = minTheta;
		double currentRadius = minR;

		double thetaInterval = (maxTheta - minTheta) / (double)(thetaRes - 1);
		double radiusInterval = (maxR - minR) / (double)(rRes - 1);

		validVarsValue[0] = currentTheta;
		validVarsValue[1] = currentRadius;

		for (int height = 0; height < rRes; height++)
		{
			for (int width = 0; width < thetaRes; width++)
			{
				double z = zEquationExpr.GetValue(validVarsValue);
				double xCylindrical = xCylindricalMathExpr.GetValue(validVarsValue);
				double yCylindrical = yCylindricalMathExpr.GetValue(validVarsValue);
				double mass = massEquationExpr.GetValue(validVarsValue);
				double xRot = xRotEquationExpr.GetValue(validVarsValue);
				double yRot = yRotEquationExpr.GetValue(validVarsValue);
				double zRot = zRotEquationExpr.GetValue(validVarsValue);				

				float zFloat = (float)z;
				float xFloat = (float)xCylindrical;
				float yFloat = (float)yCylindrical;
				float massFloat = (float)mass;
				float xRotFloat = (float)xRot;
				float yRotFloat = (float)yRot;
				float zRotFloat = (float)zRot;

				AddBoxObject(_(""), Vector3(xFloat, yFloat, zFloat), Vector3(xRotFloat, yRotFloat, zRotFloat), Vector3_Zero, Vector3_Zero, Vector3(8.0f, 1.0f, 3.0f), massFloat);

				currentTheta += thetaInterval;
				validVarsValue[0] = currentTheta;
			}

			currentTheta = minTheta;
			validVarsValue[0] = currentTheta;
			currentRadius += radiusInterval;
			validVarsValue[1] = currentRadius;
		}
	}
}

void PlaygroundSimulation::AddMultipleObjectsParametric(bool singleSurface, wxString xEquation, wxString yEquation, wxString zEquation, double uRes, double vRes, double minU, double maxU, 
	double minV, double maxV, wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation)
{
	if (singleSurface)
	{
		ParametricThreeDGraph* graph = new ParametricThreeDGraph(_("Graph"), xEquation, yEquation, zEquation, 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), device, ThreeDGraphParametric_U,
			uRes, minU, maxU, vRes, minV, maxV);

		graph->CalculateGraph();
		graph->AddToSceneManager(device, device->getSceneManager());		
		
		AddStaticGraphToBullet(graph);
	}
	else
	{
		std::string validVars[2] = { "u", "v" };
		MathExpression xParametricMathExpr = MathExpression(xEquation, validVars, 2);
		MathExpression yParametricMathExpr = MathExpression(yEquation, validVars, 2);
		MathExpression zParametricMathExpr = MathExpression(zEquation, validVars, 2);
		MathExpression massEquationExpr = MathExpression(massEquation, validVars, 2);
		MathExpression xRotEquationExpr = MathExpression(xRotEquation, validVars, 2);
		MathExpression yRotEquationExpr = MathExpression(yRotEquation, validVars, 2);
		MathExpression zRotEquationExpr = MathExpression(zRotEquation, validVars, 2);
		double validVarsValue[2] = {0,0};

		double currentU = minU;
		double currentV = minV;

		double uInterval = (maxU - minU) / (double)(uRes - 1);
		double vInterval = (maxV - minV) / (double)(vRes - 1);

		validVarsValue[0] = currentU;
		validVarsValue[1] = currentV;

		for (int height = 0; height < vRes; height++)
		{
			for (int width = 0; width < uRes; width++)
			{
				double xParametric = xParametricMathExpr.GetValue(validVarsValue);
				double yParametric = yParametricMathExpr.GetValue(validVarsValue);
				double zParametric = zParametricMathExpr.GetValue(validVarsValue);
				double mass = massEquationExpr.GetValue(validVarsValue);
				double xRot = xRotEquationExpr.GetValue(validVarsValue);
				double yRot = yRotEquationExpr.GetValue(validVarsValue);
				double zRot = zRotEquationExpr.GetValue(validVarsValue);

				float xFloat = (float)xParametric;
				float yFloat = (float)yParametric;
				float zFloat = (float)zParametric;
				float massFloat = (float)mass;
				float xRotFloat = (float)xRot;
				float yRotFloat = (float)yRot;
				float zRotFloat = (float)zRot;

				AddBoxObject(_(""), Vector3(xFloat, yFloat, zFloat), Vector3(xRotFloat, yRotFloat, zRotFloat), Vector3_Zero, Vector3_Zero, Vector3(8.0f, 1.0f, 3.0f), massFloat);

				currentU += uInterval;
				validVarsValue[0] = currentU;
			}

			currentU = minU;
			validVarsValue[0] = currentU;
			currentV += vInterval;
			validVarsValue[1] = currentV;
		}
	}
}

void PlaygroundSimulation::AddMultipleObjectsRectangular(bool singleSurface, int axisIndex, wxString equation, double firstRes, double secondRes, double minFirst, double maxFirst,
	double minSecond, double maxSecond,	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation)
{
	if (singleSurface)
	{
		RectangularAxis axis = ThreeDGraph_X;
		switch(axisIndex)
		{
		case 1:
			axis = ThreeDGraph_Y;
			break;
		case 2:
			axis = ThreeDGraph_Z;
			break;
		}

		RectangularThreeDGraph* graph = new RectangularThreeDGraph(_("Graph"), equation, 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), device, axis, axis,
			firstRes, minFirst, maxFirst, secondRes, minSecond, maxSecond, false);

		graph->CalculateGraph();
		graph->AddToSceneManager(device, device->getSceneManager());		
		
		AddStaticGraphToBullet(graph);
	}
	else
	{
		std::string validVars[2];
		switch (axisIndex)
		{
		case 0:
			validVars[0] = "y";
			validVars[1] = "z";
			break;
		case 1:
			validVars[0] = "x";
			validVars[1] = "z";
			break;
		case 2:
			validVars[0] = "x";
			validVars[1] = "y";
			break;
		}
		MathExpression equationExpr = MathExpression(equation, validVars, 2);
		MathExpression massEquationExpr = MathExpression(massEquation, validVars, 2);
		MathExpression xRotEquationExpr = MathExpression(xRotEquation, validVars, 2);
		MathExpression yRotEquationExpr = MathExpression(yRotEquation, validVars, 2);
		MathExpression zRotEquationExpr = MathExpression(zRotEquation, validVars, 2);
		double validVarsValue[2] = {0,0};


		double currentWidth = minFirst;
		double currentHeight = minSecond;

		double widthInterval = (maxFirst - minFirst) / (double)(firstRes - 1);
		double heightInterval = (maxSecond - minSecond) / (double)(secondRes - 1);

		validVarsValue[0] = currentWidth;
		validVarsValue[1] = currentHeight;

		for (int height = 0; height < secondRes; height++)
		{
			for (int width = 0; width < firstRes; width++)
			{
				double value = equationExpr.GetValue(validVarsValue);
				double mass = massEquationExpr.GetValue(validVarsValue);
				double xRot = xRotEquationExpr.GetValue(validVarsValue);
				double yRot = yRotEquationExpr.GetValue(validVarsValue);
				double zRot = zRotEquationExpr.GetValue(validVarsValue);

				float currentWidthFloat = (float)currentWidth;
				float currentHeightFloat = (float)currentHeight;
				float valueFloat = (float)value;
				float massFloat = (float)mass;
				float xRotFloat = (float)xRot;
				float yRotFloat = (float)yRot;
				float zRotFloat = (float)zRot;

				switch (axisIndex)
				{
				case 0:
					AddBoxObject(_(""), Vector3(valueFloat, currentWidthFloat, currentHeightFloat), Vector3(xRotFloat, yRotFloat, zRotFloat), Vector3_Zero, Vector3_Zero, Vector3(8.0f, 1.0f, 3.0f), massFloat);
					break;
				case 1:
					AddBoxObject(_(""), Vector3(currentWidthFloat, valueFloat, currentHeightFloat), Vector3(xRotFloat, yRotFloat, zRotFloat), Vector3_Zero, Vector3_Zero, Vector3(8.0f, 1.0f, 3.0f), massFloat);
					break;
				case 2:
					AddBoxObject(_(""), Vector3(currentHeightFloat, currentWidthFloat, valueFloat), Vector3(xRotFloat, yRotFloat, zRotFloat), Vector3_Zero, Vector3_Zero, Vector3(8.0f, 1.0f, 3.0f), massFloat);
					break;
				}

				currentWidth += widthInterval;
				validVarsValue[0] = currentWidth;
			}

			currentWidth = minFirst;
			validVarsValue[0] = currentWidth;
			currentHeight += heightInterval;
			validVarsValue[1] = currentHeight;
		}
	}
}

void PlaygroundSimulation::AddMultipleObjectsSpherical(bool singleSurface, wxString rEquation, double thetaRes, double phiRes, double minTheta, double maxTheta, double minPhi, double maxPhi,
	wxString massEquation, wxString xRotEquation, wxString yRotEquation, wxString zRotEquation)
{
	if (singleSurface)
	{
		SphericalThreeDGraph* graph = new SphericalThreeDGraph(_("Graph"), rEquation, 1.0f, SColor(255, 255, 0, 0), SColor(255, 0, 0, 255), device, ThreeDGraphSpherical_Theta,
			thetaRes, minTheta, maxTheta, phiRes, minPhi, maxPhi);

		graph->CalculateGraph();
		graph->AddToSceneManager(device, device->getSceneManager());		
		
		AddStaticGraphToBullet(graph);
	}
	else
	{
		std::string validVars[2] = { "theta", "phi" };
		MathExpression rExpr = MathExpression(rEquation, validVars, 2);
		/*MathExpression xSphericalMathExpr = MathExpression("sin(phi)*cos(theta)", validVars, 2);
		MathExpression ySphericalMathExpr = MathExpression("sin(phi)*sin(theta)", validVars, 2);
		MathExpression zSphericalMathExpr = MathExpression("cos(phi)", validVars, 2);*/
		MathExpression massEquationExpr = MathExpression(massEquation, validVars, 2);
		MathExpression xRotEquationExpr = MathExpression(xRotEquation, validVars, 2);
		MathExpression yRotEquationExpr = MathExpression(yRotEquation, validVars, 2);
		MathExpression zRotEquationExpr = MathExpression(zRotEquation, validVars, 2);

		double validVarsValue[2] = {0,0};

		double currentTheta = minTheta;
		double currentPhi = minPhi;

		double thetaInterval = (maxTheta - minTheta) / (double)(thetaRes - 1);
		double phiInterval = (maxPhi - minPhi) / (double)(phiRes - 1);

		validVarsValue[0] = currentTheta;
		validVarsValue[1] = currentPhi;

		//Setup vertex positions
		int i = 0;
		for (int height = 0; height < phiRes; height++)
		{
			for (int width = 0; width < thetaRes; width++)
			{
				double radius = rExpr.GetValue(validVarsValue);
				double xSpherical = sin(validVarsValue[1])*cos(validVarsValue[0]);
				double ySpherical = sin(validVarsValue[1])*sin(validVarsValue[0]);
				double zSpherical = cos(validVarsValue[1]);
				double mass = massEquationExpr.GetValue(validVarsValue);
				double xRot = xRotEquationExpr.GetValue(validVarsValue);
				double yRot = yRotEquationExpr.GetValue(validVarsValue);
				double zRot = zRotEquationExpr.GetValue(validVarsValue);

				float radiusFloat = (float)radius;
				float xSphericalFloat = (float)xSpherical;
				float ySphericalFloat = (float)ySpherical;
				float zSphericalFloat = (float)zSpherical;
				float massFloat = (float)mass;
				float xRotFloat = (float)xRot;
				float yRotFloat = (float)yRot;
				float zRotFloat = (float)zRot;

				AddBoxObject(_(""), Vector3(radiusFloat*xSphericalFloat, radiusFloat*ySphericalFloat,radiusFloat*zSphericalFloat), 
					Vector3(xRotFloat, yRotFloat, zRotFloat), Vector3_Zero, Vector3_Zero, Vector3(8.0f, 1.0f, 3.0f), massFloat);

				currentTheta += thetaInterval;
				validVarsValue[0] = currentTheta;
				i++;
			}

			currentTheta = minTheta;
			validVarsValue[0] = currentTheta;
			currentPhi += phiInterval;
			validVarsValue[1] = currentPhi;
		}
	}
}



void PlaygroundSimulation::RemoveObject(int index)
{
	irrToBullConnector->RemoveEntity(index, physicsEngine);
}

void PlaygroundSimulation::ClearObjects(void)
{
	mouseOverSceneNode = NULL;
	irrToBullConnector->ClearEntities(physicsEngine);
}

void PlaygroundSimulation::ChangeSelection(wxArrayInt intArray)
{
	ClearSelectedObjects();

	for(unsigned int i = 0; i < intArray.size(); i++)
	{
		IrrlichtToBulletEntityListPointer* entityPointer = irrToBullConnector->entityTrackerList.GetAt(intArray[i])->GetData();

		if (entityPointer->entityType == IrrlichtToBulletEntityListPointerType_Object)
		{
			List<IrrlichtToBulletObjectStorage*>::iterator objIt = ((List<IrrlichtToBulletObjectStorage*>::iterator)entityPointer->entityListPointer);
			AddSelectedObject(objIt->GetData()->node);
		}
	}
	
}

void PlaygroundSimulation::ObjectListDoubleClick(int index)
{
	IrrlichtToBulletEntityListPointer* entityPointer = irrToBullConnector->entityTrackerList.GetAt(index)->GetData();

	if (entityPointer->entityType == IrrlichtToBulletEntityListPointerType_Object)
	{
		List<IrrlichtToBulletObjectStorage*>::iterator objIt = ((List<IrrlichtToBulletObjectStorage*>::iterator)entityPointer->entityListPointer);
		viewportManager->GetSelectedViewport()->StartTargeting(objIt->GetData()->node->getAbsolutePosition(), 15.0f);
	}
}

void PlaygroundSimulation::StartRecording()
{
	Simulation::StartRecording();

	foreach(IrrlichtToBulletObjectStorage*, irrToBullObjIt, irrToBullConnector->objectList)
	{
		IrrlichtToBulletObjectStorage* obj = irrToBullObjIt->GetData();

		if (obj->objType == IrrlichtBulletObjectType_Dynamic)
		{
			IrrlichtToBulletDynamicObject* dynObj = (IrrlichtToBulletDynamicObject*)obj;

			if (dynObj->GetMass() > 0.0f)
			{
				wxString posName = _("Position");
				wxString velName = _("Velocity");
				wxString frcName = _("Force");
				List<wxString> yNames;
				yNames.Add(_("X"));
				yNames.Add(_("Y"));
				yNames.Add(_("Z"));

				dynObj->AddDataToRecord(posName, &yNames, dynObj->GetPositionPointer());
				dynObj->AddDataToRecord(velName, &yNames, dynObj->GetVelocityPointer());
				dynObj->AddDataToRecord(frcName, &yNames, dynObj->GetForcePointer());

				recordingObjects->Add(dynObj, false);
			}
		}
	}
}

void PlaygroundSimulation::StopRecording()
{
	Simulation::StopRecording();

	if (recordingObjects->GetSize() > 0)
	{
		List<ObjectTabStructure*> chartTabStructure;

		foreach(IrrlichtToBulletDynamicObject*, dynObjIt, recordingObjects)
		{
			IrrlichtToBulletDynamicObject* dynObj = dynObjIt->GetData();

			chartTabStructure.Add(dynObj->GetObjectTabStructure(dynObj->GetIrrBullName()));
		}

		WxIrrChartWindow* chartWindow = new WxIrrChartWindow(&chartTabStructure);
		chartWindow->Show();

		foreach(IrrlichtToBulletDynamicObject*, dynObjIt, recordingObjects)
		{
			dynObjIt->GetData()->ClearRecordings();
		}

		chartTabStructure.Clear(); 

		recordingObjects->Clear();
	}
}

void PlaygroundSimulation::StartMouseCheck()
{
	Simulation::StartMouseCheck();

	switch(mouseAddObjectType)
	{
	case MouseAddObjectType_CapsuleOrSphere:
		tempAddMouseObject = device->getSceneManager()->addSphereSceneNode(5.0f, 16, 0, IDFlag_IsMousePickable);
		break;
	case MouseAddObjectType_BoxOrCube:
		tempAddMouseObject = device->getSceneManager()->addCubeSceneNode(1.0f, 0, IDFlag_IsMousePickable);
		break;
	case MouseAddObjectType_Cylinder:
		//tempAddMouseObject = new CylinderSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), IDFlag_IsMousePickable, SColor(255, 255, 255, 255), 10, 1.0f, 1.0f);
		tempAddMouseObject = customSceneNodeManager->CreateCylinderSceneNode(device->getSceneManager(), IDFlag_IsMousePickable, SColor(255, 255, 255, 255), 10, 1.0f, 1.0f);
		break;
	case MouseAddObjectType_Cone:
		//tempAddMouseObject = new CylinderSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), IDFlag_IsMousePickable, SColor(255, 255, 255, 255), 10, 1.0f, 1.0f);
		tempAddMouseObject = customSceneNodeManager->CreateConeSceneNode(device->getSceneManager(), IDFlag_IsMousePickable, SColor(255, 255, 255, 255), 10, 1.0f, 1.0f);
		break;
	case MouseAddObjectType_Capsule:
		//tempAddMouseObject = new CylinderSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), IDFlag_IsMousePickable, SColor(255, 255, 255, 255), 10, 1.0f, 1.0f);
		tempAddMouseObject = customSceneNodeManager->CreateCapsuleSceneNode(device->getSceneManager(), IDFlag_IsMousePickable, SColor(255, 255, 255, 255), 10, 1.0f, 1.0f);
		break;
	case MouseAddObjectType_HingeJoint:
		statusBarText = _("Choose an object to attach the hinge to.");
		ChangeStatusBarTextFunction(statusBarText);
		break;
	}

	if (tempAddMouseObject)
		tempAddMouseObject->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
}

//returns true if done checking for mouse clicks.
bool PlaygroundSimulation::MouseClick(bool isShiftDown, bool isControlDown)
{
	bool tempIsMouseChecking = isMouseChecking;
	int tempNumOfMouseClicks = numOfMouseClicks;

	bool retValue = false;

	if (isMouseChecking)
	{
		switch(mouseAddObjectType)
		{
		case MouseAddObjectType_BoxOrCube:
			retValue = MouseClickNumLeft(isShiftDown, 4);
			break;

		case MouseAddObjectType_Cylinder:
		case MouseAddObjectType_Cone:
		case MouseAddObjectType_Capsule:
			retValue = MouseClickNumLeft(isShiftDown, 3);
			break;

		case MouseAddObjectType_HingeJoint:
			retValue = MouseClickNumLeft(isShiftDown, 5);
			break;

		default:
			retValue = MouseClickNumLeft(isShiftDown, 2);
			break;
		}
	}
	else
	{
		if (isControlDown && mouseOverSceneNode)
		{
			IrrlichtToBulletObjectStorage* obj = irrToBullConnector->FindObjectWithSceneNode(mouseOverSceneNode);
			if (obj && obj->objType == IrrlichtBulletObjectType_Dynamic)
			{
				IrrlichtToBulletDynamicObject* dynObj = CastToDynamicObject(obj);
				dynObj->SetObjectGUI(physicsHelperGUIEnviornment->AddBasicDynamicObjectWindow(dynObj->GetIrrBullName(), dynObj->GetMass(),
					dynObj->GetPosition(), dynObj->GetVelocity(), dynObj->GetForce()));
			}
		}
		else
		{
			MouseClickNumLeft(isShiftDown, 0);
		}
			
	}

	if (isMouseChecking || tempIsMouseChecking != isMouseChecking)
	{
		if (numOfMouseClicks == 1)
		{
			switch(mouseAddObjectType)
			{
			case MouseAddObjectType_Spring:
				if(mouseOverSceneNode)
				{
					ChangeSelectedObjects(mouseOverSceneNode);

					tempSpringSceneNode = new SpringSceneNode(device->getSceneManager()->getRootSceneNode(), device->getSceneManager(), -1, 0, 0);
					tempSpringSceneNode->drop();
				}
				else
				{
					//Contiue mouse checking because no node was clicked
					numOfMouseClicks = 0;
				}
				break;

			case MouseAddObjectType_PointToPointJoint:
				if(mouseOverSceneNode)
				{
					ChangeSelectedObjects(mouseOverSceneNode);

					tempConstraint = new IrrlichtBulletConstraint(mouseOverSceneNode);
				}
				else
				{
					//Contiue mouse checking because no node was clicked
					numOfMouseClicks = 0;
				}
				break;
			case MouseAddObjectType_HingeJoint:
				if(mouseOverSceneNode)
				{
					ChangeSelectedObjects(mouseOverSceneNode);

					tempConstraint = new IrrlichtBulletHingeConstraint(mouseOverSceneNode);

					statusBarText = _("Choose the point on the object to rotate around.");
					ChangeStatusBarTextFunction(statusBarText);
				}
				else
				{
					//Contiue mouse checking because no node was clicked
					numOfMouseClicks = 0;
				}
				break;
			
			case MouseAddObjectType_Cylinder:
			case MouseAddObjectType_Cone:
			case MouseAddObjectType_Capsule:
				UsePlaneForMousePicking(true, tempAddMouseObject->getPosition());
				EnableRotationOfMousePlane(AxisIdentifier_Y);

				tempAddMouseObject->setPosition(threeDMousePosition);
				break;

			case MouseAddObjectType_BoxOrCube:
				UsePlaneForMousePicking(true, tempAddMouseObject->getPosition());
				EnableRotationOfMousePlane(AxisIdentifier_X);

				tempAddMouseObject->setPosition(threeDMousePosition);
				break;

			default:				
				UsePlaneForMousePicking(true, tempAddMouseObject->getPosition());
				EnableRotationOfMousePlane(AxisIdentifier_ALL);

				tempAddMouseObject->setPosition(threeDMousePosition);
				break;
			}
		}
		else if (numOfMouseClicks == 2 || tempNumOfMouseClicks == 1 )
		{
			switch(mouseAddObjectType)
			{
			case MouseAddObjectType_CapsuleOrSphere:
				AddSphereObject(_(""), tempAddMouseObject->getPosition(), Vector3_Zero, Vector3_Zero, Vector3_Zero, tempAddMouseObject->getScale().X * 5.0f, 1.0f);
				tempAddMouseObject->remove();
				tempAddMouseObject = NULL;

				DisablePlaneForMousePicking();
				break;

			case MouseAddObjectType_BoxOrCube:
				if (isShiftDown)
				{
					//Since all axes are being scaled just add the object.
					AddCubeObject(_(""), tempAddMouseObject->getPosition(), Vector3_Zero, Vector3_Zero, Vector3_Zero, tempAddMouseObject->getScale().X / 2.0f, 1.0f);
					tempAddMouseObject->remove();
					tempAddMouseObject = NULL;

					StopMouseCheck();
					retValue = false;

					DisablePlaneForMousePicking();
				}
				else
				{
					EnableRotationOfMousePlane(AxisIdentifier_Y);
				}
				break;

			case MouseAddObjectType_Cylinder:
				if (isShiftDown)
				{
					//Since all axes are being scaled just add the object.
					AddCylinderObject(_(""), tempAddMouseObject->getPosition(), Vector3_Zero, Vector3_Zero, Vector3_Zero, tempAddMouseObject->getScale().X, tempAddMouseObject->getScale().Y * 2.0f, 1.0f);
					tempAddMouseObject->remove();
					tempAddMouseObject = NULL;

					StopMouseCheck();
					retValue = false;

					DisablePlaneForMousePicking();
				}
				break;

			case MouseAddObjectType_Cone:
				if (isShiftDown)
				{
					//Since all axes are being scaled just add the object.
					AddConeObject(_(""), tempAddMouseObject->getPosition(), Vector3_Zero, Vector3_Zero, Vector3_Zero, tempAddMouseObject->getScale().X, tempAddMouseObject->getScale().Y, 1.0f);
					tempAddMouseObject->remove();
					tempAddMouseObject = NULL;

					StopMouseCheck();
					retValue = false;

					DisablePlaneForMousePicking();
				}
				break;

			case MouseAddObjectType_Capsule:
				if (isShiftDown)
				{
					//Since all axes are being scaled just add the object.
					AddCapsuleObject(_(""), tempAddMouseObject->getPosition(), Vector3_Zero, Vector3_Zero, Vector3_Zero, tempAddMouseObject->getScale().X, tempAddMouseObject->getScale().Y * 2.0f, 1.0f);
					tempAddMouseObject->remove();
					tempAddMouseObject = NULL;

					StopMouseCheck();
					retValue = false;

					DisablePlaneForMousePicking();
				}
				break;

			case MouseAddObjectType_Spring:
				if(mouseOverSceneNode)
				{
					AddSelectedObject(mouseOverSceneNode);

					ISceneNode* node1 = selectedObjects->GetHead()->GetData();
					ISceneNode* node2 = selectedObjects->GetTail()->GetData();
					IrrlichtToBulletObjectStorage* obj1 = irrToBullConnector->FindObjectWithSceneNode(node1);
					IrrlichtToBulletObjectStorage* obj2 = irrToBullConnector->FindObjectWithSceneNode(node2);

					IrrlichtToBulletDynamicObject* dynObj1 = CastToDynamicObject(obj1);
					IrrlichtToBulletDynamicObject* dynObj2 = CastToDynamicObject(obj2);

					List<Physics_Engine::Spring*>::iterator springElem = physicsEngine->AddSpring(dynObj1, dynObj2, 1.0f, node1->getPosition().getDistanceFrom(node2->getPosition()));

					tempSpringSceneNode->SetObjects(node1, node2);
					
					irrToBullConnector->AddSpring(tempSpringSceneNode, 1.0f, springElem);
					tempSpringSceneNode = NULL;

					springCount++;					
					AddObjectToListBox(_("Spring")+wxString::Format(_("%i"), springCount));
				}
				else
				{
					numOfMouseClicks = 1;
					retValue = true;
				}
				break;

			case MouseAddObjectType_PointToPointJoint:
				if(mouseOverSceneNode)
				{
					AddSelectedObject(mouseOverSceneNode);

					tempConstraint->SetNode2(mouseOverSceneNode);

					IrrlichtToBulletObjectStorage* obj1 = irrToBullConnector->FindObjectWithSceneNode(tempConstraint->GetNode1());
					IrrlichtToBulletObjectStorage* obj2 = irrToBullConnector->FindObjectWithSceneNode(mouseOverSceneNode);

					if (obj1->objType == IrrlichtBulletObjectType_Static || obj1->objType == IrrlichtBulletObjectType_Dynamic)
					{
						if (obj2->objType == IrrlichtBulletObjectType_Static || obj1->objType == IrrlichtBulletObjectType_Dynamic)
						{
							btRigidBody* body1 = CastToDynamicObject(obj1)->body;
							btRigidBody* body2 = CastToDynamicObject(obj2)->body;

							btVector3 body1Pos = body1->getWorldTransform().getOrigin();
							btVector3 body2Pos = body2->getWorldTransform().getOrigin();
							btVector3 halfPos = (body2Pos - body1Pos) / 2.0f + body1Pos;
							btVector3 body1Dir = halfPos - body1Pos;
							btVector3 body2Dir = halfPos - body2Pos;

							btTypedConstraint* pointToPointJoint = new btPoint2PointConstraint(*(body1), *(body2), btVector3(0, 0, 0), body1Pos - body2Pos);

							tempConstraint->SetConstraint(pointToPointJoint);
							irrToBullConnector->AddConstraint(tempConstraint, pointToPointJoint);

							tempConstraint = NULL;

							constraintCount++;
							AddObjectToListBox(_("Constraint")+wxString::Format(_("%i"), constraintCount));

							break;
						}
					}

					delete tempConstraint;
					tempConstraint = NULL;
				}
				else
				{
					numOfMouseClicks = 1;
					retValue = true;
				}
				break;
			case MouseAddObjectType_HingeJoint:
				if(mouseOverSceneNode && selectedObjects->GetHead()->GetData() == mouseOverSceneNode)
				{
					((IrrlichtBulletHingeConstraint*)tempConstraint)->SetPosition1(threeDMousePosition);

					statusBarText = _("Choose another object to attach the hinge to.");
					ChangeStatusBarTextFunction(statusBarText);
				}
				else
				{
					//Contiue mouse checking because the same node was not cliked.
					numOfMouseClicks = 1;
				}
				break;
			}
		}
		else if (numOfMouseClicks == 3 || tempNumOfMouseClicks == 2 )
		{
			switch(mouseAddObjectType)
			{
			case MouseAddObjectType_BoxOrCube:
				EnableRotationOfMousePlane(AxisIdentifier_Z);
				break;

			case MouseAddObjectType_Cylinder:
				AddCylinderObject(_(""), tempAddMouseObject->getPosition(), Vector3_Zero, Vector3_Zero, Vector3_Zero, tempAddMouseObject->getScale().X, tempAddMouseObject->getScale().Y, 1.0f);
				tempAddMouseObject->remove();
				tempAddMouseObject = NULL;

				DiablePlaneForMousePicking();
				break;

			case MouseAddObjectType_Cone:
				AddConeObject(_(""), tempAddMouseObject->getPosition(), Vector3_Zero, Vector3_Zero, Vector3_Zero, tempAddMouseObject->getScale().X, tempAddMouseObject->getScale().Y, 1.0f);
				tempAddMouseObject->remove();
				tempAddMouseObject = NULL;

				DiablePlaneForMousePicking();
				break;

			case MouseAddObjectType_Capsule:
				AddCapsuleObject(_(""), tempAddMouseObject->getPosition(), Vector3_Zero, Vector3_Zero, Vector3_Zero, tempAddMouseObject->getScale().X, tempAddMouseObject->getScale().Y, 1.0f);
				tempAddMouseObject->remove();
				tempAddMouseObject = NULL;

				DiablePlaneForMousePicking();
				break;
			case MouseAddObjectType_HingeJoint:
				if(mouseOverSceneNode && mouseOverSceneNode != tempConstraint->GetNode1())
				{
					AddSelectedObject(mouseOverSceneNode);

					((IrrlichtBulletHingeConstraint*)tempConstraint)->SetNode2(mouseOverSceneNode);

					statusBarText = _("Choose the point the other object will rotate around.");
					ChangeStatusBarTextFunction(statusBarText);
				}
				else
				{
					//Contiue mouse checking because no node was clicked
					numOfMouseClicks = 2;
				}
				break;
			}
		}
		else if (numOfMouseClicks == 4 || tempNumOfMouseClicks == 3)
		{
			switch(mouseAddObjectType)
			{
			case MouseAddObjectType_BoxOrCube:
				AddBoxObject(_(""), tempAddMouseObject->getPosition(), Vector3_Zero, Vector3_Zero, Vector3_Zero, tempAddMouseObject->getScale() / 2.0f, 1.0f);
				tempAddMouseObject->remove();
				tempAddMouseObject = NULL;
				
				DiablePlaneForMousePicking();
				break;
			case MouseAddObjectType_HingeJoint:
				if(mouseOverSceneNode && selectedObjects->GetTail()->GetData() == mouseOverSceneNode)
				{
					IrrlichtBulletHingeConstraint* hingeConstraintData = ((IrrlichtBulletHingeConstraint*)tempConstraint);
					hingeConstraintData->SetPosition2(threeDMousePosition);

					statusBarText = _("Choose the axis to rotate around. Hold shift to choose one of the global axes(X, Y, Z).");
					ChangeStatusBarTextFunction(statusBarText);

					UsePlaneForMousePicking(true, mouseOverSceneNode->getPosition());
					EnableRotationOfMousePlane(AxisIdentifier_ALL);
				}
				else
				{
					//Contiue mouse checking because the same node was not cliked.
					numOfMouseClicks = 3;
				}
				break;
			}
		}
		else if (numOfMouseClicks == 5 || tempNumOfMouseClicks == 4)
		{
			switch(mouseAddObjectType)
			{
			case MouseAddObjectType_HingeJoint:
				IrrlichtBulletHingeConstraint* hingeConstraintData = ((IrrlichtBulletHingeConstraint*)tempConstraint);

				btRigidBody* body1 = NULL;
				btRigidBody* body2 = NULL;
				
				ISceneNode* firstSelectedSceneNode = GetSelectedObjects()->GetHead()->GetData();
				ISceneNode* secondSelectedSceneNode = GetSelectedObjects()->GetTail()->GetData();
				IrrlichtToBulletObjectStorage* obj1 = irrToBullConnector->FindObjectWithSceneNode(firstSelectedSceneNode);
				IrrlichtToBulletObjectStorage* obj2 = irrToBullConnector->FindObjectWithSceneNode(secondSelectedSceneNode);

				if (obj1->objType == IrrlichtBulletObjectType_Static)
				{
					body1 = ((IrrlichtToBulletStaticObject*)obj1)->body;
				}
				else if (obj1->objType == IrrlichtBulletObjectType_Dynamic)
				{
					body1 = ((IrrlichtToBulletDynamicObject*)obj1)->body;
				}

				if (obj2->objType == IrrlichtBulletObjectType_Static)
				{
					body2 = ((IrrlichtToBulletStaticObject*)obj2)->body;
				}
				else if (obj2->objType == IrrlichtBulletObjectType_Dynamic)
				{
					body2 = ((IrrlichtToBulletDynamicObject*)obj2)->body;
				}

				Vector3 irrAxis = (threeDMousePosition - hingeConstraintData->GetPosition2()).normalize();
				btVector3 bulletAxis = IrrlichtToBulletVector3(irrAxis);

				btHingeConstraint* hinge = new btHingeConstraint((*body1), *(body2),
					IrrlichtToBulletVector3(hingeConstraintData->GetPosition1() - firstSelectedSceneNode->getAbsolutePosition()),
					IrrlichtToBulletVector3(hingeConstraintData->GetPosition2() - secondSelectedSceneNode->getAbsolutePosition()), bulletAxis, bulletAxis, true);

				hingeConstraintData->SetConstraint(hinge);

				irrToBullConnector->AddConstraint(hingeConstraintData, hinge);
				
				tempConstraint = NULL;
				DisablePlaneForMousePicking();

				constraintCount++;
				AddObjectToListBox(_("Constraint")+wxString::Format(_("%i"), constraintCount));

				break;
			}
		}
	}

	isMouseChecking = retValue;
	if (!isMouseChecking)
	{
		mouseAddObjectType = MouseAddObjectType_None;
		DeselectSelectedObjectListView();
	}

	return retValue;
}

void PlaygroundSimulation::UpdateMousePosition(wxPoint mousePos, bool isShiftDown, WxIrrViewport* mouseOverViewport, float collisionOffset)
{
	Simulation::UpdateMousePosition(mousePos, isShiftDown, mouseOverViewport, 0.0f);

	if (isMouseChecking)
	{
		if (numOfMouseClicks == 0)
		{
			if (tempAddMouseObject)
			{
				tempAddMouseObject->setPosition(threeDMousePosition);

				ChangeStatusBarTextFunction(_("Position: {") + wxString::Format("%f", threeDMousePosition.X) + _(", ") +
					wxString::Format("%f", threeDMousePosition.Y) + _(", ") + wxString::Format("%f", threeDMousePosition.Z) + _("}"));
			}
		}
		else if (numOfMouseClicks == 1)
		{
			switch(mouseAddObjectType)
			{
			case MouseAddObjectType_Spring:
				{
					Vector3 posFirst = selectedObjects->GetHead()->GetData()->getPosition();
					if (mouseOverSceneNode)
					{
						Vector3 posSecond = mouseOverSceneNode->getPosition();
						tempSpringSceneNode->UpdatePositions(posFirst, posSecond);
					}
					else
					{
						tempSpringSceneNode->UpdatePositions(posFirst, threeDMousePosition);
					}

					break;
				}

			case MouseAddObjectType_PointToPointJoint:
				{
					if (mouseOverSceneNode)
					{
						Vector3 posSecond = mouseOverSceneNode->getPosition();
						tempConstraint->SetPosition2(posSecond);
					}
					else
					{
						tempConstraint->SetPosition2(threeDMousePosition);
					}

					break;
				}

			case MouseAddObjectType_BoxOrCube:
				{
					if (isShiftDown)
					{
						float dist = tempAddMouseObject->getPosition().getDistanceFrom(threeDMousePosition);
						if (dist != 0.0f)
						{
							float newScale = dist * 2.0f;
							tempAddMouseObject->setScale(Vector3(newScale));

							ChangeStatusBarTextFunction(_("Side Length: ") + wxString::Format("%f", newScale));
						}
					}
					else
					{
						Vector3 diff = threeDMousePosition - tempAddMouseObject->getPosition();
						diff.X = abs_(diff.X) * 2.0f;
						tempAddMouseObject->setScale(Vector3(diff.X, 1.0f, 1.0f));

						ChangeStatusBarTextFunction(_("X Length: ") + wxString::Format("%f", diff.X * 2.0f));
					}
					break;
				}

			case MouseAddObjectType_Cylinder:
				{
					if (isShiftDown)
					{
						float dist = tempAddMouseObject->getPosition().getDistanceFrom(threeDMousePosition);
						if (dist != 0.0f)
						{
							float newScale = dist;
							tempAddMouseObject->setScale(Vector3(newScale));

							ChangeStatusBarTextFunction(_("Radius and Height: ") + wxString::Format("%f", newScale));
						}
					}
					else
					{
						Vector3 diff = threeDMousePosition - tempAddMouseObject->getPosition();
						diff.Y = abs_(diff.Y);
						tempAddMouseObject->setScale(Vector3(1.0f, diff.Y*2.0f, 1.0f));

						ChangeStatusBarTextFunction(_("Height: ") + wxString::Format("%f", diff.Y));
					}
					break;
				}

			case MouseAddObjectType_Cone:
				{
					if (isShiftDown)
					{
						float dist = tempAddMouseObject->getPosition().getDistanceFrom(threeDMousePosition);
						if (dist != 0.0f)
						{
							float newScale = dist;
							tempAddMouseObject->setScale(Vector3(newScale));

							ChangeStatusBarTextFunction(_("Radius and Height: ") + wxString::Format("%f", newScale));
						}
					}
					else
					{
						Vector3 diff = threeDMousePosition - tempAddMouseObject->getPosition();
						diff.Y = abs_(diff.Y) * 2.0f;
						tempAddMouseObject->setScale(Vector3(1.0f, diff.Y, 1.0f));

						ChangeStatusBarTextFunction(_("Height: ") + wxString::Format("%f", diff.Y));
					}
					break;
				}

			case MouseAddObjectType_Capsule:
				{
					if (isShiftDown)
					{
						float dist = tempAddMouseObject->getPosition().getDistanceFrom(threeDMousePosition);
						if (dist != 0.0f)
						{
							float newScale = dist;
							tempAddMouseObject->setScale(Vector3(newScale));

							ChangeStatusBarTextFunction(_("Radius and Height: ") + wxString::Format("%f", newScale));
						}
					}
					else
					{
						Vector3 diff = threeDMousePosition - tempAddMouseObject->getPosition();
						diff.Y = abs_(diff.Y);
						tempAddMouseObject->setScale(Vector3(1.0f, diff.Y, 1.0f));

						ChangeStatusBarTextFunction(_("Height: ") + wxString::Format("%f", diff.Y));
					}
					break;
				}

			case MouseAddObjectType_HingeJoint:
				break;

			default:
				float dist = tempAddMouseObject->getPosition().getDistanceFrom(threeDMousePosition);

				if (dist != 0.0f)
				{
					float newScale = 1.0f;

					switch(mouseAddObjectType)
					{
					case MouseAddObjectType_CapsuleOrSphere:
						newScale = dist / 5.0f;
						break;
					}

					tempAddMouseObject->setScale(Vector3(newScale));

					switch(mouseAddObjectType)
					{
					case MouseAddObjectType_CapsuleOrSphere:
						ChangeStatusBarTextFunction(_("Radius: ") + wxString::Format("%f", newScale * 5.0f));
						break;
					}				
				}

				break;
			}
		}
		else if (numOfMouseClicks == 2)
		{
			switch(mouseAddObjectType)
			{
			case MouseAddObjectType_BoxOrCube:
				{					
					Vector3 diff = threeDMousePosition - tempAddMouseObject->getPosition();
					diff.Y = abs_(diff.Y) * 2.0f;
					Vector3 currentScale = tempAddMouseObject->getScale();
					tempAddMouseObject->setScale(Vector3(currentScale.X, diff.Y, currentScale.Z));

					ChangeStatusBarTextFunction(_("Y Length: ") + wxString::Format("%f", diff.Y * 2.0f));
					break;
				}

			case MouseAddObjectType_Cylinder:
				{			
					Vector3 diff = threeDMousePosition - tempAddMouseObject->getPosition();
					float dist = vector2df(diff.X, diff.Z).getLength();
					Vector3 currentScale = tempAddMouseObject->getScale();
					tempAddMouseObject->setScale(Vector3(dist, currentScale.Y, dist));

					ChangeStatusBarTextFunction(_("Radius: ") + wxString::Format("%f", dist));
					break;
				}

			case MouseAddObjectType_Cone:
				{			
					Vector3 diff = threeDMousePosition - tempAddMouseObject->getPosition();
					float dist = vector2df(diff.X, diff.Z).getLength();
					Vector3 currentScale = tempAddMouseObject->getScale();
					tempAddMouseObject->setScale(Vector3(dist, currentScale.Y, dist));

					ChangeStatusBarTextFunction(_("Radius: ") + wxString::Format("%f", dist));
					break;
				}

			case MouseAddObjectType_Capsule:
				{			
					Vector3 diff = threeDMousePosition - tempAddMouseObject->getPosition();
					float dist = vector2df(diff.X, diff.Z).getLength();
					Vector3 currentScale = tempAddMouseObject->getScale();
					tempAddMouseObject->setScale(Vector3(dist, currentScale.Y, dist));

					ChangeStatusBarTextFunction(_("Radius: ") + wxString::Format("%f", dist));
					break;
				}
			}
		}
		else if (numOfMouseClicks == 3)
		{
			switch(mouseAddObjectType)
			{
			case MouseAddObjectType_BoxOrCube:
				{					
					Vector3 diff = threeDMousePosition - tempAddMouseObject->getPosition();
					diff.Z = abs_(diff.Z) * 2.0f;
					Vector3 currentScale = tempAddMouseObject->getScale();
					tempAddMouseObject->setScale(Vector3(currentScale.X, currentScale.Y, diff.Z));

					ChangeStatusBarTextFunction(_("Z Length: ") + wxString::Format("%f", diff.Z * 2.0f));
					break;
				}
			}
		}
		else if (numOfMouseClicks == 4)
		{
			switch(mouseAddObjectType)
			{
			case MouseAddObjectType_HingeJoint:
				{
					IrrlichtBulletHingeConstraint* hingeConstraint = (IrrlichtBulletHingeConstraint*)tempConstraint;
					if (isShiftDown)
					{
						DisableRotationOfMousePlane();

						UsePlaneForMousePicking(true, tempConstraint->GetPosition2(), Vector3(1.0f, 0.0f, 0.0f));
						Simulation::UpdateMousePosition(mousePos, isShiftDown, mouseOverViewport, 0.0f);
						Vector3 xPlanePos = threeDMousePosition;

						UsePlaneForMousePicking(true, tempConstraint->GetPosition2(), Vector3(0.0f, 1.0f, 0.0f));
						Simulation::UpdateMousePosition(mousePos, isShiftDown, mouseOverViewport, 0.0f);
						Vector3 yPlanePos = threeDMousePosition;

						UsePlaneForMousePicking(true, tempConstraint->GetPosition2(), Vector3(0.0f, 0.0f, 1.0f));
						Simulation::UpdateMousePosition(mousePos, isShiftDown, mouseOverViewport, 0.0f);
						Vector3 zPlanePos = threeDMousePosition;

						float xMax = max_(xPlanePos.X, yPlanePos.X, zPlanePos.X);
						float yMax = max_(xPlanePos.Y, yPlanePos.Y, zPlanePos.Y);
						float zMax = max_(xPlanePos.Z, yPlanePos.Z, zPlanePos.Z);

						float max = max_(xMax, yMax, zMax);

						if (max == xMax)
						{
							hingeConstraint->SetAxis(Vector3(max, 0.0f, 0.0f));
							threeDMousePosition = tempConstraint->GetPosition2() + Vector3(1.0f, 0.0f, 0.0f);
						}
						else if (max == yMax)
						{
							hingeConstraint->SetAxis(Vector3(0.0f, max, 0.0f));
							threeDMousePosition = tempConstraint->GetPosition2() + Vector3(0.0f, 1.0f, 0.0f);
						}
						else if (max == zMax)
						{
							hingeConstraint->SetAxis(Vector3(0.0f, 0.0f, max));
							threeDMousePosition = tempConstraint->GetPosition2() + Vector3(0.0f, 0.0f, 1.0f);
						}
					}
					else
					{
						EnableRotationOfMousePlane(AxisIdentifier_ALL);
						Simulation::UpdateMousePosition(mousePos, isShiftDown, mouseOverViewport, 0.0f);

						Vector3 objPos = tempConstraint->GetPosition2();
						hingeConstraint->SetAxis(objPos - threeDMousePosition);
					}
				}
			}
		}


	}
}

void PlaygroundSimulation::AddMoveToPoint(Vector3& point)
{
	Simulation::AddMoveToPoint(point);
}
void PlaygroundSimulation::AddMoveToObject(ISceneNode* obj)
{
	Simulation::AddMoveToObject(obj);
}


void PlaygroundSimulation::SerializeInListOfIrrlichtToBulletObjects(istream& is)
{
	int size = 0;
	is >> size;

	for(int i = 0; i < size; i++)
	{
		int objSpecificTypeInt = 0;
		is >> objSpecificTypeInt;
	
		switch(objSpecificTypeInt)
		{
		case IrrlichtBulletObjectSpecificType_Sphere:
			{
				IrrlichtToBulletDynamicSphereObject sphereElem;
				sphereElem.SerializeIn(is);
				AddSphereObject(sphereElem.GetIrrBullName(), sphereElem.nodePos, sphereElem.nodeRot, sphereElem.BulletVelocity, sphereElem.BulletAngularVelocity, sphereElem.radius, sphereElem.GetMass()); 
				break;
			}
		case IrrlichtBulletObjectSpecificType_Box:
			{
				IrrlichtToBulletDynamicBoxObject boxElem;
				boxElem.SerializeIn(is);
				AddBoxObject(boxElem.GetIrrBullName(), boxElem.nodePos, boxElem.nodeRot, boxElem.BulletVelocity, boxElem.BulletAngularVelocity, boxElem.scale, boxElem.GetMass()); 
				break;
			}
		case IrrlichtBulletObjectSpecificType_Capsule:
			{
				IrrlichtToBulletDynamicCapsuleObject capsuleElem;
				capsuleElem.SerializeIn(is);
				AddCapsuleObject(capsuleElem.GetIrrBullName(), capsuleElem.nodePos, capsuleElem.nodeRot, capsuleElem.BulletVelocity, capsuleElem.BulletAngularVelocity,
					capsuleElem.radius, capsuleElem.heightFromSphereCenters, capsuleElem.GetMass()); 
				break;
			}
		case IrrlichtBulletObjectSpecificType_Cone:
			{
				IrrlichtToBulletDynamicConeObject coneElem;
				coneElem.SerializeIn(is);
				AddConeObject(coneElem.GetIrrBullName(), coneElem.nodePos, coneElem.nodeRot, coneElem.BulletVelocity, coneElem.BulletAngularVelocity, coneElem.radius, coneElem.height, coneElem.GetMass()); 
				break;
			}
		case IrrlichtBulletObjectSpecificType_Cylinder:
			{
				IrrlichtToBulletDynamicCylinderObject cylinderElem;
				cylinderElem.SerializeIn(is);
				AddCylinderObject(cylinderElem.GetIrrBullName(), cylinderElem.nodePos, cylinderElem.nodeRot, cylinderElem.BulletVelocity, cylinderElem.BulletAngularVelocity,
					cylinderElem.radius, cylinderElem.height, cylinderElem.GetMass()); 
				break;
			}
		case IrrlichtBulletObjectSpecificType_StaticGraph:
			{
				IrrlichtToBulletStaticGraphObject graphElem;
				graphElem.SerializeIn(is, device);

				ThreeDGraph* newGraph = graphElem.graph;
				graphElem.graph = NULL;

				newGraph->CalculateGraph();
				newGraph->AddToSceneManager(device, device->getSceneManager());		
				
				AddStaticGraphToBullet(newGraph);

				break;
			}
		}
	}
}

void PlaygroundSimulation::SerializeIn(istream& is)
{
	Simulation::SerializeIn(is);

	is >> IrrlichtToBulletDynamicObject::showVelocity;
	is >> IrrlichtToBulletDynamicObject::showAngularVelocity;
    is >> IrrlichtToBulletDynamicObject::showNetAcceleration;
    is >> IrrlichtToBulletDynamicObject::showNetForce;
	IrrlichtToBulletDynamicObject::velocityArrowColor = SerializeInSColor(is);
	IrrlichtToBulletDynamicObject::angularVelocityArrowColor = SerializeInSColor(is);
	IrrlichtToBulletDynamicObject::accelerationArrowColor = SerializeInSColor(is);
	IrrlichtToBulletDynamicObject::forceArrowColor = SerializeInSColor(is);

	SerializeInListOfIrrlichtToBulletObjects(is);
}
void PlaygroundSimulation::SerializeOut(ostream& os)
{
	Simulation::SerializeOut(os);

	os << IrrlichtToBulletDynamicObject::showVelocity << endl;
	os << IrrlichtToBulletDynamicObject::showAngularVelocity << endl;
    os << IrrlichtToBulletDynamicObject::showNetAcceleration << endl;
    os << IrrlichtToBulletDynamicObject::showNetForce << endl;
	SerializeOutSColor(os, IrrlichtToBulletDynamicObject::velocityArrowColor);
	SerializeOutSColor(os, IrrlichtToBulletDynamicObject::angularVelocityArrowColor);
	SerializeOutSColor(os, IrrlichtToBulletDynamicObject::accelerationArrowColor);
	SerializeOutSColor(os, IrrlichtToBulletDynamicObject::forceArrowColor);

	SerializeOutListPointer(os, irrToBullConnector->objectList);
}