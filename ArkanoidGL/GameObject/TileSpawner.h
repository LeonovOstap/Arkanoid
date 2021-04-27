#pragma once
#include "../general/Game.h"
#include "../general/GameObject.h"
#include "../general/World.h"
#include "../mesh/MeshFactory.h"
#include "../misc/DelayTimer.h"


template<int R,int C>
class TileSpawner : public GameObject
{
    friend class GameProcess;
public:
    TileSpawner(Mesh m)
        : GameObject(Mesh(m))
    {
        attributes = NO_DRAW | NO_COLLISION_RESPONSE;
        //cout << "e" << endl;

        
        
    }

    void update(double delta) override;
    void spawnTile(float x, float y, int row, int column);
    void onTileDestroyed(GameTile* T);
    void Deserialize(prcore::Stream& stream) override
    {
        GameObject::Deserialize(stream);
        checkAndSpawn();
    };
    void checkAndSpawn()
    {
        for(int row = 0; row < R; row++)
        {
            float r_y = position.y + 30 * row;
        
            for(int column = 0;column < C;++column)
            {
                float c_x = position.x + 30 * column;
                spawnTile(c_x,r_y,row,column);
                //cout << "e" << endl;

            
            }
        }
    }

private:
    GameTile* tiles[R][C] = {nullptr};
    
};

template <int R, int C>
void TileSpawner<R, C>::update(double delta)
{
    //cout << "  " << endl;
    static int remainingTiles = 0;
    for(int row = 0; row < R; row++)
    {      
        for(int column = 0;column < C;++column)
        {
            if(tiles[row][column] == NULL)
                remainingTiles--;

            
        }
    }

    if(remainingTiles <= 0)
    {
        //GGameProcess->toNextLevel();
        //todo::wtf?
        remainingTiles = 73275498379845;
    }
}

template <int R, int C>
void TileSpawner<R, C>::spawnTile(float x, float y, int row, int column)
{
    Mesh Ob1 = MeshFactory::Get().ConstructObject("../Content/Models/tile.mdl");   
    tiles[row][column] = worldPointer->addGameObject<GameTile>(vec3f(x,y,position.z),Ob1,STATIC | NO_COLLISION_RESPONSE | NO_DRAW,this);
}

//Should`ve used smart ptrs
template <int R, int C>
void TileSpawner<R, C>::onTileDestroyed(GameTile* T)
{
    // i know its bad, time constraints is an awful thing
    static int score;
    //cout << "fg" << endl;
    for(int row = 0; row < R;row++)
    {
        for(int column = 0; column < C;column++)
        {
            if(tiles[row][column] == T)
                tiles[row][column] = nullptr;
        }
        
    }
    cout << "You scored : " << score++ << endl;
}

using LargeTileGrid24x = TileSpawner<8,24>;
using MediumTileGrid12x = TileSpawner<6,12>;
using SmallTileGrid8x = TileSpawner<4,8>;