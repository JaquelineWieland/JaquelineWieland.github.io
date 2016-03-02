#pragma once
#include "stdafx.h"

class NoisyObjectFactory : public AbstractGameObjectFactory
{
public:
	NoisyObjectFactory(int iWidth, int iHeight, bool bBlocksVision, std::string strSpritePath, RenderWindow* pWindow, std::string strType);
	GameObject* CreateGameObject(Vector2f position) override;

private:
	int m_iWidth;
	int m_iHeight;
	bool m_bBlocksVision;
	std::string m_strSpritePath;
	std::string m_strType;
	RenderWindow* m_pWindow;
};

