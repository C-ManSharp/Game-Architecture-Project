#include "../header/LevelManager.h"
#include "../components/header/InstantObjectSpawnerComponent.h"
#include "../components/header/Component.h"
#include "../components/header/TextRenderComponent.h"
#include "../components/header/IntegerRenderComponent.h"
#include "../components/header/AsteroidPhysicsComponent.h"
#include "../components/header/CollisionComponent.h"
#include "../components/header/HealthComponent.h"
#include "../components/header/AIComponent.h"
#include "../header/Event.h"
#include "../header/mydrawengine.h"
#include "../header/gameObject.h"
#include "../header/gamecode.h"

LevelManager::LevelManager() : score{ 0 }, scoreValueRenderComponent{ nullptr }, 
instantObjectSpawnerComponent{ nullptr }, gruntSpaceShipEnemyCount { 0 }, 
healthPackCount{ 0 }, astroidCount{ 0 }, MAXIMUM_AMOUNT_OF_GRUNT_SPACESHIPS{ 5 }, 
MAXIMUM_AMOUNT_OF_HEALTH_PACKS{ 2 }, MAXIMUM_AMOUNT_OF_ASTROIDS{ 3 }
{
	objectType = ObjectType::LEVEL_MANAGER;
	startLevel();
}

std::shared_ptr<InstantObjectSpawnerComponent> LevelManager::getInstantObjectSpawnerComponent()
{
	InstantObjectSpawnerComponent iosc;
	return getComponentFromClassAndName(iosc, L"instant_object_spawner_component");
}

void LevelManager::startLevel()
{
	if (instantObjectSpawnerComponent)
	{
		instantObjectSpawnerComponent->requestThatObjectBeSpawnedByName(L"playership");
		//Spawn 3 astroids at the start.
		for (int i = 0; i < 3; i++)
			spawnAstroid();
	}
}

void LevelManager::update(float frameTime)
{
	if (gruntSpaceShipEnemyCount < MAXIMUM_AMOUNT_OF_GRUNT_SPACESHIPS)
		spawnGruntEnemyShip();

	if (astroidCount < MAXIMUM_AMOUNT_OF_ASTROIDS)
		spawnAstroid();
	
	if (healthPackCount < MAXIMUM_AMOUNT_OF_HEALTH_PACKS)
		spawnHealthPack();
}

void LevelManager::endLevel()
{
	std::shared_ptr<TextRenderComponent>endGameMessage = std::make_shared<TextRenderComponent>();
	endGameMessage->initialise(L"GAME OVER! Press Escape to return to the main menu", Vector2D(-400.0f, 0.0f), MyDrawEngine::RED);

	std::shared_ptr<TextRenderComponent>youDiedMessage = std::make_shared<TextRenderComponent>();
	youDiedMessage->initialise(L"You Died!", Vector2D(-1700.0f, 950.0f), MyDrawEngine::RED);

	components.push_back(endGameMessage);
	components.push_back(youDiedMessage);
}

void LevelManager::handleEvent(Event& event)
{
	switch (event.eventType)
	{
		case EventType::PLAYER_DEATH:
			endLevel();
			break;
		case EventType::GRUNT_ENEMY_SHIP_DEATH:
			gruntSpaceShipEnemyCount--;
			if (event.killer)
			{
				if (event.killer->getObjectType() == ObjectType::PLAYER_SHIP)
					addScore(event.source->getObjectType());
			}
			break;
		case EventType::ASTEROID_DEATH:
			if (event.source->creatorObjectType == ObjectType::UNKOWN)
				astroidCount--;

			if (event.killer)
			{
				if (event.killer->getObjectType() == ObjectType::PLAYER_SHIP)
					addScore(event.source->getObjectType());
			}
			break;
		case EventType::HEALTH_PACK_PICKUP:
			healthPackCount--;
			break;
	}
}

