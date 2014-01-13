#ifndef USER_PLANE
#define USER_PLANE

//Annwvyn Engine 
#include <Annwvyn.h>
//C++ 
#include <iostream>
//C Library for C++
#include <cstdlib>

using namespace Annwvyn;
using namespace Ogre;

class UserPlane
{
    public:
        UserPlane();
        UserPlane(AnnGameObject* Cocktpit);
        
        void setGameEngine(AnnEngine* GameEngine);
        
        void setCameraToPlanePosition();

        void setVelocity(Vector3 v);
        void move(float time = -1, bool millisec = false);

        void setPos(float x, float y, float z);
        
        void setRollAngle(float rad);
        void setPitchAngle(float rad);

        void setRollVelocity(float omega);
        void setPitchVelocity(float omega);

        float getRollAngle();
        void updateAngles();
        
        void calculateAngularTransform();

        Ogre::Quaternion calculateOrientation();

    private:
        AnnGameObject* m_Cocktpit;
        AnnEngine* m_GameEngine;
        int m_life;
        int m_damage;

        //physics
        float m_mass; //in kg
        Vector3 m_velocity; //in m/s
        float m_acceleration; //in m/s²
        float m_gravitationalAcceleration; //in m/s²
        float m_thrust; //in newton
        float m_portance; // in newtown 
        
        float m_rollAngle; //in rad
        float m_pitchAngle; //in rad
        float m_rollVelocity;//in rad/s
        float m_pitchVelocity;//in rad/s
        
        float m_lastRollAngle, m_lastPitchAngle;
        Ogre::Quaternion RollTransform, PitchTransform;
};

#endif
