#pragma once
#include "stdafx.h"
//Event handles Sprite changing and sound if an enemy begins to chase the player | Could also be handled by observers
class  EnemyAttackEvent : public CustomEvent
{
public:
	int m_GameObjectID;
	bool m_isAttacking;
	EnemyAttackEvent(Object* const sender, int GameObjectID, bool isAttacking) : CustomEvent(sender)
	{
		m_GameObjectID = GameObjectID; //To determine which enemy has to change his sprite
		m_isAttacking = isAttacking;   //if the Enemy chases the target or stopped todo so
	}

	virtual ~EnemyAttackEvent() { }
};