#include "ArkWindow.h"

#include <gl/GLU.h>
#include <prmath/euler.hpp>

#include "../Game.h"

void ArkWindow::EventSize(int width, int height)
{
    glViewport(0, 0, width, height);
    glScissor(0, 0, width, height);
    
}

void ArkWindow::EventKeyboard(int keycode, bool press)
{
    GGameProcess->handleKeyboardInput(keycode, press);


}

void ArkWindow::EventMouseButton(int x, int y, MouseButton button, int count)
{
    GGameProcess->handleMousePress(x,y,button,count);
}

bool ArkWindow::EventMain()
{
    GGameProcess->mainLoop();
    EventDraw();
    
    return true;
}

void ArkWindow::EventDraw()
{
    //MS OGL32 does not support alpha channels at all
    // Why the fuck its not deprecated then?
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    drawProjection3D();
    drawProjection2D();



    
   
    //KBuf->BlitImage(*KBuf,Surface::BLIT_SCALE);
    

    //free(RenderTarget);
    
    //if(KBuf)
        //memset(KBuf->GetImage(), reinterpret_cast<uint8>(RenderTarget),1*PIXELFORMAT_ARGB8888.GetBytes());

    //for(int i = 0; i < 5;++i)
    //    cout << RenderTarget[i] << " ";
    //cout << endl;


    //PageFlip();
}

void ArkWindow::drawProjection3D()
{
    /*//todo:: fix FOV
    float t, b, r, l, a = 0;
    a = GetWindowAspect();

    t = 6 * tanf((70 / 2));
    b = -t;
    r = a * t;
    l = -r;

    // Create camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(l, r, b, t, 6, 1200);*/

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(90,GetWindowAspect(),6,1200);

    GGameProcess->world->drawObjects();
}

void ArkWindow::drawProjection2D()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-640, 640, -360, 360);

    //GGameProcess->canvasUI->draw();
    
    
}

void ArkWindow::EventMouseMove(int x, int y)
{
    GGameProcess->handleMousePos(x, y, false);
}
