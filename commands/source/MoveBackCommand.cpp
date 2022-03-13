//Author: Connor Tall

#include "../header/MoveBackCommand.h"
#include "../../components/header/PlayerPhysicsComponent.h"

void MoveBackCommand::execute(PlayerPhysicsComponent& physicsComponent)
{
	physicsComponent.moveBack();
}
