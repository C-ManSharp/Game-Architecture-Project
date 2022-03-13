#include "../header/DoubleRenderComponent.h"
#include "../../header/GameObject.h"
#include "../../header/mydrawengine.h"

DoubleRenderComponent::DoubleRenderComponent() : doubleToDraw{ 0.0 }, position{ Vector2D(0.0f, 0.0f) },
colour{ 0 }
{
}

void DoubleRenderComponent::initialise(double doubleToDraw, Vector2D position, int colour)
{
	this->doubleToDraw = doubleToDraw;
	this->position = position;
	this->colour = colour;
}

void DoubleRenderComponent::updateDoubleToDraw(double doubleToDraw)
{
	this->doubleToDraw = doubleToDraw;
}

void DoubleRenderComponent::update(GameObject& gameObject, float frameTime)
{
	if (gameObject.state == ObjectState::ACTIVE || gameObject.state == ObjectState::INVINCIBLE)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		if (pDE)
			pDE->WriteDouble(position, doubleToDraw, colour);
	}
}

DoubleRenderComponent::~DoubleRenderComponent()
{
}
