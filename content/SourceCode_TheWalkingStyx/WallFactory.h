#pragma once
#include "stdafx.h"

class WallFactory
{
public:
	WallFactory(int iTileSize, Graph* pGraph, RenderWindow* pWindow);
	GameObject* CreateGameObject(Vector2f position, int iWidth, int iHeight);

private:
	int m_iTileSize;
	Graph* m_pGraph;
	RenderWindow* m_pWindow;
};

