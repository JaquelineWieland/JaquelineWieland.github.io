#include "stdafx.h"
#include "Game.h"

bool Game::Initialization()
{

    //m_window.create(VideoMode(800,800), "The Walking Styx");
   m_window.create(VideoMode::getDesktopMode(), "The Walking Styx", Style::Fullscreen);

	m_window.setFramerateLimit(120);
	m_gui.setWindow(m_window);


	SoundManager::GetInstance()->Init();
	m_eventHandleRegistrations.push_back(EventBus::AddHandler<PlayMusicEvent>(SoundManager::GetInstance()));
	m_eventHandleRegistrations.push_back(EventBus::AddHandler<StopMusicEvent>(SoundManager::GetInstance()));
	m_eventHandleRegistrations.push_back (EventBus::AddHandler<PlaySoundEvent>(SoundManager::GetInstance()));

	m_gameStateManager = GameStateManager();
	m_gameStateManager.Init(&m_window);
	m_eventHandleRegistrations.push_back(EventBus::AddHandler<GameStateChangeEvent>(&m_gameStateManager));
	InputManager::GetInstance()->bind(Shutdown, Keyboard::Escape, 0);

	// Seeding for rand()
	srand(time(new time_t()));

	return true;
}

void Game::Run()
{
	if (Initialization())
	{
		while (m_window.isOpen() && !InputManager::GetInstance()->isKeyPressed(Shutdown, 0))
		{

			static Clock clock;
			Time elapsedTime = clock.restart();
			const float elapsedTimeAsSeconds = elapsedTime.asSeconds();

			Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					m_window.close();
			}
			update(elapsedTimeAsSeconds, event);
			draw();
		}
		shutdown();
	}
}
void Game::update(float elapsedTimeAsSeconds, Event event)
{
	m_gameStateManager.Update(elapsedTimeAsSeconds, event);
}
void Game::draw()
{
	m_window.clear();

	m_gameStateManager.Render(&m_window);

	m_window.display();
}

void Game::shutdown()
{
	
	MainGameObjectFactory::getInstance()->Release();
	m_gameStateManager.shutdown();
	SoundManager::GetInstance()->Release();
	InputManager::GetInstance()->Release();
	GameObjectManager::getInstance().ReleaseAllGameObjects();

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

	EventBus::GetInstance()->Shutdown();	
}