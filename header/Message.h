/*
Author: Connor Tall
This idea was taken from game programming patters. https://gameprogrammingpatterns.com/component.html 
This class contains data that is broadcasted to all components.
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include <list>

class Command;

struct Message
{
	std::list<std::shared_ptr<Command>>commands;
};

#endif