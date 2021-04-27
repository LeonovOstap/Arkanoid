#pragma once
#include <map>

#include "../general/GameObject.h"


class PhysicsSolver
{
protected:
    friend class World;
    PhysicsSolver(class World* worldPtr);

    World* world;

    virtual void sweepAABB(GameObject* Ours, GameObject* Theirs);
    //void sweep1D(box3f b1,box3f b2,vec3f l1,vec3f l2,vec3f vl1,vec3f vl2,)

    virtual void update();

    std::map<GameObject*, GameObject*> collisionPairs;
};

struct hit_info
{
    hit_info(vec3f entry_point, vec3f exit_point, vec3f hit_normal, float entry_time, float exit_time,GameObject* InOther)
        : entryPoint(entry_point),
          exitPoint(exit_point),
          hit_normal(hit_normal),
          entryTime(entry_time),
          exitTime(exit_time), Other(InOther)
    {
    }

    vec3f entryPoint, exitPoint;
    vec3f hit_normal;
    float entryTime, exitTime;
    GameObject* Other;
};
