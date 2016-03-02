#include "stdafx.h"
#include "GameStatesHeader.h"

bool SettingsGameState::Init(RenderWindow* pWindow)
{
	m_gui.setWindow(*pWindow);
	m_gui.setFont("..\\assets\\Fonts\\Tibet.ttf");

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);
	
	tgui::Label::Ptr themeLabel = make_shared<tgui::Label>();
	themeLabel->setText("Settings");
	themeLabel->setTextStyle(Text::Bold);
	themeLabel->setTextSize(56);
	themeLabel->setTextColor(Color(230, 199, 81));
	themeLabel->setAutoSize(true);
	
	themeLabel->setPosition(windowWidth / 2 - themeLabel->getSize().x, windowHeight * 0.5 / 10);
	m_gui.add(themeLabel, "Title_Label");


	tgui::Label::Ptr ControlsLabel = tgui::Label::copy(themeLabel);
	ControlsLabel->setText("Constrols:\n Arrowkeys");
	ControlsLabel->setTextSize(42);
	ControlsLabel->setTextColor(Color(255, 255, 255));
	ControlsLabel->setPosition(50, themeLabel->getPosition().y + 200);
	m_gui.add(ControlsLabel, "Contr_Label");

	tgui::Label::Ptr specialLabel = tgui::Label::copy(ControlsLabel);
	specialLabel->setText("Special Move:\n Space Key");
	specialLabel->setPosition(50, ControlsLabel->getPosition().y  + 300);
	m_gui.add(specialLabel, "special_Label");




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

	}, this);


	return true;
}

void SettingsGameState::Update(float fTime, Event event)
{
	m_gui.handleEvent(event);
	//for (auto gameObject : m_gameObjects) gameObject->Update(fTime);
	for (auto settingStateObject : GameObjectManager::getInstance().FindGameObjectsByType("Settings"))
		settingStateObject->Render();
}

void SettingsGameState::Render(RenderWindow* pWindow)
{
	//for (auto gameObject : m_gameObjects) gameObject->Render();
	for (auto settingStateObject : GameObjectManager::getInstance().FindGameObjectsByType("Settings"))
		settingStateObject->Render();

	m_gui.draw();
}