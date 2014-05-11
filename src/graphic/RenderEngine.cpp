
#include "graphic/RenderEngine.hpp"

using namespace Robotarium;
using namespace graphic;

RenderEngine::RenderEngine(void)
{
	this->logManager = NULL;
	this->root = NULL;
	this->initialized = false;
}

RenderEngine::~RenderEngine(void)
{

}

void RenderEngine::Load()
{
	if (!this->root)
	{
		// Create a new log manager and prevent output from going to stdout
		this->logManager = new Ogre::LogManager();

		std::string logPath = "./ogre.log";

		this->logManager->createLog(logPath, true, false, false);

		// Make the root
		try
		{
			this->root = new Ogre::Root();
		}
		catch(Ogre::Exception &e)
		{
			return;
		}

		// Setup the rendering system, and create the context
		this->SetupRenderSystem();


		// Setup and connect a dummy window to render on
		//this->CreateAndConnectWindow();

		// Create SceneManager
		this->CreateScene("Main Scene");

		// Setup the available resources
		this->SetupResources();
	}

	//this->CreateViewport();

}

void RenderEngine::Init()
{
	this->initialized = false;

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// init the resources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(
		Ogre::TFO_ANISOTROPIC);

	//rendering::Material::CreateMaterials();

	//for (unsigned int i = 0; i < this->scenes.size(); i++)
	//	this->scenes[i]->Init();

	this->initialized = true;
}

void RenderEngine::Terminate()
{
	delete this->root;
}

void RenderEngine::SetupRenderSystem()
{
	Ogre::RenderSystem *renderSys;
	const Ogre::RenderSystemList *rsList;

	// Set parameters of render system (window size, etc.)
	rsList = &(this->root->getAvailableRenderers());

	int c = 0;

	renderSys = NULL;

	do
	{
		if (c == static_cast<int>(rsList->size()))
			break;

		renderSys = rsList->at(c);
		c++;
	}
	while (renderSys &&
		renderSys->getName().compare("OpenGL Rendering Subsystem") != 0);
		//renderSys->getName().compare("Direct3D9 Rendering Subsystem") != 0);
		

	if (renderSys == NULL)
	{
		return;
	}

	// We operate in windowed mode
	renderSys->setConfigOption("Full Screen", "No");
	renderSys->setConfigOption("Video Mode", "640 x 480 @ 32-bit colour");
	//renderSys->setConfigOption("RTT Preferred Mode", "FBO");
	renderSys->setConfigOption("FSAA", "4");
	renderSys->setConfigOption("VSync", "Yes");

	this->root->setRenderSystem(renderSys);
	//root->showConfigDialog();
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initialising Root...");
	root->initialise(false);
	Ogre::RenderWindow* target = root->createRenderWindow("MainWin", 1, 1, false);
	target->setHidden(true);
}


void RenderEngine::SetupResources()
{
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
}

void RenderEngine::RunRenderLoop()
{
	//this->root->_fireFrameStarted();
	//this->root->_fireFrameRenderingQueued();
	//this->root->_fireFrameEnded();
	mThread = boost::thread(&RenderEngine::RenderLoopWorker, this);
}

ScenePtr& RenderEngine::CreateScene(const std::string &_name)
{
	mScene = boost::make_shared<Robotarium::graphic::Scene>();
	mScene = ScenePtr(new Scene());



	static const char * matName = "main_grid_mat";
    Ogre::MaterialPtr mtl = Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
    mtl->setReceiveShadows(false);
    mtl->setSceneBlending( Ogre::SBT_TRANSPARENT_ALPHA );
    mtl->setDepthBias( 0.1, 0 );
    Ogre::TextureUnitState * tu = mtl->getTechnique(0)->getPass(0)->createTextureUnitState();
    assert( tu );
    tu->setColourOperationEx( Ogre::LBX_SOURCE1, Ogre::LBS_DIFFUSE );
    mtl->getTechnique(0)->setLightingEnabled(false);


	// create ManualObject
	Ogre::ManualObject* manual = mScene->GetOgreSceneMgr()->createManualObject("main_grid");
	Ogre::ColourValue c(0.5, 0.5, 0.5);
	Ogre::ColourValue c1(0.7, 0.7, 0.7);
	// specify the material (by name) and rendering type
	manual->begin(matName, Ogre::RenderOperation::OT_LINE_LIST);

	// define start and end point
	for (int i = -5; i <= 5; i++)
	{
		manual->position(i, 0, -5);
		if(i!=0) manual->colour(c); else manual->colour(c1);
		manual->position(i, 0, 5);
		if(i!=0) manual->colour(c); else manual->colour(c1);
	}

	for (int i = -5; i <= 5; i++)
	{
		manual->position(-5, 0, i);
		if(i!=0) manual->colour(c); else manual->colour(c1);
		manual->position(5, 0, i);
		if(i!=0) manual->colour(c); else manual->colour(c1);
	}
	// tell Ogre, your definition has finished
	manual->end();

	// add ManualObject to the RootSceneNode (so it will be visible)
	mScene->GetOgreSceneMgr()->getRootSceneNode()->attachObject(manual);
	//mScene->Load();
	return mScene;
}

Ogre::Root* RenderEngine::GetOgreRoot()
{
	return this->root;
}

ScenePtr& RenderEngine::GetScene()
{
	return mScene;
}

void RenderEngine::RenderLoopWorker()
{
	for(;;)
	{
		root->renderOneFrame();
		Ogre::WindowEventUtilities::messagePump();
		boost::this_thread::sleep(boost::posix_time::milliseconds(17));
	}
}