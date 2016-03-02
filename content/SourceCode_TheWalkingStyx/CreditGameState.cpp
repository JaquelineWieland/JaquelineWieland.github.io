#include "stdafx.h"
#include "GameStatesHeader.h"

bool CreditGameState::Init(RenderWindow* pWindow)
{
	GameObject* pCamera = new GameObject(Vector2f(0.0f, 0.0f));
	pCamera->addComponent(new ScrollSpeedComponent(pWindow, false));
	//m_gameObjects.push_back(pCamera);
	GameObjectManager::getInstance().AddGameObject(pCamera, "Credits");

	GameObject* pBackground = new GameObject(Vector2f(0.0f, 0.0f));
	BackgroundSpriteComponent* pSBackground = new BackgroundSpriteComponent(pWindow);
	if (!pSBackground->Init("..\\assets\\Backgrounds\\Credits_new.png", false, false))
		return false;
	pBackground->addComponent(pSBackground);
	//m_gameObjects.push_back(pBackground);
	GameObjectManager::getInstance().AddGameObject(pBackground, "Credits");


	m_gui.setWindow(*pWindow);
	m_gui.setFont("..\\assets\\Fonts\\Tibet.ttf");

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);
	

	//auto background = std::make_shared<tgui::Picture>("..\\assets\\Backgrounds\\Credits.png");
	////background->setSize(windowWidth, windowHeight);
	//m_gui.add(background, "Background");


	tgui::Button::Ptr return_button = make_shared<tgui::Button>();
	return_button->setText("Return");
	return_button->setSize(windowWidth / 10, windowHeight / 20);
	return_button->setPosition(0, 0);
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
	},this);

	return true;
}

void CreditGameState::Update(float fTime, Event event)
{
	//for (auto gameObject : m_gameObjects) gameObject->Update(fTime);

	for (auto credit : GameObjectManager::getInstance().FindGameObjectsByType("Credits"))
		credit->Update(fTime);

	m_gui.handleEvent(event);
}

void CreditGameState::Render(RenderWindow* pWindow)
{
	//for (auto gameObject : m_gameObjects) gameObject->Render();

	for (auto credit : GameObjectManager::getInstance().FindGameObjectsByType("Credits"))
		credit->Render();

	m_gui.draw();
}