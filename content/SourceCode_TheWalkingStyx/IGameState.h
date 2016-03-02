#pragma once
#include "stdafx.h"
#include "GameObjectsHeader.h"

class IGameState : public Object
{
public:
	IGameState() {}
	virtual bool Init(RenderWindow* window) { return true; }
	virtual void ReInit(){}
	virtual void exit() {}
	virtual void Update(float fTime, Event event) {}
	virtual void Render(RenderWindow* pWindow) {}
	virtual void shutdown() {}
	
protected:
	virtual bool initGui(RenderWindow* pWindow) { return true; }
	Music m_music;
	tgui::Gui m_gui;
};
