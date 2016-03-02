#pragma once
#include "stdafx.h"
#include "Graph.h"
#include "PhysicManager.h"
#include "EventHeader.h"


class CritterMovementComponent : public IComponent
{
public:
	CritterMovementComponent(GameObject* pOwner, RenderWindow* pWindow);
	void Update(float fTime, GameObject* pOwner);
	void Render(GameObject* pOwner);
	void Shutdown();

private:
	void moveIdle(float fTime, GameObject* pOwner);
	float length(Vector2f a);
	int m_iFrameCounter;
	int m_iIdleMovementRadius;
	float m_fSpeed;
	GameObject* m_pOwner;
	float m_fIdleMovementTime;
	Vector2f m_idleMovementDirection;
	Vector2f m_pCenterOfMovement;
	RenderWindow* m_pWindow;
};