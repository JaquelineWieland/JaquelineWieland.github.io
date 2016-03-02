#pragma once
#include "stdafx.h"

class FontSpriteComponent : public SpriteComponent
{

protected:
	Font m_font;
	Text m_text;
public:
	FontSpriteComponent(RenderWindow* pWindow) : SpriteComponent(pWindow){ }
	bool Init(std::string texturePath, std::string text, int size, Vector2f position, Color color)
	{
		m_font.loadFromFile(texturePath);
		m_text.setFont(m_font);
		m_text.setCharacterSize(size);
		m_text.setString(text);
		m_text.setColor(color);
		m_text.setPosition(position);
		return true;
	}
	void Update(float fTime, GameObject* pOwner) {};
	void Render(GameObject* pOwner) 
	{ 
		m_pWindow->draw(m_text);
	}

};