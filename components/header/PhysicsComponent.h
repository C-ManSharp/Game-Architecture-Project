/*
Author: Connor Tall
Abstract base class for all physics components.
*/

#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <memory>

#include "Component.h"
//#include "../../header/GameObject.h"
#include "../../header/vector2D.h"

class IShape2D;
class GameObject;
struct Event;
enum class EventType;
enum class ObjectState;

class PhysicsComponent : public Component
{

protected:
	Vector2D velocity;
	std::shared_ptr<GameObject> collider;
public:
	PhysicsComponent();
	virtual void update(GameObject& gameObject, float frameTime) = 0;
	virtual const IShape2D& getShape() const = 0;
	virtual void notifyCollision(const GameObject& gameObject) = 0;
	Event createEvent(GameObject& source, EventType eventType, 
		std::shared_ptr<GameObject> collider);

	void resetPositionIfObjectHasLeftScreen(GameObject& gameObject);
	Vector2D getVelocity() const;
	virtual ~PhysicsComponent() {};
};
#endif