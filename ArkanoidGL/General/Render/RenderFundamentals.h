#pragma once
#include <vector>
#include <prcore/prcore.hpp>
#include <prcore/surface.hpp>
#include <prmath/vector2.hpp>

struct RenderTarget
{
    friend class Renderer;

public:

    std::vector<int> pixelData;
    prcore::Surface renderTarget;
    point2f size;
private:
    RenderTarget(point2f inSize)
        : size(inSize)
    {
        pixelData.resize((int)size.x*size.y*4);
    }
    void update()
    {
        auto format = prcore::PixelFormat(32, 0x0000ff, 0x00ff00, 0xff0000, 0xff000000);
        renderTarget = prcore::Surface(size.x,size.y,size.x*format.GetBytes(),format,pixelData.data());
        renderTarget.FlipImageY();
    }
};
//todo:: this should be renamed, its just a helper class
class Renderer
{
public:

    Renderer()
        : SceneRT(RenderTarget(point2f(0,0)))
    {
        
    };
    virtual void render();

    void updateScreensize(point2f Size)
    {
        screenSize = Size;
    };

    virtual void createRT(RenderTarget& RT, point2f size);

    RenderTarget& getSceneRT()
    {
        return SceneRT;
    }
    uint32 BlendWithBuffer_Alpha(prcore::Bitmap tex, point2f position, point2f scale);

private:
    point2f screenSize = point2f(0,0);
    RenderTarget SceneRT;

    //This is fucking retarded
    
    
};
