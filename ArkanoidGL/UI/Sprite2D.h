#pragma once
#include <windows.h>
#include <GL/GL.h>
#include <prcore/bitmap.hpp>
#include <prcore/rect.hpp>

class Sprite2D : public prcore::Rect
{
public:
    Sprite2D(prcore::Bitmap image)
        : Image(image)
    {
    }

    Sprite2D(int x, int y, int width, int height, prcore::Bitmap image);

    virtual void render(double delta);

    void init();

private:
    prcore::Bitmap Image;
    GLuint TexData = 0;
};
