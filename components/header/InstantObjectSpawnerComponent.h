/*
Author: Connor Tall
This component allows objects to spawn other object instantly.
*/

#ifndef INSTANTOBJECTSPAWNERCOMPONENT
#define INSTANTOBJECTSPAWNERCOMPONENT

#include "ObjectSpawnerComponent.h"

#include <string>

class ObjectFactory;
class ObjectManager;
class GameObject;

class InstantObjectSpawnerComponent : public ObjectSpawnerComponent
{
public:
	InstantObjectSpawnerComponent(const std::shared_ptr<ObjectFactory>objectFactory);
	InstantObjectSpawnerComponent();
	void update(GameObject& gameObject, float frameTime) override;
	~InstantObjectSpawnerComponent();
};

#endif