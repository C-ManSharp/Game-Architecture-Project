/*
Author: Connor Tall
This class acts as a concrete dependency between the input and player physics component. Moves the player back. 
This is the dodge effect.
*/

#ifndef MOVEBACKCOMMAND
#define MOVEBACKCOMMAND

#include "Command.h"

class MoveBackCommand : public Command
{
public:
	MoveBackCommand() {};
	void execute(PlayerPhysicsComponent& physicsComponent) override;
	~MoveBackCommand() {};
};

#endif