/*
Author: Connor Tall
Performs movement and physics calculations for the astroids. Also, handles collisions.
*/

#ifndef ASTROIDPHYSICSCOMPONENT_H
#define ASTROIDPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "../../header/Shapes.h"

class HealthComponent;

class AstroidPhysicsComponent : public PhysicsComponent
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
	AstroidPhysicsComponent();
	AstroidPhysicsComponent(Circle2D collisionShape);
	void initialise(std::shared_ptr<HealthComponent> healthComponent, float acceleration, 
		float rotationSpeed, float friction, float scale, Vector2D velocity);
	void initialise(float acceleration, float rotationSpeed, float friction, float scale, 
		Vector2D velocity);
	void update(GameObject& gameObject, float frameTime) override;
	const IShape2D& getShape() const override;
	void notifyCollision(const GameObject& gameObject) override;
	void spawnChildAstroids(GameObject& gameObject);
	~AstroidPhysicsComponent();
};

#endif
