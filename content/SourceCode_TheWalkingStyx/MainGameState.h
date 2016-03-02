#pragma once
#include "stdafx.h"
class MainGameState : public IGameState, public EventHandler<HeroChoosingEvent>, public EventHandler<LevelChangeEvent>, public EventHandler<ChangeScoreEvent>
{
public:
	bool Init(RenderWindow * pWindow);
	void InizializeGameObjects(std::string Hero);
	void Update(float time, Event event);
	void setTime(float time);
	void Render(RenderWindow* pWindow);
	void onEvent(HeroChoosingEvent* e) override;
	void onEvent(LevelChangeEvent* e) override;
	void onEvent(ChangeScoreEvent* e) override;
	void shutdown() override;
	void ReInit() override;

private:
	void loadLevelFromTiled(std::string strPath);
	void createGameObjectsFromTiled(std::string Hero);
	string m_currentLevel;
	Graph m_graph;
	RenderWindow* m_pWindow;
	vector<HandlerRegistration*> m_eventHandleRegistrations;
	string m_chosenHero;
	bool m_bGameIsRunning;
	bool m_bGameIsLoading;
	NLTmxMap* m_pTilemap;
	std::map<std::string, Texture*> m_tilesetTexture;
	vector<GameObject*> m_layer;
	map<int, string>m_levels;
	int m_iLevelCounter;
	std::vector<std::string> m_gameObjectTypes;
	sf::Clock m_clock;
};
