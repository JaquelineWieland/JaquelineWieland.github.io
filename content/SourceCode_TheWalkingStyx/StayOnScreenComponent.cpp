#include "stdafx.h"
#include "ComponentHeader.h"

void StayOnScreenComponent::Update(float fTime, GameObject* pOwner)
{
	int iLeftBorder = m_pWindow->getView().getCenter().x - m_pWindow->getSize().x / 2;
	int iRightBorder = m_pWindow->getView().getCenter().x + m_pWindow->getSize().x / 2 - 32;
	int iTopBorder = m_pWindow->getView().getCenter().y - m_pWindow->getSize().y / 2;
	int iBottomBorder = m_pWindow->getView().getCenter().y + m_pWindow->getSize().y / 2 - 32;

	//corrects the position if gamobject is out of window
	if (pOwner->m_position.x < iLeftBorder)
		pOwner->m_position.x = iLeftBorder;

	if (pOwner->m_position.x > iRightBorder)
		pOwner->m_position.x = iRightBorder;

	if (pOwner->m_position.y < iTopBorder)
		pOwner->m_position.y = iTopBorder;

	if (pOwner->m_position.y > iBottomBorder)
		pOwner->m_position.y = iBottomBorder;
}
