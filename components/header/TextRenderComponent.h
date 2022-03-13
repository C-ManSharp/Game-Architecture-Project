/*
Author: Connor Tall
A component that can draw strings to the screen.
*/

#ifndef TEXTRENDERCOMPONENT_H
#define TEXTRENDERCOMPONENT_H

#include "RenderComponent.h"

class TextRenderComponent : public RenderComponent
{
private:
	std::wstring text;
	Vector2D position;
	int colour;
public:
	TextRenderComponent();
	void update(GameObject& gameObject, float frameTime) override;
	void initialise(std::wstring text, Vector2D position, int colour);
	void updateText(std::wstring text);
	~TextRenderComponent();
};
#endif