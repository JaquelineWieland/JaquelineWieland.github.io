#pragma once
#include "stdafx.h"
#include "GameObject.h"

class GameObjectManager
{
public:
	static GameObjectManager& getInstance();

	void AddGameObject(GameObject* pGameObject, std::string type);
	void RemoveGameObject(GameObject* pGameObject);
	void RemoveGameObjectsByType(std::string strType);
	void RemoveGameObjectsByType(std::vector<std::string> types);
	std::vector<GameObject*> FindGameObjectsByType(std::string strType);
	std::vector<GameObject*> FindGameObjectsByType(std::vector<std::string> types);
	std::vector<GameObject*> FindGameObjectByRange(IntRect rectangle);
	std::vector<GameObject*> GetAllGameObjects();
	void ReleaseAllGameObjects();

private:
	GameObjectManager() = default;
	~GameObjectManager() = default;
	GameObjectManager(const GameObjectManager& p) = delete;
	GameObjectManager& operator= (GameObjectManager const&) = delete;

	std::map<std::string, std::map<int, GameObject*>> m_TypeMapOfGameObject;
};