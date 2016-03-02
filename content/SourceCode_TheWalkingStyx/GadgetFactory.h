#pragma once
#include "stdafx.h"
#include "Object.hpp"
enum GadgetType 
{
	Phantom, SoundBox
};
class GadgetFactory : public AbstractGameObjectFactory, public EventHandler<DirectionEvent>
{
public:
	GadgetFactory(int iWidth, int iHeight, std::string strSpritePath, RenderWindow* pWindow);
    GadgetFactory(int iWidth, int iHeight, std::string strSpritePath, RenderWindow * pWindow, GadgetType gadgetType);
	GameObject* CreateGameObject(Vector2f position);
	void onEvent(DirectionEvent* e);

private:
	int m_iWidth;
	int m_iHeight;
	GadgetType m_gadgetType;
	std::string m_strSpritePath;
	RenderWindow* m_pWindow;
	MoveEvent m_eTargetDir;
};

