#pragma once
#include "../general/GameObject.h"

class Ball : public GameObject
{
public:
    explicit Ball(Mesh model)
        : GameObject(model)
    {
    }
    virtual void handle_collision(hit_info& info) override;
};
