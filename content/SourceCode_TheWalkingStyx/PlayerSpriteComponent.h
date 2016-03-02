#pragma once
#include "stdafx.h"

class PlayerSpriteComponent : public SpriteComponent, public EventHandler<PlayerSpriteChangeEvent>
{
public:
	PlayerSpriteComponent(RenderWindow* pWindow) : SpriteComponent(pWindow) { }
	void Init(std::string strTexturePath, int iHeight, int iWidth, sf::Vector2f Position, PlayerMovementComponent* pPlayerMovement);
	void Update(float fTime, GameObject* pOwner);
	void Render(GameObject* pOwner) { SpriteComponent::Render(pOwner); }
	void UpdateSprite(float fTime);
	void Shutdown();
	void onEvent(PlayerSpriteChangeEvent* e) override;

private:
	PlayerMovementComponent* m_playerMovement;
	int m_iWidth;
	int m_iHeight;

	IntRect m_moveUp;
	IntRect m_moveDown;
	IntRect m_moveLeft;
	IntRect m_moveRight;
	IntRect m_standStill;
	IntRect m_Death;
	MoveEvent m_lastMovementEvent;
	int m_maxSpritePerMovement;
};