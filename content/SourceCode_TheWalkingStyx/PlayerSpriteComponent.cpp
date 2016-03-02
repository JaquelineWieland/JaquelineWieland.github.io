#include "stdafx.h"
#include "ComponentHeader.h"

void PlayerSpriteComponent::Init(std::string strTexturePath, int iWidth, int iHeight, sf::Vector2f Position, PlayerMovementComponent* pPlayerMovement)
{
	this->m_playerMovement = pPlayerMovement;
	this->m_position = Position;
	this->m_maxSpritePerMovement = 5;
	m_texture.loadFromFile(strTexturePath);
	m_sprite.setTexture(m_texture);

	m_iWidth = iWidth;
	m_iHeight = iHeight;

	m_moveDown = (IntRect(32, 0, m_iWidth, m_iHeight));
	m_moveLeft = (IntRect(32, 64, m_iWidth, m_iHeight));
	m_moveUp = (IntRect(32, 128, m_iWidth, m_iHeight));
	m_moveRight = (IntRect(32, 192, m_iWidth, m_iHeight));
	m_Death = (IntRect(160, 0, m_iWidth, m_iHeight));
	m_standStill = (IntRect(0, 0, m_iWidth, m_iHeight));

	this->m_sprite.setTextureRect(m_standStill);
	this->m_sprite.setPosition(m_position);
}


void PlayerSpriteComponent::Update(float fTime, GameObject* pOwner)
{
	UpdateSprite(fTime);
	m_sprite.setPosition(Vector2f(pOwner->m_position.x, pOwner->m_position.y - m_iHeight / 2));
}


void PlayerSpriteComponent::UpdateSprite(float fTime)
{
	static int SpriteIdx;
	static float Timecounter;

	if ( SpriteIdx >= m_maxSpritePerMovement * m_iWidth)
	{
		SpriteIdx = 1;
	}

	Timecounter += fTime;

	switch (m_playerMovement->GetMoveEvent())
	{
	case Move_Down:
		m_moveDown.left = SpriteIdx;
		this->m_sprite.setTextureRect(m_moveDown);
		break;

	case Move_DownLeft:
		m_moveDown.left = SpriteIdx;
		this->m_sprite.setTextureRect(m_moveDown);
		break;

	case Move_DownRight:
		m_moveDown.left = SpriteIdx;
		this->m_sprite.setTextureRect(m_moveDown);
		break;

	case Move_Up: 
		m_moveUp.left = SpriteIdx;
		this->m_sprite.setTextureRect(m_moveUp);
		break;

	case Move_UpLeft:
		m_moveUp.left = SpriteIdx;
		this->m_sprite.setTextureRect(m_moveUp);
		break;

	case Move_UpRight:
		m_moveUp.left = SpriteIdx;
		this->m_sprite.setTextureRect(m_moveUp);
		break;

	case Move_Left:
		m_moveLeft.left = SpriteIdx;
		this->m_sprite.setTextureRect(m_moveLeft);
		break;

	case Move_Right:
		m_moveRight.left = SpriteIdx;
		this->m_sprite.setTextureRect(m_moveRight);
		break;

	case Stand_Still:
		Timecounter = 0;
		break;
	default:
		break;
	}


	if (m_playerMovement->GetMoveEvent() != Stand_Still)
	{
		if (Timecounter > 0.25f)
		{
			SpriteIdx += 32;
			Timecounter -= 0.25;
		}
	}
   
}

void PlayerSpriteComponent::Shutdown()
{
	m_playerMovement = nullptr;
}

void PlayerSpriteComponent::onEvent(PlayerSpriteChangeEvent * e)
{
	if (e->m_sNewSpriteSet == "Death") 
	{
		switch (m_playerMovement->GetMoveEvent())
		{
		case Move_Down:
			m_Death.top = 0;
			break;

		case Move_DownLeft:
			m_Death.top = 0;
			break;

		case Move_DownRight:
			m_Death.top = 0;
			break;

		case Move_Up:
			m_Death.top = 128;
			break;

		case Move_UpLeft:
			m_Death.top = 128;
			break;

		case Move_UpRight:
			m_Death.top = 128;
			break;

		case Move_Left:
			m_Death.top = 64;
			break;

		case Move_Right:
			m_Death.top = 192;
			break;

		default:
			m_Death.top = 0;
		}

		this->m_sprite.setTextureRect(m_Death);
	}
}
