#include "../header/PlayerPhysicsComponent.h"
#include "../../header/GameObject.h"
#include "../../commands/header/Command.h"
#include "../../header/Shapes.h"
#include "../header/InstantObjectSpawnerComponent.h"
#include "../../header/SoundFX.h"
#include "../../components/header/AnimationComponent.h"
#include "../header/HealthComponent.h"
#include "../../header/Event.h"
#include "../../header/EventDispatcher.h"
#include "../header/IntegerRenderComponent.h"
#include "../header/HealthComponent.h"
#include "../../header/ObjectManager.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(AngledRectangle2D collisionShape) : 
acceleration{ 300.0f }, rotationSpeed{ 1.2f }, friction{ -0.5f }, angle{ 0.0f }, 
frameTime{ 0.0f }, collisionShape{ collisionShape }, REVERSE_ACCELERATION{ 4 }, damageToTake{ 0 }, 
smokeTime{ 0.2f }, healthToHeal{ 0 }, healthComponent{ nullptr }, health{ 0 }
{
}

PlayerPhysicsComponent::PlayerPhysicsComponent() :
acceleration{ 300.0f }, rotationSpeed{ 1.2f }, friction{ -0.5f }, angle{ 0.0f },
frameTime{ 0.0f }, collisionShape{  }, REVERSE_ACCELERATION{ 4 }, damageToTake{ 0 },
smokeTime{ 0.2f }, healthToHeal{ 0 }, healthComponent{ nullptr }, health{ 0 }
{
}

void PlayerPhysicsComponent::initialise(std::shared_ptr<HealthComponent> healthComponent)
{
	this->healthComponent = healthComponent;
}

