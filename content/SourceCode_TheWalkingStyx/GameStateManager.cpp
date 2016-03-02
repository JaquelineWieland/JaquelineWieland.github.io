#include "stdafx.h"
#include  "GameStateManager.h"

void GameStateManager::Init(RenderWindow* window) 
{
	m_pWindow = window;
	MainGameState* mainGameState = new MainGameState();
	registerState("MainGameState", mainGameState);
	registerState("MenuGameState", new MenuGameState());
	registerState("HeroChoosingGameState", new HeroChoosingGameState());
	registerState("CreditGameState", new CreditGameState());
	registerState("SettingsGameState", new SettingsGameState());
	registerState("GameOverGameState", new GameOverGameState());
	registerState("SuccessGameState", new SuccessGameState());
	registerState("ShutdownGameState", new ShutdownGameState()); //ShutdownGameState musst be the last state in our vector. Important for stopping the game loop
    
	for (auto gameState : m_gameStates) gameState.second->Init(window);
	setState("MenuGameState");

    m_eventHandleRegistrations.push_back(EventBus::AddHandler<HeroChoosingEvent>(mainGameState));
	m_eventHandleRegistrations.push_back(EventBus::AddHandler<LevelChangeEvent>(mainGameState));
	m_eventHandleRegistrations.push_back(EventBus::AddHandler<ChangeScoreEvent>(mainGameState));
}
void GameStateManager::registerState(std::string strStateName, IGameState* pGameState)
{
	m_gameStates.emplace(strStateName, pGameState);
}

void GameStateManager::setState(std::string strStateName)
{
	m_pWindow->setView(m_pWindow->getDefaultView());
	if (m_gameStates.size() > 0 && m_gameStates.find(strStateName) != m_gameStates.end())
	{
		//if(m_pCurrentState != nullptr)
		//	m_pCurrentState->shutdown();
		m_pCurrentState = m_gameStates[strStateName];
		//m_pCurrentState->Init(m_pWindow);
	}
	else
	{
		std::cout << "Name of requested State does not exist." << std::endl;
		std::cout << "Continue with current State" << std::endl;
	}
}

void GameStateManager::Update(float fTime, Event event)
{
	if (InputManager::GetInstance()->isKeyPressed(Shutdown, 0))
		setState("ShutdownGameState");

	m_pCurrentState->Update(fTime, event);	
}

void GameStateManager::Render(RenderWindow* pWindow)
{
	m_pCurrentState->Render(pWindow);
}

void GameStateManager::shutdown()
{
	for (auto gameState : m_gameStates) 
	{
		gameState.second->shutdown();
		delete gameState.second;
	}
	m_pCurrentState = nullptr;
	m_gameStates.clear();
	if (!m_eventHandleRegistrations.empty())
	{
		for (auto handler : m_eventHandleRegistrations)
		{
			handler->removeHandler();
			handler->ShutDown();
			delete handler;
		}
		m_eventHandleRegistrations.clear();
	}
}

void GameStateManager::onEvent(GameStateChangeEvent * e)
{
	setState(e->m_newGameState);
	if (e->m_reinit)
	{
		m_pCurrentState->ReInit();
	}	
}
