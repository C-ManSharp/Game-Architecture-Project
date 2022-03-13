/*
Author: Connor Tall
Data and functions for all game objects
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "vector2D.h"

struct Message;
class Component;
class Command;
class ObjectFactory;
class CollisionComponent;
class ObjectSpawnerComponent;
class AnimationComponent;
class SoundFX;
class EventDispatcher;

enum class ObjectState { INVINCIBLE, ACTIVE, INACTIVE, CAN_DELETE };
enum class ObjectType {UNKOWN, PLAYER_SHIP, ASTROID, EXPLOSION, MACHINE_GUN_BULLET, PLASMA_BULLET, 
	LEVEL_MANAGER, GRUNT_ENEMY_SHIP, HEALTH_PACK};

class GameObject
{
protected:
	ObjectType objectType;
public:
	std::list<std::shared_ptr<Component>> components;
	bool invincibleOnSpawn;
	Vector2D position;
	float angle;
	ObjectState state;
	int damage;
	float scale;
	int healthToHeal;
	std::shared_ptr<EventDispatcher> eventDispatcher;
	std::shared_ptr<GameObject> creator;
	std::shared_ptr<GameObject> killer;
	ObjectType creatorObjectType;
	/**
	A bit of a hack. The velocity variable is here so that the object spawner components can easily
	access it.
	*/
	Vector2D velocity;
	GameObject(std::shared_ptr<EventDispatcher> eventDispatcher, ObjectType objectType);
	GameObject(ObjectType objectType);
	GameObject();
	void addComponent(std::shared_ptr<Component>component);
	void sendMessage(std::shared_ptr<Message>message);
	void updateComponents(float frameTime);
	const ObjectType getObjectType() const;
	std::shared_ptr<Component> getComponentFromName(std::wstring componentName) const;
	~GameObject();

	template<typename T>
	std::shared_ptr<T> getComponentFromClass(T componentClass)
	{
		for (std::shared_ptr<Component>component : components)
		{
			if (typeid(*component) == typeid(componentClass))
				//Reference: https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast
				return std::dynamic_pointer_cast<T>(component);
		}
		return nullptr;
	}

	template<typename T>
	std::vector<std::shared_ptr<T>> getComponentsFromClass(T componentClass)
	{
		std::vector<std::shared_ptr<T>>components;
		for (std::shared_ptr<Component>component : this->components)
		{
			if (typeid(*component) == typeid(componentClass))
				//Reference: https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast
				components.push_back(std::dynamic_pointer_cast<T>(component));
		}
		return components;
	}

	template<typename T>
	std::shared_ptr<T> getComponentFromClassAndName(T componentClass, 
		std::wstring componentName)
	{
		for (std::shared_ptr<Component>component : components)
		{
			if (typeid(*component) == typeid(componentClass) && 
				component->getComponentName() == componentName)
				//Reference: https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast
				return std::dynamic_pointer_cast<T>(component);
		}
		return nullptr;
	}
};

#endif