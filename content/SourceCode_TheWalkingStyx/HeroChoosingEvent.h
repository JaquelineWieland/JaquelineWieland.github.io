#pragma once
#include "stdafx.h"
class HeroChoosingEvent : public CustomEvent
{
public:
	std::string m_Hero;
	HeroChoosingEvent(Object* const sender, std::string hero) : CustomEvent(sender)
	{
		m_Hero = hero;
	}

	virtual ~HeroChoosingEvent() { }
};