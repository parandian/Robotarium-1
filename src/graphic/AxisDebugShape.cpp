#include "AxisDebugShape.hpp"

using namespace Robotarium;
using namespace graphic;

AxisDebugShape::AxisDebugShape(SceneNodePtr& _scenenode)
{
	static const char * matName = "axis_mat";
    Ogre::MaterialPtr mtl = Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
    mtl->setReceiveShadows(false);
    mtl->setSceneBlending( Ogre::SBT_TRANSPARENT_ALPHA );
    mtl->setDepthBias( 0.1, 0 );
    Ogre::TextureUnitState * tu = mtl->getTechnique(0)->getPass(0)->createTextureUnitState();
    assert( tu );
    tu->setColourOperationEx( Ogre::LBX_SOURCE1, Ogre::LBS_DIFFUSE );
    mtl->getTechnique(0)->setLightingEnabled(false);


	// create ManualObject
	this->mShape = RenderEngine::GetSingleton()->GetScene()->GetOgreSceneMgr()->createManualObject();
	Ogre::ColourValue r(1, 0, 0);  
	Ogre::ColourValue g(0, 1, 0);  
	Ogre::ColourValue b(0, 0, 1);  
	// specify the material (by name) and rendering type
	mShape->begin(matName, Ogre::RenderOperation::OT_LINE_LIST);
	
	mShape->position(0, 0, 0);
	mShape->colour(r);
	mShape->position(1, 0, 0);
	mShape->colour(r);
	
	mShape->position(0, 0, 0);
	mShape->colour(g);
	mShape->position(0, 1, 0);
	mShape->colour(g);
	
	mShape->position(0, 0, 0);
	mShape->colour(b);
	mShape->position(0, 0, 1);
	mShape->colour(b);
	
	// tell Ogre, your definition has finished
	mShape->end();

	// add ManualObject to the RootSceneNode (so it will be visible)
	_scenenode->GetOgreSceneNode()->attachObject(mShape);
	//mScene->Load();
}

AxisDebugShape::~AxisDebugShape()
{
}