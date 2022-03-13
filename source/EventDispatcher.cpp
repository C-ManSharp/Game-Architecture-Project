#include "../header/EventDispatcher.h"
#include "../header/Event.h"
#include "../header/LevelManager.h"

EventDispatcher::EventDispatcher(LevelManager& levelManager) : levelManager{ levelManager }
{
}

void EventDispatcher::dispatchEvent(Event e)
{
	levelManager.handleEvent(e);
}

EventDispatcher::~EventDispatcher()
{
}
