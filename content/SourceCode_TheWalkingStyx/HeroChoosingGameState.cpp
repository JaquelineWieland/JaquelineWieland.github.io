#include "stdafx.h"
#include "GameStatesHeader.h"

bool HeroChoosingGameState::Init(RenderWindow* pWindow)
{
	m_gui.setWindow(*pWindow);
	m_gui.setFont("..\\assets\\Fonts\\Tibet.ttf");

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);
	
	auto cassandraPicture = std::make_shared<tgui::Picture>("..\\assets\\Characters\\CassandraFront.png");
	cassandraPicture->setSize(cassandraPicture->getSize().x * 3, cassandraPicture->getSize().y * 3);
	cassandraPicture->setPosition(windowWidth / 4 - cassandraPicture->getSize().x / 2, windowHeight / 4);

	auto ikarusPicture = std::make_shared<tgui::Picture>("..\\assets\\Characters\\IkarusFront.png");
	ikarusPicture->setSize(tgui::bindSize(cassandraPicture));
	ikarusPicture->setPosition(tgui::bindPosition(cassandraPicture));

	auto background1 = std::make_shared<tgui::Picture>("..\\assets\\Backgrounds\\old2.jpg");
	auto background2 = std::make_shared<tgui::Picture>("..\\assets\\Backgrounds\\stone2.jpg");
	m_gui.add(background2);
	background2->setSize(tgui::bindSize(m_gui));

	tgui::Button::Ptr cassandra_button = std::make_shared<tgui::Button>();
	cassandra_button->setText("");
	cassandra_button->setSize(windowWidth / 2, windowHeight);
	cassandra_button->setPosition(0, 0);
	cassandra_button->getRenderer()->setBackgroundColor(Color::Transparent);
	cassandra_button->getRenderer()->setBackgroundColorHover(Color(255, 255, 255, 30));
	m_gui.add(cassandra_button);

	tgui::Label::Ptr cassandraTitle = make_shared<tgui::Label>();
	cassandraTitle->setText("Cassandra - The Seer");
	cassandraTitle->setFont("..\\assets\\Fonts\\Abibas.ttf");
	cassandraTitle->setTextSize(48);
	cassandraTitle->setAutoSize(true);
	cassandraTitle->setTextColor(Color::Color(230, 199, 81));

	tgui::TextBox::Ptr cassandraText = std::make_shared<tgui::TextBox>();
	cassandraText->setText("Cassandra \nThe daughter of King Priam and Queen Hecuba\nApollo has given her the power of Prophecy.\nBut when she refused his love for her, he also cursed her so nobody ever will belive her Prophecies.\n\nAbilities: \nIncreased Sight Field");
	cassandraText->setReadOnly(true);
	cassandraText->setSize(windowWidth / 2  - 220, 300);
	cassandraText->getRenderer()->setBackgroundTexture(tgui::Texture("..\\assets\\Backgrounds\\txtBackground2.png"));
	cassandraText->getRenderer()->setCaretWidth(0);
	cassandraText->getRenderer()->setCaretColor(Color::Transparent);
	cassandraText->getRenderer()->setBorders(0, 0);
	cassandraText->getRenderer()->setPadding(30, 25);
	cassandraText->getRenderer()->setTextColor(Color::Color(43, 46, 56));
	cassandraText->setTextSize(20);


	auto panel1 = std::make_shared<tgui::Panel>();
	panel1->setFont("..\\assets\\Fonts\\Abibas.ttf");
	panel1->setSize(tgui::bindSize(cassandra_button));
	panel1->setPosition(tgui::bindPosition(cassandra_button));
	panel1->add(background1);
	panel1->add(cassandraPicture);
	panel1->add(cassandraTitle);
	panel1->add(cassandraText);
	m_gui.add(panel1);

	cassandraTitle->setPosition(panel1->getSize().x / 2 - cassandraTitle->getSize().x / 2 , windowHeight * 1 / 10);
	background1->setSize(tgui::bindSize(panel1));
	cassandraText->setPosition(panel1->getSize().x / 2 - cassandraText->getSize().x / 2, windowHeight * 6 / 10);

	tgui::Button::Ptr ikarus_button = tgui::Button::copy(cassandra_button);
	ikarus_button->setPosition(windowWidth/2, 0);
	m_gui.add(ikarus_button);

	tgui::Label::Ptr ikarusTitle = tgui::Label::copy(cassandraTitle);
	ikarusTitle->setText("Ikarus - The Inventor");

	tgui::TextBox::Ptr ikarusText = tgui::TextBox::copy(cassandraText);
	ikarusText->setText("Ikarus \nAs the son of the master craftsman Daedalus, Ikarus always was interessted in special Inventions.\nFor Example the unique Wings his Father made for him.\n\nAbilities: \nFaster Movement Speed \nInventions to distract Enemys");
	ikarusTitle->setPosition(tgui::bindPosition(cassandraTitle));
	ikarusText->setPosition(tgui::bindPosition(cassandraText));

	auto panel2 = std::make_shared<tgui::Panel>();
	panel2->setFont("..\\assets\\Fonts\\Abibas.ttf");
	panel2->setSize(tgui::bindSize(ikarus_button));
	panel2->setPosition(tgui::bindPosition(ikarus_button));
	//panel2->add(background2);
	panel2->add(ikarusPicture);
	panel2->add(ikarusTitle);
	//panel2->add(BorderPicture);
	panel2->add(ikarusText);
	panel2->setBackgroundColor(Color::Transparent);
	m_gui.add(panel2);


	ikarus_button->moveToFront();
	cassandra_button->moveToFront();


	tgui::Button::Ptr return_button = make_shared<tgui::Button>();
	return_button->setText("Return");
	return_button->setSize(windowWidth / 10, windowHeight / 20);
	return_button->setPosition(10, windowHeight - return_button->getSize().y);
	return_button->getRenderer()->setBackgroundColor(Color::Transparent);
	return_button->getRenderer()->setBorders(0, 0);
	return_button->getRenderer()->setTextColor(Color(0, 0, 0));
	return_button->getRenderer()->setTextColorHover(Color(230, 199, 81));
	m_gui.add(return_button, "Return_Btn");

	return_button->connect("clicked", [](IGameState* state)
	{
		PlaySoundEvent s(state, "ButtonClick");
		EventBus::FireEvent(s);
		GameStateChangeEvent e(state, "MenuGameState", true);
		EventBus::FireEvent(e);
		std::cout << "Returning to Menu" << std::endl;
	}, this);


	cassandra_button->connect("clicked", [](IGameState* state)
	{
		PlaySoundEvent s(state, "ButtonClick");
		EventBus::FireEvent(s);
		GameStateChangeEvent e(state, "MainGameState", false);
		EventBus::FireEvent(e);
		HeroChoosingEvent b(state, "Cassandra");
		EventBus::FireEvent(b);
		std::cout << "Choosen Cassandra" << std::endl;
	

	}, this);

	ikarus_button->connect("clicked", [](IGameState* state)
	{
		PlaySoundEvent s(state, "ButtonClick");
		EventBus::FireEvent(s);
		GameStateChangeEvent e(state, "MainGameState", false);
		EventBus::FireEvent(e);
		HeroChoosingEvent b(state, "Ikarus");
		EventBus::FireEvent(b);
		std::cout << "Choosen Ikarus" << std::endl;
		
	}, this);

	return true;
}

void HeroChoosingGameState::Update(float fTime, Event event)
{
	//for (auto gameObject : m_gameObjects) gameObject->Update(fTime);
	for (auto heroStateObject : GameObjectManager::getInstance().FindGameObjectsByType("HeroState"))
		heroStateObject->Render();
	m_gui.handleEvent(event);
}

void HeroChoosingGameState::Render(RenderWindow* pWindow)
{
	//for (auto gameObject : m_gameObjects) gameObject->Render();
	for (auto heroStateObject : GameObjectManager::getInstance().FindGameObjectsByType("HeroState"))
		heroStateObject->Render();
	m_gui.draw();
}