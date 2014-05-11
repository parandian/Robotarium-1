#include "graphic/CameraSceneNode.hpp"

using namespace Robotarium;
using namespace graphic;

CameraSceneNode::CameraSceneNode(SceneNodePtr& parent, String name, UInt32 Id, String HWND, Vec2 viewportSize, Vec3 position, Vec3 lapPoint)
	:SceneNodeBase(name, parent->GetNodeMapSize() + 1), mHWND(HWND), 
	mViewportSize(viewportSize), mPosition(position), mLapPoint(lapPoint)
{
	SetNodeType(CAMERA_SCENE_NODE_TYPE);

	this->SetID(parent->GetNodeMapSize() + 1);

	this->SetName(name);
}

CameraSceneNode::~CameraSceneNode()
{
}

void CameraSceneNode::Load(SceneNodePtr& parent)
{

	Ogre::NameValuePairList params;
    
    params["externalWindowHandle"] = mHWND;

	mRenderWindow = Ogre::Root::getSingleton().
		createRenderWindow(GetName() , mViewportSize.x, mViewportSize.y, false , &params);

	Ogre::SceneManager* mSceneMgr = RenderEngine::GetSingleton()->GetScene()->GetOgreSceneMgr();

	mCamera = mSceneMgr->createCamera(GetName());


	mOgreSceneNode = RenderEngine::GetSingleton()->
		GetScene()->GetOgreSceneMgr()->getRootSceneNode()->createChildSceneNode(GetName());

	mOgreSceneNode->attachObject(mCamera);

	mCamera->setNearClipDistance(0.001);

	// Create one viewport, entire window
	mViewport = mRenderWindow->addViewport(mCamera);

	mViewport->setBackgroundColour(Ogre::ColourValue(0.2,0.2,0.2));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Real(mViewport->getActualWidth())/Real(mViewport->getActualHeight()));

	SetPosition(mPosition);

	SetLookAtPoint(mLapPoint);
}

void CameraSceneNode::Load()
{
}

void CameraSceneNode::Update()
{
}

void CameraSceneNode::LoadChildNodes()
{
}

void CameraSceneNode::UpdateChildNodes()
{
}

void CameraSceneNode::SetPosition(Real x, Real y, Real z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
	mOgreSceneNode->setPosition(mPosition);
}

void CameraSceneNode::SetPosition(Vec3 pos)
{
	mPosition = pos;
	mOgreSceneNode->setPosition(mPosition);
}

Vec3 CameraSceneNode::GetPosition()
{
	return mPosition;
}

void CameraSceneNode::SetOrientation(Quat rot)
{
	mOrientation = rot;
	mOgreSceneNode->setOrientation(mOrientation);
}

void CameraSceneNode::SetOrientation(Real angle, Vec3 axis)
{
	mOrientation.FromAngleAxis(Ogre::Radian(angle), axis);
	mOgreSceneNode->setOrientation(mOrientation);
}

void CameraSceneNode::SetLookAtPoint(Vec3 lap)
{
	//mOgreSceneNode->lookAt(lap, Ogre::Node::TS_WORLD);

	Vec3 z = -(lap - mPosition); z.normalise(); // z
	Vec3 x = z.crossProduct(Vec3::NEGATIVE_UNIT_Y); x.normalise(); // x
	Vec3 y = -x.crossProduct(z); y.normalise(); // y

	Ogre::Matrix3 R;
	R.FromAxes(x, y, z);

	Quat q; q.FromRotationMatrix(R);
	mOgreSceneNode->setOrientation(q);

	mOrientation = mOgreSceneNode->getOrientation();
}