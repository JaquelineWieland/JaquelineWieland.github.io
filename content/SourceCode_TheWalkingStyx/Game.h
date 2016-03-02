#pragma once
#include "stdafx.h"
#include "EventHeader.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "SoundManager.h"

class Game
{
public:
	void Run();

private:
	bool Initialization();
	void update(float elapsedTimeAsSeconds, Event event);
	void draw();
	void shutdown();

	GameStateManager m_gameStateManager;
	RenderWindow m_window;
	tgui::Gui m_gui;
	vector<HandlerRegistration*> m_eventHandleRegistrations;
};