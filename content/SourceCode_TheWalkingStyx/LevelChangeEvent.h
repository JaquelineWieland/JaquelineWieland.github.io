#pragma once
#include "stdafx.h"
class  LevelChangeEvent : public CustomEvent
{
public:
	LevelChangeEvent(Object* const sender) : CustomEvent(sender)
	{ 

		GameStateChangeEvent e(sender, "MainGameState", true);
		EventBus::FireEvent(e);
		std::cout << "Next Level" << std::endl;
	}

	virtual ~LevelChangeEvent() { }
};