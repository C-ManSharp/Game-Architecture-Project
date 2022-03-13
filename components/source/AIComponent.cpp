#include "../header/AIComponent.h"
#include "../../header/GameObject.h"
#include "../../header/ObjectManager.h"
#include "../../header/gamecode.h"

AIComponent::AIComponent() : aiState{ AIState::PATROL }, assaultCooldown{ 3.0f }, assaultLength{ 2.0f }, 
assaultCooldownValue{ 3.0f }, assaultTime { 2.0f }
{
}

void AIComponent::update(GameObject& gameObject, float frameTime)
{
	if (assaultCooldownValue <= 0.0f && gameObject.state != ObjectState::INVINCIBLE)
		aiState = AIState::ATTACKING;

	if (aiState == AIState::ATTACKING)
		assaultTime -= 1.0f * frameTime;

	if (assaultTime <= 0.0f)
	{
		assaultCooldownValue = assaultCooldown;
		assaultTime = assaultLength;
		aiState = AIState::PATROL;
	}
	assaultCooldownValue -= 1.0f * frameTime;
}

void AIComponent::initialise(float assaultCooldown, float assaultLength)
{
	this->assaultCooldown = assaultCooldown;
	this->assaultLength = assaultLength;
	this->assaultCooldownValue = assaultCooldown;
	this->assaultTime = assaultLength;
}

std::shared_ptr<GameObject> AIComponent::getPointerToPlayerShip() const
{
	return Game::instance.getGameObjectManager().getPlayerShip();
}

AIState AIComponent::getAIState() const
{
	return aiState;
}

AIComponent::~AIComponent()
{
}
