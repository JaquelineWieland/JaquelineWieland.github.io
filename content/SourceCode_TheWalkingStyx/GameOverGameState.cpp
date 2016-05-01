#include "stdafx.h"
#include "GameStatesHeader.h"

bool GameOverGameState::Init(RenderWindow* pWindow)
{
	//GameObject* pBackground = new GameObject(Vector2f(0.0f, 0.0f));
	//BackgroundSpriteComponent* pSBackground = new BackgroundSpriteComponent(pWindow);
	//if (!pSBackground->Init("..\\assets\\Backgrounds\\Death_red.png", true, true))
	//	return false;
	//pBackground->addComponent(pSBackground);
	//pBackground->addComponent(new StayOnScreenComponent(pWindow));
	////m_gameObjects.push_back(pBackground);
	//GameObjectManager::getInstance().AddGameObject(pBackground, "GameOverState");

	m_gui.setWindow(*pWindow);
	m_gui.setFont("..\\assets\\Fonts\\Tibet.ttf");

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);

	auto background = std::make_shared<tgui::Picture>("..\\assets\\Backgrounds\\Death_red.png");
	background->setSize(windowWidth, windowHeight);
	m_gui.add(background, "Background");

	tgui::Label::Ptr themeLabel = make_shared<tgui::Label>();
	themeLabel->setText("Game\nOver");
	themeLabel->setTextSize(64);
	themeLabel->getRenderer()->setTextColor(Color(92, 22, 16));
	themeLabel->setPosition(windowWidth / 2 - themeLabel->getSize().x, windowHeight / 2 - themeLabel->getSize().y);
	m_gui.add(themeLabel, "GameOver_Label");

	tgui::Button::Ptr return_button = make_shared<tgui::Button>();
	return_button->setText("Back to\nMain Menu");
	return_button->setTextSize(30);
	return_button->setSize(windowWidth / 10, windowHeight / 20);
	return_button->setPosition(50, windowHeight / 2);
	return_button->getRenderer()->setBackgroundColor(Color::Transparent);
	return_button->getRenderer()->setBorders(0, 0);
	return_button->getRenderer()->setTextColor(Color(230, 199, 81));
	return_button->getRenderer()->setTextColorHover(Color(92, 22, 16));
	m_gui.add(return_button, "Return_Btn");

	return_button->connect("clicked", [](IGameState* state)
	{
		PlaySoundEvent s(state, "ButtonClick");
		EventBus::FireEvent(s);
		GameStateChangeEvent e(state, "MenuGameState", true);
		EventBus::FireEvent(e);
		std::cout << "Returning to Menu" << std::endl;

	}, this);

	tgui::Button::Ptr restart_button = tgui::Button::copy(return_button);
	restart_button->setText("Restart\nLevel");
	restart_button->setSize(windowWidth / 10, windowHeight / 20);
	restart_button->setPosition(windowWidth - restart_button->getSize().x - 50, windowHeight / 2);
	m_gui.add(restart_button, "restart_Btn");

	restart_button->connect("clicked", [](IGameState* state)
	{
		PlaySoundEvent s(state, "ButtonClick");
		EventBus::FireEvent(s);
		GameStateChangeEvent e(state, "MainGameState", true);
		EventBus::FireEvent(e);
		std::cout << "Restart Level" << std::endl;
	}, this);

	return true;
}

void GameOverGameState::Update(float fTime, Event event)
{
	//for (auto gameObject : m_gameObjects) gameObject->Update(fTime);
	for (auto gameOverStateObject : GameObjectManager::getInstance().FindGameObjectsByType("GameOverState"))
		gameOverStateObject->Update(fTime);
	m_gui.handleEvent(event);
}

void GameOverGameState::Render(RenderWindow* pWindow)
{
	//for (auto gameObject : m_gameObjects) gameObject->Render();
	for (auto gameOverStateObject : GameObjectManager::getInstance().FindGameObjectsByType("GameOverState"))
		gameOverStateObject->Render();
	m_gui.draw();
}