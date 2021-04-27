#pragma once
#undef min
#undef max
#include <vector>
#include <prmath/intersect.hpp>
#include <prmath/matrix4x4.hpp>


#include "prcore/prcore.hpp"
#include "prmath/prmath.hpp"

using BoxElement = box3f;
using SphereElement = sphere3f;
//using ConvexElement = std::vector<vec3f>;

using namespace std;

namespace collision
{
    struct CollisionGeometry
    {
        vector<BoxElement> boxElements;
        vector<SphereElement> sphereElements;
    };

    //We dont need to transform Box Rotation, since all box colliders are stationary objects
    //I was wrong
    inline BoxElement BoxToWorld(BoxElement bounds, vec3f Origin, vec3f scale = vec3f(1, 1, 1))
    {
        BoxElement K;
        K.vmax = Origin + bounds.vmax * scale;
        K.vmin = Origin + bounds.vmin * scale;

        return K;
    }

    inline BoxElement CalculateAABB(BoxElement bounds, matrix4x4f objectTransform)
    {
        BoxElement k = bounds;
        //matrix4x4f objectToWorld = prmath::MatrixInverse(objectTransform);

        k.vmin *= objectTransform;
        k.vmax *= objectTransform;

        return k;

        vec3f vertecies[8];
        bounds.GetVertexArray8(vertecies, objectTransform);

        for (int i = 0; i < 8; ++i)
        {
            k.vmin = min(k.vmin, vertecies[i]);
            k.vmax = max(k.vmax, vertecies[i]);
        }

        return k;
    }

    inline SphereElement SphereToWorld(SphereElement bounds, matrix4x4f transform)
    {
        bounds.center *= transform;
        return bounds;
    }

    inline bool AABBvsAABB(const BoxElement& A1,
                           const BoxElement& B1)
    {
        if ((A1.vmin.x > B1.vmax.x) || (B1.vmin.x > A1.vmax.x))
        {
            return false;
        }

        if ((A1.vmin.y > B1.vmax.y) || (B1.vmin.y > A1.vmax.y))
        {
            return false;
        }

        if ((A1.vmin.z > B1.vmax.z) || (B1.vmin.z > A1.vmax.z))
        {
            return false;
        }

        return true;
    };

    inline bool AABBvsSphere(const BoxElement Box, const SphereElement sphere)
    {
        /*
                using namespace std;
                float x = max(Box.vmin.x,min(sphere.center.x,Box.vmax.x));
                float y = max(Box.vmin.y,min(sphere.center.y,Box.vmax.y));
                float z = max(Box.vmin.z,min(sphere.center.z,Box.vmax.z));
                
                float distance = sqrt((x - sphere.center.x) * (x - sphere.center.x) +
                                   (y - sphere.center.y) * (y - sphere.center.y) +
                                   (z - sphere.center.z) * (z - sphere.center.z));
              
                return distance < sphere.radius;*/
        return IntersectBoxSphere(Box, sphere);
    }
}
