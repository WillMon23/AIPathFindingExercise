#include "Agent.h"
#include "MoveComponent.h"
#include "SteeringComponent.h"
#include "Engine.h"

float maxSpeedRef = 0;
Agent::Agent(float x, float y, const char* name, float maxSpeed, float maxForce) : Actor(x, y, name)
{
	setMaxForce(maxForce);
	maxSpeedRef = maxSpeed;
}

void Agent::start()
{
	Actor::start();

	m_moveComponent = addComponent<MoveComponent>();
	m_moveComponent->setMaxSpeed(maxSpeedRef);
	m_moveComponent->setUpdateFacing(true);
}

void Agent::fixedUpdate(float deltaTime)
{
	Actor::fixedUpdate(deltaTime);
	//Get all force being applied from steering behaviours
	for (int i = 0; i < m_steeringComponents.getLength(); i++)
	{
		m_force = m_force + m_steeringComponents[i]->calculateForce();
	}

	//Clamp force if it exceeds the maximum scale
	if (m_force.getMagnitude() > getMaxForce())
	{
		m_force = m_force.getNormalized() * getMaxForce();
	}

	//Apply force to velocity
	applyForce(m_force);
}

void Agent::onAddComponent(Component* component)
{
	SteeringComponent* steeringComponent = dynamic_cast<SteeringComponent*>(component);
	if (steeringComponent)
		m_steeringComponents.addItem(steeringComponent);
}

void Agent::applyForce(MathLibrary::Vector2 force)
{
	m_moveComponent->setVelocity((m_moveComponent->getVelocity() + force));
}
