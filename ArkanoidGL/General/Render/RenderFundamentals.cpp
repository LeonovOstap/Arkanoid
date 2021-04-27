#include "RenderFundamentals.h"

#include <GL/GL.h>
#include <prcore/surface.hpp>

void Renderer::render()
{
    //createRT(SceneRT,screenSize);
     
}

void Renderer::createRT(RenderTarget& RT, point2f size)
{
    RT = RenderTarget(size);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_BACK);
    glReadPixels(0,0,size.x,size.y,GL_RGBA,GL_UNSIGNED_BYTE,RT.pixelData.data());
    RT.update();
}

uint32 Renderer::BlendWithBuffer_Alpha(prcore::Bitmap tex, point2f position, point2f scale)
{
    using namespace prcore;
    prcore::Surface s = SceneRT.renderTarget;
    auto format =prcore::PixelFormat(32, 0x0000ff, 0x00ff00, 0xff0000, 0xff000000);

    tex.ReformatImage(format);
    
    prcore::SetAlphaFunc(prcore::SRCALPHA, prcore::SRCINVALPHA);
    prcore::AlphaBlend((int)position.x,(int)position.y,s,tex);
    

    

    //glDrawPixels(screenSize.x,screenSize.y,GL_RGBA,GL_UNSIGNED_BYTE,SceneRT.pixelData.data());

    prcore::Surface s1 = s;
    //s1.SaveImage("../tes4553t.jpg");
    	
   
    //this will crash over time
    GLuint in;
    glGenTextures(1, &in);
    glBindTexture(GL_TEXTURE_2D, in);
    

    glTexImage2D(GL_TEXTURE_2D,
                     0,GL_RGBA8,
                     s1.GetWidth(),
                     s1.GetHeight(),
                     0,GL_RGBA,GL_UNSIGNED_BYTE,
                     s1.GetImage());
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    return in; 
}
