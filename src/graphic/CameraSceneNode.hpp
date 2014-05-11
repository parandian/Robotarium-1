#pragma once
#ifndef __CAMERA_NODE_HPP__
#define __CAMERA_NODE_HPP__

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
		class CameraSceneNode : public SceneNodeBase//   : public boost::enable_shared_from_this<Node>
		{
					/// \brief Constructor
					/// \param[in] scene Pointer to the parent Scene
					/// \param[in] name Name of the new Node
					/// \param[in] meshName Name of the mesh associated with 
					///			   this GraphicNode. There should be a mesh
					///			   with this name in the resources, otherwise
					///			   will crash when loading.
		public:		CameraSceneNode(SceneNodePtr& parent, String name, UInt32 Id, String HWND, Vec2 viewportSize, Vec3 position, Vec3 lapPoint);

					/// \brief Destructor
		public:		~CameraSceneNode();

					/// \brief Loads the camera. This method creates 
					///	the actual Ogre camera and should be called 
					/// after RenderEngine is loaded and initialized.
		public:		void Load(SceneNodePtr& parent);

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

		//			/// \brief Returns shared pointer for this class
		//public:		boost::shared_ptr<Camera> GetPtr()
		//			{
		//				return shared_from_this();
		//			}

					/// \brief Set main cameras position
		public:		void SetPosition(Real x, Real y, Real z);
					void SetPosition(Vec3 pos);

					/// \brief Sets the orientation of the camera
		public:		void SetOrientation(Quat rot);

					/// \brief Sets the orientation of the camera
		public:		void SetOrientation(Real angle, Vec3 axis);

					/// \brief Sets the look-at-point of the camera
		public:		void SetLookAtPoint(Vec3 lap);

					/// \brief Sets the field of view for the camera
		public:		void SetFOV(Real fov);

					/// \brief Get position
		public:		Vec3 GetPosition();

					/// \brief Pointer to the viewport
		private:	Ogre::Viewport* mViewport;

					/// \brief Pointer to the Ogre camera
		private:	Ogre::Camera * mCamera;

					/// \brief Pointer to the Ogre RenderWindow
		private:	Ogre::RenderWindow * mRenderWindow;

					/// \brief Pointer to corresponding Ogre SceneNode
		private:	Ogre::SceneNode* mOgreSceneNode;

					/// \brief Stores viewport dimension sizes for 
					///	current camera.
		private:	Vec2 mViewportSize;

					/// \brief Stores position of the camera
		private:	Vec3 mPosition;

					/// \brief Stores rosition of the camera
		private:	Quat mOrientation;

					/// \brief Stores coordinates of look at point of the
					///	camera relative to its parent node.
		private:	Vec3 mLapPoint;

					/// \brief Stores the target hwnd for camera's output.
		private:	String mHWND;

		};
	}
}
#endif