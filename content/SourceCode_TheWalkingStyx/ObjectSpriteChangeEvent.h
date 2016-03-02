#pragma once
#include "stdafx.h"
class ObjectSpriteChangeEvent : public CustomEvent
{
public:
	string m_newSpriteSet;
	int m_GameObjectID;
	ObjectSpriteChangeEvent(Object* const sender, string newSpriteSet, int id) : CustomEvent(sender)
	{
		m_newSpriteSet = newSpriteSet;
		m_GameObjectID = id;
	}

	virtual ~ObjectSpriteChangeEvent() { }
};