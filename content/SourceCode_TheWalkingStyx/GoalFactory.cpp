#include "stdafx.h"
#include "GameObjectsHeader.h"

GoalFactory::GoalFactory(int iWidth, int iHeight, RenderWindow* pWindow)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_pWindow = pWindow;
}

GameObject* GoalFactory::CreateGameObject(Vector2f position)
{
	GameObject* goal = new GameObject(position);

	RigidBodyComponent* rigidBody = new RigidBodyComponent(0, m_iWidth, m_iHeight, false, goal, m_pWindow, "Goal");
	goal->addComponent(rigidBody);

	return goal;
}
