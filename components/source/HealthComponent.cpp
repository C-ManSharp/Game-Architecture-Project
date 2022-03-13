#include "../header/HealthComponent.h"
#include "../header/IntegerRenderComponent.h"
#include "../../header/GameObject.h"
#include "../../header/mydrawengine.h"
#include "../../header/SoundFX.h"

HealthComponent::HealthComponent() : health{ 100 }, maxHealth{ 100 }, healthToAdd{ 0 }, 
healthToRemove{ 0 }, integerRenderComponent{ nullptr }
{
}

void HealthComponent::update(GameObject& gameObject, float frameTime)
{
	if (integerRenderComponent)
		integerRenderComponent->updateIntToDraw(health);
	
	if (health <= 0)
		gameObject.state = ObjectState::CAN_DELETE;
}

void HealthComponent::initialise(std::shared_ptr<IntegerRenderComponent> integerRenderComponent, int health, unsigned int maxHealth)
{
	this->integerRenderComponent = integerRenderComponent;
	this->health = health;
	this->maxHealth = maxHealth;
}

void HealthComponent::addHealth(unsigned int healthToAdd)
{
	health += healthToAdd;
	if (health > (int)maxHealth)
		health = maxHealth;
}

void HealthComponent::removeHealth(unsigned int healthToRemove)
{
	health -= healthToRemove;
}

int HealthComponent::getHealth() const
{
	return health;
}

HealthComponent::~HealthComponent()
{
}
