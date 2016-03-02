#pragma once
#include "stdafx.h"
class StopMusicEvent : public CustomEvent
{
public:
	StopMusicEvent(Object* const sender) : CustomEvent(sender)
	{
	}

	virtual ~StopMusicEvent() { }
};