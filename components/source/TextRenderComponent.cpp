#include "../header/TextRenderComponent.h"
#include "../../header/GameObject.h"
#include "../../header/mydrawengine.h"

TextRenderComponent::TextRenderComponent() : text{ L"" }, position{ Vector2D(0.0f, 0.0f) },
colour{ 0 }
{
}

void TextRenderComponent::initialise(std::wstring text, Vector2D position, int colour)
{
	this->position = position;
	this->text = text;
	this->colour = colour;
}

void TextRenderComponent::updateText(std::wstring text)
{
	this->text = text;
}

void TextRenderComponent::update(GameObject& gameObject, float frameTime)
{
	if ((gameObject.state == ObjectState::ACTIVE || gameObject.state == ObjectState::INVINCIBLE)
		&& !text.empty())
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		if (pDE)
			pDE->WriteText(position, text.c_str(), colour);
	}
}

TextRenderComponent::~TextRenderComponent()
{
}
