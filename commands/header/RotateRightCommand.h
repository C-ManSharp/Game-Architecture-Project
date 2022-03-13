/*
Author: Connor Tall
This class acts as a concrete dependency between the input and player physics component.
Rotates the player to the right.
*/

#ifndef ROTATERIGHTCOMMAND_H
#define ROTATERIGHTCOMMAND_H

#include "Command.h"

class RotateRightCommand : public Command
{
private:

public:
	RotateRightCommand() {};
	void execute(PlayerPhysicsComponent& physicsComponent) override;
	~RotateRightCommand() {};
};

#endif