#pragma once
#include "stdafx.h"
#include "EventHeader.h"

class HealthComponent : public IComponent, public EventHandler<PlayerDamageEvent>
{
public:
	HealthComponent(int baseHealth, std::string type) 
	{ 
		this->m_hitPoints = baseHealth; 
		m_sTypeOf = type;
	};
	void Update(float fTime, GameObject* pOwner);
	int  GetHitPoints();
	void TakeDamage(int dmg);
	void onEvent(PlayerDamageEvent* e)override;
	
private:
	int m_hitPoints;
	std::string m_sTypeOf;
};