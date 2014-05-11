#include "physics/PhysicsWorld.hpp"

using namespace Robotarium;
using namespace physic;

PhysicsWorld::PhysicsWorld()
{
}

PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::Load()
{
	
	mBroadphase = new btAxisSweep3(btVector3(-100,-100,-100), btVector3(100,100,100), 1024);
	
	mCollisionConfig = new btSoftBodyRigidBodyCollisionConfiguration();
	
	mDispatcher = new btCollisionDispatcher(mCollisionConfig);
	
	mSolver = new btSequentialImpulseConstraintSolver();



	mWorld = new btSoftRigidDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfig);
	
	mWorld->getDispatchInfo().m_enableSPU = true;
	
	mWorld->setGravity(btVector3(0,-9.8,0));
}


btDynamicsWorld * PhysicsWorld::GetBulletWorld(void)
{
	return this->mWorld;
}

