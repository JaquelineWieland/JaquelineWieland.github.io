#include "stdafx.h"
#include "ComponentHeader.h"

bool BackgroundSpriteComponent::Init(std::string strTexturePath, bool verticalScreenScale, bool horizontalScreenScale)
{
	m_texture.loadFromFile(strTexturePath);
	m_sprite.setTexture(m_texture);

	
	if (!m_texture.loadFromFile(strTexturePath))
	{
		err() << "Texture not loaded! Path: " << strTexturePath << std::endl;
		return false;
	}
	
	m_sprite.setTexture(m_texture);
	const float fBackgroundScale = static_cast<float>(m_pWindow->getSize().y) / static_cast<float>(m_texture.getSize().y);
	m_texture.setSmooth(true);
	if (verticalScreenScale && horizontalScreenScale) m_sprite.setScale(fBackgroundScale, fBackgroundScale);
	else if (verticalScreenScale) m_sprite.setScale(m_sprite.getScale().x, fBackgroundScale);
	else if(horizontalScreenScale) m_sprite.setScale(fBackgroundScale, m_sprite.getScale().y);
	return true;

}

