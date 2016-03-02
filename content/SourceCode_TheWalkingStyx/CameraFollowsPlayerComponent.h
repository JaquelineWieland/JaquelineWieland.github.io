#pragma once
#include "stdafx.h"

class CameraFollowsPlayerComponent : public IComponent
{
public:
	CameraFollowsPlayerComponent(Vector2f playerPosition, int iPlayerRectWidth, int iPlayerRectHeight, int iLevelWidth, int iLevelHeight, RenderWindow* pWindow);
	void Update(float fTime, GameObject* pOwner);
	void Shutdown() override;
private:
	void correctionOfView();

	View m_view;
	View m_InitialView;
	RenderWindow* m_pWindow;
	Vector2f m_playerPosition;
	int m_iPlayerRectWidth;
	int m_iPlayerRectHeight;
	int m_iLevelWidth;
	int m_iLevelHeight;
};
