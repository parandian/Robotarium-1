/*
 *  BtOgreSoftBody.cpp
 *  pixtream-ogre
 *
 *  Created by Luiz Geovani Vier <lgvier@gmail.com> on 4/6/09.
 *  Copyright 2009 pixtream.com.br. All rights reserved.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 */

#include "BtOgreSoftBody.h"

namespace BtOgre
{
	
	StaticMeshToSoftBodyConverter::StaticMeshToSoftBodyConverter(btSoftBodyWorldInfo* worldInfo, Ogre::Renderable *rend, const Ogre::Matrix4 &transform) 
		: StaticMeshToShapeConverter(rend, transform), mWorldInfo(worldInfo) {}
	StaticMeshToSoftBodyConverter::StaticMeshToSoftBodyConverter(btSoftBodyWorldInfo* worldInfo, Ogre::Entity *entity,   const Ogre::Matrix4 &transform) 
		: StaticMeshToShapeConverter(entity, transform), mWorldInfo(worldInfo) {}
	StaticMeshToSoftBodyConverter::StaticMeshToSoftBodyConverter(btSoftBodyWorldInfo* worldInfo) 
		: StaticMeshToShapeConverter(), mWorldInfo(worldInfo) {}
	
	
	btSoftBody* StaticMeshToSoftBodyConverter::createSoftBodyFromTrimesh()
	{
		
		BtOgreSoftBody *s = new BtOgreSoftBody(mWorldInfo);
		return s->create(mEntity, mVertexCount, mVertexBuffer, mIndexCount, mIndexBuffer);
	}
	
	///////
	
	BtOgreSoftBody::BtOgreSoftBody(btSoftBodyWorldInfo* worldInfo)
		: mWorldInfo(worldInfo), mEntity(0), mSoftBody(0)
	{
	}
	
	BtOgreSoftBody::~BtOgreSoftBody()
	{
		delete[] mDupVertices;
		delete[] mNewIndexes;
	}
	
	btSoftBody* BtOgreSoftBody::create(Ogre::Entity *entity, const unsigned int vertexCount, const Ogre::Vector3* vertexBuffer, const unsigned int indexCount, const unsigned int* indexBuffer)
	{
		
		assert(vertexCount && (indexCount >= 6) && 
			   ("Mesh must have some vertices and at least 6 indices (2 triangles)"));
		
		static int createCount = 0;
		
		internalId = createCount;
		createCount++;
		printf("Creating softbody %d\n", internalId);
		
		mEntity = entity;
		mDupVertices = new int[vertexCount];
		mNewIndexes = new int[vertexCount];
		mDupVerticesCount = 0;
		
		int i,j;
		
		for(i=0; i < vertexCount; i++)
		{
			Ogre::Vector3 v1 =  vertexBuffer[i];
			mDupVertices[i] = -1;
			mNewIndexes[i] = i - mDupVerticesCount;
			for(j=0; j < i; j++)
			{
				Ogre::Vector3 v2 =  vertexBuffer[j];
				if (v1 == v2) {
					mDupVertices[i] = j;
					mDupVerticesCount++;
					break;
				}
			}
		}
		printf("dupVerticesCount %d\n", mDupVerticesCount);
		
		const int newVertexCount = vertexCount - mDupVerticesCount;
		printf("newVertexCount %d\n", newVertexCount);
		//btScalar *vertices;
		//vertices = (btScalar *) malloc(newVertexCount * 3); 
		btScalar *vertices = new btScalar[newVertexCount * 3];
		//btScalar vertices[newVertexCount * 3];
		//btScalar vertices[3];
		for(i=0, j=0; i < vertexCount; i++)
		{
			if (mDupVertices[i] == -1) {
				Ogre::Vector3 v =  vertexBuffer[i];
				vertices[j++] = v.x;
				vertices[j++] = v.y;
				vertices[j++] = v.z;
			}
		}
		
		//int *indexes;
		//indexes = (int *) malloc(indexCount); 
		//int indexes[indexCount];
		int idx;
		int *indexes = new int[indexCount];
		for(i=0; i < indexCount; i++)
		{
			indexes[i] = getBulletIndex(indexBuffer[i]);
		}
		int ntriangles = indexCount / 3;
		
		mSoftBody = btSoftBodyHelpers::CreateFromTriMesh(*mWorldInfo, vertices, indexes, ntriangles);
		
		btTransform	trs;
		trs.setIdentity();
		trs.setOrigin(Convert::toBullet(entity->getParentNode()->getPosition()));
		trs.setRotation(Convert::toBullet(entity->getParentNode()->getOrientation()));
		mSoftBody->transform(trs);
		
		mSoftBody->setUserPointer(this);
		return mSoftBody;
	}
	
