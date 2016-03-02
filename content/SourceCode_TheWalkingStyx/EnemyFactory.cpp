#include "stdafx.h"
#include "GameObjectsHeader.h"

EnemyFactory::EnemyFactory(int iWidth, int iHeight, int iSightRadius, int iHearRadius, bool bBlocksVision, std::string strSpritePath, RenderWindow* pWindow, Graph* pGraph)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iSightRadius = iSightRadius;
	m_iHearRadius = iHearRadius;
	m_bBlocksVision = bBlocksVision;
	m_strSpritePath = strSpritePath;
	m_pWindow = pWindow;
	m_pGraph = pGraph;
}

GameObject* EnemyFactory::CreateGameObject(Vector2f position)
{
	GameObject* pEnemy = new GameObject(position);

	RigidBodyComponent* rigidBodyComp = new RigidBodyComponent(1, m_iWidth, m_iHeight / 2, m_bBlocksVision, pEnemy, m_pWindow, "Enemy");
	pEnemy->addComponent(rigidBodyComp);

	NPCSpriteComponent* spriteComp = new NPCSpriteComponent(m_pWindow);
	spriteComp->Init(m_strSpritePath, m_iWidth, m_iHeight, position,5);
	pEnemy->addComponent(spriteComp);

	EnemyMovementComponent* behaviourComp = new EnemyMovementComponent(m_iSightRadius, m_iHearRadius, m_pGraph, pEnemy, m_pWindow);
	pEnemy->addComponent(behaviourComp);

	m_eventHandleRegistrations.push_back(EventBus::AddHandler<EnemyAttractionEvent>(behaviourComp));
	m_eventHandleRegistrations.push_back(EventBus::AddHandler<EnemyAttackEvent>(spriteComp));

	return pEnemy;
}