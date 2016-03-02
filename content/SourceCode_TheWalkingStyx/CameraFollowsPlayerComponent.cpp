#include "stdafx.h"
#include "ComponentHeader.h"

CameraFollowsPlayerComponent::CameraFollowsPlayerComponent(Vector2f playerPosition, int iPlayerRectWidth, int iPlayerRectHeight, int iLevelWidth, int iLevelHeight, RenderWindow* pWindow)
{
	m_pWindow = pWindow;
	m_view = pWindow->getView();
	m_InitialView = pWindow->getView();
	m_iPlayerRectWidth = iPlayerRectWidth;
	m_iPlayerRectHeight = iPlayerRectHeight;
	m_playerPosition = playerPosition;
	m_iLevelWidth = iLevelWidth;
	m_iLevelHeight = iLevelHeight;

	correctionOfView();
}

void CameraFollowsPlayerComponent::correctionOfView()
{
	Vector2f correctionOfView = m_playerPosition;
	if (m_iLevelWidth > m_pWindow->getSize().x)
	{
		if (m_playerPosition.x - m_pWindow->getSize().x / 2 < 0)
			correctionOfView.x -= (m_playerPosition.x - m_pWindow->getSize().x / 2);
		if (m_playerPosition.x + m_pWindow->getSize().x / 2 > m_iLevelWidth)
			correctionOfView.x -= ((m_pWindow->getSize().x / 2 + m_playerPosition.x) - m_iLevelWidth);
	}
	else
		correctionOfView.x = m_iLevelWidth / 2;

	if (m_iLevelHeight > m_pWindow->getSize().y)
	{
		if (m_playerPosition.y - m_pWindow->getSize().y / 2 < 0)
			correctionOfView.y -= (m_playerPosition.y - m_pWindow->getSize().y / 2);
		if (m_playerPosition.y + m_pWindow->getSize().y / 2 > m_iLevelHeight)
			correctionOfView.y -= ((m_pWindow->getSize().y / 2 + m_playerPosition.y) - m_iLevelHeight);
	}
	else
		correctionOfView.y = m_iLevelHeight / 2;

	m_view.setCenter(correctionOfView);
	m_pWindow->setView(m_view);
}

void CameraFollowsPlayerComponent::Update(float fTime, GameObject* pOwner)
{
	int iLeftBorder = m_view.getCenter().x - m_iPlayerRectWidth / 2;
	int iRightBorder = m_view.getCenter().x + m_iPlayerRectWidth / 2;
	int iTopBorder = m_view.getCenter().y - m_iPlayerRectHeight / 2;
	int iBottomBorder = m_view.getCenter().y + m_iPlayerRectHeight / 2;

	Vector2f center = m_view.getCenter();
	Vector2f topLeftCorner = Vector2f(m_pWindow->getSize().x / 2 + 32, m_pWindow->getSize().y / 2 + 32);
	Vector2f botRightCorner = Vector2f(m_iLevelWidth - m_pWindow->getSize().x / 2, m_iLevelHeight - m_pWindow->getSize().y / 2);

	// Camera follows left/right
	if (pOwner->m_position.x < iLeftBorder && center.x > topLeftCorner.x)
		m_view.move(pOwner->m_position.x - iLeftBorder, 0.0f);
	else if (pOwner->m_position.x > iRightBorder && center.x < botRightCorner.x)
		m_view.move(pOwner->m_position.x - iRightBorder, 0.0f);

	// Camera follows top/bottom
	if (pOwner->m_position.y < iTopBorder && center.y > topLeftCorner.y)
		m_view.move(0.0f, pOwner->m_position.y - iTopBorder);
	else if (pOwner->m_position.y > iBottomBorder && center.y < botRightCorner.y)
		m_view.move(0.0f, pOwner->m_position.y - iBottomBorder);

	m_pWindow->setView(m_view);
}

 void CameraFollowsPlayerComponent::Shutdown()
{
	m_pWindow->setView(m_InitialView);
}
