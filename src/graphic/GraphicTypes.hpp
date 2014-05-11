#pragma once
#ifndef __GRAPHICTYPES_HPP__
#define __GRAPHICTYPES_HPP__

#include <vector>
#include <map>
#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include "common/Types.hpp"

namespace Robotarium
{

	namespace graphic
	{

		class RenderEngine;

		class Scene;

		class GraphicNode;

		class Camera;

		class CameraSceneNode;

		class SceneNodeBase;

		class SceneNode;

		class DebugShape;

		class AxisDebugShape;

		/// \def NodePtr
		/// \brief Shared pointer to Node
		typedef boost::shared_ptr<SceneNode> SceneNodePtr;

		/// \def Node_M
		/// \brief Map of visuals and their names
		typedef std::map<UInt32, SceneNodePtr> SceneNodeMap;

		/// \def Node_MPtr
		/// \brief Pointer to the map of visuals and their names
		typedef boost::shared_ptr<SceneNodeMap> SceneNodeMapPtr;

		/// \def ScenePtr
		/// \brief Shared pointer to Scene
		typedef boost::shared_ptr<Scene> ScenePtr;

		/// \def CameraPtr
		/// \brief Shared pointer to Camera
		typedef boost::shared_ptr<Camera> CameraPtr;

		/// \def Camera_M
		/// \brief Map of visuals and their names
		typedef std::map<UInt32, CameraPtr> CameraMap;

		/// \def Camera_MPtr
		/// \brief Pointer to the map of visuals and their names
		typedef boost::shared_ptr<CameraMap> CameraMapPtr;

		/// \def NodePtr
		/// \brief Shared pointer to Node
		typedef boost::shared_ptr<GraphicNode> GraphicNodePtr;

		/// \def Node_M
		/// \brief Map of visuals and their names
		typedef std::map<UInt32, GraphicNodePtr> GraphicNodeMap;

		/// \def Node_MPtr
		/// \brief Pointer to the map of visuals and their names
		typedef boost::shared_ptr<GraphicNodeMap> GraphicNodeMapPtr;

		/// \def CameraSceneNodePtr
		/// \brief Shared pointer to Node
		typedef boost::shared_ptr<CameraSceneNode> CameraSceneNodePtr;

		/// \def CameraSceneNode_M
		/// \brief Map of visuals and their names
		typedef std::map<UInt32, CameraSceneNodePtr> CameraSceneNodeMap;

		/// \def CameraSceneNode_MPtr
		/// \brief Pointer to the map of visuals and their names
		typedef boost::shared_ptr<CameraSceneNodeMap> CameraSceneNodeMapPtr;
	}
}
#endif
