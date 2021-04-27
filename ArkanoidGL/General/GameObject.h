#pragma once

#include "../mesh/Mesh.h"
#include "../misc/Primitive.h"
#include "../misc/Serializer.h"


struct hit_info;

enum EGameObjectAttributes
{
    NONE = 1,
    NO_DRAW = 2,
    NO_COLLISION_RESPONSE = 4,
    //todo:: prophecys matricies are weird,this is why we dont want to update velocity
    STATIC = 8
};

DEFINE_ENUM_FLAG_OPERATORS(EGameObjectAttributes);

class GameObject : public Primitive, public Serializable
{
    friend class World;
    friend class Serializer;
    friend class ArkWindow;
    friend class PhysicsSolver;
    friend class Sprite2D;

public:
    explicit GameObject(Mesh model)
       : model(model)
    {
    }

    virtual ~GameObject();

    virtual void update(double delta);

    vec3f getLinearVelocity()
    {
        return linear_velocity;
    };

    void setLinearVelocity(vec3f Velocity)
    {
        linear_velocity = Velocity;
    };

    void handle_collision(hit_info& info) override;

    void onObjectCollided(Primitive* Other) override
    {
    };
public:
    
    EGameObjectAttributes attributes = NONE;
    GameObject* Owner = 0;
    prcore::Timer Lifetime = prcore::Timer();
protected:
    virtual void render();
    Mesh model;
    class World* worldPointer = 0;


    vec3f linear_velocity = vec3f(0,0,0);


    virtual void Serialize(prcore::Stream& stream) override;
    virtual void Deserialize(prcore::Stream& stream) override;
    virtual bool IsSerializable() override {return true;};
};

