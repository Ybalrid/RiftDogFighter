#include <Annwvyn.h>

#include "UserPlane.hpp"
#include "EnemyPlane.hpp"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
    //Declare and init the engine
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
    Map->node()->setScale(40,10,40);

    //add lights
    GameEngine->setAmbiantLight(Ogre::ColourValue(0.3f,0.3f,0.3f));
    Annwvyn::AnnLightObject* light = GameEngine->addLight();
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(-0.25,-1,-0.5);
    //set sky
    GameEngine->setSkyDomeMaterial(true,"Sky/dome1");
    GameEngine->getBodyParams()->Position = Ogre::Vector3(0,0,200);

    GameEngine->oculusInit();

    UserPlane player(GameEngine->createGameObject("Cocktpit.mesh")); player.setGameEngine(GameEngine); player.setPos(0,500,0);
    
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    CEGUI::StereoscopicWindow sw;
    sw.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
    sw.setCenterOffset(GameEngine->getCentreOffset());
    sw.setText("100\% life");
    sw.setSize(0.13,0.04);
    sw.setPosition(0.3,0.3);
    sw.addChildToSheet(sheet);

    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
    
    int axis0(0),axis1(0),axis2(0),axis3(0);
    
    std::vector <EnemyPlane *> Enemies;
    
    EnemyPlane* enemy = new EnemyPlane(GameEngine->createGameObject("Icosphere.mesh"));
    enemy->setPos(0,500,-100);
    
    Enemies.push_back(enemy);

    player.setEnemyList(&Enemies);

    bool start(false);
    while(!GameEngine->requestStop())
    {
        if(GameEngine->getOISJoyStick())
        {
            std::cerr << "Joystick detected at startup ";
            //GameEngine->getOISJoyStick()->capture();
            
            std::cerr << "Joystick has " << GameEngine->getOISJoyStick()->getJoyStickState().mAxes.size() << " Axes" << std::endl;
            
                if(GameEngine->getOISJoyStick()->getJoyStickState().mAxes.size()>1)
            axis0 = GameEngine->getOISJoyStick()->getJoyStickState().mAxes[0].abs;
                if(GameEngine->getOISJoyStick()->getJoyStickState().mAxes.size()>2)
            axis1 = GameEngine->getOISJoyStick()->getJoyStickState().mAxes[1].abs;
                if(GameEngine->getOISJoyStick()->getJoyStickState().mAxes.size()>3)
            axis2 = GameEngine->getOISJoyStick()->getJoyStickState().mAxes[2].abs;
                if(GameEngine->getOISJoyStick()->getJoyStickState().mAxes.size()>4)
            axis3 = GameEngine->getOISJoyStick()->getJoyStickState().mAxes[3].abs;
            
            std::cerr << axis0 << " " << axis1 << " " << axis2 << " " << axis3 << std::endl;
            
            for(size_t i = 0; i < GameEngine->getOISJoyStick()->getJoyStickState().mButtons.size(); i++)
            {
                if(GameEngine->getOISJoyStick()->getJoyStickState().mButtons[i])
                {
                    std::cerr << "Button " << i+1 << " Pressed" << std::endl;
                    if(i+1==12)
                    {
                        player.setVelocity(Ogre::Vector3(0,0,-100));
                        start = true;
                    }
                    if(i+1==1)
                        player.shoot();
                }
            }
            //Roll
            if(axis0 > 256 || axis0 < -255)
                player.setRollVelocity(((float)axis0/(float)GameEngine->getOISJoyStick()->MAX_AXIS)*2);
            //Pitch
            if(axis1 > 256 || axis1 < -255)
                player.setPitchVelocity(((float)axis1/(float)GameEngine->getOISJoyStick()->MAX_AXIS)*1.5);
            //Yaw
            if(axis3 > 256 || axis3 < -255)
                player.setYawVelocity(((float)axis3/(float)GameEngine->getOISJoyStick()->MAX_AXIS)*-0.5);
            //Throttle
            if(axis2 > 256 || axis2 < -255)
                if(start)
                player.setVelocity(Ogre::Vector3(0,0,-100 +  ((float)axis2/(float)GameEngine->getOISJoyStick()->MAX_AXIS)*50));

        }    
        
        if(GameEngine->isKeyDown(OIS::KC_RETURN))
        {
            player.setVelocity(Ogre::Vector3(0,0,-100));
            start = true;
        }

        //Roll
        if(GameEngine->isKeyDown(OIS::KC_LEFT))
            player.setRollVelocity(-2);
        else if(GameEngine->isKeyDown(OIS::KC_RIGHT))
            player.setRollVelocity(2);
        else if(!(axis0 > 256 || axis0 < -255))
            player.setRollVelocity(0);
        
        //Pitch
        if(GameEngine->isKeyDown(OIS::KC_UP))
            player.setPitchVelocity(-1.5);
        else if(GameEngine->isKeyDown(OIS::KC_DOWN))
            player.setPitchVelocity(1.5);
        else if(!(axis1 > 256 || axis1 < -255))
            player.setPitchVelocity(0);

        //Yaw
        if(!(axis3>256 || axis3 < -255))
            player.setYawVelocity(0);

        //Throttle
        if(!(axis2>256 || axis2 < -255))
            if(start)
            player.setVelocity(Ogre::Vector3(0,0,-100));
            else player.setVelocity(Ogre::Vector3::ZERO);
    
        if(GameEngine->isKeyDown(OIS::KC_SPACE))
            player.shoot();
        
        player.move();
        player.setCameraToPlanePosition();
        
        enemy->stepAI();

        GameEngine->refresh();
    }

    delete GameEngine;
    return 0;
}
