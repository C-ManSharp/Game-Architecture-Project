// Author: Connor Tall
#include "../header/RotateRightCommand.h"
#include "../../components/header/PlayerPhysicsComponent.h"

void RotateRightCommand::execute(PlayerPhysicsComponent& physicsComponent)
{
	physicsComponent.rotateRight();
}
