#include "stdafx.h"
#include "ComponentHeader.h"

bool SpriteComponent::Init(std::string strTexturePath)
{
	Image tmpImage;
	if (!tmpImage.loadFromFile(strTexturePath))
	{
		err() << "Texture not loaded! Path: " << strTexturePath << std::endl;
		return false;
	}
	m_texture.loadFromImage(tmpImage);
	m_texture.setSmooth(true);

	m_sprite.setTexture(m_texture);
	const float fBackgroundScale = static_cast<float>(m_pWindow->getSize().y) / static_cast<float>(m_texture.getSize().y);
	m_sprite.setScale(fBackgroundScale, fBackgroundScale);
	return true;
}

bool SpriteComponent::Init(std::string strTexturePath, IntRect Rect, sf::Vector2f Position)
{
	m_texture.loadFromFile(strTexturePath);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(Rect);
	m_sprite.setPosition(Position);
	return true;
}

void SpriteComponent::Update(float fTime, GameObject* pOwner)
{
	m_sprite.setPosition(pOwner->m_position);
}

void SpriteComponent::Render(GameObject* pOwner)
{
	m_pWindow->draw(m_sprite);
}

void SpriteComponent::onEvent(ObjectSpriteChangeEvent * e)
{
	if (e->m_newSpriteSet == "BrokenVaseSprite" && this->m_iObjectID == e->m_GameObjectID)
	{
		m_sprite.setTextureRect(IntRect(21, 0, 50, 40));
		if (!m_alreadyPlayed) {
			PlaySoundEvent BreakingVaseSound(this, "VaseBreakingSound");
			EventBus::FireEvent(BreakingVaseSound);
			m_alreadyPlayed = true;
		}

	}
}

