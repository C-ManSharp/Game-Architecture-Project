#include "../header/InstantObjectSpawnerComponent.h"
#include "../../header/ObjectFactory.h"
#include "../../header/gamecode.h"
#include "../../header/mydrawengine.h"

InstantObjectSpawnerComponent::InstantObjectSpawnerComponent(
	const std::shared_ptr<ObjectFactory> objectFactory)
{
	this->objectFactory = objectFactory;
}

InstantObjectSpawnerComponent::InstantObjectSpawnerComponent()
{
	this->objectFactory = nullptr;
}

void InstantObjectSpawnerComponent::update(GameObject& gameObject, float frameTime)
{
	if (spawnObjectRequested && objectsToSpawn.size() > 0)
	{
		for (const std::shared_ptr<GameObject>gameObject : objectsToSpawn)
			Game::instance.getGameObjectManager().addGameObject(gameObject);

		objectsToSpawn.clear();
	}

	if (spawnObjectRequested && namesOfObjectsToSpawn.size() > 0)
	{
		for (const std::wstring gameObjectName : namesOfObjectsToSpawn)
		{
			std::shared_ptr<GameObject> objectToSpawn = createGameObject(gameObjectName);
			if (objectToSpawn)
				Game::instance.getGameObjectManager().addGameObject(objectToSpawn);
		}
		namesOfObjectsToSpawn.clear();
	}

	spawnObjectRequested = false;
}

InstantObjectSpawnerComponent::~InstantObjectSpawnerComponent()
{
}
