#pragma once
#include <prcore/keyboard.hpp>
#include <prcore/mouse.hpp>

class InputReceiver
{
public:
    virtual void ReceiveKeyboard(int Key, bool pressed) = 0;
    virtual void ReceiveMousePosition(int x, int y) = 0;
    virtual void ReceiveMousePress(int x, int y,prcore::MouseButton Mouse,int amount) = 0;

    void setEnableInput(bool Receive)
    {
        bReceivesInput = Receive;
    };

protected:
    bool bReceivesInput = true;
};
