#include "../header/AnimationComponent.h"
#include "../../header/GameObject.h"
#include "../../header/mydrawengine.h"
#include "../header/ImageRenderComponent.h"

AnimationComponent::AnimationComponent(std::vector<PictureIndex> images,
	std::shared_ptr<ImageRenderComponent> renderComponent) : 
	images{ images }, animationSpeed{0.0f}, currentImage{ 0.0 },
	velocity{ Vector2D(0.0f, 0.0f) }, position{ Vector2D(0.0f, 0.0f) }, size{1.0f},
	time{ 1.0f }, renderComponent{ renderComponent }
{
}

AnimationComponent::AnimationComponent() :
	images{}, animationSpeed{ 0.0f }, currentImage{ 0.0 },
	velocity{ Vector2D(0.0f, 0.0f) }, position{ Vector2D(0.0f, 0.0f) }, size{ 1.0f },
	time{ 1.0f }, renderComponent{ nullptr }
{
}

void AnimationComponent::update(GameObject& gameObject, float frameTime)
{
	if (gameObject.state == ObjectState::ACTIVE && renderComponent)
	{
		renderComponent->initialise(images[(int)currentImage], Vector2D(0.0f, 0.0f), true, true, 
			0.0f, 0.0f, true, 1.0f);
		currentImage += frameTime * animationSpeed;
	}

	if (currentImage >= (float)images.size())
		gameObject.state = ObjectState::CAN_DELETE;

	gameObject.position += velocity * frameTime;
}

void AnimationComponent::initialise(float size, float time, Vector2D vel)
{
	this->size = size;
	animationSpeed = images.size() / time;
	this->velocity = vel;
}

AnimationComponent::~AnimationComponent()
{
}
