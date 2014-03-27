#include "UserPlane.hpp"

using namespace Annwvyn;
using namespace Ogre;
using namespace std;

UserPlane::UserPlane()
{
    std::cout << "You have to give a cockpit to create the user's plane !" 
        << std::endl;
    exit(-1);
}

UserPlane::UserPlane(AnnGameObject* Cocktpit) :
    m_Cocktpit(Cocktpit),
    m_GameEngine(NULL),
    m_life(100),
    m_damage(5),
    m_velocity(0,0,0),
    m_rollAngle(0),
    m_rollVelocity(0),
    m_pitchAngle(0),
    m_pitchVelocity(0),
    m_yawAngle(0),
    m_yawVelocity(0),
    RollTransform(Quaternion::IDENTITY),
    PitchTransform(Quaternion::IDENTITY),
    YawTransform(Quaternion::IDENTITY),
    EnemyList(NULL)
{
    if (!Cocktpit)
        exit(-1);
    
    std::cout << "Player's Plane created !" << std::endl;

}

void UserPlane::shoot()
{
    EnemyPlane* enemy(NULL); //create a pointer to an EnemyPlane
    //Get Ray parameters
    std::cout << "Player shoot" << std::endl;
    Ogre::Vector3 pointing
        (m_Cocktpit->Orientation()*Ogre::Vector3::NEGATIVE_UNIT_Z);
    Ogre::Vector3 origin(m_Cocktpit->pos());
    
    //Construct Ray
    Ogre::Ray bullet (origin, pointing);
    
    std::cerr << "Origin : " << origin << std::endl << "Pointing : " << pointing << std::endl;

    Ogre::RaySceneQuery* rsq = m_GameEngine->getSceneManager()->createRayQuery(bullet);
    rsq->setSortByDistance(true);
    
    //Execute RayCast
    Ogre::RaySceneQueryResult rsqr =  rsq->execute();
    std::cerr << "Raycast executed : " << rsqr.size() << " results"  << std::endl;
    
    //get node
    Ogre::RaySceneQueryResult::iterator it;

    for (it = rsqr.begin(); it != rsqr.end(); it++)
    {
        Ogre::SceneNode* node(NULL);
        if(it->movable && it->movable->getMovableType() == "Entity")
            node = static_cast<Ogre::SceneNode*>(it->movable->getParentNode());

        else continue;

        std::cerr << "Node found" << std::cerr;

        //get AnnGameObject 
        Annwvyn::AnnGameObject* object = m_GameEngine->getFromNode(node); //fetch object address from game engine
        if(!object) continue;
        if(object == m_Cocktpit) continue;

        std::cerr << "you shot to node " 
            << static_cast<void*>(node) 
            << " member of object " 
            << static_cast<void*>(object) 
            << std::endl; 
#ifdef DEBUG
        node->showBoundingBox(true);
#endif //DEBUG

        if(!EnemyList) continue;
        
        for(size_t i(0); i < (*EnemyList).size();i++)
            if((*EnemyList)[i]->isObject(object))
                (*EnemyList)[i]->gotShoot(m_damage);
    }
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
    
    setRollAngle(m_rollVelocity*time);
    setPitchAngle(m_pitchVelocity*time);
    setYawAngle(m_yawVelocity*time);
    updateAngles();

    m_Cocktpit->setPos(m_Cocktpit->pos() + m_Cocktpit->node()->getOrientation()*m_velocity*time);
    
    std::cerr << "Player : " << m_Cocktpit->pos() << std::endl;
}

void UserPlane::setPos(float x, float y, float z)
{
    m_Cocktpit->setPos(x,y,z);
}

void UserPlane::setRollAngle(float rad)
{
    m_rollAngle = rad;
}

void UserPlane::setPitchAngle(float rad)
{
    m_pitchAngle = rad;
}
void UserPlane::setYawAngle(float rad)
{
    m_yawAngle = rad;
}


void UserPlane::updateAngles()
{
    calculateAngularTransform();
    Ogre::Quaternion newOrientation(calculateOrientation());
    m_Cocktpit->setOrientation(newOrientation);
    m_GameEngine->setReferenceQuaternion(newOrientation);
    std::cerr << m_rollVelocity << " "
        << m_pitchVelocity << " " << m_yawVelocity << endl;
    std::cerr << m_rollAngle << " " 
        << m_pitchAngle << " " << m_yawAngle << endl;
}

float UserPlane::getRollAngle()
{
    return m_rollAngle;
}

void UserPlane::setRollVelocity(float omega)
{
    m_rollVelocity = omega;
}
void UserPlane::setPitchVelocity(float omega)
{
    m_pitchVelocity = omega;
}

void UserPlane::setYawVelocity(float omega)
{
    m_yawVelocity = omega;
}


Ogre::Quaternion UserPlane::calculateOrientation()
{
    return m_Cocktpit->Orientation()*RollTransform*PitchTransform*YawTransform;
}

void UserPlane::calculateAngularTransform()
{
    RollTransform = Ogre::Quaternion((Ogre::Radian)m_rollAngle,Vector3::NEGATIVE_UNIT_Z);
    PitchTransform = Ogre::Quaternion((Ogre::Radian)m_pitchAngle, Vector3::UNIT_X);
    YawTransform = Ogre::Quaternion((Ogre::Radian)m_yawAngle, Vector3::UNIT_Y);
}

Ogre::Vector3 UserPlane::getVelocity()
{
    return m_velocity; 
}

void UserPlane::setEnemyList(std::vector<EnemyPlane*>* vect)
{
    EnemyList = vect;
}
