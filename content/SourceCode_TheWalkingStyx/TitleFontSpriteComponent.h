#pragma once
#include "stdafx.h"

class TitelFontSpriteComponent : public FontSpriteComponent
{
public:
	TitelFontSpriteComponent(RenderWindow* pWindow) : FontSpriteComponent(pWindow){}
	bool Init(std::string texturePath, std::string text, int size, Vector2f position, Color color)
	{
		FontSpriteComponent::Init(texturePath, text, size, position, color);
		m_text.setStyle(sf::Text::Bold);
		return true;
	}
	void Update(float fTime, GameObject* pOwner) { FontSpriteComponent::Update( fTime,  pOwner); }
	void Render(GameObject* pOwner) { FontSpriteComponent::Render(pOwner); }
};