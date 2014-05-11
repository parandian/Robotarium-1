#pragma once
#ifndef __AXIS_DEBUG_SHAPE_HPP__
#define __AXIS_DEBUG_SHAPE_HPP__

#include "DebugShape.hpp"
#include "SceneNode.hpp"

namespace Robotarium
{
	namespace graphic
	{
		class AxisDebugShape : public DebugShape
		{
			
					/// \brief Constructor
		public:		AxisDebugShape(SceneNodePtr&);

					/// \brief Destructor
		public:		~AxisDebugShape();

		};
	}
}

#endif