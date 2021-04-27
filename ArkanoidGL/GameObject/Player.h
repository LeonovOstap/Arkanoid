#pragma once
#include "../general/GameObject.h"
#include "../misc/Input.h"


class Player : public GameObject, public InputReceiver
{
public:

public:
    Player(Mesh model);

    void SpawnBall();


private:
    void update(double delta) override;
    class Ball* ball = 0;

    //Input
    void ReceiveKeyboard(int Key, bool pressed) override;
    void ReceiveMousePosition(int x, int y) override;
    void ReceiveMousePress(int x, int y, prcore::MouseButton Mouse, int amount) override;

    //Collision
    void reinitialize_collision();

private:
    vec3f inputVector = vec3f(0,0,0);

    vec3f lastPosition;

    float movementSpeed = 50.f;
};
