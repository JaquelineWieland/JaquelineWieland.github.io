#pragma once
#include "stdafx.h"
enum MoveEvent;
//Send the Direction to somebody who wants to know it
class  DirectionEvent : public CustomEvent
{
public:
	MoveEvent m_Dircetion;
	Vector2f m_OwnerPos;
	DirectionEvent(Object* const sender, MoveEvent move, Vector2f OwnerPos) : CustomEvent(sender)
	{
		m_Dircetion = move;
		m_OwnerPos = OwnerPos;
	}

	virtual ~DirectionEvent() { }
};