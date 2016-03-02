#pragma once
#include "stdafx.h"
//Send the Direction to somebody who wants to know it
class  ChangeScoreEvent : public CustomEvent
{
public:
	int m_iscore;
	ChangeScoreEvent(Object* const sender, int score) : CustomEvent(sender)
	{
		m_iscore = score;
	}

	virtual ~ChangeScoreEvent() { }
};