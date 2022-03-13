/*
Author: Connor Tall
Handles the movement and collision for the player.
*/

#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "../../header/Shapes.h"

class HealthComponent;

class PlayerPhysicsComponent : public PhysicsComponent
{
private:
	float acceleration;
	float rotationSpeed;
	float friction;
	float angle;
	float frameTime;
	float smokeTime;
	unsigned int damageToTake;
	unsigned int healthToHeal;
	AngledRectangle2D collisionShape;
	const int REVERSE_ACCELERATION;
	std::shared_ptr<HealthComponent> healthComponent;
	int health;
	void spawnExplosion(GameObject& gameObject) const;
	void spawnSmoke(GameObject& gameObject, Vector2D position) const;

public:
	PlayerPhysicsComponent(AngledRectangle2D collisionShape);
	PlayerPhysicsComponent();
	void update(GameObject& gameObject, float frameTime) override;
	const IShape2D& getShape() const override;
	void notifyCollision(const GameObject& gameObject) override;
	void initialise(std::shared_ptr<HealthComponent> healthComponent);
	void moveForward();
	void rotateLeft();
	void rotateRight();
	void moveBack();
	~PlayerPhysicsComponent();
};

#endif