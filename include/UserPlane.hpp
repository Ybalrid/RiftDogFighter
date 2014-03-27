#ifndef USER_PLANE
#define USER_PLANE

//Annwvyn Engine 
#include <Annwvyn.h>
//C++ 
#include <iostream>
//C Library for C++
#include <cstdlib>
#include "EnemyPlane.hpp"

using namespace Annwvyn;
using namespace Ogre;

class UserPlane
{
    public:
        UserPlane();
        UserPlane(AnnGameObject* Cocktpit);
        void shoot();       
        void setGameEngine(AnnEngine* GameEngine);
        
        void setCameraToPlanePosition();

        void setVelocity(Vector3 v);
        void move(float time = -1, bool millisec = false);

        void setPos(float x, float y, float z);
        
        void setRollAngle(float rad);
        void setPitchAngle(float rad);
        void setYawAngle(float rad);

        void setRollVelocity(float omega);
        void setPitchVelocity(float omega);
        void setYawVelocity(float omega);

        float getRollAngle();
        void updateAngles();
        
        void calculateAngularTransform();

        Ogre::Quaternion calculateOrientation();
        Ogre::Vector3 getVelocity();

        void setEnemyList(std::vector<EnemyPlane*>* vect);

    private:
        AnnGameObject* m_Cocktpit;
        AnnEngine* m_GameEngine;
        int m_life;
        int m_damage;

        //physics
        Vector3 m_velocity; //in m/s
        
        float m_rollAngle; //in rad
        float m_pitchAngle; //in rad
        float m_yawAngle; //in rad
        float m_rollVelocity;//in rad/s
        float m_pitchVelocity;//in rad/s
        float m_yawVelocity;//in rad/s
        
        Ogre::Quaternion RollTransform, PitchTransform, YawTransform;
        
        std::vector<EnemyPlane*> *EnemyList;
        
};

#endif
