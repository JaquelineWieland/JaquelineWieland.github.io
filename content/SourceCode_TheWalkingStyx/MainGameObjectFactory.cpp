#include "stdafx.h"
#include "GameObjectsHeader.h"

MainGameObjectFactory* MainGameObjectFactory::m_instance = nullptr;
MainGameObjectFactory* MainGameObjectFactory::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new MainGameObjectFactory();

	return m_instance;
}

void MainGameObjectFactory::Release()
{
	m_instance->shutdown();
	if (m_instance != nullptr)
		delete m_instance;
	m_instance = nullptr;
}

void MainGameObjectFactory::ReInit()
{
	for (auto kvp : m_factories)
	{
		kvp.second->ReInit();
		delete kvp.second;
	}
	m_factories.clear();
}

void MainGameObjectFactory::RegisterFactory(const std::string strName, AbstractGameObjectFactory* pFactory)
{
	assert(m_factories.count(strName) == 0);
	m_factories.emplace(strName, pFactory);
}

GameObject* MainGameObjectFactory::CreateGameObject(const std::string strName, Vector2f position)
{
	assert(m_factories.count(strName) > 0);
	return m_factories[strName]->CreateGameObject(position);
}

void MainGameObjectFactory::shutdown()
{
	for (auto kvp : m_factories)
	{
		kvp.second->Shutdown();
		delete kvp.second;
	}
}
