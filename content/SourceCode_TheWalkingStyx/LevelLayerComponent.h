#pragma once
#include "stdafx.h"

class LevelLayerComponent : public IComponent
{
public:
	LevelLayerComponent(int layerIdx, NLTmxMap* pTilemap, std::map<std::string, Texture*>* pTilesetTexture, RenderWindow* pWindow);
	void Render(GameObject* pOwner);
	void Shutdown();

private:
	int m_iTileSize;
	vector<Sprite*> m_pLayerSprites;
	RenderWindow* m_pWindow;
};

