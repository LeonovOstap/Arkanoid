#pragma once
#include <type_traits>
#include <prmath/quaternion.hpp>
#include <prmath/vector3.hpp>

#include "GameObject.h"
#include "../physics/PhysicsSolver.h"

extern Serializer GSerializer;
extern double GDeltaSeconds;

class GameObject;

class World
{
public:
    World()
        : solver(new PhysicsSolver(this))
    {
        //_oldtime = timer.GetTick();
    }
    ;
    virtual ~World();

    virtual void update();
    virtual void drawObjects();
    virtual void drawDebug();
    virtual void simulatePhysics();
    void killObjects();


    template <typename T>
    T* addGameObject(vec3f location, float3 rotation, vec3f scale, Mesh Model, EGameObjectAttributes attributes,GameObject* Owner = 0)
    {
        T* Object = new T(Model);
        Object->set_rotation(rotation);
        Object->set_position(location);
        Object->attributes |= attributes;
        Object->set_scale(scale);
        Object->Owner = Owner;
        Object->worldPointer = this;

        GameObjects.push_back(static_cast<GameObject*>(Object));
        return Object;
    }

    template <typename T>
    T* addGameObject(vec3f location, Mesh Model,EGameObjectAttributes attributes = NONE,GameObject* Owner = 0)
    {
        return addGameObject<T>(location, float3(), vec3f(1, 1, 1), Model, attributes,Owner);
    }

    void destroySafe(GameObject* object)
    {
         GameObjects.erase(std::remove(GameObjects.begin(), GameObjects.end(), object), GameObjects.end());
        object->attributes |= NO_DRAW | NO_COLLISION_RESPONSE;
        //PendingKill.push_back(make_unique<GameObject*>(object));
        //object->destroy();
        //delete object.get();
        //object.reset();
        delete object;
        object = nullptr;
        
    }

    vector<GameObject*> GameObjects;
    vector<std::unique_ptr<GameObject*>> PendingKill;

    bool Debug = false;
protected:
    prcore::Timer timer;



    PhysicsSolver* solver;
};
