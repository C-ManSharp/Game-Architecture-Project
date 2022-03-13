#include "../header/ImageRenderComponent.h"
#include "../../header/GameObject.h"
#include "../../header/mydrawengine.h"

ImageRenderComponent::ImageRenderComponent() : image{ 0 }, angle{ 0.0f }, 
transparency{ 0.0f }, drawUsingOwnerAngle{ false }, drawUsingOwnerScale { true }, scale{ 1.0f }
{
}

void ImageRenderComponent::initialise(PictureIndex image, Vector2D position, bool drawAtOwnerPosition, 
	bool drawUsingOwnerAngle, float angle, float transparency, bool drawUsingOwnerScale, float scale)
{
	this->image = image;
	this->angle = angle;
	this->transparency = transparency;
	this->position = position;
	this->drawAtOwnerPosition = drawAtOwnerPosition;
	this->drawUsingOwnerAngle = drawUsingOwnerAngle;
	this->drawUsingOwnerScale = drawUsingOwnerScale;
	this->scale = scale;
}

void ImageRenderComponent::initialise(std::wstring pathToImage, Vector2D position, 
	bool drawAtOwnerPosition, bool drawUsingOwnerAngle, float angle, float transparency,
	bool drawUsingOwnerScale, float scale)
{
	image = MyDrawEngine::GetInstance()->LoadPicture(pathToImage.c_str());
	this->angle = angle;
	this->transparency = transparency;
	this->position = position;
	this->drawAtOwnerPosition = drawAtOwnerPosition;
	this->drawUsingOwnerAngle = drawUsingOwnerAngle;
	this->drawUsingOwnerScale = drawUsingOwnerScale;
	this->scale = scale;
}

void ImageRenderComponent::changeImage(std::wstring filePath)
{
	PictureIndex newImage = MyDrawEngine::GetInstance()->LoadPicture(filePath.c_str());
	if (newImage != 0)
		image = newImage;
}

void ImageRenderComponent::update(GameObject& gameObject, float frameTime)
{
	if (gameObject.state == ObjectState::ACTIVE && image != 0)
	{
		Vector2D positionOfImage = position;
		float angleOfImage = angle;
		float imageScale = scale;
		if (drawAtOwnerPosition)
			positionOfImage = gameObject.position;
		if (drawUsingOwnerAngle)
			angleOfImage = gameObject.angle;
		if (drawUsingOwnerScale)
			imageScale = gameObject.scale;
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		if (pDE)
			pDE->DrawAt(positionOfImage, image, imageScale, angleOfImage, transparency);
	}
	else if (gameObject.state == ObjectState::INVINCIBLE && image != 0)
	{
		Vector2D positionOfImage = position;
		float angleOfImage = angle;
		float imageScale = scale;
		if (drawAtOwnerPosition)
			positionOfImage = gameObject.position;
		if (drawUsingOwnerAngle)
			angleOfImage = gameObject.angle;
		if (drawUsingOwnerScale)
			imageScale = gameObject.scale;
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		if (pDE)
			pDE->DrawAt(positionOfImage, image, imageScale, angleOfImage, 0.5f);
	}
}

ImageRenderComponent::~ImageRenderComponent()
{
}
