#pragma once
#include <primport/q1mdl.hpp>


#include "Mesh.h"

class MeshFactory
{
public:
    virtual ~MeshFactory() = default;
    static MeshFactory Get() { return MeshFactory(); };

    Mesh ConstructObject(prcore::String Path);
protected:
    virtual collision::CollisionGeometry CalculateBounds(primport::ImportQ1MDL* MDL);
    virtual GLuint CreateTexture(primport::ImportQ1MDL* MDL);
};
