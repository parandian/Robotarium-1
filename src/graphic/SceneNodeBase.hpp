#pragma once
//#ifndef __SCENE_NODE_BASE_HPP__
//#define __SCENE_NODE_BASE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "graphic/OgreHeaders.hpp"
#include "graphic/GraphicTypes.hpp"
#include "common/Node.hpp"

namespace Robotarium
{
	namespace graphic
	{
		class SceneNodeBase : public Node//   : public boost::enable_shared_from_this<Node>
		{
			/// \brief Constructor
			/// \param[in] scene Pointer to the parent Scene
			/// \param[in] name Name of the new Node
		public:		SceneNodeBase(String, UInt32);

					/// \brief Destructor
		public:		~SceneNodeBase();

					/// \brief Load this SceneNode and its children
		public:		virtual void Load() = 0;

					/// \brief Load this SceneNode's children
		private:	virtual void LoadChildNodes() = 0;

					/// \brief Update this SceneNode and its children
		public:		virtual void Update() = 0;

					/// \brief Update this SceneNode's children
		private:	virtual void UpdateChildNodes() = 0;

					/// \brief Terminate this SceneNode and its children
		//public:		virtual void Terminate();
		};
	}
}
//#endif