#pragma once
#include "SteeringComponent.h"

class InputComponent;

class PlayerMoveComponent :
    public SteeringComponent
{
public:
    void start() override;
    MathLibrary::Vector2 calculateForce();

private:
    InputComponent* m_input;
};

