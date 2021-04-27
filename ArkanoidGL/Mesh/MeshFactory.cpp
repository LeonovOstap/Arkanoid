#include "MeshFactory.h"
#include <primport/q1mdl.hpp>


Mesh MeshFactory::ConstructObject(prcore::String Path)
{
    primport::ImportQ1MDL* Model = new primport::ImportQ1MDL(Path);
    GLuint Tex = CreateTexture(Model);
    collision::CollisionGeometry geom = CalculateBounds(Model);
    //cout << Path.c_str() << endl; 

    return Mesh(Tex, Model, geom, Path);
}

collision::CollisionGeometry MeshFactory::CalculateBounds(primport::ImportQ1MDL* MDL)
{
    collision::CollisionGeometry Geom;
    Geom.boxElements.push_back(MDL->frames[0].box);

    return Geom;
}

GLuint MeshFactory::CreateTexture(primport::ImportQ1MDL* MDL)
{
    prcore::Bitmap map = MDL->skin;
    int nlog = prcore::log2i(map.GetWidth());
    int size = 1 << nlog;

    map.ReformatImage(prcore::PixelFormat(32, 0x0000ff, 0x00ff00, 0xff0000, 0xff000000));
    map.ResizeImage(size, size);
    GLuint itx = 0;
    glGenTextures(1, &itx);
    glBindTexture(GL_TEXTURE_2D, itx);

    for (int j = 0; j < (nlog + 1); ++j)
    {
        prcore::Bitmap mip = CreateMipLevel(map, j);
        glTexImage2D(GL_TEXTURE_2D,
                     j,GL_RGBA8,
                     mip.GetWidth(),
                     mip.GetHeight(),
                     0,GL_RGBA,GL_UNSIGNED_BYTE,
                     mip.GetImage());
    }
    return itx;
}
