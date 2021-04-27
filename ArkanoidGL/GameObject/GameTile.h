#pragma once

#include "../general/GameObject.h"

class GameTile : public GameObject
{
public:
    explicit GameTile(Mesh model)
        : GameObject(model)
    {
    }
    void update(double delta) override;
    void onObjectCollided(Primitive* Other) override;
    bool IsSerializable() override {return false;};
};
