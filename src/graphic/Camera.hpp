#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "graphic/OgreHeaders.hpp"
#include "graphic/GraphicTypes.hpp"
#include "graphic/Scene.hpp"

namespace Robotarium
{
	namespace graphic
	{
		class Camera : BaseObject//   : public boost::enable_shared_from_this<Camera>
		{

					/// \brief Constructor
		public:		Camera(String name, String HWND,
						Vec2 viewportSize, Vec3 position = Vec3(0.0f, 0.0f, 0.0f), 
						Vec3 lapPosition = Vec3(0.0f, 0.0f, 1.0f));

					/// \brief Destructor
		public:		~Camera();

					/// \brief Loads the camera. This method creates 
					///	the actual Ogre camera and should be called 
					/// after RenderEngine is loaded and initialized.
		public:		void Load();

					/// \brief Returns the ID representing this Camera
		public:		UInt32 GetID();

		//			/// \brief Returns shared pointer for this class
		//public:		boost::shared_ptr<Camera> GetPtr()
		//			{
		//				return shared_from_this();
		//			}

					/// \brief Set main cameras position
		public:		void SetPosition(Real x, Real y, Real z);
					void SetPosition(Vec3 pos);

					/// \brief Sets the orientation of the camera
		public:		void SetOrientation(Ogre::Quaternion rot);

					/// \brief Sets the look-at-point of the camera
		public:		void SetLookAtPoint(Vec3 lap);

					/// \brief Sets the field of view for the camera
		public:		void SetFOV(Real fov);

					/// \brief Pointer to the viewport
		private:	Ogre::Viewport* mViewport;

					/// \brief Pointer to the Ogre camera
		private:	Ogre::Camera * mCamera;

					/// \brief Pointer to the Ogre camera node
		private:	Ogre::SceneNode * mCameraSceneNode;

					/// \brief Pointer to the Ogre RenderWindow
		private:	Ogre::RenderWindow * mRenderWindow;

					/// \brief Stores viewport dimension sizes for 
					///	current camera.
		private:	Vec2 mViewportSize;

					/// \brief Stores position of the camera relative to
					///	its parent node.
		private:	Vec3 mPosition;

					/// \brief Stores coordinates of look at point of the
					///	camera relative to its parent node.
		private:	Vec3 mLapPoint;

					/// \brief Stores the name of the camera.
		private:	String mName;

					/// \brief Stores the target hwnd for camera's output.
		private:	String mHWND;

					/// \brief Stores the unique ID of the current camera
		private:	UInt32 mID;

		};
	}
}


#endif