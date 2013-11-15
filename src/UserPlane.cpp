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
    m_portance(0)

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
    cout << "time : " << time << endl;
    m_Cocktpit->setPos(m_Cocktpit->pos() + m_velocity*time);
}
