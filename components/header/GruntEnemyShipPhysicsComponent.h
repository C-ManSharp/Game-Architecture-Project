/*
Author: Connor Tall
Handles the movement and collision events for the grunt enemy ships. Also reacts to the states in the AI component.
*/

#ifndef GRUNTENEMYSHIPPHYSICSCOMPONENT
#define GRUNTENEMYSHIPPHYSICSCOMPONENT

#include "PhysicsComponent.h"
#include "../../header/Shapes.h"

class AIComponent;
class HealthComponent;

class GruntEnemyShipPhysicsComponent : public PhysicsComponent
{
private:
	float acceleration;
	float rotationSpeed;
	float friction;
	float angle;
	float frameTime;
	const float COLLISION_RADIUS_WITH_NO_SCALING;
	float collisionRadius;
	int damageToTake;
	Circle2D collisionShape;
	Vector2D ownerPosition;
	Vector2D accelerationVector;
	float turn;
	float desiredAngle;
	std::shared_ptr<AIComponent> gruntShipAIComponent;
	std::shared_ptr<HealthComponent> healthComponent;
	void rotateLeft(float frameTime);
	void rotateRight(float frameTime);
	void spawnExplosion(GameObject& gameObject) const;
	void getTargetAngle(GameObject& gameObject);
	void spawnJet(GameObject& gameObject) const;
	bool whiskerIntersects(GameObject& gameObject) const;
	void moveForward(GameObject& gameObject);
	float getDistanceBetweenShipAndPlayerShip(GameObject& gameObject) const;
	void shootPlayer(GameObject& gameObject);
public:
	GruntEnemyShipPhysicsComponent(Circle2D collisionShape);
	GruntEnemyShipPhysicsComponent();
	void initialise(std::shared_ptr<HealthComponent> healthComponent, float acceleration, 
		float rotationSpeed, float friction, float angle, float scale, Vector2D velocity, 
		std::shared_ptr<AIComponent> gruntShipAIComponent);
	void update(GameObject& gameObject, float frameTime) override;
	const IShape2D& getShape() const override;
	void notifyCollision(const GameObject& gameObject) override;
	~GruntEnemyShipPhysicsComponent();
};

#endif