	int BtOgreSoftBody::getBulletIndex(int idx) {
		int idxDup = mDupVertices[idx];
		//int idxDup = -1;
		return mNewIndexes[idxDup == -1 ? idx : idxDup];
	}
	
	void BtOgreSoftBody::updateOgreMesh()
	{
		Ogre::Node *ogreNode = mEntity->getParentNode();
		
		//printf("updateOgreMesh %d %s %s\n", internalId, mEntity->getName().c_str(), ogreNode->getName().c_str());
		
		Ogre::MeshPtr mesh = mEntity->getMesh();
		Ogre::Mesh::SubMeshIterator subMeshI = mesh->getSubMeshIterator();
		Ogre::SubMesh* subMesh = NULL;
		
		Ogre::VertexData* vData = NULL;
		Ogre::VertexDeclaration* vDeclaration = NULL;
		const Ogre::VertexElement* vPosElement = NULL;
		
		bool isSharedVerticesAdded = false;
		unsigned short bufferIndex = 0;
		Ogre::HardwareVertexBufferSharedPtr vBuffer;
		
		// Can not do arithmetic operations on void*
		unsigned char* lockedMem = NULL;
		float* vPosition;
		
		btSoftBody::tNodeArray& btNodes = mSoftBody->m_nodes;
		//printf("Bullet nodes size %d\n", btNodes.size());
		
		int ogreVertexIdx = 0;
		
		while (subMeshI.hasMoreElements()) {
			subMesh = subMeshI.getNext();
			
			if (subMesh->useSharedVertices) {
				
				if (isSharedVerticesAdded) {
					continue;
				}
				
				vData = mesh->sharedVertexData;
				
				// We need to add shared vertices only once
				isSharedVerticesAdded = true;
			} else  {
				vData = subMesh->vertexData;
			}
			
			vDeclaration = vData->vertexDeclaration;
			vPosElement = vDeclaration->findElementBySemantic(Ogre::VES_POSITION);
			
			bufferIndex = vPosElement->getSource();
			vBuffer = vData->vertexBufferBinding->getBuffer(bufferIndex);
			
			// Lock the buffer before reading from it
			lockedMem = static_cast<unsigned char*>(vBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
			
			// Read each vertex
			for (unsigned int i = 0; i < vData->vertexCount; ++i) {
				vPosElement->baseVertexPointerToElement(lockedMem, &vPosition);
				
				int idx = getBulletIndex(ogreVertexIdx);
				
				*vPosition++ = btNodes[idx].m_x.x();
				*vPosition++ = btNodes[idx].m_x.y();
				*vPosition = btNodes[idx++].m_x.z();
				
				// Point to the next vertex
				lockedMem += vBuffer->getVertexSize();
				
				ogreVertexIdx++;
			}
			
			vBuffer->unlock();
		}
				
		btTransform transform = mSoftBody->getWorldTransform();
		btQuaternion rot = transform.getRotation();
	    ogreNode->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
	    btVector3 pos = transform.getOrigin();
	    ogreNode->setPosition(pos.x(), pos.y(), pos.z());
		
	}
	
	void BtOgreSoftBody::updateOgreMeshes(btDynamicsWorld *world)
	{
		int size = world->getNumCollisionObjects();
		int updateCount = 0;
		for ( int i = 0; i < size; ++i ) {
			btCollisionObject* colObj = world->getCollisionObjectArray()[i];
			if ( colObj->isActive() && colObj->getInternalType() == btCollisionObject::CO_SOFT_BODY) {
				btSoftBody* body = btSoftBody::upcast(colObj);
				void *userPtr = body->getUserPointer();
				BtOgreSoftBody *osb = (BtOgreSoftBody*)userPtr;
				if (osb) {
					osb->updateOgreMesh();
					updateCount++;
				}
			}
		}
	}
}
