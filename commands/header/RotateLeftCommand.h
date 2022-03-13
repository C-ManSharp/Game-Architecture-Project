/*
Author: Connor Tall
This class acts as a concrete dependency between the input and player physics component. 
Rotates the player to the left.
*/
#ifndef ROTATELEFTCOMMAND_H
#define ROTATELEFTCOMMAND_H

#include "Command.h"

class RotateLeftCommand : public Command
{
private:

public:
	RotateLeftCommand() {};
	void execute(PlayerPhysicsComponent& physicsComponent) override;
	~RotateLeftCommand() {};
};

#endif