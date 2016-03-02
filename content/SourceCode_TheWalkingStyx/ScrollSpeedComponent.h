#pragma once
#include "stdafx.h"
#include "ComponentHeader.h"

class ScrollSpeedComponent : public IRenderComponent
{
public:
	ScrollSpeedComponent(RenderWindow* pWindow, bool directionFlag) : IRenderComponent(pWindow) 
	{ 
		this->m_sideScrolling = directionFlag;
		this->m_view = pWindow->getView();
	}
	~ScrollSpeedComponent() {}
	void Update(float fTime, GameObject* pOwner);

private:
	float m_fScrollSpeed;
	bool m_sideScrolling;
	View m_view;
};

