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

#ifndef WX_IRR_GRID_SCENENODE
#define WX_IRR_GRID_SCENENODE

#include "../IrrlichtInclude.h"

class GridSceneNode : public scene::ISceneNode
{
private:
	core::aabbox3d<f32> boundingBox;
    irr::core::array<video::S3DVertex> vertices;
	irr::core::array<u16> indices;
	video::SMaterial material;
	SColor color;

public:
	GridSceneNode(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id, SColor& _color, unsigned int widthResolution = 101, unsigned int heightResolution = 101,
		float widthSpacing = 5.0f, float heightSpacing = 5.0f);

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
		driver->drawVertexPrimitiveList(vertices.pointer(), vertices.size(), indices.pointer(), indices.size()/2, video::EVT_STANDARD, scene::EPT_LINES, video::EIT_16BIT);
    }

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