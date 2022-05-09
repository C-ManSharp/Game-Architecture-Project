#include "../header/GruntEnemyShipPhysicsComponent.h"
#include "../../components/header/AnimationComponent.h"
#include "../header/InstantObjectSpawnerComponent.h"
#include "../header/TimedObjectSpawnerComponent.h"
#include "../header/PlasmaBulletPhysicsComponent.h"
#include "../header/AnimationComponent.h"
#include "../header/AIComponent.h"
#include "../../header/Event.h"
#include "../../header/EventDispatcher.h"
#include "../../header/GameObject.h"
#include "../../header/SoundFX.h"
#include "../header/HealthComponent.h"
//To go in AI component
#include "../../header/gamecode.h"
#include "../../header/mydrawengine.h"


GruntEnemyShipPhysicsComponent::GruntEnemyShipPhysicsComponent(Circle2D collisionShape) : 
acceleration{ 300.0f }, rotationSpeed{ 2.5f }, friction{ -0.3f }, angle{ 0.0f }, frameTime{ 0.0f }, 
collisionShape{ collisionShape }, collisionRadius{ 30.0f }, ownerPosition{ Vector2D(0.0f, 0.0f) }, 
damageToTake{ 0 }, COLLISION_RADIUS_WITH_NO_SCALING{ 30.0f }, gruntShipAIComponent{ nullptr }, 
turn{ 0.0f }, accelerationVector{ Vector2D() }, desiredAngle{ 0.0f }
{
}

GruntEnemyShipPhysicsComponent::GruntEnemyShipPhysicsComponent() : acceleration{ 300.0f }, 
rotationSpeed{ 2.5f }, friction{ -0.3f }, angle{ 0.0f }, frameTime{ 0.0f }, 
collisionShape{ Circle2D() }, collisionRadius{ 30.0f }, ownerPosition{ Vector2D(0.0f, 0.0f) },
damageToTake{ 0 }, COLLISION_RADIUS_WITH_NO_SCALING{ 30.0f }, gruntShipAIComponent{ nullptr },
turn{ 0.0f }, accelerationVector{ Vector2D() }, desiredAngle{ 0.0f }
{
}

void GruntEnemyShipPhysicsComponent::initialise(std::shared_ptr<HealthComponent> healthComponent, 
	float acceleration, float rotationSpeed, float friction, float angle, float scale,
	Vector2D velocity, std::shared_ptr<AIComponent> gruntShipAIComponent)
{
	this->healthComponent = healthComponent;
	this->acceleration = acceleration;
	this->rotationSpeed = rotationSpeed;
	this->friction = friction;
	this->velocity = velocity;
	this->angle = angle;
	collisionRadius = COLLISION_RADIUS_WITH_NO_SCALING * scale;
	this->gruntShipAIComponent = gruntShipAIComponent;
}

