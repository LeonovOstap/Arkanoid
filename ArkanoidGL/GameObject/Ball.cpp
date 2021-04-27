#include "Ball.h"


#include "Player.h"
#include "../physics/PhysicsSolver.h"

void Ball::handle_collision(hit_info& info)
{
    if(typeid(*info.Other) == typeid(Player))
    {
        linear_velocity = info.Other->getWorldTransform().GetZ() * Length(linear_velocity) * -1;
    }
    else
    {
        GameObject::handle_collision(info);
    }
}
