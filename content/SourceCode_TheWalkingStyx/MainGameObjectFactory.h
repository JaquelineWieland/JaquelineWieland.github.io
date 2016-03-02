#pragma once
#include "stdafx.h"
#include "Object.hpp"
// A Factory for GameObjects, which don't have variable properties, like Enemies, or triggerpoints.
// There are different types of enemies, but one type will always have the same properties, when initialized.
// Walls for example have variing width and height
//
// Also, any factory that is registered here can be accessed in any part of the game, not just when the factory itself is initialized.

class AbstractGameObjectFactory : public  Object
{
public:
	virtual ~AbstractGameObjectFactory() = default;
	virtual GameObject* CreateGameObject(Vector2f position) = 0;
	virtual void Shutdown()
	{
		if (!m_eventHandleRegistrations.empty())
		{
			for (auto handler : m_eventHandleRegistrations)
			{
				handler->removeHandler();
				handler->ShutDown();
				delete handler;
			}
			m_eventHandleRegistrations.clear();
		}
	}
	virtual void ReInit() 
	{
		for (auto handler : m_eventHandleRegistrations)
		{
			handler->removeHandler();
		}
		m_eventHandleRegistrations.clear();
	}

protected:
	std::vector<HandlerRegistration*> m_eventHandleRegistrations;
};

class MainGameObjectFactory	// Singleton
{
public:
	static MainGameObjectFactory* getInstance();
	static void Release();
	void ReInit();
	void RegisterFactory(const std::string strName, AbstractGameObjectFactory* pFactory);
	GameObject* CreateGameObject(const std::string strName, Vector2f position);

private:
	MainGameObjectFactory() = default;
	~MainGameObjectFactory() = default;
	MainGameObjectFactory(const MainGameObjectFactory& p) = delete;
	MainGameObjectFactory& operator= (MainGameObjectFactory const&) = delete;

	void shutdown();

	std::map<const std::string, AbstractGameObjectFactory*> m_factories;
	static MainGameObjectFactory* m_instance;
};
