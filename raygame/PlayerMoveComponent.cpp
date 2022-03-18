#include "PlayerMoveComponent.h"
#include "InputComponent.h"
#include "Actor.h"
#include "Agent.h"

void PlayerMoveComponent::start()
{
    SteeringComponent::start();
    m_input = getOwner()->getComponent<InputComponent>();
}

MathLibrary::Vector2 PlayerMoveComponent::calculateForce()
{
    return m_input->getMoveAxis() * getAgent()->getMaxForce();
}
