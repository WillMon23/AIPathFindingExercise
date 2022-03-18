#include "AABBCollider.h"
#include "CircleCollider.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Player.h"
#include <algorithm>

AABBCollider::AABBCollider(Actor* owner) : Collider::Collider(owner, ColliderType::BOX)
{
	m_width = getOwner()->getTransform()->getScale().x;
	m_height = getOwner()->getTransform()->getScale().y;
}

AABBCollider::AABBCollider(float width, float height, Actor* owner) : Collider::Collider(owner, ColliderType::BOX)
{
	m_width = width;
	m_height = height;
}

float AABBCollider::getLeft()
{
	return getOwner()->getTransform()->getWorldPosition().x - getWidth() / 2;
}

float AABBCollider::getRight()
{
	return getOwner()->getTransform()->getWorldPosition().x + getWidth() / 2;
}

float AABBCollider::getTop()
{
	return getOwner()->getTransform()->getWorldPosition().y - getHeight() / 2;
}

float AABBCollider::getBottom()
{
	return getOwner()->getTransform()->getWorldPosition().y + getHeight() / 2;
}

bool AABBCollider::checkCollisionCircle(CircleCollider* collider)
{
	//Return false if the actor is checking collision against itself
	if (collider->getOwner() == getOwner())
		return false;

	//Call the function to check a circle against an AABB
	return collider->checkCollisionAABB(this);
}

bool AABBCollider::checkCollisionAABB(AABBCollider* collider)
{
	//Return false if the actor is checking collision against itself
	if (collider->getOwner() == getOwner())
		return false;

	//Check for AABB overlap
	if (collider->getLeft() <= getRight() &&
		collider->getTop() <= getBottom() &&
		getLeft() <= collider->getRight() &&
		getTop() <= collider->getBottom())
	{
		//find collision normal
		int left = abs(collider->getRight() - getLeft());
		int right = abs(collider->getLeft() - getRight());
		int top = abs(collider->getBottom() - getTop());
		int bottom = abs(getBottom() - collider->getTop());
		int arr[] = { left, right, top, bottom };

		std::pair<int*, int*> minMax = std::minmax_element(std::begin(arr), std::end(arr));
		int min = *(minMax.first);
		if (min == left)
			setCollisionNormal({ -1,0 });
		else if (min == right)
			setCollisionNormal({ 1,0 });
		else if (min == top)
			setCollisionNormal({ 0,-1 });
		else if (min == bottom)
			setCollisionNormal({ 0, 1 });

		return true;
	}



	return false;
}