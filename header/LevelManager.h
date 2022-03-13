/*
Author: Connor Tall
This class handles events and spawns objects.
*/

#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "GameObject.h"

struct Event;

class InstantObjectSpawnerComponent;
class IntegerRenderComponent;

class LevelManager : public GameObject
{
private:
	int score;
	int gruntSpaceShipEnemyCount;
	int healthPackCount;
	int astroidCount;
	const int MAXIMUM_AMOUNT_OF_GRUNT_SPACESHIPS;
	const int MAXIMUM_AMOUNT_OF_HEALTH_PACKS;
	const int MAXIMUM_AMOUNT_OF_ASTROIDS;
	std::shared_ptr<InstantObjectSpawnerComponent> getInstantObjectSpawnerComponent();
	std::shared_ptr<IntegerRenderComponent> scoreValueRenderComponent;
	std::shared_ptr<InstantObjectSpawnerComponent> instantObjectSpawnerComponent;
	void addScore(ObjectType victimObjectType);
	void spawnHealthPack();
	void spawnGruntEnemyShip();
	void spawnAstroid();
public:
	LevelManager();
	void startLevel();
	void update(float frameTime);
	void endLevel();
	void handleEvent(Event& event);
	void initialise(std::shared_ptr<IntegerRenderComponent> scoreValueRenderComponent, 
		std::shared_ptr<InstantObjectSpawnerComponent> instantObjectSpawnerComponent);
	~LevelManager();
};

#endif
