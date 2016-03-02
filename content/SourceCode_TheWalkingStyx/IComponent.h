#pragma once
#include "stdafx.h"
#include "EventHeader.h"
#include "GameObject.h"

class GameObject;

class IComponent : public Object
{
public:
	IComponent() { }
	IComponent(int iID) : m_iObjectID(iID) { }
	virtual void SetID(int iID) { m_iObjectID = iID; }
	virtual int GetID() { return m_iObjectID; }
	virtual void Update(float fTime, GameObject* pOwner) { }
	virtual void Render(GameObject* pOwner) { }
	virtual void Shutdown() { }

protected:
	int m_iObjectID;
};
