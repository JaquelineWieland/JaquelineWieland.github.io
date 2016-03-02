#pragma once
#include "stdafx.h"
#include "GameObjectsHeader.h"
#include "EventHeader.h"
#include "InputManager.h"
class GadgetFactory;
class CassandraSpecialMoveComponent : public IComponent
{
public:
	CassandraSpecialMoveComponent(RenderWindow* pWindow);
	void Update(float fTime, GameObject* pOwner);
	void Render(GameObject* pOwner);
	void Shutdown() override;
	void deleteGadget();
	void NotifyEnemies();

private:
	void sendPhantomGagdget(GameObject* pOwner);
	GadgetFactory* m_phantomGadget;
	float m_pGadgetLifeTime;
	GameObject* m_pGadget;
	HandlerRegistration* m_eventHandleRegistrations;
	
};
