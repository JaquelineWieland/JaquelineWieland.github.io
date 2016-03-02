#include "stdafx.h"
#include "GameObjectsHeader.h"

GadgetFactory::GadgetFactory(int iWidth, int iHeight, std::string strSpritePath, RenderWindow* pWindow, GadgetType gadgetType)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_strSpritePath = strSpritePath;
	m_pWindow = pWindow;
	m_gadgetType = gadgetType;
}

GameObject* GadgetFactory::CreateGameObject(Vector2f position)
{

	GameObject* pGagdet = new GameObject(position);
	
	if (m_gadgetType == GadgetType::Phantom)
	{
		ConstantDirectionMovementComponent* movementBehav = new ConstantDirectionMovementComponent(pGagdet, m_pWindow, m_eTargetDir);
		pGagdet->addComponent(movementBehav);
		NPCSpriteComponent* NPCspriteComp = new NPCSpriteComponent(m_pWindow);
		NPCspriteComp->Init(m_strSpritePath, m_iWidth, m_iHeight, position, 5);
		pGagdet->addComponent(NPCspriteComp);
	}
	else if(m_gadgetType == GadgetType::SoundBox)
	{
		SpriteComponent* spriteComp = new SpriteComponent(m_pWindow);
		spriteComp->Init(m_strSpritePath, IntRect(0, 0, m_iWidth, m_iHeight), position);
		pGagdet->addComponent(spriteComp);
	}
	

	return pGagdet;
}

void GadgetFactory::onEvent(DirectionEvent* e) 
{
	m_eTargetDir = e->m_Dircetion;
	std::cout << m_eTargetDir << std::endl;
	//CreateGameObject(e->m_OwnerPos);
}
