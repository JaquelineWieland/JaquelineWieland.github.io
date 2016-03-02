#pragma once
#include "stdafx.h"

class CassandraFactory : public AbstractGameObjectFactory
{
public:
	CassandraFactory(int iWidth, int iHeight, int iLevelWidth, int iLevelHeight, std::string strSpritePath, RenderWindow* pwindow);
	GameObject* CreateGameObject(Vector2f position);

private:
	int m_iWidth;
	int m_iHeight;
	int m_iLevelWidth;
	int m_iLevelHeight;
	std::string m_strSpritePath;
	RenderWindow* m_pWindow;
};

