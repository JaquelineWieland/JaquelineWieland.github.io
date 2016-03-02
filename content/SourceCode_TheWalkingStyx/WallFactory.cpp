#include "stdafx.h"
#include "GameObjectsHeader.h"

WallFactory::WallFactory(int iTileSize, Graph* pGraph, RenderWindow* pWindow)
{
	m_iTileSize = iTileSize;
	m_pGraph = pGraph;
	m_pWindow = pWindow;
}

GameObject* WallFactory::CreateGameObject(Vector2f position, int iWidth, int iHeight)
{
	m_pGraph->PlaceObstacle(position.x / m_iTileSize, position.y / m_iTileSize, iWidth / m_iTileSize, iHeight / m_iTileSize);

	GameObject* pWall = new GameObject(position);
	RigidBodyComponent* rigidBodyComp = new RigidBodyComponent(0, iWidth, iHeight, true, pWall, m_pWindow, "Wall");
	pWall->addComponent(rigidBodyComp);

	return pWall;
}
