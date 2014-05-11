#pragma once
#ifndef __PHYSICTYPES_HPP__
#define __PHYSICTYPES_HPP__

#include <vector>
#include <map>
#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include "common/Types.hpp"

namespace Robotarium
{
	namespace physic
	{

		class RigidBody;

		class CollisionShape;

		/// \def RigidBodyPtr
		/// \brief Shared pointer to RigidBody
		typedef boost::shared_ptr<RigidBody> RigidBodyPtr;

	}
}
#endif
