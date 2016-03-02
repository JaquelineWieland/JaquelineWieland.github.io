#pragma once
#include "stdafx.h"

class BackgroundSpriteComponent : public SpriteComponent
{
public:
	BackgroundSpriteComponent(RenderWindow* pWindow) : SpriteComponent(pWindow) { }
	bool Init(std::string strTexturePath, bool verticalScreenScale, bool horizontalScreenScale);
	void Update(float fTime, GameObject* pOwner) { SpriteComponent::Update(fTime, pOwner);}
	void Render(GameObject* pOwner) { SpriteComponent::Render(pOwner); }

private:

	

};