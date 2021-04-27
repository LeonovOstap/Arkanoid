#pragma once
#include "General/Game.h"
#include "General/Render/ArkWindow.h"


int main(int argc, char** argv)
{
    GGameProcess = new GameProcess;
    GGameProcess->createProcess();
    GGameProcess->window->MainLoop();

    return 0;
}
