#pragma once
#include "stdafx.h"


class StayOnScreenComponent : public IRenderComponent
{
public:
	StayOnScreenComponent(RenderWindow* pWindow) : IRenderComponent(pWindow) {}
	~StayOnScreenComponent() {}
	void Update(float fTime, GameObject* pOwner);
};
