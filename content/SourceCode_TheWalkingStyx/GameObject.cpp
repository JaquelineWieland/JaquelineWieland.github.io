#include "stdafx.h"
#include "GameObject.h"

int GameObject::m_iIDcounter = 1;

GameObject::GameObject(Vector2f position)
{
	m_iID = m_iIDcounter;
	m_iIDcounter++;
	m_position = position;
}

void GameObject::addComponent(IComponent* pComponent)
{
	pComponent->SetID(m_iID);
	m_components.push_back(pComponent);
}

void GameObject::Update(float fTime)
{
	for  (auto component : m_components)
	{
		component->Update(fTime, this);
	}
}

void GameObject::Render()
{
	for (auto component : m_components)
	{
		component->Render(this);
	}
}

void GameObject::shutdown() 
{
	for (auto component : m_components)
	{
		component->Shutdown();
		delete component;
		component = nullptr;
	}
	m_components.clear();
}
