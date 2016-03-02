#include "stdafx.h"
#include "GameStatesHeader.h"

bool MainGameState::Init(RenderWindow* pWindow)
{
	m_pWindow = pWindow;

	m_gui.setWindow(*pWindow);
	m_gui.setFont("..\\assets\\Fonts\\Tibet.ttf");

	auto windowWidth = tgui::bindWidth(m_gui);
	auto windowHeight = tgui::bindHeight(m_gui);


	tgui::Button::Ptr return_button = make_shared<tgui::Button>();
	return_button->setText("Main Menu");
	return_button->setTextSize(20);
	return_button->setSize(windowWidth / 10, windowHeight / 20);
	return_button->setPosition(10, windowHeight - return_button->getSize().y);
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

	
	tgui::Label::Ptr HealthLabel = make_shared<tgui::Label>();
	HealthLabel->setText("100");
	HealthLabel->setTextSize(25);
	HealthLabel->getRenderer()->setTextColor(Color(230, 199, 81));
	HealthLabel->setPosition(10, 10);
	m_gui.add(HealthLabel, "Health_Label");

	tgui::Label::Ptr TimeLabel = make_shared<tgui::Label>();
	TimeLabel->setText("00:00");
	TimeLabel->setTextSize(25);
	TimeLabel->getRenderer()->setTextColor(Color(230, 199, 81));
	TimeLabel->setPosition(windowWidth - TimeLabel->getSize().x, 10);
	m_gui.add(TimeLabel, "Time_Label");

	m_levels.clear();

	//m_levels.emplace(-2, "test.tmx");
	m_levels.emplace(-2, "IkarusHouse.tmx");
	m_levels.emplace(-1, "CassandraHouse.tmx");
	m_levels.emplace(1, "Level1_new.tmx");
	m_levels.emplace(2, "hades.tmx");

	m_gameObjectTypes.push_back("Wall");
	m_gameObjectTypes.push_back("Critter");
	m_gameObjectTypes.push_back("Vase");
	m_gameObjectTypes.push_back("Enemy");
	m_gameObjectTypes.push_back("Goal");
	m_gameObjectTypes.push_back("Hero");

	m_clock.restart();

	return true;
}
void MainGameState::onEvent(ChangeScoreEvent* e) 
{
	tgui::Label::Ptr HealthLabel = m_gui.get<tgui::Label>("Health_Label");
	std::string health = HealthLabel->getText();
	int ihealth = stoi(health);
	ihealth -= e->m_iscore;
	HealthLabel->setText(std::to_string(ihealth));

}

void MainGameState::InizializeGameObjects(std::string Hero)
{
	// Should be read from level -> after level size is chosen
	//loadLevelFromTiled("..\\assets\\Level1.tmx");
	if (m_iLevelCounter == 2) 
	{
		PlayMusicEvent e(this, "Level2Music");
		EventBus::FireEvent(e);
	}
	
	

	loadLevelFromTiled("..\\assets\\" + m_currentLevel);

	m_graph.Init(m_pTilemap->tileHeight, m_pTilemap->width * m_pTilemap->tileWidth, m_pTilemap->height * m_pTilemap->tileHeight);
	createGameObjectsFromTiled(Hero);
}

void MainGameState::Update(float fTime, Event event)
{
	PhysicManager::GetInstance().Update();

	for (auto hero : GameObjectManager::getInstance().FindGameObjectsByType(m_gameObjectTypes))
		hero->Update(fTime);

	setTime(fTime);
	m_gui.handleEvent(event);
}
void MainGameState::setTime(float time) 
{
	sf::Time elapsed1 = m_clock.getElapsedTime();
	int seconds = elapsed1.asSeconds();
	int min = seconds  / 60;
	int sec = seconds % 60;
	tgui::Label::Ptr TimeLabel = m_gui.get<tgui::Label>("Time_Label");
	TimeLabel->setText(std::to_string(min) + ":" + std::to_string(sec));

}
void MainGameState::Render(RenderWindow* pWindow)
{
	m_layer.at(0)->Render();
	m_layer.at(1)->Render();
	m_layer.at(2)->Render();

	for (auto hero : GameObjectManager::getInstance().FindGameObjectsByType(m_gameObjectTypes))
		hero->Render();

	m_layer.at(3)->Render();
	m_layer.at(4)->Render();

	m_gui.draw();

	// Debug Information
	//m_graph.Render(pWindow);
}

void MainGameState::onEvent(HeroChoosingEvent * e)
{
	m_chosenHero = e->m_Hero;
	m_iLevelCounter = 0;

	if (e->m_Hero == "Cassandra") 
		m_currentLevel = m_levels.at(-1);
	else 
		m_currentLevel = m_levels.at(-2);

	if (m_bGameIsRunning) 
		ReInit();
	else 
		InizializeGameObjects(m_chosenHero);

	m_bGameIsRunning = true;
}

void MainGameState::shutdown()
{
	PhysicManager::GetInstance().ReleaseData();
	IGameState::shutdown();
	m_graph.Shutdown();
}

