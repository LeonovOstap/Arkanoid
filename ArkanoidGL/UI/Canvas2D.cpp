#include "Canvas2D.h"
#include <windows.h>
#include "GL/GL.h"

void Canvas2D::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(320,240,0);
    //glTranslatef(-0,-0,0);

    
    glColor3f(1, 1, 1);

    //glLoadIdentity();

    for(Sprite2D* sprite_2d : sprites)
    {
        sprite_2d->render(0);
    }
    
    //glEnd();
    
}
