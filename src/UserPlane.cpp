#include "UserPlane.hpp"

using namespace Annwvyn;
using namespace Ogre;
using namespace std;

UserPlane::UserPlane()
{
    std::cout << "You have to give a cockpit to create the user's plane !" << std::endl;
    exit(-1);
}

UserPlane::UserPlane(AnnGameObject* Cocktpit) :
    m_Cocktpit(Cocktpit),
    m_GameEngine(NULL),
    m_life(100),
    m_damage(100),
    m_mass(24500),
    m_acceleration(0),
    m_thrust(0),
    m_portance(0),
    m_rollAngle(0),
    m_rollVelocity(0)
{
    if (!Cocktpit)
        exit(-1);
    
    std::cout << "Player's Plane created !" << std::endl;

}

void UserPlane::setGameEngine(AnnEngine* GameEngine)
{
    m_GameEngine = GameEngine;
}

void UserPlane::setCameraToPlanePosition()
{
    if(m_GameEngine)
    {
        m_GameEngine->getBodyParams()->Position = m_Cocktpit->pos();
    }
}

void UserPlane::setVelocity(Vector3 v)
{
    m_velocity = v;
}

void UserPlane::move(float time, bool millisec)
{
    if(time < 0) time = m_GameEngine->getTime();
    if(millisec) time /= 1000.0f;
    
    
    m_Cocktpit->setPos(m_Cocktpit->pos() + m_velocity*time);

    setRollAngle(getRollAngle() + m_rollVelocity*time);
}

void UserPlane::setPos(float x, float y, float z)
{
    m_Cocktpit->setPos(x,y,z);
}

void UserPlane::setRollAngle(float rad)
{
    m_rollAngle = rad;
    updateRoll();
}

void UserPlane::updateRoll()
{
    Ogre::Quaternion Roll((Ogre::Radian)m_rollAngle,Ogre::Vector3::NEGATIVE_UNIT_Z);
    m_Cocktpit->setOrientation(Roll);
    m_GameEngine->setReferenceQuaternion(Roll);
}

float UserPlane::getRollAngle()
{
    return m_rollAngle;
}

void UserPlane::setRollVelocity(float omega)
{
    m_rollVelocity = omega;
}
