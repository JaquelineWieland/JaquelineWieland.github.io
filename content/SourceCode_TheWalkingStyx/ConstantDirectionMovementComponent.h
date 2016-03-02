#pragma once
#include "stdafx.h"
#include "GameObject.h"

class ConstantDirectionMovementComponent : public IComponent
{
public:
	ConstantDirectionMovementComponent(GameObject* pOwner, RenderWindow* pWindow, MoveEvent direction);
	void mapDirection(MoveEvent moveAction);
	void Update(float fTime, GameObject* pOwner);
	void Render(GameObject* pOwner);
	void Shutdown();

private:
	float m_fSpeed;
	GameObject* m_pOwner;
	RenderWindow* m_pWindow;
	Vector2f m_v2fdirection;

};