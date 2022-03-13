// Author: Connor Tall
#include "../header/MoveForwardCommand.h"
#include "../../components/header/PlayerPhysicsComponent.h"

void MoveForwardCommand::execute(PlayerPhysicsComponent& physicsComponent)
{
	physicsComponent.moveForward();
}
