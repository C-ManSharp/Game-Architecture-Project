#include "../header/AsteroidPhysicsComponent.h"
#include "../../header/GameObject.h"
#include "../../commands/header/Command.h"
#include "../../header/Shapes.h"
#include "../header/HealthComponent.h"
#include "../header/InstantObjectSpawnerComponent.h"
#include "../../header/Event.h"
#include "../../header/EventDispatcher.h"

AsteroidPhysicsComponent::AsteroidPhysicsComponent(Circle2D collisionShape) : 
acceleration{ 300.0f }, rotationSpeed{ 1.0f }, friction{ -0.5f }, angle{ 0.0f }, frameTime{ 0.0f }, 
collisionShape{ collisionShape }, collisionRadius{ 60.0f }, ownerPosition{Vector2D(0.0f, 0.0f)}, 
COLLISION_RAIDUS_WITH_NO_SCALING{ 60.0f }, healthComponent{ nullptr }, damageToTake{ 0 }
{
}

AsteroidPhysicsComponent::AsteroidPhysicsComponent() :
acceleration{ 300.0f }, rotationSpeed{ 1.0f }, friction{ -0.5f }, angle{ 0.0f },
frameTime{ 0.0f }, collisionShape{ Circle2D() }, collisionRadius{ 60.0f }, 
ownerPosition{ Vector2D(0.0f, 0.0f) }, COLLISION_RAIDUS_WITH_NO_SCALING{ 60.0f }, 
healthComponent{ nullptr }, damageToTake{ 0 }
{
}

void AsteroidPhysicsComponent::initialise(std::shared_ptr<HealthComponent> healthComponent,
	float acceleration, float rotationSpeed, float friction, float scale, Vector2D velocity)
{
	this->healthComponent = healthComponent;
	this->acceleration = acceleration;
	this->rotationSpeed = rotationSpeed;
	this->friction = friction;
	this->velocity = velocity;
	collisionRadius = COLLISION_RAIDUS_WITH_NO_SCALING * scale;
}

void AsteroidPhysicsComponent::initialise(float acceleration, float rotationSpeed, float friction,
	float scale, Vector2D velocity)
{
	this->acceleration = acceleration;
	this->rotationSpeed = rotationSpeed;
	this->friction = friction;
	this->velocity = velocity;
	collisionRadius = COLLISION_RAIDUS_WITH_NO_SCALING * scale;
}

void AsteroidPhysicsComponent::update(GameObject& gameObject, float frameTime)
{
	ownerPosition = gameObject.position;
	this->frameTime = frameTime;
	gameObject.angle += rotationSpeed * frameTime;
	gameObject.position += (velocity * frameTime);
	
	if (healthComponent)
	{
		if (damageToTake > 0)
		{
			healthComponent->removeHealth(damageToTake);
			damageToTake = 0;
		}

		if (healthComponent->getHealth() <= 0)
		{
			Event e = createEvent(gameObject, EventType::ASTEROID_DEATH, collider);
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
		if (healthComponent->getHealth() <= 0 && gameObject.creatorObjectType == ObjectType::UNKOWN)
			spawnChildAsteroids(gameObject);
	}

	if (collider)
	{
		collider->creator = nullptr;
		collider->killer = nullptr;
		collider->eventDispatcher = nullptr;
	}
	collider = nullptr;
	collisionShape.PlaceAt(gameObject.position, collisionRadius);
	resetPositionIfObjectHasLeftScreen(gameObject);
}

void AsteroidPhysicsComponent::spawnChildAsteroids(GameObject& gameObject)
{
	InstantObjectSpawnerComponent instantObjectSpawnerComponentType;
	std::shared_ptr<InstantObjectSpawnerComponent> objectSpawnerComponent =
		gameObject.getComponentFromClassAndName(instantObjectSpawnerComponentType,
			L"asteroid_instant_object_spawner_component");
	const int NUMBER_OF_asteroidS_TO_SPAWN = (int)rand() % 3 + 2;
	for (int i = 0; i < NUMBER_OF_asteroidS_TO_SPAWN; i++)
	{
		if (objectSpawnerComponent)
		{
			std::shared_ptr<GameObject> asteroid = objectSpawnerComponent->createGameObject(
				L"asteroid");
			if (asteroid)
			{
				asteroid->scale = 0.5;
				asteroid->creatorObjectType = gameObject.getObjectType();
				asteroid->invincibleOnSpawn = false;
				AsteroidPhysicsComponent asteroidPhysicsComponentType;
				std::shared_ptr<AsteroidPhysicsComponent> asteroidPhysicsComponent =
					asteroid->getComponentFromClassAndName(asteroidPhysicsComponentType,
						L"asteroid_physics_component");
				if (asteroidPhysicsComponent)
				{
					Vector2D pos;
					Vector2D velocity;
					pos.setBearing(rand() % 628 / 100.0f, rand() % -30 + 30.0f);
					velocity.setBearing(rand() % 628 / 100.0f, rand() % -80 + 80.0f);
					pos += gameObject.position;
					asteroid->position = pos;
					asteroidPhysicsComponent->initialise(300.0f, 0.3f,
						-0.8f, asteroid->scale, velocity);
					objectSpawnerComponent->spawnGameObject(asteroid);
				}
			}
		}
	}
}

const IShape2D& AsteroidPhysicsComponent::getShape() const
{
	return collisionShape;
}

void AsteroidPhysicsComponent::notifyCollision(const GameObject& gameObject)
{
	Vector2D normal = (ownerPosition - gameObject.position).unitVector();
	switch (gameObject.getObjectType())
	{
		case ObjectType::ASTEROID:
			if (normal * velocity < 0)
			{
				velocity = velocity - 2 * (velocity * normal) * normal;
				velocity *= 0.8f;
			}
			break;
		case ObjectType::PLASMA_BULLET:
			damageToTake = gameObject.damage;
			break;
		case ObjectType::MACHINE_GUN_BULLET:
			damageToTake = gameObject.damage;
			break;
		default:
			damageToTake = 0;
	}

	if (!collider)
	{
		collider = std::make_shared<GameObject>(gameObject.getObjectType());
		collider->killer = gameObject.killer;
		collider->creator = gameObject.creator;
	}
}

AsteroidPhysicsComponent::~AsteroidPhysicsComponent()
{
}