void PlayerPhysicsComponent::update(GameObject& gameObject, float frameTime)
{
	this->frameTime = frameTime;
	gameObject.angle = angle;
	if (healthComponent)
	{
		int HEALTH = healthComponent->getHealth();
		if (damageToTake > 0)
		{
			healthComponent->removeHealth(damageToTake);
			damageToTake = 0;
		}
		if (healthComponent->getHealth() <= 0)
		{
			SoundFX::instance.playExplosionSound();
			spawnExplosion(gameObject);
			gameObject.state = ObjectState::CAN_DELETE;
			Event e = createEvent(gameObject, EventType::PLAYER_DEATH, collider);
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

		if (healthToHeal > 0)
		{
			if (healthComponent)
			{
				healthComponent->addHealth(healthToHeal);
				healthToHeal = 0;
			}
		}

		//Spawn smoke on right wing
		if (HEALTH <= 75 && gameObject.state != ObjectState::CAN_DELETE &&
			smokeTime <= 0.0f)
		{
			Vector2D smokePositionOffset;
			smokePositionOffset.setBearing(angle + 2.5f, 50.0f);
			spawnSmoke(gameObject, gameObject.position + smokePositionOffset);
			if (HEALTH > 50)
				smokeTime = 0.2f;
		}
		//Spawn smoke on left wing.
		if (HEALTH <= 50 && gameObject.state != ObjectState::CAN_DELETE &&
			smokeTime <= 0.0f)
		{
			Vector2D smokePositionOffset;
			smokePositionOffset.setBearing(angle - 2.5f, 50.0f);
			spawnSmoke(gameObject, gameObject.position + smokePositionOffset);
			smokeTime = 0.2f;
		}
	}
	//collider = nullptr;
	const size_t NUMBER_OF_COMMANDS = message->commands.size();
	if (NUMBER_OF_COMMANDS > 0)
	{
		for (std::shared_ptr<Command>& command : message->commands)
			command->execute(*this);
		this->message->commands.clear();
	}
	
	if (collider)
	{
		collider->creator = nullptr;
		collider->killer = nullptr;
		collider->eventDispatcher = nullptr;
	}
	collider = nullptr;
	velocity += (friction * velocity) * this->frameTime;
	gameObject.position += (velocity * this->frameTime);

	collisionShape.SetAngle(gameObject.angle);
	collisionShape.SetCentre(gameObject.position);

	gameObject.velocity = velocity;
	smokeTime -= 1.0f * frameTime;
	resetPositionIfObjectHasLeftScreen(gameObject);
}

void PlayerPhysicsComponent::moveForward()
{
	Vector2D accelerationVector;
	accelerationVector.setBearing(angle, acceleration);
	velocity += (accelerationVector * frameTime);
}

void PlayerPhysicsComponent::rotateLeft()
{
	angle -= (rotationSpeed * frameTime);
}

void PlayerPhysicsComponent::rotateRight()
{
	angle += (rotationSpeed * frameTime);
}

const IShape2D& PlayerPhysicsComponent::getShape() const
{
	return collisionShape;
}

void PlayerPhysicsComponent::notifyCollision(const GameObject& gameObject)
{
	switch (gameObject.getObjectType())
	{
		case ObjectType::ASTROID:
			damageToTake = gameObject.damage;
			break;
		case ObjectType::PLASMA_BULLET:
			damageToTake = gameObject.damage;
			break;
		case ObjectType::MACHINE_GUN_BULLET:
			damageToTake = gameObject.damage;
			break;
		case ObjectType::GRUNT_ENEMY_SHIP:
			damageToTake = gameObject.damage;
			break;
		case ObjectType::HEALTH_PACK:
			healthToHeal = gameObject.healthToHeal;
			break;
		default:
			damageToTake = 0;
			healthToHeal = 0;
			break;
	}
	if (!collider)
	{
		collider = std::make_shared<GameObject>(gameObject.getObjectType());
		collider->killer = gameObject.killer;
		collider->creator = gameObject.creator;
	}
}

void PlayerPhysicsComponent::moveBack()
{
	Vector2D accelerationVector;
	accelerationVector.setBearing(angle, acceleration);
	velocity -= (accelerationVector * (frameTime * REVERSE_ACCELERATION));
}

void PlayerPhysicsComponent::spawnExplosion(GameObject& gameObject) const
{
	const float EXPLOSION_SIZE = 2.5f;
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
		std::vector<std::shared_ptr<AnimationComponent>>animationComponents = 
			explosion->getComponentsFromClass(animationComponentType);
		if (animationComponents.size() > 0)
		{
			for (std::shared_ptr<AnimationComponent>animationComponent : animationComponents)
			{
				if (animationComponent->getComponentName() == L"explosion_animation_component")
				{
					animationComponent->initialise(EXPLOSION_SIZE, EXPLOSION_TIME,
						velocity);
					explosion->position = gameObject.position;
					objectSpawnerComponent->spawnGameObject(explosion);
				}
			}
		}
	}
}

void PlayerPhysicsComponent::spawnSmoke(GameObject& gameObject, Vector2D position) const
{
	const float SMOKE_SIZE = 0.5f;
	const float SMOKE_TIME = 1.0f;

	InstantObjectSpawnerComponent objectSpawnerComponentType;

	std::shared_ptr<InstantObjectSpawnerComponent>objectSpawnerComponent =
		gameObject.getComponentFromClassAndName(objectSpawnerComponentType, 
			L"instant_object_spawner_component");

	if (objectSpawnerComponent)
	{
		std::shared_ptr<GameObject>smoke =
			objectSpawnerComponent->createGameObject(L"smoke");
		smoke->scale = SMOKE_SIZE;
		smoke->angle = gameObject.angle;

		AnimationComponent animationComponentType;
		std::shared_ptr<AnimationComponent>animationComponent =
			smoke->getComponentFromClassAndName(animationComponentType,
				L"smoke_animation_component");
			if (animationComponent)
			{
				animationComponent->initialise(SMOKE_SIZE, SMOKE_TIME,
					velocity);
				smoke->position = position;
				objectSpawnerComponent->spawnGameObject(smoke);
			}
	}
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}

