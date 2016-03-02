#include "stdafx.h"
#include "ComponentHeader.h"
#include "InputManager.h"

PlayerMovementComponent::PlayerMovementComponent(Keyboard::Key left, Keyboard::Key right, Keyboard::Key up, Keyboard::Key down, Keyboard::Key shoot, int iID)
{
	m_keys.push_back(left);
	m_keys.push_back(right);
	m_keys.push_back(up);
	m_keys.push_back(down);
	m_keys.push_back(shoot);

	m_fSpeed = 150.0f;

	m_iObjectID = iID;
	InputManager::GetInstance()->bind(MoveLeft, m_keys[0], m_iObjectID);
	InputManager::GetInstance()->bind(MoveRight, m_keys[1], m_iObjectID);
	InputManager::GetInstance()->bind(MoveUp, m_keys[2], m_iObjectID);
	InputManager::GetInstance()->bind(MoveDown, m_keys[3], m_iObjectID);
	InputManager::GetInstance()->bind(SpecialMove, m_keys[4], m_iObjectID);
}

void PlayerMovementComponent::Update(float fTime, GameObject* pOwner)
{
	if (InputManager::GetInstance()->isKeyDown(MoveRight, pOwner->m_iID))
	{
		
		if (InputManager::GetInstance()->isKeyDown(MoveUp, pOwner->m_iID))
		{
			m_eMoveEvent = MoveEvent::Move_UpRight;
			pOwner->m_position.y -= fTime * m_fSpeed / 3 * 2;
			pOwner->m_position.x += fTime * m_fSpeed / 3 * 2;
			m_eLastMovementAction = m_eMoveEvent;
			
		}
		else if (InputManager::GetInstance()->isKeyDown(MoveDown, pOwner->m_iID))
		{
			m_eMoveEvent = MoveEvent::Move_DownRight;
			pOwner->m_position.y += fTime * m_fSpeed / 3 * 2;
			pOwner->m_position.x += fTime * m_fSpeed / 3 * 2;
			m_eLastMovementAction = m_eMoveEvent;
			
		}
		else 
		{
			m_eMoveEvent = MoveEvent::Move_Right;
			pOwner->m_position.x += fTime * m_fSpeed;
			m_eLastMovementAction = m_eMoveEvent;
		}
		
	}

	else if (InputManager::GetInstance()->isKeyDown(MoveLeft, pOwner->m_iID))
	{
		
		if (InputManager::GetInstance()->isKeyDown(MoveUp, pOwner->m_iID))
		{
			m_eMoveEvent = MoveEvent::Move_UpLeft;
			pOwner->m_position.y -= fTime * m_fSpeed / 3 * 2;
			pOwner->m_position.x -= fTime * m_fSpeed / 3 * 2;
			m_eLastMovementAction = m_eMoveEvent;
		}

		

		else if (InputManager::GetInstance()->isKeyDown(MoveDown, pOwner->m_iID))
		{
			m_eMoveEvent = MoveEvent::Move_DownLeft;
			pOwner->m_position.y += fTime * m_fSpeed / 3 * 2;
			pOwner->m_position.x -= fTime * m_fSpeed / 3 * 2;
			m_eLastMovementAction = m_eMoveEvent;
		
		}
		else 
		{
			m_eMoveEvent = MoveEvent::Move_Left;
			pOwner->m_position.x -= fTime * m_fSpeed;
			m_eLastMovementAction = m_eMoveEvent;
			
		}
	}

	else if (InputManager::GetInstance()->isKeyDown(MoveUp, pOwner->m_iID))
	{
		m_eMoveEvent = MoveEvent::Move_Up;
		pOwner->m_position.y -= fTime * m_fSpeed;
		m_eLastMovementAction = m_eMoveEvent;
		
	}

	else if (InputManager::GetInstance()->isKeyDown(MoveDown, pOwner->m_iID))
	{
		m_eMoveEvent = MoveEvent::Move_Down;
		pOwner->m_position.y += fTime * m_fSpeed;
		m_eLastMovementAction = m_eMoveEvent;
		
	}
	else 
		m_eMoveEvent = MoveEvent::Stand_Still;

	if (InputManager::GetInstance()->isKeyDown(SpecialMove, pOwner->m_iID))
	{
		//Fire Event to get the Orientaion of the Player
		DirectionEvent e(this, m_eLastMovementAction, pOwner->m_position);
		EventBus::FireEvent(e);
	}

	
}

