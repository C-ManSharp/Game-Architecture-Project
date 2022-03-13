/*
Author: Connor Tall
Handles the movement and collision for the machine gun bullets.
*/

#ifndef MACHINEGUNBULLETPHYSCICSCOMPONENT_H
#define MACHINEGUNBULLETPHYSCICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "../../header/Shapes.h"

class HealthComponent;

class MachineGunBulletPhysicsComponent : public PhysicsComponent
{
private:
	Circle2D collisionShape;
	const float COLLISION_RADIUS_WITH_NO_SCALING;
	float frameTime;
	float speed;
	float collisionRadius;
	bool destroyOwningObject;
	float timer;
	std::shared_ptr<HealthComponent> healthComponent;
public:
	MachineGunBulletPhysicsComponent(Circle2D& collisionShape);
	MachineGunBulletPhysicsComponent();
	void update(GameObject& gameObject, float frameTime) override;
	const IShape2D& getShape() const override;
	void notifyCollision(const GameObject& gameObject) override;
	void initialise(float angle, float scale, Vector2D shooterVelocity);
	~MachineGunBulletPhysicsComponent();
};
#endif