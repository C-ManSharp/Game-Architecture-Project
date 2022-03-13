/*
Author: Connor Tall
A render component that renders numbers of type double.
*/

#ifndef DOUBLERENDERCOMPONENT_H
#define DOUBLERENDERCOMPONENT_H

#include "RenderComponent.h"

/*
TODO: TEST THIS CODE BEFORE HAND IN.
*/

class DoubleRenderComponent : public RenderComponent
{
private:
	double doubleToDraw;
	Vector2D position;
	int colour;
public:
	DoubleRenderComponent();
	void update(GameObject& gameObject, float frameTime) override;
	void initialise(double doubleToDraw, Vector2D position, int colour);
	void updateDoubleToDraw(double doubleToDraw);
	~DoubleRenderComponent();
};

#endif