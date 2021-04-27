#pragma once
#include <prcore/prcore.hpp>

#include "World.h"
#include "../UI/Canvas2D.h"
#include "render/RenderFundamentals.h"

using namespace prcore;
#define PRCORE_IMPLEMENT_MAIN

class GameProcess final
{
    friend int main(int argc, char** argv);
    friend class ArkWindow;

public:
    void exit() { destroyProcess(); };

    World* getWorld() {return world;};
    Renderer* getRenderer() {return renderer;}
    void toNextLevel();
    
private:
    void createProcess();
    void destroyProcess();

    //todo:: this is dumb
    

    /*todo: prophecy has inputbase class, witch allows to access keyboard and mouse directly. Including support for controllers too.
     *w
     */
    void handleKeyboardInput(int key, bool bPressed);
    void handleMousePos(int x, int y, bool press);
    void handleMousePress(int x,int y, MouseButton button,int amount);

    void mainLoop();
    void openLevel(const char* filename);


    class ArkWindow* window;
    World* world;
    Canvas2D* canvasUI;
    Renderer* renderer;
    
};

extern GameProcess* GGameProcess;
