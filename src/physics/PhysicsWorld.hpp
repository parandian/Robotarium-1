#pragma once
#ifndef __PHYSICS_WORLD_HPP__
#define __PHYSICS_WORLD_HPP__

#include "Robotarium.hpp"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include "BtOgrePG.h"
#include "BtOgreGP.h"
#include "BtOgreExtras.h"
#include "BtOgreSoftBody.h"

#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "MeshUtils.h"

namespace Robotarium
{
	/// \ingroup Robotarium_physics
	/// \brief Physics Engine namespace
	namespace physic
	{		
		/// \addtogroup Robotarium_physics
		/// \{

		/// \class PhysicsEngine PhysicsEngine.hpp physics/PhysicsEngine.hpp
		/// \brief 
		///
		/// 
		class PhysicsWorld: public SingletonT<PhysicsWorld>
		{

		private:	PhysicsWorld();

		private:	~PhysicsWorld();

		public:		void	Load();

		public:		void	Init();

		private:	btDynamicsWorld *mWorld;

		private:	BtOgre::DebugDrawer *dbgdraw;

		private:	btAxisSweep3 *mBroadphase;

		private:	btDefaultCollisionConfiguration *mCollisionConfig;

		private:	btCollisionDispatcher *mDispatcher;

		private:	btSequentialImpulseConstraintSolver *mSolver;

		private:	btDynamicsWorld *GetBulletWorld(void);

					/// \brief Thread used to run rendering loop
		private:	boost::thread mThread;

					/// \brief Render loop worker
		private:	void WorldStepWorker();
		};
	}
}

#endif