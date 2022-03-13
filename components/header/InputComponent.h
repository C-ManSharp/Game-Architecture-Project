/*
Author: Connor Tall
Handles player input. Sends commands to the physics component. Spawns bullets when the player shoots. 
*/

#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "Component.h"
#include <memory>
#include "../../header/mysoundengine.h"

class PhysicsComponent;
class ObjectSpawnerComponent;
class Command;

enum class Weapon {PLASMA, MACHINE_GUN};

class InputComponent : public Component
{
private:
	std::list<std::shared_ptr<Command>>commands;
	const std::shared_ptr<Command>moveForwardCommand;
	const std::shared_ptr<Command>rotateLeftCommand;
	const std::shared_ptr<Command>rotateRightCommand;
	const std::shared_ptr<Command>moveBackCommand;
	const size_t MAX_SIZE_OF_REVERSE_COMMANDS_ARRAY;
	bool moveFowardButtonIsDown;
	int frameCount;
	const int REVERSE_BOOST_RECHARGE_RATE;
	void spawnJet(GameObject& gameObject) const;
	void shootPlasmaBullet(GameObject& gameObject);
	void shootMachineGunBullet(GameObject& gameObject);
	Weapon weapon;
public:
	InputComponent();
	void update(GameObject& gameObject, float frameTime) override;
	~InputComponent();
};

#endif
