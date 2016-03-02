#include "stdafx.h"
#include "ComponentHeader.h"


void NPCSpriteComponent::Init(std::string strTexturePath, int iWidth, int iHeight, sf::Vector2f Position, int spriteNum)
{

	this->m_position = Position;
	this->m_maxSpritePerMovement = spriteNum;
	m_texture.loadFromFile(strTexturePath);
	m_sprite.setTexture(m_texture);

	m_iWidth = iWidth;
	m_iHeight = iHeight;

	m_moveDown = (IntRect(0, 0, m_iWidth, m_iHeight));
	m_moveLeft = (IntRect(0, m_iHeight, m_iWidth, m_iHeight));
	m_moveUp = (IntRect(0, m_iHeight * 2, m_iWidth, m_iHeight));
	m_moveRight = (IntRect(0, m_iHeight * 3, m_iWidth, m_iHeight));

	m_moveAttackDown = (IntRect(0, m_iHeight * 4, m_iWidth, m_iHeight));
	m_moveAttackLeft = (IntRect(0, m_iHeight * 5, m_iWidth, m_iHeight));
	m_moveAttackRight = (IntRect(0, m_iHeight * 6, m_iWidth, m_iHeight));

	m_standStill = m_moveDown;

	this->m_sprite.setTextureRect(m_standStill);
	this->m_sprite.setPosition(m_position);
	m_lastPosition = m_position;
}


void NPCSpriteComponent::Update(float fTime, GameObject* pOwner)
{
	m_position = pOwner->m_position;
	UpdateSprite(fTime);
	m_sprite.setPosition(Vector2f(pOwner->m_position.x, pOwner->m_position.y - m_iHeight / 2));
	m_lastPosition = pOwner->m_position;
}


void NPCSpriteComponent::UpdateSprite(float fTime)
{
	static int SpriteIdx;
	static float Timecounter;

	if (SpriteIdx >= m_maxSpritePerMovement * m_iWidth)
		SpriteIdx = 1;

	Timecounter += fTime;


	if (abs(m_position.y - m_lastPosition.y) < abs(m_position.x - m_lastPosition.x))
	{
		if (m_position.x < m_lastPosition.x)
		{
			 //Strategy Pattern would be better
			if (m_bIsAttacking)
			{
				m_moveAttackLeft.left = SpriteIdx;
				this->m_sprite.setTextureRect(m_moveAttackLeft);
			}
			else
			{
				m_moveLeft.left = SpriteIdx;
				this->m_sprite.setTextureRect(m_moveLeft);
			}

		}

		if (m_position.x > m_lastPosition.x)
		{
			if (m_bIsAttacking)
			{
				m_moveAttackRight.left = SpriteIdx;
				this->m_sprite.setTextureRect(m_moveAttackRight);
			}
			else
			{
				m_moveRight.left = SpriteIdx;
				this->m_sprite.setTextureRect(m_moveRight);
			}
		}
	}

	else
	{
		if (m_position.y > m_lastPosition.y)
		{
			if (m_bIsAttacking) 
			{
				m_moveAttackDown.left = SpriteIdx;
				this->m_sprite.setTextureRect(m_moveAttackDown);
			}	
			else 
			{
				m_moveDown.left = SpriteIdx;
				this->m_sprite.setTextureRect(m_moveDown);
			}
				
		}
		else if (m_position.y < m_lastPosition.y)
		{
			m_moveUp.left = SpriteIdx;
			this->m_sprite.setTextureRect(m_moveUp);
		}
	}


	if (m_position == m_lastPosition)
	{
		this->m_sprite.setTextureRect(m_standStill);
		//Timecounter = 0;
	}
		
	m_lastPosition = m_position;



	if (Timecounter > 5.0) //Some Parameter to handle spritechanges
	{
		SpriteIdx += m_iWidth;
		Timecounter -= 5.0;
	}
}

void NPCSpriteComponent::Shutdown()
{
	
}


void NPCSpriteComponent::onEvent(EnemyAttackEvent* e)
{
	if (e->m_GameObjectID == this->GetID())
		if (e->m_isAttacking) 
		{
			m_bIsAttacking = true;
			EventBus::FireEvent(PlaySoundEvent(this, "EnemyAttackSound"));
		}
		else
			m_bIsAttacking = false;


}