void MainGameState::ReInit()
{
	m_clock.restart();
	m_layer.clear();
	for (auto handler : m_eventHandleRegistrations)
	{
		handler->removeHandler();
	}
	m_eventHandleRegistrations.clear();
	IGameState::shutdown();
	PhysicManager::GetInstance().ReleaseData();
	MainGameObjectFactory::getInstance()->ReInit();

	loadLevelFromTiled("..\\assets\\" + m_currentLevel);
	createGameObjectsFromTiled(m_chosenHero);
}

void MainGameState::loadLevelFromTiled(std::string strPath)
{
	FileInputStream mapStream;
	if (!mapStream.open(strPath))
	{
		err() << "loadMap: could not open file " << std::endl;
		return;
	}

	// convert FileInputStream to char* mapBuffer
	char* mapBuffer = new char[mapStream.getSize() + 1];
	mapStream.read(mapBuffer, mapStream.getSize());
	mapBuffer[mapStream.getSize()] = '\0';

	// load a NLTmxMap
	m_pTilemap = NLLoadTmxMap(mapBuffer);
	delete mapBuffer;

	// load textures for every tileset
	for (auto tileset : m_pTilemap->tilesets)
	{
		Image img;
		img.loadFromFile("..\\assets\\" + tileset->filename);
		img.createMaskFromColor(Color::Color(75, 99, 127));
		img.createMaskFromColor(Color::Color(255, 255, 255));
		Texture* texture = new Texture();
		texture->loadFromImage(img);
		m_tilesetTexture[tileset->name] = texture;
	}

	for (int i = 0; i < m_pTilemap->layers.size(); i++)
	{
		GameObject* pLayer = new GameObject(Vector2f(0.0f, 0.0f));
		LevelLayerComponent* pLayerComp = new LevelLayerComponent(i, m_pTilemap, &m_tilesetTexture, m_pWindow);
		pLayer->addComponent(pLayerComp);
		m_layer.push_back(pLayer);
	}

}

void MainGameState::createGameObjectsFromTiled(std::string Hero)
{
	GameObjectManager::getInstance().RemoveGameObjectsByType(m_gameObjectTypes);

	// Player
	int levelWidth = m_pTilemap->width * m_pTilemap->tileWidth;
	int levelHeight = m_pTilemap->height * m_pTilemap->tileHeight;

	GameObject* pPlayer = nullptr;
	if (Hero == "Cassandra")
	{
		MainGameObjectFactory::getInstance()->RegisterFactory("Hero", new CassandraFactory(32, 64, levelWidth, levelHeight, "..\\assets\\Characters\\Cassandra.png", m_pWindow));
		MainGameObjectFactory::getInstance()->RegisterFactory("Critter", new CritterFactory(48, 48, false, "..\\assets\\Characters\\Wolf_black.png", m_pWindow));
	}
	else if (Hero == "Ikarus")
	{
		MainGameObjectFactory::getInstance()->RegisterFactory("Hero", new IkarusFactory(32, 64, levelWidth, levelHeight, "..\\assets\\Characters\\Ikarus.png", m_pWindow));
		MainGameObjectFactory::getInstance()->RegisterFactory("Critter", new CritterFactory(48, 48, false, "..\\assets\\Characters\\Wolf_grey.png", m_pWindow));
	}

	WallFactory wallFactory = WallFactory(m_pTilemap->tileHeight, &m_graph, m_pWindow);
	MainGameObjectFactory::getInstance()->RegisterFactory("Vase", new NoisyObjectFactory(21, 40, false, "..\\assets\\Objects\\Vase.png", m_pWindow, "Vase"));
	MainGameObjectFactory::getInstance()->RegisterFactory("Enemy", new EnemyFactory(32, 64, 200, 350, false, "..\\assets\\Characters\\Soulless.png", m_pWindow, &m_graph));
	MainGameObjectFactory::getInstance()->RegisterFactory("Goal", new GoalFactory(80, 40, m_pWindow));

	//MainGameObjectFactory::getInstance()->RegisterFactory("LevelSwitch", new GoalFactory(40, 40, m_pWindow));

	for (auto group : m_pTilemap->groups)
	{
		for (auto object : group->objects)
		{
			if (object->name == "Wall")
				GameObjectManager::getInstance().AddGameObject(wallFactory.CreateGameObject(Vector2f(object->x, object->y), object->width, object->height), object->name);
			else
				GameObjectManager::getInstance().AddGameObject(MainGameObjectFactory::getInstance()->CreateGameObject(object->name, Vector2f(object->x, object->y)), object->name);
		}
	}
}

void MainGameState::onEvent(LevelChangeEvent* e)
{
	m_layer.clear();
	cout << "Next Level started" << endl;
	m_iLevelCounter += 1;
	if (m_iLevelCounter >= m_levels.size())
	{
		m_iLevelCounter = 1;
	}
	m_currentLevel = m_levels.at(m_iLevelCounter);


	for (auto handler : m_eventHandleRegistrations)
	{
		handler->removeHandler();
	}
	m_eventHandleRegistrations.clear();

	IGameState::shutdown();
	m_graph.Shutdown();

	PhysicManager::GetInstance().ReleaseData();

	MainGameObjectFactory::getInstance()->ReInit();

	InizializeGameObjects(m_chosenHero);
}
