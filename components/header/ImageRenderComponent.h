/*
Author: Connor Tall
This component renders images to the screen.
*/
#ifndef IMAGERENDERCOMPONENT
#define IMAGERENDERCOMPONENT

#include "RenderComponent.h"

typedef int PictureIndex;

class ImageRenderComponent : public RenderComponent
{
private:
	PictureIndex image;
	float angle;
	float transparency;
	float scale;
	bool drawUsingOwnerAngle;
	bool drawUsingOwnerScale;
public:
	ImageRenderComponent();
	void update(GameObject& gameObject, float frameTime) override;
	void initialise(PictureIndex image, Vector2D position, bool drawAtOwnerPosition, 
		bool drawUsingOwnerAngle, float angle, float transparency, bool drawUsingOwnerScale, 
		float scale);
	void initialise(std::wstring pathToImage, Vector2D position, bool drawAtOwnerPosition,
		bool drawUsingOwnerAngle, float angle, float transparency, bool drawUsingOwnerScale, 
		float scale);
	void changeImage(std::wstring filePath);
	~ImageRenderComponent();
};
#endif