void GruntEnemyShipPhysicsComponent::update(GameObject& gameObject, float frameTime)
{
	this->ownerPosition = gameObject.position;
	gameObject.angle = angle;
	this->frameTime = frameTime;

	moveForward(gameObject);

	const bool WHISKER_INTERSECTS = whiskerIntersects(gameObject);

	if (healthComponent)
	{
		if (damageToTake > 0)
		{
			healthComponent->removeHealth(damageToTake);
			damageToTake = 0;
		}
		if (healthComponent->getHealth() <= 0)
		{
			SoundFX::instance.playExplosionSound();
			spawnExplosion(gameObject);
			Event e = createEvent(gameObject, EventType::GRUNT_ENEMY_SHIP_DEATH, collider);
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
	}
	
	if (gruntShipAIComponent)
	{
		if (gruntShipAIComponent->getAIState() == AIState::ATTACKING && !WHISKER_INTERSECTS)
		{
			if (angle != desiredAngle)
			{
				getTargetAngle(gameObject);
				if (turn < 0)
					rotateRight(frameTime);
				if (turn > 0)
					rotateLeft(frameTime);
			}
			
			if (turn >= 0.0f && turn <= 0.5f && 
				getDistanceBetweenShipAndPlayerShip(gameObject) < 1000.0f)
				shootPlayer(gameObject);
		}
	}
	if (collider)
	{
		collider->creator = nullptr;
		collider->killer = nullptr;
		collider->eventDispatcher = nullptr;
	}

	collider = nullptr;

	if (WHISKER_INTERSECTS)
		rotateLeft(frameTime);

	velocity += friction * velocity * frameTime;
	gameObject.position += velocity * frameTime;

	collisionShape.PlaceAt(gameObject.position, collisionRadius);
	resetPositionIfObjectHasLeftScreen(gameObject);
}

const IShape2D& GruntEnemyShipPhysicsComponent::getShape() const
{
	return collisionShape;
}

void GruntEnemyShipPhysicsComponent::notifyCollision(const GameObject& gameObject)
{
	switch (gameObject.getObjectType())
	{
		case ObjectType::ASTEROID:
			damageToTake = gameObject.damage;
			break;
		case ObjectType::PLASMA_BULLET:
			damageToTake = gameObject.damage;
			break;
		case ObjectType::GRUNT_ENEMY_SHIP:
			damageToTake = gameObject.damage;
			break;
		case ObjectType::MACHINE_GUN_BULLET:
			damageToTake = gameObject.damage;
			break;
		case ObjectType::PLAYER_SHIP:
			damageToTake = gameObject.damage;
			break;
		default:
			damageToTake = 0;
			break;
	}
	if (!collider)
	{
		collider = std::make_shared<GameObject>(gameObject.getObjectType());
		collider->killer = gameObject.killer;
		collider->creator = gameObject.creator;
	}
}

void GruntEnemyShipPhysicsComponent::moveForward(GameObject& gameObject)
{
	accelerationVector.setBearing(angle, acceleration);
	velocity += (accelerationVector * frameTime);
	spawnJet(gameObject);
}

float GruntEnemyShipPhysicsComponent::getDistanceBetweenShipAndPlayerShip(GameObject& gameObject) const
{
	float distance = 9999999.0f;
	std::shared_ptr<GameObject> playerShip = Game::instance.getGameObjectManager().getPlayerShip();
	if (playerShip)
	{
		Vector2D relativeVector = gameObject.position - playerShip->position;
		distance = relativeVector.magnitude();
	}
	return distance;
}

void GruntEnemyShipPhysicsComponent::getTargetAngle(GameObject& gameObject)
{
	std::shared_ptr<GameObject> playerShip = Game::instance.getGameObjectManager().getPlayerShip();
	if (playerShip && playerShip->state != ObjectState::CAN_DELETE)
	{
		Vector2D target = playerShip->position;
		Vector2D desiredDirection = target - gameObject.position;
		desiredAngle = desiredDirection.angle();
		turn = angle - desiredAngle;
		if (turn > 3.141f) 
			turn -= 6.282f;
	}
}

void GruntEnemyShipPhysicsComponent::rotateLeft(float frameTime)
{
	angle -= rotationSpeed * frameTime;
	accelerationVector.setBearing(angle, acceleration);
}

void GruntEnemyShipPhysicsComponent::rotateRight(float frameTime)
{
	angle += rotationSpeed * frameTime;
	accelerationVector.setBearing(angle, acceleration);
}

void GruntEnemyShipPhysicsComponent::shootPlayer(GameObject& gameObject)
{
	std::shared_ptr<GameObject> playerShip = Game::instance.getGameObjectManager().getPlayerShip();
	if (playerShip)
	{
		TimedObjectSpawnerComponent timedObjectSpawnerComponent;
		std::shared_ptr<TimedObjectSpawnerComponent> plasmaGunSpawnerComponent =
			gameObject.getComponentFromClassAndName(timedObjectSpawnerComponent,
				L"plasma_gun_timed_object_spawner_component");
		if (plasmaGunSpawnerComponent)
		{
			if (playerShip->state != ObjectState::CAN_DELETE)
			{
				std::shared_ptr<GameObject> plasmaBullet = 
					plasmaGunSpawnerComponent->createGameObject(L"plasma_bullet");
				if (plasmaBullet)
				{
					PlasmaBulletPhysicsComponent physicsComponentType;
					std::shared_ptr<PlasmaBulletPhysicsComponent> plasmaBulletPhysicsComponent = 
						plasmaBullet->getComponentFromClassAndName(physicsComponentType, 
						L"plasma_bullet_physics_component");
					if (plasmaBulletPhysicsComponent)
					{
						plasmaBulletPhysicsComponent->initialise(angle, plasmaBullet->scale,
							 velocity);
						Vector2D offset;
						offset.setBearing(angle, 45.0f);
						plasmaBullet->creatorObjectType = ObjectType::GRUNT_ENEMY_SHIP;
						plasmaBullet->position = gameObject.position + offset;
						
						plasmaGunSpawnerComponent->spawnGameObject(plasmaBullet);
					}
				}
			}
		}
	}
}

void GruntEnemyShipPhysicsComponent::spawnExplosion(GameObject& gameObject) const
{
	const float EXPLOSION_SIZE = 2.0f;
	const float EXPLOSION_TIME = 0.4f;

	InstantObjectSpawnerComponent objectSpawnerComponentType;

	std::shared_ptr<InstantObjectSpawnerComponent>objectSpawnerComponent =
		gameObject.getComponentFromClass(objectSpawnerComponentType);

	if (objectSpawnerComponent)
	{
		std::shared_ptr<GameObject>explosion =
			objectSpawnerComponent->createGameObject(L"expolsion");
		explosion->scale = EXPLOSION_SIZE;
		AnimationComponent animationComponentType;
		std::shared_ptr<AnimationComponent> animationComponent =
			explosion->getComponentFromClassAndName(animationComponentType, 
				L"explosion_animation_component");
		if (animationComponent)
		{
			animationComponent->initialise(EXPLOSION_SIZE, EXPLOSION_TIME,
				velocity);
			explosion->position = gameObject.position;
			objectSpawnerComponent->spawnGameObject(explosion);
		}
	}
}

void GruntEnemyShipPhysicsComponent::spawnJet(GameObject& gameObject) const
{
	const float JET_SCALE = 0.3f;
	InstantObjectSpawnerComponent iosc;
	std::shared_ptr<InstantObjectSpawnerComponent>objectSpawnerComponent =
		gameObject.getComponentFromClassAndName(iosc, L"instant_object_spawner_component");

	if (objectSpawnerComponent)
	{
		std::shared_ptr<GameObject>explosion =
			objectSpawnerComponent->createGameObject(L"expolsion");
		explosion->scale = JET_SCALE;
		AnimationComponent animComponent;
		std::shared_ptr<AnimationComponent>explosionAnimationComponent =
			explosion->getComponentFromClassAndName(animComponent, L"explosion_animation_component");
		if (explosionAnimationComponent)
		{
			Vector2D jetPosition;
			jetPosition.setBearing(gameObject.angle + 3.14f, 20.0f);
			jetPosition += gameObject.position;
			Vector2D jetVelocity;
			jetVelocity.setBearing(gameObject.angle + 3.14f, 500.0f);
			jetVelocity += gameObject.velocity;
			explosionAnimationComponent->initialise(0.4f, 0.1f, jetVelocity);
			explosion->position = jetPosition;
			objectSpawnerComponent->spawnGameObject(explosion);
		}
	}
}

bool GruntEnemyShipPhysicsComponent::whiskerIntersects(GameObject& gameObject) const
{
	const float OFFSET_MAGNITUED_WITH_NO_SCALING = 170.0f;

	Vector2D offset;
	offset.setBearing(gameObject.angle, OFFSET_MAGNITUED_WITH_NO_SCALING * gameObject.scale);
	const float RECTANGLE_TOP_WITH_NO_SCALING = gameObject.position.YValue + offset.YValue + 120.0f;
	const float RECTANGLE_LEFT_WITH_NO_SCALING = gameObject.position.XValue + offset.XValue + -50.0f;
	const float RECTANGLE_BOTTOM_WITH_NO_SCALING = gameObject.position.YValue + offset.YValue + -120.0f;
	const float RECTANGLE_RIGHT_WITH_NO_SCALING = gameObject.position.XValue + offset.XValue + 50.0f;
	const float TOP = RECTANGLE_TOP_WITH_NO_SCALING * gameObject.scale;
	const float LEFT = RECTANGLE_LEFT_WITH_NO_SCALING * gameObject.scale;
	const float BOTTOM = RECTANGLE_BOTTOM_WITH_NO_SCALING * gameObject.scale;
	const float RIGHT = RECTANGLE_RIGHT_WITH_NO_SCALING * gameObject.scale;
	Rectangle2D whisker;
	whisker.PlaceAt(TOP, LEFT, BOTTOM, RIGHT);
	std::shared_ptr<GameObject> intersectingObject = 
		Game::instance.getGameObjectManager().intersection(whisker);
	if (intersectingObject)
	{
		if (intersectingObject->state == ObjectState::CAN_DELETE)
		{
			return false;
		}
		else
		{
			ObjectType intersectingObjectType = intersectingObject->getObjectType();
			if (intersectingObject->creatorObjectType == ObjectType::GRUNT_ENEMY_SHIP || 
				intersectingObjectType == ObjectType::HEALTH_PACK ||
				(intersectingObjectType == ObjectType::PLAYER_SHIP &&
					getDistanceBetweenShipAndPlayerShip(gameObject) > 300.0f))
				return false;
			else
				return true;
		}
	}
	intersectingObject = nullptr;
	return false;
}

GruntEnemyShipPhysicsComponent::~GruntEnemyShipPhysicsComponent()
{
}
