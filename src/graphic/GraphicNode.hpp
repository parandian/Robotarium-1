#pragma once
#ifndef __GRAPHIC_NODE_HPP__
#define __GRAPHIC_NODE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "graphic/OgreHeaders.hpp"
#include "graphic/GraphicTypes.hpp"
#include "graphic/Scene.hpp"
#include "graphic/SceneNode.hpp"
#include "graphic/SceneNodeBase.hpp"

namespace Robotarium
{
	namespace graphic
	{
		class GraphicNode : public SceneNodeBase//   : public boost::enable_shared_from_this<Node>
		{
					/// \brief Constructor
					/// \param[in] scene Pointer to the parent Scene
					/// \param[in] name Name of the new Node
					/// \param[in] meshName Name of the mesh associated with 
					///			   this GraphicNode. There should be a mesh
					///			   with this name in the resources, otherwise
					///			   will crash when loading.
		public:		GraphicNode(SceneNodePtr& parent, String name, String meshName);

					/// \brief Destructor
		public:		~GraphicNode();

		public:		void Load();

					/// \brief Load this SceneNode and its children
		public:		void Load(SceneNodePtr& parent);

					/// \brief Load this SceneNode's children
		private:	void LoadChildNodes();

					/// \brief Update this SceneNode and its children
		public:		void Update();

					/// \brief Update this SceneNode's children
		private:	void UpdateChildNodes();

					/// \brief Stores the mesh name associated with this GraphicNode
		private:	String mMeshName;

					/// \brief Gets the mesh name associated with this GraphicNode
		public:		String GetMeshName();

					/// \brief Gets the mesh name associated with this GraphicNode
		public:		void SetMeshName(String);

					/// \brief Stores the mesh associated with this
		private:	Ogre::Entity* mEntity;

					/// \brief Returns pointer to the Entity
		public:		Ogre::Entity* GetEntity();
		};
	}
}
#endif