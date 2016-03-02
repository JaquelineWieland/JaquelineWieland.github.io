#include "stdafx.h"
#include "GameObjectsHeader.h"

CassandraFactory::CassandraFactory(int iWidth, int iHeight, int iLevelWidth, int iLevelHeight, std::string strSpritePath, RenderWindow* pwindow)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iLevelWidth = iLevelWidth;
	m_iLevelHeight = iLevelHeight;
	m_strSpritePath = strSpritePath;
	m_pWindow = pwindow;
}

GameObject* CassandraFactory::CreateGameObject(Vector2f position)
{
	GameObject* pPlayer = new GameObject(position);

	RigidBodyComponent* rigidBodyComp = new RigidBodyComponent(1, m_iWidth, m_iHeight / 2, false, pPlayer, m_pWindow, "Player");
	pPlayer->addComponent(rigidBodyComp);

	PlayerMovementComponent* movementComp = new PlayerMovementComponent(Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down, Keyboard::Space, pPlayer->m_iID);
	pPlayer->addComponent(movementComp);

	HealthComponent* healthComp = new HealthComponent(100, "Cassandra");
	pPlayer->addComponent(healthComp);

	CassandraSpecialMoveComponent* specialMove = new CassandraSpecialMoveComponent(m_pWindow);
	pPlayer->addComponent(specialMove);

	PlayerSpriteComponent* spriteComp = new PlayerSpriteComponent(m_pWindow);
	spriteComp->Init(m_strSpritePath, m_iWidth, m_iHeight, pPlayer->m_position, movementComp);
	pPlayer->addComponent(spriteComp);
	pPlayer->addComponent(new StayOnScreenComponent(m_pWindow));

	CameraFollowsPlayerComponent* cameraComp = new CameraFollowsPlayerComponent(position, 100, 100, m_iLevelWidth, m_iLevelHeight, m_pWindow);
	pPlayer->addComponent(cameraComp);

	m_eventHandleRegistrations.push_back(EventBus::AddHandler<PlayerDamageEvent>(healthComp));
	m_eventHandleRegistrations.push_back(EventBus::AddHandler<PlayerSpriteChangeEvent>(spriteComp));

	return pPlayer;
}
