#include "../header/TimedObjectSpawnerComponent.h"
#include "../../header/gamecode.h"
#include "../../header/SoundFX.h"
#include "../../header/GameObject.h"
#include "../header/PlasmaBulletPhysicsComponent.h"
#include "../header/MachineGunBulletPhysicsComponent.h"
#include "../header/PlayerPhysicsComponent.h"

TimedObjectSpawnerComponent::TimedObjectSpawnerComponent(
	const std::shared_ptr<ObjectFactory> objectFactory) : delay{ 0.0f }, time{ 0.0f }
{
	this->objectFactory = objectFactory;
}

TimedObjectSpawnerComponent::TimedObjectSpawnerComponent() : delay{ 0.0f }, time{ 0.0f }
{
	this->objectFactory = nullptr;
}

void TimedObjectSpawnerComponent::update(GameObject& gameObject, float frameTime)
{
	if (objectsToSpawn.size() > 0 && spawnObjectRequested && time <= 0.0f)
	{
		for (const std::shared_ptr<GameObject>gameObject : objectsToSpawn)
		{
			Game::instance.getGameObjectManager().addGameObject(gameObject);
			switch (gameObject->getObjectType())
			{
				case ObjectType::PLASMA_BULLET:
					SoundFX::instance.playPlasmaShootingSound();
					break;
				case ObjectType::MACHINE_GUN_BULLET:
					SoundFX::instance.playMachineGunShootingSound();
					break;
			}
		}
		objectsToSpawn.clear();
		spawnObjectRequested = false;
		time = delay;
	}
	objectsToSpawn.clear();
	time -= 1.0f * frameTime;
}

void TimedObjectSpawnerComponent::spawnPlasmaBullet(GameObject& owner, const float MAGNITUED_OF_OFFSET)
{
	if (time <= 0.0f)
	{
		std::shared_ptr<GameObject>bullet = createGameObject(L"plasma_bullet");
		if (bullet)
		{
			bullet->creator = std::make_shared<GameObject>(owner);
			Vector2D spawnOffset;
			spawnOffset.setBearing(owner.angle, MAGNITUED_OF_OFFSET);
			bullet->position = owner.position + spawnOffset;

			std::shared_ptr<PlasmaBulletPhysicsComponent> plasmaBulletPhysicsComponent =
				bullet->getComponentFromClassAndName(PlasmaBulletPhysicsComponent(),
					L"plasma_bullet_physics_component");
			if (plasmaBulletPhysicsComponent)
			{
				plasmaBulletPhysicsComponent->initialise(owner.angle, bullet->scale,
					owner.velocity);
			}
			spawnGameObject(bullet);
		}
	}
}

void TimedObjectSpawnerComponent::spawnMachineGunBullet(GameObject& owner, const float MAGNITUED_OF_OFFSET)
{
	if (time <= 0.0f)
	{
		std::shared_ptr<GameObject>bullet = createGameObject(L"machine_gun_bullet");
		if (bullet)
		{
			bullet->creator = std::make_shared<GameObject>(owner);
			Vector2D spawnOffset;
			spawnOffset.setBearing(owner.angle, MAGNITUED_OF_OFFSET);
			bullet->position = owner.position + spawnOffset;

			std::shared_ptr<MachineGunBulletPhysicsComponent> machineGunBulletPhysicsComponent =
				bullet->getComponentFromClassAndName(MachineGunBulletPhysicsComponent(),
					L"machine_gun_bullet_physics_component");
			if (machineGunBulletPhysicsComponent)
			{
				machineGunBulletPhysicsComponent->initialise(owner.angle, bullet->scale,
					owner.velocity);
			}
			spawnGameObject(bullet);
		}
	}
}

void TimedObjectSpawnerComponent::initialise(float delay)
{
	this->delay = delay;
}

TimedObjectSpawnerComponent::~TimedObjectSpawnerComponent()
{
}
