#pragma once
#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "graphic/OgreHeaders.hpp"
#include "graphic/GraphicTypes.hpp"
#include "common/BaseObject.hpp"


namespace Robotarium
{
	class Node : BaseObject//   : public boost::enable_shared_from_this<Node>
	{
		/// \brief Constructor
		/// \param[in] name Name of the new Node
		/// \param[in] name A unique ID for the new Node
	public:		Node(String, UInt32);

				/// \brief Destructor
	public:		~Node();

				/// \brief Set node type
	protected:	void SetNodeType(NODE_TYPE _type);

				/// \brief Get node type
	public:		NODE_TYPE GetNodeType();

				/// \brief Stores type of the node
	private:	NODE_TYPE type;

				/// \brief Contains child nodes
	private:	NodeMapPtr mChildNodes;

				/// \brief Returns the pointer to child nodes
	public:		NodeMapPtr& GetChildNodeMap();

				/// \brief Returns size of the child node map
	public:		UInt32 GetNodeMapSize();

				/// \brief Adds a new Node to the child node map
				/// \param[in] nodePtr Shared pointer to the node
				///			   which is going to be added as child
	public:		void AddNode(NodePtr nodePtr);

				/// \brief Returns the ID representing this Node
	public:		UInt32 GetID();

				/// \brief Returns the name of Node
	public:		String GetName();

				/// \brief Returns the ID representing this Node
	public:		void SetID(UInt32);

				/// \brief Returns the name of Node
	public:		void SetName(String);

				/// \brief ID of the Node
	private:	UInt32 mID;

				/// \brief Name of the Node
	private:	String mName;
	};
}
#endif