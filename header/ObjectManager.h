/*
Author: Connor Tall
Used to add, update and delete objects
*/
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <memory>
#include <list>
#include <string>

#include "../header/Shapes.h"

class GameObject;
class CollisionComponent;

class ObjectManager
{
private:
	std::list<std::shared_ptr<GameObject>> gameObjects;
	std::list<std::shared_ptr<CollisionComponent>> collisionComponents;
	std::shared_ptr<GameObject> playerShip;
	void deleteCollisionComponent();
public:
	ObjectManager();
	void addGameObject(std::shared_ptr<GameObject>gameObject);
	void deleteGameObject();
	void updateGameObjects(float frameTime);
	void checkAllCollisions();
	std::shared_ptr<GameObject> getPlayerShip();
	bool shapeIntersectsWithAGameObject(const IShape2D& SHAPE);
	std::shared_ptr<GameObject> intersection(const IShape2D& SHAPE);
	~ObjectManager();
};

#endif