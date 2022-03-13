/*
Author: Connor Tall
Component that manages the movement for the plasma bullet. Also responds to collisions.
*/

#ifndef PLASMABULLETPHYSICSCOMPONENT
#define PLASMABULLETPHYSICSCOMPONENT

#include "PhysicsComponent.h"
#include "../../header/Shapes.h"

class HealthComponent;

class PlasmaBulletPhysicsComponent : public PhysicsComponent
{
private:
	Circle2D collisionShape;
	float frameTime;
	float speed;
	int damageToTake;
	const float COLLISION_RADIUS_WITH_NO_SCALING;
	float collisionRadius;
	float timer;
	std::shared_ptr<HealthComponent> healthComponent;
public:
	PlasmaBulletPhysicsComponent(Circle2D& collisionShape);
	PlasmaBulletPhysicsComponent();
	void update(GameObject& gameObject, float frameTime) override;
	const IShape2D& getShape() const override;
	void notifyCollision(const GameObject& gameObject) override;
	void initialise(std::shared_ptr<HealthComponent> healthComponent, float angle, float scale, 
		Vector2D shooterVelocity);
	void initialise(float angle, float scale, Vector2D shooterVelocity);
	~PlasmaBulletPhysicsComponent();
};

#endif