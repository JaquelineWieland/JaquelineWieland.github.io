#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager& GameObjectManager::getInstance()
{
	static GameObjectManager m_instance;
	return m_instance;
}

void GameObjectManager::AddGameObject(GameObject* pGameObject, std::string type)
{
	if (m_TypeMapOfGameObject.find(type) == m_TypeMapOfGameObject.end())
	{
		std::map<int, GameObject*> newType;
		newType.emplace(pGameObject->m_iID, pGameObject);
		m_TypeMapOfGameObject.emplace(type, newType);
	}
	else
		m_TypeMapOfGameObject[type].emplace(pGameObject->m_iID, pGameObject);
}

void GameObjectManager::RemoveGameObject(GameObject* pGameObject)
{
	for (auto types : m_TypeMapOfGameObject)
		for (auto object : types.second)
			if (object.first == pGameObject->m_iID)
				types.second.erase(pGameObject->m_iID);
}

void GameObjectManager::RemoveGameObjectsByType(std::string strType)
{
	for (auto types : m_TypeMapOfGameObject)
	{
		if (types.first == strType)
		{
			int mapsize = types.second.size();
			for (auto i = 0; i < mapsize; i++)
			{
				auto iterator = types.second.begin()->first;
				types.second.begin()->second->shutdown();
				delete types.second.begin()->second;
				types.second.erase(iterator);
			}
		}
	}
	m_TypeMapOfGameObject.erase(strType);
}

void GameObjectManager::RemoveGameObjectsByType(std::vector<std::string> types)
{
	for (auto type : types)
		RemoveGameObjectsByType(type);
}

std::vector<GameObject*> GameObjectManager::FindGameObjectsByType(std::string strType)
{
	std::vector<GameObject*> exclusiveType;

	for (auto type : m_TypeMapOfGameObject)
		if (type.first == strType)
		{
			for (auto object : type.second)
				exclusiveType.push_back(object.second);
			return exclusiveType;
		}

	return exclusiveType;
}

std::vector<GameObject*> GameObjectManager::FindGameObjectsByType(std::vector<std::string> types)
{
	std::vector<GameObject*> exclusiveType;

	for (auto type : types)
	{
		std::vector<GameObject*> tmp = FindGameObjectsByType(type);
		exclusiveType.insert(exclusiveType.end(), tmp.begin(), tmp.end());
	}

	return exclusiveType;
}

std::vector<GameObject*> GameObjectManager::FindGameObjectByRange(IntRect rectangle)
{
	std::vector<GameObject*> filteredByRange;

	for (auto type : m_TypeMapOfGameObject)
		for (auto object : type.second)
			if (object.second->m_position.x > rectangle.left &&
				object.second->m_position.x < rectangle.left + rectangle.width &&
				object.second->m_position.y > rectangle.top &&
				object.second->m_position.y < rectangle.top + rectangle.height)
			{
				filteredByRange.push_back(object.second);
			}

	return filteredByRange;
}

std::vector<GameObject*> GameObjectManager::GetAllGameObjects()
{
	std::vector<GameObject*> allGameObjects;

	for (auto type : m_TypeMapOfGameObject)
		for (auto object : type.second)
			allGameObjects.push_back(object.second);

	return allGameObjects;
}

void GameObjectManager::ReleaseAllGameObjects()
{
	for (auto type : m_TypeMapOfGameObject)
	{
		for (auto object : type.second)
		{
			object.second->shutdown();
			delete object.second;
			object.second = nullptr;
		}
		type.second.clear();
	}
	m_TypeMapOfGameObject.clear();
}