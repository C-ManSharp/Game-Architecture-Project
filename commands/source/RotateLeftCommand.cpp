// Author: Connor Tall

#include "../header/RotateLeftCommand.h"
#include "../../components/header/PlayerPhysicsComponent.h"

void RotateLeftCommand::execute(PlayerPhysicsComponent& physicsComponent)
{
	physicsComponent.rotateLeft();
}
