#include "graphic/GraphicNode.hpp"

using namespace Robotarium;
using namespace graphic;

GraphicNode::GraphicNode(SceneNodePtr& parent, String name, String meshName)
	: SceneNodeBase(name, parent->GetNodeMapSize() + 1)
{
	SetNodeType(GRAPHIC_NODE_TYPE);

	//this->mSceneNode = RenderEngine::GetSingleton()->GetScene()->GetOgreSceneMgr()->getRootSceneNode()->createChildSceneNode(name);
	this->SetID(parent->GetNodeMapSize() + 1);

	this->SetName(name);

	this->SetMeshName(meshName);

	//RenderEngine::GetSingleton()->GetScene()->AddNode(boost::shared_ptr<Node>(this));
}

GraphicNode::~GraphicNode()
{
}

String GraphicNode::GetMeshName()
{
	return mMeshName;
}

void GraphicNode::SetMeshName(String meshName)
{
	this->mMeshName = meshName;
}

void GraphicNode::Load()
{
}

void GraphicNode::Load(SceneNodePtr& parent)
{
	Ogre::LogManager::getSingleton().logMessage(GetName() + ": Loading.");

	Ogre::SceneManager* sceneMgr = RenderEngine::GetSingleton()->GetScene()->GetOgreSceneMgr();

	Ogre::LogManager::getSingleton().logMessage(GetMeshName());

	Ogre::Entity* mEntity = sceneMgr->createEntity(GetName(), GetMeshName());

	Ogre::LogManager::getSingleton().logMessage(GetName() + ": Attaching Node.");

	parent->GetOgreSceneNode()->attachObject(mEntity);
	
	Ogre::LogManager::getSingleton().logMessage(GetName() + ": Fnished Loading.");

	mEntity->getMesh()->updateMaterialForAllSubMeshes();
}

void GraphicNode::Update()
{
}

void GraphicNode::LoadChildNodes()
{
	//NodeMapPtr childNodeMap = GetChildNodeMap();

	//NodeMap::const_iterator nodeIterator = childNodeMap->begin();
	//NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	//for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	//	boost::static_pointer_cast<GraphicNode>
	//		(nodeIterator->second)->Load(boost::make_shared<SceneNode>(*this));
}


void GraphicNode::UpdateChildNodes()
{
	
	NodeMapPtr childNodeMap = GetChildNodeMap();
	
	NodeMap::const_iterator nodeIterator = childNodeMap->begin();
	NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
		boost::static_pointer_cast<GraphicNode>
			(nodeIterator->second)->Update();
}
Ogre::Entity* GraphicNode::GetEntity()
{
	return mEntity;
}
//
//void GraphicNode::AttachEntity(Ogre::Entity* entity)
//{
//	this->mSceneNode->attachObject(entity);
//}
//
//void GraphicNode::AttachEntity(String entityName, String meshName)
//{
//	Ogre::Entity* entity = RenderEngine::GetSingleton()->GetScene()->GetOgreSceneMgr()->createEntity(entityName, meshName);
//	this->AttachEntity(entity);
//}