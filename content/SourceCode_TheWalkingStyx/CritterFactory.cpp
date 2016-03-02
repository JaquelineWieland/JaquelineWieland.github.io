#include "stdafx.h"
#include "GameObjectsHeader.h"

CritterFactory::CritterFactory(int iWidth, int iHeight, bool bBlocksVision, std::string strSpritePath,  RenderWindow* pWindow)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_bBlocksVision = bBlocksVision;
	m_strSpritePath = strSpritePath;
	m_pWindow = pWindow;
}

GameObject* CritterFactory::CreateGameObject(Vector2f position)
{
	GameObject* pCritter = new GameObject(position);

	RigidBodyComponent* rigidBodyComp = new RigidBodyComponent(1, m_iWidth, m_iHeight / 2, m_bBlocksVision, pCritter, m_pWindow, "Critter");
	pCritter->addComponent(rigidBodyComp);

	NPCSpriteComponent* spriteComp = new NPCSpriteComponent(m_pWindow);
	spriteComp->Init(m_strSpritePath, m_iWidth, m_iHeight, position, 4);
	pCritter->addComponent(spriteComp);

	CritterMovementComponent* behaviourComp = new CritterMovementComponent(pCritter, m_pWindow);
	pCritter->addComponent(behaviourComp);


	return pCritter;
}