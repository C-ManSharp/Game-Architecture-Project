#include "../header/CollisionComponent.h"
#include "../header/PhysicsComponent.h"
#include "../../header/Shapes.h"
#include "../../header/GameObject.h"

CollisionComponent::CollisionComponent(std::shared_ptr<PhysicsComponent> physicsComponent,
	const GameObject& gameObject):
	physicsComponent{ physicsComponent }, collisionShape{physicsComponent->getShape()},
	gameObject{ gameObject }, INVINCIBILITY_LENGTH{ 3.0f },
	invincibilityTimer{ INVINCIBILITY_LENGTH }, invincibilityHasExpired{ false }
{
}

CollisionComponent::CollisionComponent(const GameObject& gameObject) :
	physicsComponent{ nullptr }, collisionShape{ Circle2D() },
	gameObject{ gameObject }, INVINCIBILITY_LENGTH{ 3.0f }, 
	invincibilityTimer{ INVINCIBILITY_LENGTH }, invincibilityHasExpired{ false }
{
}


void CollisionComponent::update(GameObject& gameObject, float frameTime)
{
	if (invincibilityHasExpired == false && gameObject.invincibleOnSpawn)
	{
		invincibilityTimer -= 1.0f * frameTime;
		if (invincibilityTimer > 0)
		{
			gameObject.state = ObjectState::INVINCIBLE;
		}
		else
		{
			gameObject.state = ObjectState::ACTIVE;
			invincibilityHasExpired = true;
		}
	}
}

const IShape2D& CollisionComponent::getShape() const
{
	return collisionShape;
}

const GameObject& CollisionComponent::getGameObject() const
{
	return gameObject;
}

void CollisionComponent::notifyCollison(const GameObject& gameObject)
{
	if (physicsComponent)
		physicsComponent->notifyCollision(gameObject);
	
}

CollisionComponent::~CollisionComponent()
{
	physicsComponent = nullptr;
}
