/*
Author: Connor Tall
Stores and manages the objects health. Sets the state to can delete when health is <= 0.
*/

#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Component.h"

class IntegerRenderComponent;
struct Event;
enum class EventType;
enum class ObjectState;

class HealthComponent : public Component
{
private:
	int health;
	unsigned int healthToAdd;
	unsigned int healthToRemove;
	unsigned int maxHealth;
	std::shared_ptr<IntegerRenderComponent> integerRenderComponent;
public:
	HealthComponent();
	void addHealth(unsigned int healthToAdd);
	void update(GameObject& gameObject, float frameTime) override;
	void initialise(std::shared_ptr<IntegerRenderComponent> integerRenderComponent, int health, unsigned int maxHealth);
	void removeHealth(unsigned int healthToRemove);
	int getHealth() const;
	~HealthComponent();
};

#endif