#pragma once
#include "stdafx.h"
#include "Graph.h"

class EnemyFactory : public AbstractGameObjectFactory
{
public:
	EnemyFactory(int iWidth, int iHeight, int iSightRadius, int iHearRadius, bool bBlocksVision, std::string strSpritePath, RenderWindow* pwindow, Graph* pGraph);
	GameObject* CreateGameObject(Vector2f position);

private:
	int m_iWidth;
	int m_iHeight;
	int m_iSightRadius;
	int m_iHearRadius;
	bool m_bBlocksVision;
	std::string m_strSpritePath;
	RenderWindow* m_pWindow;
	Graph* m_pGraph;
};