#include "graphic/Scene.hpp"

using namespace Robotarium;
using namespace graphic;

Scene::Scene(void) : mRootSceneNode(new SceneNode("RootNode", 1)), mCameraMap(new CameraMap())
{
	mSceneMgr = RenderEngine::GetSingleton()->GetOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
}

Scene::~Scene(void)
{
}

void Scene::Load()
{
	mRootSceneNode->Load();
}

Ogre::SceneManager * Scene::GetOgreSceneMgr()
{
	return this->mSceneMgr;
}

CameraMapPtr& Scene::GetCameraMap()
{
	return mCameraMap;
}

void Scene::AddCamera(CameraPtr& camera)
{
	(*mCameraMap)[camera->GetID()] = camera;
	//camera->Load();
}

UInt32 Scene::GetCameraMapSize()
{
	return this->mCameraMap->size();
}

void Scene::LoadAllCameras()
{
	
	for (UInt32 i = 1; i <= this->GetCameraMapSize(); i++)
	{
		(*this->GetCameraMap())[i]->Load();
	}

}

void Scene::Terminate()
{
}