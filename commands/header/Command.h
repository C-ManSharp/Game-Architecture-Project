/*
Author: Connor Tall
Command pattern was taken from https://gameprogrammingpatterns.com/command.html
This class acts as a concrete dependency between the input and player physics component. 
Is an abstract class to be inherited by all commands. 
*/

#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

class PlayerPhysicsComponent;

class Command
{
public:
	Command() {};
	virtual void execute(PlayerPhysicsComponent& physicsComponent) = 0;
	virtual ~Command() {};
};

#endif