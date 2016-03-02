#pragma once
#include "stdafx.h"
class PlayerSpriteChangeEvent : public CustomEvent
{
public:
	string m_sNewSpriteSet;
	PlayerSpriteChangeEvent(Object* const sender, string newSpriteSet) : CustomEvent(sender)
	{
		m_sNewSpriteSet = newSpriteSet;
	}

	virtual ~PlayerSpriteChangeEvent() { }
};