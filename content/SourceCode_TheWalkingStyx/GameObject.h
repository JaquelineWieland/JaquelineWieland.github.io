#pragma once
#include "stdafx.h"
#include "ComponentHeader.h"
class IComponent;
class GameObject
{
public:
	GameObject(Vector2f position);

	void addComponent(IComponent* pComponent);
	void Update(float fTime);
	void Render();
	void shutdown();

	int m_iID;
	Vector2f m_position;
	std::vector<IComponent*> m_components;

private:
	static int m_iIDcounter;
};
