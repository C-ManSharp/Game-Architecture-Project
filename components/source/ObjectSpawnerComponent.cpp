#include "../header/ObjectSpawnerComponent.h"
#include "../../header/ObjectFactory.h"
#include "../../header/ObjectManager.h"

ObjectSpawnerComponent::ObjectSpawnerComponent() : objectFactory{ nullptr }, objectsToSpawn{},
spawnObjectRequested{ false }, namesOfObjectsToSpawn{}
{
}

void ObjectSpawnerComponent::requestThatObjectBeSpawnedByName(std::wstring objectToSpawn)
{
	namesOfObjectsToSpawn.push_back(objectToSpawn);
	spawnObjectRequested = true;
}

std::shared_ptr<GameObject> ObjectSpawnerComponent::createGameObject(std::wstring gameObjectName)
{
	if (objectFactory)
		return objectFactory->createGameObject(gameObjectName);
	else
		return nullptr;
}

void ObjectSpawnerComponent::spawnGameObject(std::shared_ptr<GameObject>gameObject)
{
	objectsToSpawn.push_back(gameObject);
	spawnObjectRequested = true;
}

void ObjectSpawnerComponent::initialise(std::shared_ptr<ObjectFactory> objectFactory)
{
	this->objectFactory = objectFactory;
}


ObjectSpawnerComponent::~ObjectSpawnerComponent()
{
}
