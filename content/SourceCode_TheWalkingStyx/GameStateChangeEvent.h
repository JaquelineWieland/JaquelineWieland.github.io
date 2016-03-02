#pragma once
#include "stdafx.h"
class GameStateChangeEvent : public CustomEvent
{
public:
	string m_newGameState;
	bool m_reinit;
	GameStateChangeEvent(Object* const sender, std::string newGameState, bool reinizialize);

	virtual ~GameStateChangeEvent() { }
};