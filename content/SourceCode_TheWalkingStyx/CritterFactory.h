#pragma once
#include "stdafx.h"
#include "Graph.h"

class CritterFactory : public AbstractGameObjectFactory
{
public:
	CritterFactory(int iWidth, int iHeight, bool bBlocksVision, std::string strSpritePath,  RenderWindow* pwindow);
	GameObject* CreateGameObject(Vector2f position);

private:
	int m_iWidth;
	int m_iHeight;
	bool m_bBlocksVision;
	std::string m_strSpritePath;
	RenderWindow* m_pWindow;
};