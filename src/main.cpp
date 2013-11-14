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

	GameEngine->loadZip("media/OgreOculus.zip");
	GameEngine->loadDir("media");
	GameEngine->loadDir("media/dome");
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
    while(!GameEngine->requestStop())
    {    
        player.setCameraToPlanePosition();
		GameEngine->refresh();
    }
}
