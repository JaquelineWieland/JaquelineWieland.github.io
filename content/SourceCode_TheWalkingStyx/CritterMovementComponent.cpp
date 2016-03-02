#include "stdafx.h"
#include "ComponentHeader.h"


CritterMovementComponent::CritterMovementComponent(GameObject* pOwner, RenderWindow* pWindow)
{
	m_iFrameCounter = m_iObjectID % 5;
	
	m_iIdleMovementRadius = 50;
	m_fSpeed = 25.0f;

	
	m_pOwner = pOwner;
	m_fIdleMovementTime = 0;
	m_pCenterOfMovement = pOwner->m_position;

	m_pWindow = pWindow;

}

void CritterMovementComponent::Update(float fTime, GameObject* pOwner)
{
	moveIdle(fTime, pOwner);
}

void CritterMovementComponent::Render(GameObject* pOwner)
{
}

void CritterMovementComponent::Shutdown()
{
	m_pWindow = nullptr;
}

void CritterMovementComponent::moveIdle(float fTime, GameObject* pOwner)
{
	if (m_fIdleMovementTime <= 0)
	{
		m_fIdleMovementTime = (rand() % 10) + 1;
		m_fIdleMovementTime /= 10.f;

		float angle = rand() % 360;
		m_idleMovementDirection = Vector2f(cos(angle * PI / 180), sin(angle * PI / 180));
	}
	else
	{
		m_fIdleMovementTime -= fTime;

		Vector2f distanceFromCenter = m_pCenterOfMovement - (pOwner->m_position + m_idleMovementDirection * m_fSpeed * fTime);
		if (length(distanceFromCenter) < m_iIdleMovementRadius)
			pOwner->m_position += m_idleMovementDirection * m_fSpeed * fTime / 2.f;
	}
}

float CritterMovementComponent::length(Vector2f a)
{
	float fDistance = sqrt(a.x * a.x + a.y * a.y);
	return fDistance;
}
