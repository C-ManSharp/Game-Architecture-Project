/*
Author: Connor Tall
Abstract base class for all render components.
*/

#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"
#include "../../header/vector2D.h"

typedef int PictureIndex;

class RenderComponent : public Component
{
protected:
	Vector2D position;
	bool drawAtOwnerPosition;
public:
	RenderComponent();
	virtual void update(GameObject& gameObject, float frameTime) = 0;
	~RenderComponent();
};

#endif
