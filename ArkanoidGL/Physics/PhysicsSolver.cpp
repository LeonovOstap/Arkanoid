#include "PhysicsSolver.h"

#include <prmath/intersect.hpp>
#include <prmath/vector3float.hpp>

#include "../general/GameObject.h"
#include "../Misc/Util.h"
#include "../general/World.h"


void PhysicsSolver::update()
{
    for (auto Object : world->GameObjects)
    {
        if (Object->attributes & NO_COLLISION_RESPONSE || Object->attributes & STATIC || Object->model.getCollisionGeom().boxElements.size() == 0)
            continue;

        for (auto Other : world->GameObjects)
        {
            if (Other->attributes & NO_COLLISION_RESPONSE || Object->attributes & STATIC || Other == Object || Other->model.getCollisionGeom().boxElements.size() == 0)
                continue;

            sweepAABB(Object, Other);
        }

        
    }
}

PhysicsSolver::PhysicsSolver(World* worldPtr)
    : world(worldPtr)
{
}

//This is horrible,but we leave it as is
void PhysicsSolver::sweepAABB(GameObject* Ours, GameObject* Theirs)
{
    using namespace std;

    if(Ours->attributes & NO_COLLISION_RESPONSE)
        return;

    if(Theirs->attributes & NO_COLLISION_RESPONSE)
        return;


    vec3f entryPoint, exitPoint, normal = 0.f;
    box3f b1, b2;

    b1 = Ours->model.getCollisionGeom().boxElements[0];
    b2 = Theirs->model.getCollisionGeom().boxElements[0];
    if (!collision::AABBvsAABB(collision::CalculateAABB(b1, Ours->getWorldTransform()),
                               collision::CalculateAABB(b2, Theirs->getWorldTransform())))
    {
        collisionPairs.erase(Ours);
        return;
    }

    vec3f v = Theirs->get_position() - Ours->get_position();

    vec3f u_0, u_1 = numeric_limits<float>::infinity();

    float u0 = 0.f;
    float u1 = 0.f;

    for (int i = 0; i < 3; ++i)
    {
        if (v[i] == 0)
        {
            u_0[i] = 0;
            u_1[i] = 1;
            continue;
        }

        if (b1.vmax[i] < b2.vmin[i] && v[i] < 0)
            u_0[i] = (b1.vmax[i] - b2.vmin[i]) / v[i];

        else if (b2.vmax[i] < b1.vmin[i] && v[i] > 0)
            u_0[i] = (b1.vmin[i] - b2.vmax[i]) / v[i];

        if (b2.vmax[i] > b1.vmin[i] && v[i] < 0)
            u_1[i] = (b1.vmin[i] - b2.vmax[i]) / v[i];

        else if (b1.vmax[i] > b2.vmin[i] && v[i] > 0)
            u_1[i] = (b1.vmax[i] - b2.vmin[i]) / v[i];

        u0 = max(u0, u_0[i]);
        u1 = max(u1, u_1[i]);
    }

    for (int i = 0; i < 3; ++i)
    {
        if (u_1[i] == u1)
        {
            normal[i] = v[i] > 0 ? 1.f : -1.f;
            break;
        }
    }

    if (collisionPairs.count(Ours) > 0 || u0 == numeric_limits<float>::infinity() || u1 == numeric_limits<float>::infinity())
        return;

    hit_info info(entryPoint, exitPoint, normal, u0, u1,Theirs);


    Ours->handle_collision(info);

    Ours->onObjectCollided(Theirs);
    Theirs->onObjectCollided(Ours);

    collisionPairs.try_emplace(Ours, Theirs);
    /*util::debug::drawDebugLine(Ours->getWorldTransform(), Ours->get_position(),
                               Ours->get_position() + Reflect(Ours->getLinearVelocity(), info.hit_normal) * 200,
                               color3f(255, 255, 0));*/
}

/*
bool PhysicsSolver::resolveAABBvsAABB(BoxElement ours, BoxElement theirs, vec3f& our_velocity,
    vec3f& their_velocity)
{
    their_velocity *= -1;
    return true;
}

bool PhysicsSolver::resolveAABBvsSphere(GameObject* BoxObject, GameObject* SphereObject)
{
    //vec3f vel_normal = SphereObject->getLinearVelocity();
    //vel_normal.Normalize();
    //sphere3f s1 = SphereObject->model->getCollisionGeom().sphereElements[0];
    //box3f b1 = BoxObject->model->getCollisionGeom().boxElements[0];
    //b1 = collision::BoxToWorld(b1,BoxObject->getWorldTransform().getLocation());

    //ray3f ray = ray3f(SphereObject->getWorldTransform().getLocation() + vel_normal * s1.radius,vel_normal);
    //float e;
    //float l;
    
    //if(prmath::IntersectRayBox(ray,b1,e,l))
    //{
    //    vec3f contact_point = SphereObject->getWorldTransform().getLocation() + vel_normal * ( e + s1.radius);

    //    //cout << contact_point.x << " " << contact_point.y << " " << contact_point.z << endl;
    //
    //    //util::debug::drawDebugLine(SphereObject->getWorldTransform(),SphereObject->getWorldTransform().getLocation(),vel_normal * e * 205,color3f(255,255,0));
    //    sphere3f s2 = sphere3f(contact_point,1.f);
    //    util::debug::drawDebugSphere(SphereObject->getWorldTransform(),s2,color3f(255,255,0));
    //    util::debug::drawDebugBox(BoxObject->getWorldTransform(),BoxObject->model->getCollisionGeom().boxElements[0],color3f(255,0,0));
    //}

    SphereObject->linear_velocity *=-1;
    
    
    return false;
}
*/
