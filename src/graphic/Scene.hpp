#pragma once
#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "graphic/OgreHeaders.hpp"
#include "graphic/GraphicTypes.hpp"
#include "graphic/RenderEngine.hpp"
#include "graphic/Camera.hpp"
#include "graphic/SceneNodeBase.hpp"
#include "graphic/SceneNode.hpp"
#include "common/Node.hpp"


namespace Robotarium
{
	namespace graphic
	{
		class Scene//  : public boost::enable_shared_from_this<Scene>
		{
			/// \brief Constructor
		public:		Scene(void);

					/// \brief Destructor
		public:		~Scene(void);

		private:	SceneNodePtr mRootSceneNode;

		public:		SceneNodePtr& GetRootSceneNode()
					{
						return mRootSceneNode;
					}

					/// \brief Load RootSceneNode and its children
		public:		void Load();


					/// \brief Terminate SceneManager
		public:		void Terminate();


		//			/// \brief Returns shared pointer for this class
		//public:		boost::shared_ptr<Scene> GetPtr()
		//			{
		//				return shared_from_this();
		//			}

					/// \brief Contains Cameras of the overall scene
		private:	CameraMapPtr mCameraMap;

					/// \brief Returns the pointer to cameras
		public:		CameraMapPtr& GetCameraMap();

					/// \brief Returns size of the camera node map
		public:		UInt32 GetCameraMapSize();

					/// \brief !! DO NOT CALL THIS BY YOURSELF !! Adds a new Camera to the scene
		public:		void AddCamera(CameraPtr& Node);

					/// \brief Pointer to the Ogre SceneManager
		private:	Ogre::SceneManager * mSceneMgr;

					/// \brief Returns the pointer to Ogre SceneMgr
		public:		Ogre::SceneManager * GetOgreSceneMgr();
					
					/// \brief Loads all cameras that are already added
		public:		void LoadAllCameras();

		};
	}
}
#endif