void LevelManager::addScore(ObjectType victimObjectType)
{
	switch (victimObjectType)
	{
		case ObjectType::GRUNT_ENEMY_SHIP:
			score += 20;
			break;
		case ObjectType::ASTEROID:
			score += 5;
			break;
	}
	if (scoreValueRenderComponent)
		scoreValueRenderComponent->updateIntToDraw(score);
}

void LevelManager::spawnHealthPack()
{
	std::shared_ptr<GameObject> healthPack = instantObjectSpawnerComponent->createGameObject(
		L"health_pack");
	if (healthPack)
	{
		healthPack->position.setBearing(rand() % 628 / 100.0f, rand() % 300 + 300.0f);
		instantObjectSpawnerComponent->spawnGameObject(healthPack);
		healthPackCount++;
	}
}

void LevelManager::spawnGruntEnemyShip()
{
	if (instantObjectSpawnerComponent)
	{
		std::shared_ptr<GameObject> gruntShip =
			instantObjectSpawnerComponent->createGameObject(L"grunt_enemy_ship");
		if (gruntShip)
		{
			gruntShip->position.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			CollisionComponent collisionComponentType = CollisionComponent(*gruntShip);
			std::shared_ptr<CollisionComponent> gruntCollisionComponent =
				gruntShip->getComponentFromClassAndName(collisionComponentType, 
					L"grunt_enemy_collision_component");

			AIComponent aiComponentType;
			std::shared_ptr<AIComponent> gruntAIComponent =
				gruntShip->getComponentFromClassAndName(aiComponentType, 
					L"grunt_enemy_collision_component");
			if (gruntAIComponent)
				gruntAIComponent->initialise(rand() % 5 + 2.0f, rand() % 6 + 3.0f);

			if (gruntCollisionComponent)
			{
				if (!Game::instance.getGameObjectManager().shapeIntersectsWithAGameObject(
					gruntCollisionComponent->getShape()))
				{
					instantObjectSpawnerComponent->spawnGameObject(gruntShip);
					gruntSpaceShipEnemyCount++;
				}
			}
		}
	}
}

void LevelManager::spawnAstroid()
{
	if (instantObjectSpawnerComponent)
	{
		std::shared_ptr<GameObject> asteroid =
			instantObjectSpawnerComponent->createGameObject(L"asteroid");
		if (asteroid)
		{
			AsteroidPhysicsComponent astroidPhysicsComponent;
			Vector2D pos;
			Vector2D velocity;
			pos.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			velocity.setBearing(rand() % 628 / 100.0f, rand() % -80 + 80.0f);
			asteroid->position = pos;

			std::shared_ptr<AsteroidPhysicsComponent> physicsComp =
				asteroid->getComponentFromClassAndName(astroidPhysicsComponent,
					L"asteroid_physics_component");
			if (physicsComp)
			{
				HealthComponent asteroidHealthComponentType;
				std::shared_ptr<HealthComponent> asteroidHealthComponent =
					asteroid->getComponentFromClassAndName(asteroidHealthComponentType,
						L"asteroid_health_component");
				if (asteroidHealthComponent)
				{
					physicsComp->initialise(asteroidHealthComponent, 300.0f, 0.3f, -0.8f, asteroid->scale,
						velocity);
					if (!Game::instance.getGameObjectManager().shapeIntersectsWithAGameObject(
						physicsComp->getShape()))
					{
						instantObjectSpawnerComponent->spawnGameObject(asteroid);
						astroidCount++;
					}
				}
			}
		}
	}
}

void LevelManager::initialise(std::shared_ptr<IntegerRenderComponent> scoreValueRenderComponent, 
	std::shared_ptr<InstantObjectSpawnerComponent> instantObjectSpawnerComponent)
{
	this->scoreValueRenderComponent = scoreValueRenderComponent;
	this->instantObjectSpawnerComponent = instantObjectSpawnerComponent;
}

LevelManager::~LevelManager()
{
	instantObjectSpawnerComponent = nullptr;
}
