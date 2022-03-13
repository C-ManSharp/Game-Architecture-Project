#include "../header/PhysicsComponent.h"
#include "../../header/GameObject.h"
#include "../../header/Message.h"
#include "../../header/Event.h"
#include "../../header/mydrawengine.h"

PhysicsComponent::PhysicsComponent() : velocity{ Vector2D(0.0f, 0.0f) }, collider{ nullptr }
{
}

void PhysicsComponent::resetPositionIfObjectHasLeftScreen(GameObject& gameObject)
{
	const Rectangle2D SCREEN = MyDrawEngine::GetInstance()->GetViewport();
	if (gameObject.position.YValue > SCREEN.GetTopLeft().YValue + 40)
		gameObject.position.YValue = SCREEN.GetBottomRight().YValue - 40;
		
	if (gameObject.position.YValue < SCREEN.GetBottomRight().YValue - 40)
		gameObject.position.YValue = SCREEN.GetTopLeft().YValue + 40;

	if (gameObject.position.XValue > SCREEN.GetBottomRight().XValue + 40)
		gameObject.position.XValue = SCREEN.GetTopLeft().XValue - 40;

	if (gameObject.position.XValue < SCREEN.GetTopLeft().XValue - 40)
		gameObject.position.XValue = SCREEN.GetBottomRight().XValue + 40;
}

Event PhysicsComponent::createEvent(GameObject& source, EventType eventType, 
	std::shared_ptr<GameObject> collider)
{
	Event e;
	e.eventType = eventType;
	e.source = std::make_shared<GameObject>(source);
	if (collider)
	{
		e.killer = collider->creator;
		if (!e.killer)
			e.killer = collider;
	}
	else
	{
     	e.killer = nullptr;
	}
	return e;
}

Vector2D PhysicsComponent::getVelocity() const
{
	return velocity;
}