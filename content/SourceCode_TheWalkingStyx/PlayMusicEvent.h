#pragma once
#include "stdafx.h"
class PlayMusicEvent : public CustomEvent
{
public:
	std::string m_ObjectType;
	PlayMusicEvent(Object* const sender, std::string ObjectType) : CustomEvent(sender)
	{
		m_ObjectType = ObjectType;
	}

	virtual ~PlayMusicEvent() { }
};