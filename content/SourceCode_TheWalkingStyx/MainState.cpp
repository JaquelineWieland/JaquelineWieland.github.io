#include "stdafx.h"
#include "MainState.h"

bool MainGameState::Init(RenderWindow* pWindow)
{
	// Background
	GameObject* pBackground = new GameObject(Vector2f(0.0f, 0.0f));
	BackgroundSpriteComponent* pScBackground = new BackgroundSpriteComponent(pWindow);
	if (!pScBackground->Init("..\\assets\\map.png"))
		return false;
	pBackground->addComponent(pScBackground);
	m_gameObjects.push_back(pBackground);

	// Graph
	m_graph.Init(10, 10, 800, 800);


	m_graph.PlaceObstacle(2, 2, 4, 1);
	GameObject* pWall1 = new GameObject(Vector2f(180, 180));
	RigidBodyComponent* wall1RigidBodyComp = new RigidBodyComponent(0, 40, 280, pWall1, pWindow);
	pWall1->addComponent(wall1RigidBodyComp);
	m_gameObjects.push_back(pWall1);

	m_graph.PlaceObstacle(2, 2, 1, 4);
	GameObject* pWall2 = new GameObject(Vector2f(180, 180));
	RigidBodyComponent* wall2RigidBodyComp = new RigidBodyComponent(0, 280, 40, pWall2, pWindow);
	pWall2->addComponent(wall2RigidBodyComp);
	m_gameObjects.push_back(pWall2);

	// Player 1
	GameObject* pPlayer = new GameObject(Vector2f(50.0f, 400.0f));

	RigidBodyComponent* playerRigidBodyComp = new RigidBodyComponent(1, 32, 64, pPlayer, pWindow);
	pPlayer->addComponent(playerRigidBodyComp);

	PlayerMovementComponent* playerMovementComp = new PlayerMovementComponent(Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down, Keyboard::Space, pPlayer->m_iID);
	pPlayer->addComponent(playerMovementComp);

	HealthComponent* player1Health = new HealthComponent(100);
	pPlayer->addComponent(player1Health);

	PlayerSpriteComponent* pPlayer1Sprite = new PlayerSpriteComponent(pWindow);
	pPlayer1Sprite->Init("..\\assets\\character\\Cassandra.png", IntRect(0, 0, 32, 64), pPlayer->m_position, playerMovementComp);
	//pPlayer1Sprite->Init("..\\assets\\character\\Ikarus.png", IntRect(0, 0, 32, 64), pPlayer->m_position, playerMovementComp);
	pPlayer->addComponent(pPlayer1Sprite);

	pPlayer->addComponent(new StayOnScreenComponent(pWindow));
	m_gameObjects.push_back(pPlayer);

	// Enemy
	GameObject* pEnemy = new GameObject(Vector2f(700.0f, 400.0f));
	
	RigidBodyComponent* enemyRigidBodyComp = new RigidBodyComponent(1, 32, 64, pEnemy, pWindow);
	pEnemy->addComponent(enemyRigidBodyComp);
	
	SpriteComponent* pScEnemy = new SpriteComponent(pWindow);
	if (!pScEnemy->Init("..\\assets\\character\\Soulless.png", IntRect(0, 0, 32, 64), pEnemy->m_position))
		return false;
	pEnemy->addComponent(pScEnemy);
	pEnemy->addComponent(new StayOnScreenComponent(pWindow));
	pEnemy->addComponent(new EnemyMovementComponent(&m_graph, pEnemy, pPlayer, pWindow));
	m_gameObjects.push_back(pEnemy);

	//// Camera
	//GameObject* pCamera = new GameObject(Vector2f(0.0f, 0.0f));
	//pCamera->addComponent(new ScrollSpeedComponent(pWindow));
	//m_gameObjects.push_back(pCamera);

	return true;
}

void MainGameState::Update(float fTime)
{
	PhysicManager::GetInstance().Update();
	for (auto gameObject : m_gameObjects)
	{
		gameObject->Update(fTime);
	}
}

void MainGameState::Render(RenderWindow* pWindow)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Render();

		//Debuggeometry of our Graph
		if (i == 0)
			m_graph.Render(pWindow);
	}
}
