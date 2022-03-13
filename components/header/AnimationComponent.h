/*
Author: Connor Tall
Controls and stores animations. Tells the render component what to draw.
*/

#ifndef ANIMATIONCOMPONENT
#define ANIMATIONCOMPONENT

#include "Component.h"
#include "../../header/vector2D.h"
#include <vector>

typedef int PictureIndex;
class ImageRenderComponent;

class AnimationComponent : public Component
{
private:
	std::vector<PictureIndex> images;
	float animationSpeed;
	float currentImage;
	Vector2D velocity;
	Vector2D position;
	float size;
	float time;
	std::shared_ptr<ImageRenderComponent>renderComponent;
public:
	AnimationComponent(std::vector<PictureIndex> images,
		std::shared_ptr<ImageRenderComponent> renderComponent);
	AnimationComponent();
	void update(GameObject& gameObject, float frameTime) override;
	void initialise(float size, float time, Vector2D vel);
	~AnimationComponent();
};
#endif
