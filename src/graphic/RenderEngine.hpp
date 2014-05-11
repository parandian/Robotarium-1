#pragma once
#ifndef __RENDERENGINE_HPP__
#define __RENDERENGINE_HPP__

#include <vector>
#include <string>
#include <Windows.h>

#include <boost/make_shared.hpp>
#include <boost/thread.hpp>

#include "common/Types.hpp"
#include "graphic/GraphicTypes.hpp"
#include "graphic/OgreHeaders.hpp"
#include "common/SingletonT.hpp"
#include "graphic/Scene.hpp"

namespace Robotarium
{
	/// \ingroup Robotarium_graphics
	/// \brief Graphics Rendering namespace
	namespace graphic
	{
		/// \addtogroup Robotarium_graphics
		/// \{

		/// \class RenderEngine RenderEngine.hpp graphic/RenderEngine.hpp
		/// \brief Wrapper Class for Ogre3d
		///
		/// Provides the interface to load, initialize the rendering engine.
		class RenderEngine: public SingletonT<RenderEngine>
		{

				/// \brief Constructor
		private:	RenderEngine(void);

				/// \brief Destructor
		private: virtual ~RenderEngine(void);

				/// \brief Load the parameters for Ogre. Load must happen before Init.
		public: void Load();

				/// \brief Initialize Ogre. Load must happen before Init.
		public: void Init();

				/// \brief Tears down the rendering engine
		public: void Terminate();

				/// \brief Setup initial resource paths.
		public: void SetupResources();

				/// \brief Setup the render system.
		public: void SetupRenderSystem();

				/// \brief Create a scene
				/// \param[in] _name The name of the scene.
		public: ScenePtr& CreateScene(const std::string &_name);

				/// \brief Return the Scene
		public: ScenePtr& GetScene();

				/// \brief Start rendering
		public: void RunRenderLoop();

				/// \brief Returns the pointer to the root object
		public:	Ogre::Root *GetOgreRoot();

				/// \brief Pointer to the root object
		private: Ogre::Root *root;

				/// \brief Pointer to the Scene Manager
		public: ScenePtr mScene;

				/// \brief Initialized.
		private: bool initialized;

				 /// \brief Pointer the log manager
		private: Ogre::LogManager *logManager;

				 /// \brief Makes this class a singleton.
		private: friend class SingletonT<RenderEngine>;

				 /// \brief Thread used to run rendering loop
		private: boost::thread mThread;

				 /// \brief Render loop worker
		private: void RenderLoopWorker();
		};
	}
}
#endif