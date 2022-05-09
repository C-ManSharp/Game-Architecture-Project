/*
Author: Connor Tall
This struct contains data that is sent to the level manager when an event is triggered.
*/

#include <memory>

class GameObject;
enum class ObjectType;

enum class EventType { UNKNOWN, PLAYER_DEATH, GRUNT_ENEMY_SHIP_DEATH, ASTEROID_DEATH, 
	HEALTH_PACK_PICKUP};

struct Event
{
	EventType eventType = EventType::UNKNOWN;
	std::shared_ptr<GameObject> source;
	std::shared_ptr<GameObject> killer;
};