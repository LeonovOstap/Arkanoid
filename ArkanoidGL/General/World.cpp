#include "World.h"

#include <prmath/euler.hpp>

#include "../misc/Util.h"


Serializer GSerializer = Serializer();
double GDeltaSeconds = 0;

World::~World()
{
    killObjects();
}

void World::update()
{
    static double _oldtime = 0;
    //Calculate delta seconds
    GDeltaSeconds = (timer.GetTick() - _oldtime) / 1000;
    _oldtime = timer.GetTick();

    simulatePhysics();

    for (auto Object : GameObjects)
    {
        if(Object != NULL)
            Object->update(GDeltaSeconds);
    }


    //GameObjects[1]->quat.y += 20 * GDeltaSeconds;
    //GameObjects[2]->quat.y += 20 * GDeltaSeconds;
}

void World::drawObjects()
{
    //todo:: other place
    //killObjects();
    
    if (Debug)
        drawDebug();

    for (int i = 0; i < GameObjects.size(); ++i)
    {
        GameObjects[i]->render();
    }
}

void World::drawDebug()
{
    for (auto Obj : GameObjects)
    {
        for (BoxElement box : Obj->model.getCollisionGeom().boxElements)
        {
            util::debug::drawDebugBox(Obj->getWorldTransform(), box, color3f(255, 255, 255));
        }

        for (SphereElement sphere : Obj->model.getCollisionGeom().sphereElements)
        {
            util::debug::drawDebugSphere(Obj->getWorldTransform(), sphere, color3f(255, 255, 255));
        }

        //Draw Object coordinate space
        util::debug::drawDebugLine(Obj->getWorldTransform(), vec3f(), Obj->getWorldTransform().GetZ() * 200,
                                   vec3f(0, 0, 255));
        util::debug::drawDebugLine(Obj->getWorldTransform(), vec3f(), Obj->getWorldTransform().GetY() * 200,
                                   vec3f(0, 255, 0));
        util::debug::drawDebugLine(Obj->getWorldTransform(), vec3f(), Obj->getWorldTransform().GetX() * 200,
                                   vec3f(255, 0, 0));
    }
}

void World::simulatePhysics()
{
    solver->update();
}

void World::killObjects()
{
    for (int i = 0; i < GameObjects.size(); ++i)
    {
        GameObject* g = GameObjects[i];
        delete g;
        g = nullptr;
    }
    GameObjects.clear();
}
