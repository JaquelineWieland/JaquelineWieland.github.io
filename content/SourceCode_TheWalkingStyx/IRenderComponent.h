#pragma once
#include "stdafx.h"


class IRenderComponent : public IComponent
{
public:
	IRenderComponent(RenderWindow* pWindow) : m_pWindow(pWindow) {}
	virtual void Shutdown() { m_pWindow = nullptr; }

protected:
	RenderWindow* m_pWindow;
};
