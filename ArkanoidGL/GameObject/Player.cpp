#include "Player.h"

#include <prmath/vector3float.hpp>
#include <windows.h>
#include <prmath/vector2.hpp>


#include "Ball.h"
#include "gl/GLU.h"
#include "../General/Game.h"
#include "../mesh/MeshFactory.h"
#include "../misc/Util.h"


Player::Player(Mesh model) : GameObject(model)
{
    //reinitialize_collision();
}

void Player::SpawnBall()
{
    Mesh m = MeshFactory::Get().ConstructObject("../Content/Models/circle.mdl");
    ball = worldPointer->addGameObject<Ball>(position + getWorldTransform().GetZ() * -20,m);
    ball->setLinearVelocity(getWorldTransform().GetZ() * -70);
}


void Player::update(double delta)
{
    lastPosition = get_position();
    //getWorldTransform().setLocation(getWorldTransform().getLocation() + movementSpeed * inputVector * delta);
    position += movementSpeed * inputVector * delta;

    //set_rotation(float3(get_rotation().x,get_rotation().y+2,get_rotation().z+2));

    GameObject::update(delta);
}

void Player::ReceiveKeyboard(int Key, bool pressed)
{
    if (Key == KEYCODE_A)
        if (pressed)
            inputVector.x = -1.f;
        else
            inputVector.x = 0.f;

    if (Key == KEYCODE_D)
        if (pressed)
            inputVector.x = 1.f;
        else
            inputVector.x = 0.f;

    if (Key == KEYCODE_W)
        if (pressed)
            inputVector.y = 1.f;
        else
            inputVector.y = 0.f;

    if (Key == KEYCODE_S)
        if (pressed)
            inputVector.y = -1.f;
        else
            inputVector.y = 0.f;

    
    /*
    if (Key == KEYCODE_Q)
    {
        if(pressed)
            GSerializer.Serialize("../1.sar");
    }*/

    if (Key == KEYCODE_SPACE)
    {
        if (pressed)
        {
            GSerializer.Serialize("../Levels/2.sar");
        }
    }

    if(Key == KEYCODE_1 && pressed)
    {
        GGameProcess->toNextLevel();
    }


    if (Key == KEYCODE_B && pressed)
        worldPointer->destroySafe(worldPointer->GameObjects[1]);

    if (Key == KEYCODE_I && pressed)
    {
        worldPointer->Debug = !worldPointer->Debug;
    }

    if(Key == KEYCODE_Q || Key == KEYCODE_E)
        if(pressed)
            rotation.x = util::clamp( Key==KEYCODE_Q? 40.0 : -40,-40,40);
        else
            rotation.x = 0;

    //if (Key ==  && pressed)
    //    position = vec3f(0,0,0);
        //worldPointer->Debug = !worldPointer->Debug;



    if (Key == KEYCODE_ESC)
        GGameProcess->exit();
}

void Player::ReceiveMousePosition(int x, int y)
{

    //rotation.x = rotation.x + x;

    static vec2f old_loc = vec2f(0,0);

    //rotation.x += y-old_loc.y>0? -3.25 : 3.25;

    //rotation = util::clamp(rotation,-40,40);

    
    //cout << getWorldTransform().getRotation().x << " " << getWorldTransform().getRotation().y << " " << getWorldTransform().getRotation().z << endl;
    //if(x > 240)
    old_loc = vec2f(x,y);
    //else
    //getWorldTransform().setRotation(float3(getWorldTransform().getRotation().x,getWorldTransform().getRotation().y-0.2,getWorldTransform().getRotation().z));
}

void Player::ReceiveMousePress(int x, int y, prcore::MouseButton Mouse, int amount)
{
    if(Mouse == MOUSE_LEFT && !ball)
        SpawnBall();

    if(Mouse == MOUSE_RIGHT && ball)
    {
        worldPointer->destroySafe(ball);
        ball = nullptr;
    }

    if(Mouse == MOUSE_WHEEL)
    {
        vec3f targetRotation = rotation;
        targetRotation.y += amount>0? -3.25 : 3.25;

        //util::vinterp(rotation,targetRotation,0.25);

        //rotation = prmath::Lerp(rotation,targetRotation,1.f/amount);
        
        
        rotation = util::clamp(targetRotation,-40,40);

    }
}


void Player::reinitialize_collision()
{
    SphereElement element = SphereElement();


    element.radius = Length(model.getCollisionGeom().boxElements[0].vmax / 2.f);
    element.center = model.getCollisionGeom().boxElements[0].GetCenter();
    model.getCollisionGeom().boxElements.clear();

    model.getCollisionGeom().sphereElements.push_back(element);
}
