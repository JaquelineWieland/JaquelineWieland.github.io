#pragma once
#include "stdafx.h"
class PlayerDamageEvent : public CustomEvent
{
public:
	int m_iDamage;
	int m_playerid;
	PlayerDamageEvent(Object* const sender, int Damage, int playerid) : CustomEvent(sender)
	{
		m_iDamage = Damage;
		m_playerid = playerid;
	}

	virtual ~PlayerDamageEvent() { }
};