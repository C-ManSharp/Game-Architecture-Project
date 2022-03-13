#include "../header/PlasmaBulletPhysicsComponent.h"
#include "../header/HealthComponent.h"
#include "../../header/GameObject.h"
#include "../../header/mydrawengine.h"

PlasmaBulletPhysicsComponent::PlasmaBulletPhysicsComponent(Circle2D& collisionShape) : 
speed{ 300.0f }, frameTime{ 0.0f }, collisionShape{ collisionShape }, 
collisionRadius{ 0.0f }, timer{ 4.0f }, 
COLLISION_RADIUS_WITH_NO_SCALING{ 18.0f }, damageToTake{ 0 }, healthComponent{ nullptr }
{
}

PlasmaBulletPhysicsComponent::PlasmaBulletPhysicsComponent() : speed{ 300.0f },
frameTime{ 0.0f }, collisionShape{ Circle2D() }, collisionRadius{ 0.0f }, 
timer{ 4.0f }, COLLISION_RADIUS_WITH_NO_SCALING{ 18.0f }, 
damageToTake{ 0 }, healthComponent{ nullptr }
{
}

void PlasmaBulletPhysicsComponent::update(GameObject& gameObject, float frameTime)
{
	this->frameTime = frameTime;
	if(gameObject.state == ObjectState::ACTIVE)
	{ 
		gameObject.position += velocity * frameTime;
	}

	if (healthComponent)
	{
		if (damageToTake > 0)
		{
			healthComponent->removeHealth(damageToTake);
			damageToTake = 0;
		}

		if (healthComponent->getHealth() <= 0)
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
	}

	collisionShape.PlaceAt(gameObject.position, collisionRadius);
	if(timer <= 0.0f)
		gameObject.state = ObjectState::CAN_DELETE;

	if (gameObject.state == ObjectState::CAN_DELETE)
	{
		gameObject.eventDispatcher = nullptr;
		gameObject.creator = nullptr;
		gameObject.killer = nullptr;
	}
	
	if (collider)
	{
		collider->creator = nullptr;
		collider->killer = nullptr;
		collider->eventDispatcher = nullptr;
	}
	collider = nullptr;
	timer -= 1.0f * frameTime;
}

const IShape2D& PlasmaBulletPhysicsComponent::getShape() const
{
	return collisionShape;
}

void PlasmaBulletPhysicsComponent::notifyCollision(const GameObject& gameObject)
{
	damageToTake = gameObject.damage;
}

void PlasmaBulletPhysicsComponent::initialise(std::shared_ptr<HealthComponent> healthComponent,
	float angle, float scale, Vector2D shooterVelocity)
{
	this->healthComponent = healthComponent;
	velocity.setBearing(angle, speed);
	velocity += shooterVelocity;
	collisionRadius = COLLISION_RADIUS_WITH_NO_SCALING * scale;
}

void PlasmaBulletPhysicsComponent::initialise(float angle, float scale, Vector2D shooterVelocity)
{
	velocity.setBearing(angle, speed);
	velocity += shooterVelocity;
	collisionRadius = COLLISION_RADIUS_WITH_NO_SCALING * scale;
}

PlasmaBulletPhysicsComponent::~PlasmaBulletPhysicsComponent()
{
}
