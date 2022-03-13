#include "../header/IntegerRenderComponent.h"
#include "../../header/GameObject.h"
#include "../../header/mydrawengine.h"

IntegerRenderComponent::IntegerRenderComponent() : intToDraw{ 0 }, position{ Vector2D(0.0f, 0.0f) },
colour{ 0 }
{
}

void IntegerRenderComponent::initialise(int intToDraw, Vector2D position, int colour)
{
	this->position = position;
	this->intToDraw = intToDraw;
	this->colour = colour;
}

void IntegerRenderComponent::updateIntToDraw(int intToDraw)
{
	this->intToDraw = intToDraw;
}

void IntegerRenderComponent::update(GameObject& gameObject, float frameTime)
{
	if (gameObject.state == ObjectState::ACTIVE || gameObject.state == ObjectState::INVINCIBLE)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		if (pDE)
			pDE->WriteInt(position, intToDraw, colour);
	}
}

IntegerRenderComponent::~IntegerRenderComponent()
{
}
