/*
Author: Connor Tall
A render component that renders numbers of type int.
*/

#ifndef INTEGERRENDERCOMPONENT
#define INTEGERRENDERCOMPONENT

#include "RenderComponent.h"

class IntegerRenderComponent : public RenderComponent
{
private:
	int intToDraw;
	Vector2D position;
	int colour;
public:
	IntegerRenderComponent();
	void update(GameObject& gameObject, float frameTime) override;
	void initialise(int intToDraw, Vector2D position, int colour);
	void updateIntToDraw(int intToDraw);
	~IntegerRenderComponent();
};

#endif