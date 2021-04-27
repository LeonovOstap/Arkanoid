#include "Sprite2D.h"
#include <windows.h>
#include <prcore/float754.hpp>
#include <prcore/mipmap.hpp>



#include "../general/Game.h"
#include "GL/GL.h"


void Sprite2D::init()
{
    //Image.ReformatImage(prcore::PixelFormat(32, 0x0000ff, 0x00ff00, 0xff0000, 0xff000000));
    Image = Bitmap("../test.png",PIXELFORMAT_ARGB8888);

    cout << Image.GetWidth() << " " << Image.GetHeight() << endl;
    
    //Image.ResizeImage(320, 240);
    int nlog = prcore::log2i(Image.GetWidth());
    int size = 1 << nlog;
    
    //Image.ReformatImage(prcore::PixelFormat(32, 0x0000ff, 0x00ff00, 0xff0000, 0xff000000));
    //Image.ResizeImage(size, size);
    //glGenTextures(1, &TexData);
    //glBindTexture(GL_TEXTURE_2D, TexData);
    

    glTexImage2D(GL_TEXTURE_2D,
                     0,GL_RGBA8,
                     Image.GetWidth(),
                     Image.GetHeight(),
                     0,GL_RGBA,GL_UNSIGNED_BYTE,
                     Image.GetImage());
    //Disable mips, we dont need them kekw
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

}


Sprite2D::Sprite2D(int x, int y, int width, int height, prcore::Bitmap image)
    : Image(image)
{
}

void Sprite2D::render(double delta)
{
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glTranslatef(0.5,0.5,0.5);

    //glBindTexture( GL_TEXTURE_2D, TexData);
    //glBegin( GL_QUADS );
    //glTexCoord2f( 0, 0 );
    //glVertex2f( 0, 0 );
    ///glTexCoord2f( 1, 0 );
    //glVertex2f( 1, 0 );
    //glTexCoord2f( 1, 1 );
    //glVertex2f( 1, 1 );
    //glTexCoord2f( 0, 1 );
    //glVertex2f( 0, 1 );
    //glEnd();

    //glEnable( GL_BLEND );

    Image = Bitmap("../test.png",PIXELFORMAT_ARGB8888);
    Image.FlipImageY();
    //Image.ResizeImage(480,480);
    GLuint k = GGameProcess->getRenderer()->BlendWithBuffer_Alpha(Image,point2f(0.0),point2f(720,720));

    TexData = k;
    
    glBindTexture(GL_TEXTURE_2D,TexData);
    //glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

    
    //glScalef()
    //glTranslatef(-1,0,0);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(0, 1);
    glVertex2f(0, -1);
    glTexCoord2f(1, 1);
    glVertex2f(1, -1);
    glTexCoord2f(1, 0);
    glVertex2f(1, 0);
    /*

    glTexCoord2f(-0.5,-0.5);
    glVertex2f(-0.5,-0.5);
    
    glTexCoord2f(0.5,0.5);
    glVertex2f(0.5,0.5);
    
    glTexCoord2f(-0.5,0.5);
    glVertex2f(-0.5,0.5);
    

    
    
    
    
    glTexCoord2f(0.5,-0.5);
    glVertex2f(0.5,-0.5);*/
    glEnd();
    //glLoadIdentity();

    //glDisable(GL_BLEND);

    
}
