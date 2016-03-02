#include "stdafx.h"
#include "GameStatesHeader.h"

using namespace std;
bool MenuGameState::Init(RenderWindow* pWindow)
{
	// Menu
	initGui(pWindow);

	GameObject* pMenu = new GameObject(Vector2f(0.0f, 0.0f));
	BackgroundSpriteComponent* pScMenu = new BackgroundSpriteComponent(pWindow);
	if (!pScMenu->Init("..\\assets\\Backgrounds\\MenuScreen.png", true, true))
		return false;
	pMenu->addComponent(pScMenu);
	pMenu->addComponent(new StayOnScreenComponent(pWindow));
	//m_gameObjects.push_back(pMenu);
	GameObjectManager::getInstance().AddGameObject(pMenu, "Menu");

	PlayMusicEvent e(this, "TitleMusic");
	EventBus::FireEvent(e);

	return true;
}
void MenuGameState::ReInit()
{
	
}
bool MenuGameState::initGui(RenderWindow* pWindow)
{
	// initialize gui
	m_gui.setWindow(*pWindow);
	m_gui.setFont("..\\assets\\Fonts\\Tibet.ttf");

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);

	//auto theme = std::make_shared<tgui::Theme>("..\\assets\\Gui_Themes\\Black.txt");

	tgui::Label::Ptr themeLabel = make_shared<tgui::Label>();
	themeLabel->setText("The Walking Styx");
	themeLabel->setTextSize(64);
	themeLabel->setTextStyle(Text::Bold);
	themeLabel->setAutoSize(true);
	themeLabel->getRenderer()->setTextColor(Color(230, 199, 81));
	themeLabel->setPosition(windowWidth/2  - themeLabel->getSize().x * 2.5, 30);
	m_gui.add(themeLabel, "Title_Label");



	tgui::Button::Ptr newGame_button = make_shared<tgui::Button>();
	newGame_button->setText("New Game");
	newGame_button->setSize(windowWidth / 5, windowHeight / 15);
	newGame_button->setPosition( 10 , windowHeight * 6.5 /10);
	newGame_button->getRenderer()->setBackgroundColor(Color::Transparent);
	newGame_button->getRenderer()->setBorders(0, 0);
	newGame_button->getRenderer()->setTextColor(Color(230, 199, 81));
	newGame_button->getRenderer()->setTextColorHover(Color(92, 22, 16));
	m_gui.add(newGame_button, "New_Game_Btn");

	
	tgui::Button::Ptr setting_button = tgui::Button::copy(newGame_button);
	setting_button->setText("Settings");
	setting_button->setSize(tgui::bindSize(newGame_button));
	setting_button->setPosition(tgui::bindRight(newGame_button) + windowWidth / 100, tgui::bindTop(newGame_button));
	m_gui.add(setting_button, "Settings_Btn");

	tgui::Button::Ptr exit_button = tgui::Button::copy(newGame_button);
	exit_button->setText("Exit");
	exit_button->setSize(tgui::bindSize(newGame_button));
	exit_button->setPosition(windowWidth - exit_button->getSize().x, tgui::bindTop(setting_button));
	m_gui.add(exit_button, "Exit_Btn");

	tgui::Button::Ptr credits_button = tgui::Button::copy(newGame_button);
	credits_button->setText("Credits");
	credits_button->setSize(tgui::bindSize(newGame_button));
	credits_button->setPosition(tgui::bindLeft(exit_button) - credits_button->getSize().x  - windowWidth * 2 / 100, tgui::bindTop(exit_button));
	m_gui.add(credits_button, "Credits_Btn");
	
	newGame_button->connect("pressed", &MenuGameState::newGameClicked, this);
	exit_button->connect("pressed", &MenuGameState::exitClicked, this, pWindow);
	setting_button->connect("pressed", &MenuGameState::settingsClicked, this);
	credits_button->connect("pressed", &MenuGameState::creditsClicked, this);

	return true;
}
void MenuGameState::newGameClicked()
{
	PlaySoundEvent s(this, "ButtonClick");
	EventBus::FireEvent(s);
	GameStateChangeEvent e(this, "HeroChoosingGameState", false);
	EventBus::FireEvent(e);

}
void MenuGameState::exitClicked(RenderWindow* pWindow)
{
	PlaySoundEvent s(this, "ButtonClick");
	EventBus::FireEvent(s);
	cout << "Bye Bye !! :D " << endl;
	pWindow->close();
	//m_stateManager->setState("ShutdownGameState")
}
void MenuGameState::settingsClicked()
{
	PlaySoundEvent s(this, "ButtonClick");
	EventBus::FireEvent(s);
	GameStateChangeEvent e(this, "SettingsGameState", false);
	EventBus::FireEvent(e);
	
}
void MenuGameState::creditsClicked()
{
	PlaySoundEvent s(this, "ButtonClick");
	EventBus::FireEvent(s);
	GameStateChangeEvent e(this, "CreditGameState", true);
	EventBus::FireEvent(e);
}
void MenuGameState::Update(float fTime, Event event)
{
	m_gui.handleEvent(event);
	//for (auto gameObject : m_gameObjects) gameObject->Update(fTime);

	for (auto menuStateObject : GameObjectManager::getInstance().FindGameObjectsByType("Menu"))
		menuStateObject->Update(fTime);
}
void MenuGameState::Render(RenderWindow* pWindow)
{
	//for (auto gameObject : m_gameObjects) gameObject->Render();

	for (auto menuStateObject : GameObjectManager::getInstance().FindGameObjectsByType("Menu"))
		menuStateObject->Render();

	m_gui.draw();
}