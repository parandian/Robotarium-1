#pragma once
#ifndef __DEBUG_SHAPE_HPP__
#define __DEBUG_SHAPE_HPP__

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "graphic/OgreHeaders.hpp"

namespace Robotarium
{
	namespace graphic
	{
		class DebugShape
		{
					/// \brief Constructor
		public:		DebugShape();

					/// \brief Destructor
		public:		~DebugShape();

					/// \brief Pointer to the Ogre Manual Object
		public:		Ogre::ManualObject* mShape;
		};
	}
}

#endif