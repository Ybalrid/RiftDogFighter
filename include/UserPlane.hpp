#ifndef USER_PLANE
#define USER_PLANE

//Annwvyn Engine 
#include <Annwvyn.h>
//C++ 
#include <iostream>
//C Library for C++
#include <cstdlib>

using namespace Annwvyn;
class UserPlane
{
    public:
        UserPlane();
        UserPlane(AnnGameObject* Cocktpit);
        
        void setGameEngine(AnnEngine* GameEngine);
        
        void setCameraToPlanePosition();
    private:
        AnnGameObject* m_Cocktpit;
        AnnEngine* m_GameEngine;
        int m_life;
        int m_damage;

        //physics
        float m_mass; //in kg
        Ogre::vector3 m_velocity; //in m/s
        float m_acceleration; //in m/s²
        float m_gravitationalAcceleration; //in m/s²
        float m_thrust; //in newton
        float m_portance; // in newtown 

};

#endif
