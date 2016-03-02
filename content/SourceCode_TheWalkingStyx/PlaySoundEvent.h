#pragma once
#include "stdafx.h"
class PlaySoundEvent : public CustomEvent
{
public:
	std::string m_SoundType;
	PlaySoundEvent(Object* const sender, std::string SoundType) : CustomEvent(sender)
	{
		m_SoundType = SoundType;
	}

	virtual ~PlaySoundEvent() { }
};