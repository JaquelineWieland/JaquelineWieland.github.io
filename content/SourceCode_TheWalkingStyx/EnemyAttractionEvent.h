#pragma once
#include "stdafx.h"
class  EnemyAttractionEvent : public CustomEvent
{
public:
	Vector2f m_Position;
	int m_GameObjectID;
	EnemyAttractionEvent(Object* const sender, Vector2f Position, int id) : CustomEvent(sender)
	{
		m_Position = Position;
		m_GameObjectID = id;
	}

	virtual ~EnemyAttractionEvent() { }
};