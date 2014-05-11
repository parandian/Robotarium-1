#include "graphic/Camera.hpp"

using namespace Robotarium;
using namespace graphic;

Camera::Camera(String name, String HWND, Vec2 viewportSize, Vec3 position, Vec3 lapPoint)
	: mName(name), mHWND(HWND), mViewportSize(viewportSize), 
		mPosition(position), mLapPoint(lapPoint)
{
	this->mID = RenderEngine::GetSingleton()->GetScene()->GetCameraMap()->size() + 1;
	RenderEngine::GetSingleton()->GetScene()->AddCamera(boost::shared_ptr<Camera>(this));
}

Camera::~Camera()
{
}

void Camera::Load()
{

	Ogre::NameValuePairList params;
    
    params["externalWindowHandle"] = mHWND;

	mRenderWindow = Ogre::Root::getSingleton().
		createRenderWindow(mName , mViewportSize.x, mViewportSize.y, false , &params);

	Ogre::SceneManager* mSceneMgr = RenderEngine::GetSingleton()->GetScene()->GetOgreSceneMgr();

	mCamera = mSceneMgr->createCamera(mName);

	mCameraSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName + "_node");

	mCameraSceneNode->attachObject(mCamera);

	mCameraSceneNode->setPosition(mPosition);

	mCameraSceneNode->lookAt(mLapPoint, Ogre::Node::TS_WORLD);

	mCamera->setNearClipDistance(0.001);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

	// Create one viewport, entire window
	mViewport = mRenderWindow->addViewport(mCamera);

	mViewport->setBackgroundColour(Ogre::ColourValue(0.2,0.2,0.2));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Real(mViewport->getActualWidth())/Real(mViewport->getActualHeight()));

}


void Camera::SetPosition(Real x, Real y, Real z)
{
	this->mCameraSceneNode->setPosition(x, y, z);
}

void Camera::SetPosition(Vec3 pos)
{
	this->mCameraSceneNode->setPosition(pos);
}

UInt32 Camera::GetID()
{
	return this->mID;
}
