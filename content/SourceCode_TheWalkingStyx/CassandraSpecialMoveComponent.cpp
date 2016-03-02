#include "stdafx.h"
#include "CassandraSpecialMoveComponent.h"

CassandraSpecialMoveComponent::CassandraSpecialMoveComponent(RenderWindow* pWindow)
{
	m_phantomGadget = new GadgetFactory(32, 64, "..\\assets\\Objects\\Phantom.png", pWindow, GadgetType::Phantom);
	MainGameObjectFactory::getInstance()->RegisterFactory("CassandraGadget", m_phantomGadget);
	m_pGadgetLifeTime = 0;
	m_pGadget = nullptr;

	//EventBus::AddHandler<DirectionEvent>(NULL, phantomGadget);
	m_eventHandleRegistrations = (EventBus::AddHandler<DirectionEvent>(m_phantomGadget));
}

void CassandraSpecialMoveComponent::Update(float fTime, GameObject* pOwner)
{
	if (InputManager::GetInstance()->isKeyDown(SpecialMove, m_iObjectID))
		sendPhantomGagdget(pOwner);


	if (m_pGadget != nullptr)
	{
		if (m_pGadgetLifeTime > 10)
		{
			deleteGadget();
		}
		else
		{
			m_pGadget->Update(fTime);
			m_pGadgetLifeTime += fTime;
			NotifyEnemies();
		}

	}
}

void CassandraSpecialMoveComponent::Render(GameObject* pOwner)
{
	if (m_pGadget != nullptr)
		m_pGadget->Render();
}

void CassandraSpecialMoveComponent::Shutdown()
{
	
	deleteGadget();
	//m_phantomGadget = nullptr;

	m_eventHandleRegistrations->removeHandler();

	delete m_eventHandleRegistrations;
	m_eventHandleRegistrations = nullptr;
	//Delte gadget out of gameObjectManager
}
void CassandraSpecialMoveComponent::deleteGadget() 
{
	m_pGadgetLifeTime = 0;
	if (m_pGadget) 
	{
		delete m_pGadget;
		m_pGadget = nullptr;
	}
	
}

void CassandraSpecialMoveComponent::NotifyEnemies()
{
	EnemyAttractionEvent PhantomAtrraction(this, m_pGadget->m_position, this->GetID());
	EventBus::FireEvent(PhantomAtrraction);
}

void CassandraSpecialMoveComponent::sendPhantomGagdget(GameObject* pOwner)
{
	//deleteGadget();
	m_pGadget = MainGameObjectFactory::getInstance()->CreateGameObject("CassandraGadget", pOwner->m_position);
}
