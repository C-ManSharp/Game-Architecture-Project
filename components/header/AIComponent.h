/*
Author: Connor Tall
This class is used to encapsulate the AI states and changes the states based on the assault time and 
cooldown values. 
*/
#ifndef AICOMPONENT
#define AICOMPONENT

#include "Component.h"
class GameObject;

enum class AIState { PATROL, ATTACKING };

class AIComponent : public Component
{
private:
	AIState aiState;
	float assaultCooldown;
	float assaultTime;
	float assaultCooldownValue;
	float assaultLength;
public:
	AIComponent();
	void update(GameObject& gameObject, float frameTime) override;
	void initialise(float assaultCooldown, float assaultTime);
	std::shared_ptr<GameObject> getPointerToPlayerShip() const;
	AIState getAIState() const;
	~AIComponent();
};

#endif
