/*
Author: Connor Tall
Abstract base class for all components that spawn objects. Contains some useful universal functions.
*/

#ifndef OBJECTSPAWNERCOMPONENT
#define OBJECTSPAWNERCOMPONENT

#include "Component.h"

#include <string>

class ObjectFactory;
class ObjectManager;
class GameObject;
class Vector2D;

class ObjectSpawnerComponent : public Component
{
protected:
	std::shared_ptr<ObjectFactory> objectFactory;
	std::list<std::shared_ptr<GameObject>> objectsToSpawn;
	std::list<std::wstring> namesOfObjectsToSpawn;
	bool spawnObjectRequested;
public:
	ObjectSpawnerComponent();
	virtual void update(GameObject& gameObject, float frameTime) = 0;
	void requestThatObjectBeSpawnedByName(std::wstring objectToSpawn);
	void spawnGameObject(std::shared_ptr<GameObject>gameObject);
	void initialise(std::shared_ptr<ObjectFactory>objectFactory);
	std::shared_ptr<GameObject> createGameObject(std::wstring gameObjectName);
	~ObjectSpawnerComponent();
};

#endif