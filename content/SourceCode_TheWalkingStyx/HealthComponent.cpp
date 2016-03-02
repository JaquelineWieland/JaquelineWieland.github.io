#include "stdafx.h"
#include "ComponentHeader.h"

void HealthComponent::Update(float fTime, GameObject* pOwner)
{
	if (m_hitPoints <= 0) 
	{
		/*sf::Time t1 = sf::seconds(1.4f);
		sf::sleep(t1);*/
	
	}
	
}
void HealthComponent::TakeDamage(int dmg) 
{
	if (m_hitPoints > 0)
	{
		m_hitPoints -= dmg;
		if (m_hitPoints <= 0) //Player is Dead
		{
			if (m_sTypeOf == "Ikarus")
			{
				PlaySoundEvent playerDeathSound(this, "IkarusDeathSound");
				EventBus::FireEvent(playerDeathSound);
			}
			else if (m_sTypeOf == "Cassandra")
			{
				PlaySoundEvent playerDeathSound(this, "CassandraDeathSound");
				EventBus::FireEvent(playerDeathSound);
			}

			PlayerSpriteChangeEvent setDeathSprite(this, "Death");
			EventBus::FireEvent(setDeathSprite);
		
			GameStateChangeEvent setGameOverScreen(this, "GameOverGameState", false);
			EventBus::FireEvent(setGameOverScreen);
		}
	}
}
void HealthComponent::onEvent(PlayerDamageEvent * e)
{
	if (e->m_playerid == this->GetID()) 
	{
		TakeDamage(e->m_iDamage);
		EventBus::FireEvent(ChangeScoreEvent(this, e->m_iDamage));
	}
		
	
}
int HealthComponent::GetHitPoints() {
	return m_hitPoints;
}
