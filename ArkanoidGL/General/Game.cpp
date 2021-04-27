#include "Game.h"
#include "Game.h"



#include "../gameobject/GameTile.h"
#include "../gameobject/Player.h"
#include "../gameobject/TileSpawner.h"
#include "../mesh/Mesh.h"
#include "../mesh/MeshFactory.h"
#include "../misc/Input.h"
#include "render/ArkWindow.h"


GameProcess* GGameProcess = nullptr;

void GameProcess::toNextLevel()
{
    //todo:: this needs to be fixed, but im out of time
    
    
    static int Level = 1;
    ++Level;
    openLevel((std::string("../Levels/") + std::to_string(Level) + ".sar").c_str());
    
}

void GameProcess::createProcess()
{
    window = new ArkWindow(1280, 720);
    world = new World;
    //canvasUI = new Canvas2D;
    renderer = new Renderer;

    //Sprite2D* u = new Sprite2D(320,240,1,1,Bitmap("../test.tga"));
   // u->init();
   // canvasUI->sprites.push_back(u);

    GSerializer.DeserializeAll("../Levels/1.sar");

/*
    Mesh Obj = MeshFactory::Get().ConstructObject("../Content/Models/wall_purple.mdl");
    Mesh Obk = MeshFactory::Get().ConstructObject("../Content/Models/player.mdl");
    Mesh Obf = MeshFactory::Get().ConstructObject("../Content/Models/floor_purple.mdl");
    Mesh Ob1 = MeshFactory::Get().ConstructObject("../Content/Models/tile.mdl");
    vec3f wallScale = vec3f(1.0f, 4.0f, 4.0f);

    world->addGameObject<Player>(vec3f(100, -50, -100), float3(0,0,0), vec3f(2, 2, 2), Obk, NONE);
    
    world->addGameObject<GameObject>(vec3f(-350, -50, -450), float3(), wallScale, Obj, STATIC);
    world->addGameObject<GameObject>(vec3f(350, -50, -450), float3(), wallScale, Obj, STATIC);
    world->addGameObject<GameObject>(vec3f(0, -50, -500), float3(0,90,0), wallScale, Obj, STATIC);
    
    
    world->addGameObject<GameObject>(vec3f(0, -150, 0), float3(0,0,0), vec3f(5,1,5), Obf, STATIC);
    world->addGameObject<GameObject>(vec3f(0, 150, 0), float3(0,0,0), vec3f(5,1,5), Obf, STATIC);
    
    
    //world->addGameObject<GameObject>(vec3f(0, -150, 400), Mesh());
    MediumTileGrid12x* TileGrid = new MediumTileGrid12x(Mesh());
    TileGrid->set_position(vec3f(-150,-50,-470));
    TileGrid->worldPointer = world;
    world->GameObjects.push_back(TileGrid);
    TileGrid->checkAndSpawn();
    /*
    
    world->addGameObject<GameTile>(vec3f(0, 50, -400), float3(0,0,0), vec3f(1,1,1), Ob1, STATIC);
    world->addGameObject<GameTile>(vec3f(0, -50, -400), float3(0,0,0), vec3f(1,1,1), Ob1, STATIC);
    world->addGameObject<GameTile>(vec3f(0, -0, -400), float3(0,0,0), vec3f(1,1,1), Ob1, STATIC);
    
    world->addGameObject<GameTile>(vec3f(60, 50, -400), float3(0,0,0), vec3f(1,1,1), Ob1, STATIC);
    world->addGameObject<GameTile>(vec3f(60, -50, -400), float3(0,0,0), vec3f(1,1,1), Ob1, STATIC);
    world->addGameObject<GameTile>(vec3f(60, -0, -400), float3(0,0,0), vec3f(1,1,1), Ob1, STATIC);

    world->addGameObject<GameTile>(vec3f(-60, 50, -400), float3(0,0,0), vec3f(1,1,1), Ob1, STATIC);
    world->addGameObject<GameTile>(vec3f(-60, -50, -400), float3(0,0,0), vec3f(1,1,1), Ob1, STATIC);
    world->addGameObject<GameTile>(vec3f(-60, -0, -400), float3(0,0,0), vec3f(1,1,1), Ob1, STATIC);*/

    //Obj2->setLinearVelocity(vec3f(20,0,0));
    //Obj3->setLinearVelocity(vec3f(-5,0,0));
    //Obj2->setLinearVelocity(vec3f(20,0,0));
    
}

void GameProcess::destroyProcess()
{
    window->MainBreak();

    delete world;
}

void GameProcess::handleKeyboardInput(int key, bool bPressed)
{
    if(!world)
        return;
    if(key == KEYCODE_N && bPressed)
        renderer->getSceneRT().renderTarget.SaveImage("../Saved/Screen.jpg",1);
    for (int i = 0; i < world->GameObjects.size(); ++i)
    {
        if (InputReceiver* receiver = dynamic_cast<InputReceiver*>(world->GameObjects[i]))
            receiver->ReceiveKeyboard(key, bPressed);
    }
}

void GameProcess::handleMousePos(int x, int y, bool press)
{
    if(!world)
        return;
    //cout << (x)/2 << endl;
    for (int i = 0; i < world->GameObjects.size(); ++i)
    {
        if (InputReceiver* receiver = dynamic_cast<InputReceiver*>(world->GameObjects[i]))
            receiver->ReceiveMousePosition(x, y);
    }
}

void GameProcess::handleMousePress(int x, int y, MouseButton button, int amount)
{
    if(!world)
        return;
    for (int i = 0; i < world->GameObjects.size(); ++i)
    {
        if (InputReceiver* receiver = dynamic_cast<InputReceiver*>(world->GameObjects[i]))
            receiver->ReceiveMousePress(x,y,button,amount);
    }
}

void GameProcess::mainLoop()
{
    renderer->updateScreensize(point2f(window->GetWindowRect().width,window->GetWindowRect().height));
    renderer->render();
    if(world)
        world->update();
    //canvasUI->draw();
    //canvasUI->draw();
    std::string profilingName = "Arkanoid 3D | ";
    profilingName = profilingName + std::to_string(static_cast<int>(1 / GDeltaSeconds)) + " FPS";
    window->RenameWindow(profilingName.c_str());
    window->PageFlip();
    
   
}

void GameProcess::openLevel(const char* filename)
{
    //todo: this could be better
    delete world;
    world = new World;
    GSerializer.DeserializeAll(filename);
}
