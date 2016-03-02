#include "stdafx.h"
#include "GameObjectsHeader.h"
#include "IkarusSpecialMoveComponent.h"
#include "InputManager.h"

IkarusSpecialMoveComponent::IkarusSpecialMoveComponent(RenderWindow* pWindow)
{
	MainGameObjectFactory::getInstance()->RegisterFactory("IkarusGadget", new GadgetFactory(40, 40, "..\\assets\\Objects\\IkarusGadget.png", pWindow, GadgetType::SoundBox));
	m_pGadgetLifeTime = 0;
	m_pGadget = nullptr;
}

void IkarusSpecialMoveComponent::Update(float fTime, GameObject* pOwner)
{
	if (InputManager::GetInstance()->isKeyPressed(SpecialMove, m_iObjectID))
		placeSoundGagdget(pOwner);	

	if (m_pGadget != nullptr)
	{
		if (m_pGadgetLifeTime > 5)
		{
			delete m_pGadget;
			m_pGadget = nullptr;
			m_pGadgetLifeTime = 0;
		}
		else
		{
			m_pGadget->Update(fTime);
			m_pGadgetLifeTime += fTime;
			NotifyEnemies();
		}		
	}
}

void IkarusSpecialMoveComponent::Render(GameObject* pOwner)
{
	if (m_pGadget != nullptr)
		m_pGadget->Render();
}

void IkarusSpecialMoveComponent::Shutdown()
{
	delete m_pGadget;
	m_pGadget = nullptr;
}

void IkarusSpecialMoveComponent::NotifyEnemies()
{
	EnemyAttractionEvent ikarusAtrraction(this, m_pGadget->m_position, this->GetID());
	EventBus::FireEvent(ikarusAtrraction);
}

void IkarusSpecialMoveComponent::placeSoundGagdget(GameObject* pOwner)
{
	m_pGadgetLifeTime = 0;
	delete m_pGadget;
	m_pGadget = MainGameObjectFactory::getInstance()->CreateGameObject("IkarusGadget", pOwner->m_position);
}
