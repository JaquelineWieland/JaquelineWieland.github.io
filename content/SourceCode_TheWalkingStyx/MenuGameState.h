#pragma once
#include "stdafx.h"
class MenuGameState : public IGameState
{
public:
	bool Init(RenderWindow* window);
	void ReInit() override;
	void Update(float time, Event event);
	void Render(RenderWindow* pWindow);
	void shutdown()
	{
		IGameState::shutdown();
	}

protected:
	 bool initGui(RenderWindow* pWindow);
	 void newGameClicked();
	 void exitClicked(RenderWindow * pWindow);
	 void settingsClicked();
	 void creditsClicked();
};
