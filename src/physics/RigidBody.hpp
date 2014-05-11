#pragma once
#ifndef __RIGID_BODY_HPP__
#define __RIGID_BODY_HPP__

#include "Robotarium.hpp"
#include "PhysicsWorld.hpp"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace Robotarium
{
	namespace physic
	{
		class RigidBody: public Robotarium::graphic::SceneNodeBase
		{

		private:	RigidBody(Robotarium::String, Robotarium::UInt32);

		private:	~RigidBody(void);

		public:		void Load(void);

		public:		void Init(void);

		private:	btCollisionShape *mCollShape;
		
		private:	btRigidBody *mRigidBody;

		};
	}
}

#endif