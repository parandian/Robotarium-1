#include "graphic/SceneNodeBase.hpp"

using namespace Robotarium;
using namespace graphic;

SceneNodeBase::SceneNodeBase(String name, UInt32 Id): 
	Node(name, Id)
{
	this->SetID(Id);
	this->SetName(name);
}

SceneNodeBase::~SceneNodeBase()
{
}
