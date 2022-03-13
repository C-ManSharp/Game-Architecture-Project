/*
Author: Connor Tall
Factory is used to create objects.
*/
#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <memory>
#include <string>
#include <vector>

class GameObject;
class LevelManager;

class ObjectFactory
{
private:
	std::shared_ptr<GameObject> createPlayerShip() const;
	std::shared_ptr<GameObject> createAstroid() const;
	std::shared_ptr<GameObject> createExplosion() const;
	std::shared_ptr<GameObject> createPlasmaBullet() const;
	std::shared_ptr<GameObject> createMachineGunBullet() const;
	std::shared_ptr<GameObject> createGruntEnemyShip() const;
	std::shared_ptr<GameObject> createSmoke() const;
	std::shared_ptr<GameObject> createHealthPack() const;
public:
	ObjectFactory();
	std::shared_ptr<GameObject> createGameObject(std::wstring objectName) const;
	std::shared_ptr<LevelManager> createLevelManager() const;
	~ObjectFactory();
};

#endif