#pragma once
#include <vector>
#include "windows.h"
#include <GL/GL.h>
#include <prcore/refcount.hpp>
#include <prcore/string.hpp>


#include "../Physics/Collision.h"
#include "primport/q1mdl.hpp"
#include "prcore/prcore.hpp"


struct Mesh
{
    friend class Serializer;
public:
    Mesh(GLuint texture, primport::ImportQ1MDL* model, collision::CollisionGeometry oriented_box, const char* inPath)
        : texture(texture),
          Model(model),
          geometry_(oriented_box), filePath(inPath)
    {
    }

    Mesh() = default;

    const GLuint& GetTexture() { return texture; }
    const char* GetPath() { return filePath; }
    const primport::ImportQ1MDL* GetModel() { return Model; };
    collision::CollisionGeometry& getCollisionGeom() { return geometry_; };
protected:
    GLuint texture = 0;
    primport::ImportQ1MDL* Model = nullptr;
    collision::CollisionGeometry geometry_;
    prcore::String filePath;
};
