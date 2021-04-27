#pragma once
#include <prmath/matrix4x4.hpp>


struct hit_info;

class Primitive
{
    friend class Serializer;
public:
    //Convert to prophecy matrix
    matrix4x4f getWorldTransform()
    {
        matrix4x4f m;

        for (int i = 0; i < 16; ++i)
            m.m16[i] = transform[i];

        return m;
    };

    void updateTransform()
    {
        glTranslatef(position.x, position.y, position.z);
        glRotatef(rotation.x, 1, 0, 0);
        glRotatef(rotation.y, 0, 1, 0);
        glRotatef(rotation.z, 0, 0, 1);
        glScalef(scale.x, scale.y, scale.z);

        glGetFloatv(GL_MODELVIEW_MATRIX, transform);
    }


    vec3f get_position() const
    {
        return position;
    }

    void set_position(const vec3f& position)
    {
        this->position = position;
    }

    float3 get_rotation() const
    {
        return rotation;
    }

    void set_rotation(const float3& rotation)
    {
        this->rotation = rotation;
    }

    vec3f get_scale() const
    {
        return scale;
    }

    void set_scale(const vec3f& scale)
    {
        this->scale = scale;
    }

    //todo::clean up
    //Collision response
    virtual void handle_collision(hit_info& info) = 0;
    //For gameplay mechanics
    virtual void onObjectCollided(Primitive* Other) = 0;


protected:
    ~Primitive() = default;
    //prophecies matrix screws rotation, fall back to ogl instead
    float transform[16];

    vec3f position;
    float3 rotation;
    vec3f scale;
};
