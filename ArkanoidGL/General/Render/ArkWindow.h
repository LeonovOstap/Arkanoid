#pragma once
#include <vector>
#include <prcore/prcore.hpp>
#include <windows.h>
#include "GL/GL.h"

using namespace prcore;

class ArkWindow : public WindowGL
{
public:
    ArkWindow(int width, int height)
    {
        // open window
        OpenWindow(width, height, "Arakanoid 3d Edition", WINDOW_NORMAL);

        gl_context = CreateContext(NULL);
        SetContext(gl_context);

       
        //Obj1->setLinearVelocity(vec3f(-200,0,0));
    }

    ~ArkWindow()
    {
        DeleteContext(gl_context);
        CloseWindow();
    }

    void EventSize(int width, int height) override;
    void EventKeyboard(int keycode, bool press) override;
    void EventMouseButton(int x, int y, MouseButton button, int count) override;
    void EventMouseMove(int x, int y) override;
    bool EventMain() override;
    void EventDraw() override;

    virtual void drawProjection3D();
    virtual void drawProjection2D();


    

private:
    
    ContextGL* gl_context = nullptr;
};
