#pragma once
#ifndef __SCENE_NODE_HPP__
#define __SCENE_NODE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "graphic/OgreHeaders.hpp"
#include "graphic/GraphicTypes.hpp"
#include "graphic/CameraSceneNode.hpp"
#include "graphic/RenderEngine.hpp"
#include "graphic/GraphicNode.hpp"
#include "graphic/SceneNodeBase.hpp"
#include "graphic/AxisDebugShape.hpp"

namespace Robotarium
{
	namespace graphic
	{
		class SceneNode : public SceneNodeBase, public boost::enable_shared_from_this<SceneNode>
		{
					/// \brief Constructor
					/// \param[in] scene Pointer to the parent Scene
					/// \param[in] name Name of the new Node
					/// \param[in] Id Unique ID of the new Node
		public:		SceneNode(SceneNodePtr&, String, UInt32);

					/// \brief Constructor
					/// \param[in] name Name of the new Node
					/// \param[in] Id Unique ID of the new Node
		public:		SceneNode(String, UInt32);

					/// \brief Destructor
		public:		~SceneNode();

					/// \brief Load this SceneNode
		public:		void Load();

					/// \brief Load this SceneNode's children
		private:	void LoadChildNodes();

					/// \brief Unload this SceneNode
		public:		void Unload();

					/// \brief Update this SceneNode and its children
		public:		void Update();

					/// \brief Update this SceneNode's children
		private:	void UpdateChildNodes();

					/// \brief Pointer to corresponding Ogre SceneNode
		private:	Ogre::SceneNode* mOgreSceneNode;

					/// \brief Returns pointer to Ogre SceneNode
		public:		Ogre::SceneNode* GetOgreSceneNode();


					/// \brief Set position
		public:		void SetPosition(Real x, Real y, Real z);
					void SetPosition(Vec3 pos);
					
					/// \brief Get position
		public:		Vec3 GetPosition();

					/// \brief Get position
		public:		Quat GetOrientation();

					/// \brief Stores position of the camera
		private:	Vec3 mPosition;

					/// \brief Stores rosition of the camera
		private:	Quat mOrientation;

					/// \brief Set orientation
		public:		void SetOrientation(Ogre::Quaternion rot);

					/// \brief Set orientation
		public:		void SetOrientation(Real angle, Vec3 axis);

					/// \brief Set look-at-point
		public:		void SetLookAtPoint(Vec3 lap);
					/// \brief Terminate this SceneNode and its children
		//public:		virtual void Terminate();
		private:	boost::shared_ptr<AxisDebugShape> mAxisDebugShape;
		};
	}
}
#endif