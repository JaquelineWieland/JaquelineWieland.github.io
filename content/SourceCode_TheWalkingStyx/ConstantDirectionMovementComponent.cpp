#include "stdafx.h"
#include "ConstantDirectionMovementComponent.h"


ConstantDirectionMovementComponent::ConstantDirectionMovementComponent(GameObject* pOwner, RenderWindow* pWindow, MoveEvent direction)
{

	m_fSpeed = 25.0f;
	m_pOwner = pOwner;
	m_pWindow = pWindow;
	mapDirection(direction);

}
void ConstantDirectionMovementComponent::mapDirection(MoveEvent moveAction) 
{
	switch (moveAction) 
	{
	case Move_Down:
		m_v2fdirection = Vector2f(0, 1);
		break;

	case Move_DownLeft:
		m_v2fdirection = Vector2f(-1, 1);
		break;

	case Move_DownRight:
		m_v2fdirection = Vector2f(1, 1);
		break;

	case Move_Up:
		m_v2fdirection = Vector2f(0, -1);
		break;

	case Move_UpLeft:
		m_v2fdirection = Vector2f(-1, -1);
		break;

	case Move_UpRight:
		m_v2fdirection = Vector2f(1, -1);
		break;

	case Move_Left:
		m_v2fdirection = Vector2f(-1, 0);
		break;

	case Move_Right:
		m_v2fdirection = Vector2f(1, 0);
		break;
	}
}

void ConstantDirectionMovementComponent::Update(float fTime, GameObject* pOwner)
{
	pOwner->m_position.x += m_v2fdirection.x * (m_fSpeed * fTime);
	pOwner->m_position.y += m_v2fdirection.y * (m_fSpeed * fTime);
}

void ConstantDirectionMovementComponent::Render(GameObject* pOwner)
{

}

void ConstantDirectionMovementComponent::Shutdown()
{
	m_pWindow = nullptr;
}