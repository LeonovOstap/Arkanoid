#pragma once
#include <vector>
#include <prcore/bitmap.hpp>
#include <prmath/matrix4x4.hpp>

#include "Sprite2D.h"

class Canvas2D
{
public:
    Canvas2D() = default;

    matrix4x4f getMatrix()
    {
        return viewMatrix;
    }

    void draw();
    std::vector<Sprite2D*> sprites;
private:
    matrix4x4f viewMatrix;
    
    //std::vector<prcore::Bitmap>
    
};
