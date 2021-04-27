#include "GameTile.h"


#include "Ball.h"
#include "TileSpawner.h"
#include "../General/World.h"


void GameTile::update(double delta)
{
    GameObject::update(delta);
    if(Lifetime.GetTime() > 2 && attributes != NONE)
    {
       //cout << Lifetime.GetTime() << endl;
       attributes &= NO_COLLISION_RESPONSE;
       attributes &= NO_DRAW;
       attributes |= STATIC;
    }
}

void GameTile::onObjectCollided(Primitive* Other)
{
    if (dynamic_cast<Ball*>(Other))
    {
        static_cast<TileSpawner<6,12>*>(Owner)->onTileDestroyed(this);
        worldPointer->destroySafe(this);
        
    }
}
