/*
Author: Connor Tall
A spawner that spawns objects based on a time delay.
*/

#ifndef TIMEDOBJECTSPAWNERCOMPONENT
#define TIMEDOBJECTSPAWNERCOMPONENT

#include "ObjectSpawnerComponent.h"

#include <string>
//Could bypass paraent class functions by passing a shared pointer to the object to be spawned via an initialise function.

class ObjectFactory;
class ObjectManager;
class GameObject;

class TimedObjectSpawnerComponent : public ObjectSpawnerComponent
{
private:
	float delay;
	float time;
public:
	TimedObjectSpawnerComponent(const std::shared_ptr<ObjectFactory>objectFactory);
	TimedObjectSpawnerComponent();
	void spawnPlasmaBullet(GameObject& owner, const float MAGNITUED_OF_OFFSET);
	void spawnMachineGunBullet(GameObject& owner, const float MAGNITUED_OF_OFFSET);
	void update(GameObject& gameObject, float frameTime) override;
	void initialise(float delay);
	~TimedObjectSpawnerComponent();
};

#endif