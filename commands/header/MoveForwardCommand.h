/*
Author: Connor Tall
This class acts as a concrete dependency between the input and player physics component. Moves the player forward.
*/

#ifndef MOVEFORWARDCOMMAND_H
#define MOVEFORWARDCOMMAND_H

#include "Command.h"

class MoveForwardCommand : public Command
{
private:

public:
	MoveForwardCommand() {};
	void execute(PlayerPhysicsComponent& physicsComponent) override;
	~MoveForwardCommand() {};
};

#endif