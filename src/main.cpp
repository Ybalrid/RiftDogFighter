#include <Annwvyn.h>

#include "UserPlane.hpp"
#include "StereoscopicWindow.hpp"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{

	Annwvyn::AnnEngine* GameEngine = new Annwvyn::AnnEngine;
    Ogre::String res= "r.cfg"; 
    Ogre::ConfigFile cf;
    cf.load(res);
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

    GameEngine->loadZip("media/OgreOculus.zip");
    GameEngine->loadDir("media");
    GameEngine->loadDir("media/dome");

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");


    GameEngine->initRessources();

    //load Map
    Annwvyn::AnnGameObject* Map = GameEngine->createGameObject("Map.mesh");


    //add lights
    GameEngine->setAmbiantLight(Ogre::ColourValue(0.3f,0.3f,0.3f));
    Annwvyn::AnnLightObject* light = GameEngine->addLight();

    //set sky
    GameEngine->setSkyDomeMaterial(true,"Sky/dome1");
    GameEngine->getBodyParams()->Position = Ogre::Vector3(0,0,100);

    GameEngine->oculusInit();


    UserPlane player(GameEngine->createGameObject("Cocktpit.mesh")); player.setGameEngine(GameEngine);
    
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    /*CEGUI::Window *Test = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
    
    Test->setText("TEST");
    Test->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25+GameEngine->getCentreOffset()/2 - 0.15/2,0),CEGUI::UDim(0.5,0)));


    Test->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

    CEGUI::Window *Test2 = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");

    Test2->setText("TEST");
    Test2->setPosition(CEGUI::UVector2(CEGUI::UDim(1 - (0.25+GameEngine->getCentreOffset()/2 + 0.15/2), 0),CEGUI::UDim(0.5,0)));
    Test2->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    
    sheet->addChild(Test2);

    sheet->addChild(Test);
    */

    CEGUI::StereoscopicWindow sw;
    sw.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
    sw.setCenterOffset(GameEngine->getCentreOffset());
    sw.setText("Hello Flat World!");
    sw.setSize(0.11,0.04);
    sw.setPosition(0.5,0.1);
    sw.addChildToSheet(sheet);

    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);


    while(!GameEngine->requestStop())
    { 

        if(GameEngine->isKeyDown(OIS::KC_C))
            player.setVelocity(Ogre::Vector3(0,0,-40));
        else if(GameEngine->isKeyDown(OIS::KC_V))
            player.setVelocity(Ogre::Vector3(0,0,40));
        else 
            player.setVelocity(Ogre::Vector3(0,0,0));



        player.move();
        player.setCameraToPlanePosition();
        std::cout << GameEngine->getCentreOffset() << std::endl;
        GameEngine->refresh();
    }
}
