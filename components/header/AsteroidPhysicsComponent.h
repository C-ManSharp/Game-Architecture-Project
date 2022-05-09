/*
Author: Connor Tall
Performs movement and physics calculations for the astroids. Also, handles collisions.
*/

#ifndef ASTEROIDPHYSICSCOMPONENT_H
#define ASTEROIDPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "../../header/Shapes.h"

class HealthComponent;

class AsteroidPhysicsComponent : public PhysicsComponent
{
private:
	float acceleration;
	float rotationSpeed;
	float friction;
	float angle;
	float frameTime;
	float COLLISION_RAIDUS_WITH_NO_SCALING;
	float collisionRadius;
	Circle2D collisionShape;
	Vector2D ownerPosition;
	int damageToTake;
	std::shared_ptr<HealthComponent> healthComponent;
public:
	AsteroidPhysicsComponent();
	AsteroidPhysicsComponent(Circle2D collisionShape);
	void initialise(std::shared_ptr<HealthComponent> healthComponent, float acceleration, 
		float rotationSpeed, float friction, float scale, Vector2D velocity);
	void initialise(float acceleration, float rotationSpeed, float friction, float scale, 
		Vector2D velocity);
	void update(GameObject& gameObject, float frameTime) override;
	const IShape2D& getShape() const override;
	void notifyCollision(const GameObject& gameObject) override;
	void spawnChildAsteroids(GameObject& gameObject);
	~AsteroidPhysicsComponent();
};

#endif
