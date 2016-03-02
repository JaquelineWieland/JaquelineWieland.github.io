#pragma once
#include "stdafx.h"
#include "GameObjectsHeader.h"


enum MoveEvent
{
	Move_Up, Move_Down, Move_Left, Move_Right, Move_UpRight, Move_UpLeft, Move_DownRight, Move_DownLeft, Stand_Still
};


class PlayerMovementComponent : public IComponent
{
public:
	PlayerMovementComponent(Keyboard::Key left, Keyboard::Key right, Keyboard::Key up, Keyboard::Key down, Keyboard::Key shoot, int iID);
	void Update(float fTime, GameObject* pOwner) override;
	MoveEvent GetMoveEvent() 
	{
		return m_eMoveEvent;
	}


private:
	float m_fSpeed;
	std::vector<Keyboard::Key> m_keys;
	MoveEvent m_eLastMovementAction;
	MoveEvent m_eMoveEvent;
};
