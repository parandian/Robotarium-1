#pragma once

#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <string>
#include <stdint.h>
#include "common/BaseObject.hpp"
#include "graphic/OgreHeaders.hpp"

namespace Robotarium
{

	typedef enum NODE_TYPE_ENUM
	{
		BASIC_NODE_TYPE = 0,
		SCENE_NODE_TYPE,
		GRAPHIC_NODE_TYPE,
		CAMERA_SCENE_NODE_TYPE,
	} NODE_TYPE;

	typedef int8_t Int8;
	typedef int16_t Int16;
	typedef int32_t Int32;

	typedef uint8_t UInt8;
	typedef uint16_t UInt16;
	typedef uint32_t UInt32;

	typedef double Real;

	typedef Ogre::Vector2 Vec2;
	typedef Ogre::Vector3 Vec3;
	typedef Ogre::Quaternion Quat;

	typedef Ogre::Radian Radian;
	typedef Ogre::Degree Degree;

	typedef std::string String;


	class Node;

	/// \def NodePtr
	/// \brief Shared pointer to Node
	typedef boost::shared_ptr<Node> NodePtr;

	/// \def Node_M
	/// \brief Map of visuals and their names
	typedef std::map<UInt32, NodePtr> NodeMap;

	/// \def Node_MPtr
	/// \brief Pointer to the map of visuals and their names
	typedef boost::shared_ptr<NodeMap> NodeMapPtr;

}
#endif