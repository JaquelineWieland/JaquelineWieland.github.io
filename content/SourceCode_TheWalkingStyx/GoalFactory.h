#pragma once
#include "stdafx.h"

class GoalFactory : public AbstractGameObjectFactory
{
public:
	GoalFactory(int iWidth, int iHeight, RenderWindow* pWindow);
	GameObject* CreateGameObject(Vector2f position);

private:
	int m_iWidth;
	int m_iHeight;
	RenderWindow* m_pWindow;
};

