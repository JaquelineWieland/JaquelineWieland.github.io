#pragma once
#include "stdafx.h"

class SpriteComponent : public IRenderComponent, public EventHandler<ObjectSpriteChangeEvent>
{
public:
	SpriteComponent(RenderWindow* pWindow) : IRenderComponent(pWindow) { }
	~SpriteComponent() {}
	bool Init(std::string strTexturePath);
	bool Init(std::string strTexturePath, IntRect Rect, sf::Vector2f Position);
    void Update(float fTime, GameObject* pOwner);
	void Render(GameObject* pOwner);
	void Shutdown() 
	{ 
		IRenderComponent::Shutdown(); 
	}
	void onEvent(ObjectSpriteChangeEvent* e) override;

protected:
	Texture m_texture;
	Sprite m_sprite;
	Vector2f m_position;
	bool m_alreadyPlayed = false;
};


