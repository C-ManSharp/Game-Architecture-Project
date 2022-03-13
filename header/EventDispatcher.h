/*
Author: Connor Tall
Dispatches an event to the Level Manager
*/

#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

class LevelManager;
struct Event;

class EventDispatcher
{
private:
	LevelManager& levelManager;
public:
	EventDispatcher(LevelManager& levelManager);
	void dispatchEvent(Event e);
	~EventDispatcher();
};

#endif
