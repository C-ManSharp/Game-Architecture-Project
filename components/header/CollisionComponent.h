/*
Author: Connor Tall
Notifies the physics component when a collision occurs. Controls the timer for invincibility
*/

#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"

class PhysicsComponent;
class IShape2D;
enum class ObjectState;

class CollisionComponent : public Component
{
private:
	const float INVINCIBILITY_LENGTH;
	float invincibilityTimer;
	bool invincibilityHasExpired;
	std::shared_ptr<PhysicsComponent> physicsComponent;
	const IShape2D& collisionShape;
	const GameObject& gameObject;
public:
	CollisionComponent(std::shared_ptr<PhysicsComponent>physicsComponent, const GameObject& gameObject);
	CollisionComponent(const GameObject& gameObject);
	//Called in the collision loop
	void notifyCollison(const GameObject& gameObject);
	void update(GameObject& gameObject, float frameTime) override;
	const IShape2D& getShape() const;
	const GameObject& getGameObject() const;
	~CollisionComponent();
};


#endif
