#include "stdafx.h"
#include "GameObjectsHeader.h"

NoisyObjectFactory::NoisyObjectFactory(int iWidth, int iHeight, bool bBlocksVision, std::string strSpritePath, RenderWindow* pWindow, std::string strType)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_bBlocksVision = bBlocksVision;
	m_strSpritePath = strSpritePath;
	m_strType = strType;
	m_pWindow = pWindow;

}

GameObject* NoisyObjectFactory::CreateGameObject(Vector2f position)
{
	GameObject* pNoisyObject = new GameObject(position);

	RigidBodyComponent* rigidBodyComp = new RigidBodyComponent(0, m_iWidth, m_iHeight, m_bBlocksVision, pNoisyObject, m_pWindow, "Vase");
	pNoisyObject->addComponent(rigidBodyComp);

	SpriteComponent* spriteComp = new SpriteComponent(m_pWindow);
	spriteComp->Init(m_strSpritePath, IntRect(0, 0, m_iWidth, m_iHeight), pNoisyObject->m_position);
	pNoisyObject->addComponent(spriteComp);

	m_eventHandleRegistrations.push_back(EventBus::AddHandler<ObjectSpriteChangeEvent>(spriteComp));

	return pNoisyObject;
}
