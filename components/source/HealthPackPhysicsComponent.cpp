#include "../header/HealthPackPhysicsComponent.h"
#include "../../header/GameObject.h"
#include "../../header/Event.h"
#include "../../header/EventDispatcher.h"
#include "../../header/mydrawengine.h"

HealthPackPhysicsComponent::HealthPackPhysicsComponent() : collisionShape{  }, 
destroyOwningObject{ false }, collisionRectangleTopOffsetWithNoScaling{ 20.0f }, 
collisionRectangleLeftOffsetWithNoScaling{ -25.0f },
collisionRectangleBottomOffsetWithNoScaling{ -20.0f },
collisionRectangleRightOffsetWithNoScaling{ 20.0f }
{
}

HealthPackPhysicsComponent::HealthPackPhysicsComponent(Rectangle2D collisionShape) : 
collisionShape{ collisionShape }, destroyOwningObject{ false },
collisionRectangleTopOffsetWithNoScaling{ 20.0f }, collisionRectangleLeftOffsetWithNoScaling{ -25.0f  },
collisionRectangleBottomOffsetWithNoScaling{ -20.0f }, 
collisionRectangleRightOffsetWithNoScaling{ 20.0f }
{
}


void HealthPackPhysicsComponent::update(GameObject& gameObject, float frameTime)
{
	if (destroyOwningObject == true)
	{
		gameObject.state = ObjectState::CAN_DELETE;
		Event e = createEvent(gameObject, EventType::HEALTH_PACK_PICKUP, collider);
		gameObject.eventDispatcher->dispatchEvent(e);
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
	updateCollisionShapePosition(gameObject);
}

const IShape2D& HealthPackPhysicsComponent::getShape() const
{
	return collisionShape;
}

void HealthPackPhysicsComponent::updateCollisionShapePosition(GameObject& gameObject)
{
	const float TOP = gameObject.position.YValue + (collisionRectangleTopOffsetWithNoScaling *
		gameObject.scale);
	const float LEFT = gameObject.position.XValue + (collisionRectangleLeftOffsetWithNoScaling *
		gameObject.scale);
	const float BOTTOM = gameObject.position.YValue + (collisionRectangleBottomOffsetWithNoScaling *
		gameObject.scale);
	const float RIGHT = gameObject.position.XValue + (collisionRectangleRightOffsetWithNoScaling *
		gameObject.scale);
	collisionShape.PlaceAt(TOP, LEFT, BOTTOM, RIGHT);
}

void HealthPackPhysicsComponent::notifyCollision(const GameObject& gameObject)
{
	//Side note: Could also have bullets destroy this object.
	if (gameObject.getObjectType() == ObjectType::PLAYER_SHIP)
		destroyOwningObject = true;

	if (!collider)
	{
		collider = std::make_shared<GameObject>(gameObject.getObjectType());
		collider->killer = gameObject.killer;
		collider->creator = gameObject.creator;
	}
}

HealthPackPhysicsComponent::~HealthPackPhysicsComponent()
{
}
