#include "stdafx.h"
#include "ScrollSpeedComponent.h"
#include "GameObject.h"

void ScrollSpeedComponent::Update(float fTime, GameObject* pOwner)
{
	const float fBackgroundScrollSpeed = 50.0f; // pixel/sekunde
	m_fScrollSpeed = fTime * fBackgroundScrollSpeed;

	m_view = m_pWindow->getView();
	if (this->m_sideScrolling) m_view.move(m_fScrollSpeed, 0.0f);
	else m_view.move(0.0f, m_fScrollSpeed);

	m_pWindow->setView(m_view);
}
