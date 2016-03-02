#pragma once
#include "stdafx.h"
#include "GameStatesHeader.h"
#include "EventHeader.h"
#include "InputManager.h"

class IGameState; 
class GameStateManager : public EventHandler<GameStateChangeEvent>
{
public:
	IGameState* m_pCurrentState;
	GameStateManager() : m_pCurrentState(nullptr) {}

	void registerState(std::string strStateName, IGameState* pGameState);
	void setState(std::string strStateName);
	void Init(RenderWindow* window);
	void Update(float fTime, Event event);
	void Render(RenderWindow* pWindow);
	void shutdown();
    void onEvent(GameStateChangeEvent* e) override;

private:
	std::map<std::string, IGameState*> m_gameStates;
	vector<HandlerRegistration*> m_eventHandleRegistrations;
	RenderWindow* m_pWindow;
};