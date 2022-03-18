#include "Player.h"
#include "PlayerMoveComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "MazeScene.h"
#include "Wall.h"
#include "AABBCollider.h"
#include "Agent.h"
#include "Collider.h"
#include "InputComponent.h";

void Player::start()
{
	Agent::start();

	addComponent<PlayerMoveComponent>();
	m_spriteComponent = dynamic_cast<SpriteComponent*>(addComponent(new SpriteComponent("Images/player.png")));
	getTransform()->setScale({ Maze::TILE_SIZE, Maze::TILE_SIZE });
	m_input = getComponent<InputComponent>();
	setCollider(new AABBCollider(Maze::TILE_SIZE, Maze::TILE_SIZE, this));
	//Set spawn point
	//Set move speed
	//Set position clamps
}

void Player::update(float deltaTime)
{
	Agent::update(deltaTime);

	if (!m_input->getMoveAxis().getMagnitude())
		getMoveComponent()->setVelocity({ 0,0 });
}

void Player::onCollision(Actor* other)
{
	if (Wall* wall = dynamic_cast<Wall*>(other)) {
		MathLibrary::Vector2 halfTile = { Maze::TILE_SIZE / 2.0f, Maze::TILE_SIZE / 2.0f };
		MathLibrary::Vector2 position = getTransform()->getWorldPosition();
		position = position + halfTile;
		MathLibrary::Vector2 tilePosition = {
			roundf(position.x / Maze::TILE_SIZE) * Maze::TILE_SIZE,
			roundf(position.y / Maze::TILE_SIZE) * Maze::TILE_SIZE
		};
		tilePosition = tilePosition - halfTile;
		//getTransform()->setWorldPostion(getTransform()->getWorldPosition() - getMoveComponent()->getVelocity().getNormalized() * -.05f);
		applyForce(getCollider()->getCollisionNormal() * -1 * getMoveComponent()->getVelocity().getMagnitude());
	}
}
