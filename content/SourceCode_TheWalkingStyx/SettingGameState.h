#pragma once
#include "stdafx.h"
class SettingsGameState : public IGameState
{
public:
	bool Init(RenderWindow* window);
	void Update(float time, Event event);
	void Render(RenderWindow* pWindow);
	void shutdown(){ IGameState::shutdown(); }
};