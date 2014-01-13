#include <Annwvyn.h>

#include "UserPlane.hpp"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
    
	Annwvyn::AnnEngine* GameEngine = new Annwvyn::AnnEngine;

    GameEngine->loadResFile("r.cfg");
    
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
    light->setPosition(0,0,250);
    //set sky
    GameEngine->setSkyDomeMaterial(true,"Sky/dome1");
    GameEngine->getBodyParams()->Position = Ogre::Vector3(0,0,200);

    GameEngine->oculusInit();


    UserPlane player(GameEngine->createGameObject("Cocktpit.mesh")); player.setGameEngine(GameEngine); player.setPos(0,200,0);
    
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    CEGUI::StereoscopicWindow sw;
    sw.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
    sw.setCenterOffset(GameEngine->getCentreOffset());
    sw.setText("2D CEGUI TEST");
    sw.setSize(0.11,0.04);
    sw.setPosition(0.5,0.1);
    sw.addChildToSheet(sheet);

    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
    
    while(!GameEngine->requestStop())
    {
        if(GameEngine->isKeyDown(OIS::KC_SPACE))  
            player.setVelocity(Ogre::Vector3(0,0,-100));
        //Roll
        if(GameEngine->isKeyDown(OIS::KC_LEFT))
            player.setRollVelocity(1.5);
        else if(GameEngine->isKeyDown(OIS::KC_RIGHT))
            player.setRollVelocity(-1.5);
        else player.setRollVelocity(0);
        
        //Pitch
        if(GameEngine->isKeyDown(OIS::KC_UP))
            player.setPitchVelocity(-1);
        else if(GameEngine->isKeyDown(OIS::KC_DOWN))
            player.setPitchVelocity(1);
        else
            player.setPitchVelocity(0);
        
        player.move();
        player.setCameraToPlanePosition();
        
        GameEngine->refresh();
    }
}
