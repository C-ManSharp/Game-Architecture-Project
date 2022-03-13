/*
Author: Connor Tall
Handles the collisions with the health pack.
*/
#ifndef HEALTHPACKPHYSICSCOMPONENT_H
#define HEALTHPACKPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "../../header/Shapes.h"

class HealthPackPhysicsComponent : public PhysicsComponent
{
private:
	Rectangle2D collisionShape;
	bool destroyOwningObject;
	float collisionRectangleTopOffsetWithNoScaling;
	float collisionRectangleLeftOffsetWithNoScaling;
	float collisionRectangleBottomOffsetWithNoScaling;
	float collisionRectangleRightOffsetWithNoScaling;
public:
	HealthPackPhysicsComponent();
	HealthPackPhysicsComponent(Rectangle2D collisionShape);
	void update(GameObject& gameObject, float frameTime) override;
	void updateCollisionShapePosition(GameObject& gameObject);
	const IShape2D& getShape() const override;
	void notifyCollision(const GameObject& gameObject) override;
	~HealthPackPhysicsComponent();
};

#endif