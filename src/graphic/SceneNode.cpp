#include "graphic/SceneNode.hpp"

using namespace Robotarium;
using namespace graphic;


SceneNode::SceneNode(String name, UInt32 Id)
	:SceneNodeBase(name, Id)
{
	SetNodeType(SCENE_NODE_TYPE);
	this->SetID(Id);
	this->SetName(name);
}

SceneNode::~SceneNode()
{
}

void SceneNode::Load()
{
	Ogre::LogManager::getSingleton().logMessage("##############" + GetName() + ": Loading.");

	mOgreSceneNode = RenderEngine::GetSingleton()->
		GetScene()->GetOgreSceneMgr()->getRootSceneNode()->createChildSceneNode(GetName());

	this->mAxisDebugShape = boost::shared_ptr<AxisDebugShape>(new AxisDebugShape(this->shared_from_this()));
	//if(parent)
	//{
	//	Ogre::LogManager::getSingleton().logMessage(GetName() + ": Inside if.");
	//	Ogre::LogManager::getSingleton().logMessage(GetName() + RenderEngine::GetSingleton()->
	//		GetScene()->GetOgreSceneMgr()->getRootSceneNode()->getName());
	//}

	//if (parent) // check if this is the RootSceneNode or not
	//{
	//	parent->AddNode(boost::static_pointer_cast<Node>
	//		(boost::make_shared<SceneNode>(*this)));
	//}

	//LoadChildNodes();

}

void SceneNode::Update()
{

}

Ogre::SceneNode* SceneNode::GetOgreSceneNode()
{
	return mOgreSceneNode;
}

void SceneNode::LoadChildNodes()
{
	Ogre::LogManager::getSingleton().logMessage(GetName() + ": Loading child nodes: " + Ogre::StringConverter::toString(this->GetNodeMapSize()));

	NodeMapPtr childNodeMap = GetChildNodeMap();

	NodeMap::const_iterator nodeIterator = childNodeMap->begin();
	NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	{
		switch(nodeIterator->second->GetNodeType())
		{
		case Robotarium::SCENE_NODE_TYPE:
			boost::static_pointer_cast<SceneNodeBase>(nodeIterator->second)->Load();
			break;
		case Robotarium::GRAPHIC_NODE_TYPE:
			boost::static_pointer_cast<GraphicNode>(nodeIterator->second)->Load(shared_from_this());
			break;
		case Robotarium::CAMERA_SCENE_NODE_TYPE:
			boost::static_pointer_cast<CameraSceneNode>(nodeIterator->second)->Load(shared_from_this());
			break;
		}
	}
}


void SceneNode::UpdateChildNodes()
{

	NodeMapPtr childNodeMap = GetChildNodeMap();

	NodeMap::const_iterator nodeIterator = childNodeMap->begin();
	NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
		boost::static_pointer_cast<SceneNode>
		(nodeIterator->second)->Update();
}


void SceneNode::Unload()
{
	mOgreSceneNode->detachAllObjects();

	delete mOgreSceneNode;
}

void SceneNode::SetPosition(Vec3 pos)
{
	mPosition = pos;
	this->mOgreSceneNode->setPosition(mPosition);
}

Vec3 SceneNode::GetPosition()
{
	return mPosition;
}

Quat SceneNode::GetOrientation()
{
	return mOrientation;
}

void SceneNode::SetOrientation(Quat rot)
{
	mOrientation = rot;
	this->mOgreSceneNode->setOrientation(mOrientation);
}

void SceneNode::SetOrientation(Real angle, Vec3 axis)
{
	mOrientation.FromAngleAxis(Ogre::Radian(angle), axis);
	this->mOgreSceneNode->setOrientation(mOrientation);
}
