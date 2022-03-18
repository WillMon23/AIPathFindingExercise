#pragma once
#include "Actor.h"
#include "ActorArray.h"
#include <Vector2.h>

class SteeringComponent;
class MoveComponent;

class Agent :
	public Actor
{
public:
	Agent(float x, float y, const char* name, float maxSpeed, float maxForce);
	void start() override;
	void fixedUpdate(float deltaTime) override;
	void onAddComponent(Component* component) override;
	float getMaxForce() { return m_maxForce; }
	void setMaxForce(float maxForce) { m_maxForce = maxForce; }
	MoveComponent* getMoveComponent() { return m_moveComponent; }
	void applyForce(MathLibrary::Vector2 force);
	MathLibrary::Vector2 getForce() { return m_force; }

private:
	DynamicArray<SteeringComponent*> m_steeringComponents;
	float m_maxForce;
	MoveComponent* m_moveComponent;
	MathLibrary::Vector2 m_force;
};

