#include "common/Node.hpp"

using namespace Robotarium;

Node::Node(String name, UInt32 id) : mChildNodes(new NodeMap())
{
	SetNodeType(BASIC_NODE_TYPE);
	mID = id;
	mName = name;
}

Node::~Node()
{
}

NodeMapPtr& Node::GetChildNodeMap()
{
	return mChildNodes;
}

void Node::AddNode(NodePtr nodePtr)
{
	Ogre::LogManager::getSingleton().logMessage("Name >>>>>>>>>>>>>  " + nodePtr->GetName());
	Ogre::LogManager::getSingleton().logMessage("  ID >>>>>>>>>>>>>  " + Ogre::StringConverter::toString(nodePtr->GetID()));
	Ogre::LogManager::getSingleton().logMessage("Size >>>>>>>>>>>>>  " + Ogre::StringConverter::toString(nodePtr->GetNodeMapSize()));
	Ogre::LogManager::getSingleton().logMessage("About parent:");
	Ogre::LogManager::getSingleton().logMessage("Name >>>>>>>>>>>>>  " + this->GetName());
	Ogre::LogManager::getSingleton().logMessage("  ID >>>>>>>>>>>>>  " + Ogre::StringConverter::toString(this->GetID()));
	Ogre::LogManager::getSingleton().logMessage("Size >>>>>>>>>>>>>  " + Ogre::StringConverter::toString(this->GetNodeMapSize()));
	
	(*(NodeMapPtr)mChildNodes)[nodePtr->GetID()] = nodePtr;
}

UInt32 Node::GetNodeMapSize()
{
	return mChildNodes->size();
}

UInt32 Node::GetID()
{
	return this->mID;
}

void Node::SetID(UInt32 id)
{
	this->mID = id;
}

String Node::GetName()
{
	return this->mName;
}

void Node::SetName(String name)
{
	this->mName = name;
}

void Node::SetNodeType(NODE_TYPE _type)
{
	type = _type;
}

NODE_TYPE Node::GetNodeType()
{
	return type;
}