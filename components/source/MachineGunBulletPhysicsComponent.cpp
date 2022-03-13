#include "../header/MachineGunBulletPhysicsComponent.h"
#include "../../header/GameObject.h"

MachineGunBulletPhysicsComponent::MachineGunBulletPhysicsComponent(Circle2D& collisionShape) :
COLLISION_RADIUS_WITH_NO_SCALING{ 2.5f }, speed{ 500.0f }, frameTime{ 0.0f },
collisionShape{ collisionShape }, collisionRadius{ COLLISION_RADIUS_WITH_NO_SCALING },
destroyOwningObject{ false }, timer{ 5.0f }, healthComponent{ nullptr }
{
}

MachineGunBulletPhysicsComponent::MachineGunBulletPhysicsComponent() : 
COLLISION_RADIUS_WITH_NO_SCALING{ 2.5f }, speed{ 500.0f }, frameTime{ 0.0f },
collisionShape{ Circle2D() }, collisionRadius{ COLLISION_RADIUS_WITH_NO_SCALING },
destroyOwningObject{ false }, timer{ 5.0f }, healthComponent{ nullptr }
{
}

void MachineGunBulletPhysicsComponent::update(GameObject& gameObject, float frameTime)
{
	this->frameTime = frameTime;
	if (gameObject.state == ObjectState::ACTIVE)
		gameObject.position += velocity * frameTime;
	
	if (destroyOwningObject)
		gameObject.state = ObjectState::CAN_DELETE;

	if (timer <= 0.0f)
		gameObject.state = ObjectState::CAN_DELETE;

	if (gameObject.state == ObjectState::CAN_DELETE)
	{
		gameObject.eventDispatcher = nullptr;
		gameObject.creator = nullptr;
		gameObject.killer = nullptr;
		if (collider)
		{
			collider->creator = nullptr;
			collider->killer = nullptr;
			collider->eventDispatcher = nullptr;
		}
		collider = nullptr;
	}
	if (collider)
	{
		collider->creator = nullptr;
		collider->killer = nullptr;
		collider->eventDispatcher = nullptr;
	}
	collider = nullptr;
	collisionShape.PlaceAt(gameObject.position, collisionRadius);
	timer -= 1.0f * frameTime;
}

const IShape2D& MachineGunBulletPhysicsComponent::getShape() const
{
	return collisionShape;
}

void MachineGunBulletPhysicsComponent::notifyCollision(const GameObject& gameObject)
{
	destroyOwningObject = true;
}

void MachineGunBulletPhysicsComponent::initialise(float angle, float scale, Vector2D shooterVelocity)
{
	velocity.setBearing(angle, speed);
	velocity += shooterVelocity;
	collisionRadius = COLLISION_RADIUS_WITH_NO_SCALING * scale;
}


MachineGunBulletPhysicsComponent::~MachineGunBulletPhysicsComponent()
{
}
