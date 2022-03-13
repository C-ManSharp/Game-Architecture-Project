#include "../header/ObjectManager.h"
#include "../header/GameObject.h"
#include "../components/header/CollisionComponent.h"
#include "../header/Shapes.h"

ObjectManager::ObjectManager() : playerShip{ nullptr }
{
}

bool ObjectManager::shapeIntersectsWithAGameObject(const IShape2D& SHAPE)
{
	bool shapeIntersects = false;
	
	std::list<std::shared_ptr<CollisionComponent>>::iterator it;
	for (it = collisionComponents.begin(); it != collisionComponents.end(); it++)
	{
		if ((*it)->getShape().Intersects(SHAPE))
			shapeIntersects = true;
	}
	return shapeIntersects;
}

std::shared_ptr<GameObject> ObjectManager::intersection(const IShape2D& SHAPE)
{
	std::shared_ptr<GameObject> gameObject;
	
	for (std::shared_ptr<CollisionComponent> collisionComponent : collisionComponents)
	{
		if (SHAPE.Intersects(collisionComponent->getShape()))
			gameObject = std::make_shared<GameObject>(collisionComponent->getGameObject());
	}

	return gameObject;
}

void ObjectManager::addGameObject(std::shared_ptr<GameObject>gameObject)
{
	gameObjects.push_back(gameObject);
	CollisionComponent collisionComponentType(*gameObject);
	std::shared_ptr<CollisionComponent>collisionComponent =
		gameObject->getComponentFromClass(collisionComponentType);

	if (collisionComponent)
		collisionComponents.push_back(collisionComponent);

	if (gameObject->getObjectType() == ObjectType::PLAYER_SHIP)
		playerShip = gameObject;
}

void ObjectManager::checkAllCollisions()
{
	
	std::list<std::shared_ptr<CollisionComponent>>::iterator it1;
	std::list<std::shared_ptr<CollisionComponent>>::iterator it2;
	
	for(it1 = collisionComponents.begin(); it1 != collisionComponents.end(); it1++)
	{
		for (it2 = std::next(it1); it2 != collisionComponents.end(); it2++)
		{
			if ((*it1) && (*it2) &&
				(*it1)->getGameObject().state == ObjectState::ACTIVE &&
				(*it2)->getGameObject().state == ObjectState::ACTIVE &&
				(*it1)->getShape().Intersects((*it2)->getShape())
				)
			{
				(*it1)->notifyCollison((*it2)->getGameObject());
				(*it2)->notifyCollison((*it1)->getGameObject());
			}
		}
	}
}

void ObjectManager::deleteCollisionComponent()
{
	for (std::shared_ptr<CollisionComponent>& collisionComponent : collisionComponents)
	{
		if (collisionComponent->getGameObject().state == ObjectState::CAN_DELETE)
			collisionComponent = nullptr;
	}

	auto it = std::remove(collisionComponents.begin(), collisionComponents.end(), nullptr);
	collisionComponents.erase(it, collisionComponents.end());
}

void ObjectManager::deleteGameObject()
{
	deleteCollisionComponent();
	for (std::shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->state == ObjectState::CAN_DELETE)
			gameObject = nullptr;
	}
	auto it = std::remove(gameObjects.begin(), gameObjects.end(), nullptr);
	gameObjects.erase(it, gameObjects.end());
}

std::shared_ptr<GameObject> ObjectManager::getPlayerShip()
{
	return playerShip;
}

void ObjectManager::updateGameObjects(float frameTime)
{
	for (std::shared_ptr<GameObject>& gameObject : gameObjects)
		gameObject->updateComponents(frameTime);
}

ObjectManager::~ObjectManager()
{
}