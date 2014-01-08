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

#ifndef WX_IRR_SPRING_SCENE_NODE
#define WX_IRR_SPRING_SCENE_NODE

#include "../../IrrlichtInclude.h"
#include "../../General/GeneralFunctions.h"
#include "../Physics Object/PhysicsObject.h"

using namespace Physics_Engine;

class SpringSceneNode : public scene::ISceneNode
{
private:
	core::aabbox3d<f32> boundingBox;
    irr::core::array<video::S3DVertex> vertices;
	irr::core::array<u16> indices;
	video::SMaterial material;
	SColor color;

	ISceneNode* obj1;
	ISceneNode* obj2;

	Vector3 pos1;
	Vector3 pos2;

public:
	SpringSceneNode(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id, ISceneNode* obj1 = 0, ISceneNode* obj2 = 0);

	virtual void OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();
    }

	virtual void render()
    {
        video::IVideoDriver* driver = SceneManager->getVideoDriver();

        driver->setMaterial(material);
        driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);

		if (obj1 && obj2)
		{
			Vector3 pos1 = obj1->getPosition();
			Vector3 pos2 = obj2->getPosition();
			UpdatePositions(pos1, pos2);
		}
		driver->drawVertexPrimitiveList(vertices.pointer(), vertices.size(), indices.pointer(), indices.size()/2, video::EVT_STANDARD, scene::EPT_LINES, video::EIT_16BIT);
    }

	void UpdatePositions(Vector3& _pos1, Vector3& _pos2);

	void SetObjects(ISceneNode* obj1, ISceneNode* obj2);

	virtual const core::aabbox3d<f32>& getBoundingBox() const
    {
        return boundingBox;
    }

    virtual u32 getMaterialCount() const
    {
        return 1;
    }

    virtual video::SMaterial& getMaterial(u32 i)
    {
        return material;
    }
	
	ISceneNode* GetSceneNode1()
	{
		return obj1;
	}

	ISceneNode* GetSceneNode2()
	{
		return obj2;
	}

	SColor& GetColor()
	{
		return color;
	}

	void SetColor(SColor& _color)
	{
		color = _color;
		for(unsigned int i = 0; i < vertices.size(); i++)
		{
			vertices[i].Color = _color;
		}
	}
};


#endif