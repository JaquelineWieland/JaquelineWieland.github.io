#pragma once
#include "stdafx.h"

class NPCSpriteComponent : public SpriteComponent, public EventHandler<EnemyAttackEvent>
{
public:
	NPCSpriteComponent(RenderWindow* pWindow) : SpriteComponent(pWindow) { }
	void Init(std::string strTexturePath, int iWidth, int iHeight, sf::Vector2f Position, int spriteNum);
	void Update(float fTime, GameObject* pOwner);
	void Render(GameObject* pOwner) { SpriteComponent::Render(pOwner); }
	void UpdateSprite(float fTime);
	void Shutdown();
	void onEvent(EnemyAttackEvent* e);

private:
	int m_iWidth;
	int m_iHeight;

	IntRect m_moveUp;
	IntRect m_moveDown;
	IntRect m_moveLeft;
	IntRect m_moveRight;
	IntRect m_standStill;
	IntRect m_moveAttackLeft;
	IntRect m_moveAttackRight;
	IntRect m_moveAttackDown;
	bool m_bIsAttacking;
	std::string m_lastMovementEvent;
	int m_maxSpritePerMovement;
	Vector2f m_lastPosition;
};