#pragma once
#include "stdafx.h"

class IkarusSpecialMoveComponent : public IComponent
{
public:
	IkarusSpecialMoveComponent(RenderWindow* pWindow);
	void Update(float fTime, GameObject* pOwner);
	void Render(GameObject* pOwner);
	void Shutdown();

	void NotifyEnemies();

private:
	void placeSoundGagdget(GameObject* pOwner);

	float m_pGadgetLifeTime;
	GameObject* m_pGadget;
};
