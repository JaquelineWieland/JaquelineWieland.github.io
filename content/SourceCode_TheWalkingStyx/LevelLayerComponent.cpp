#include "stdafx.h"
#include "ComponentHeader.h"

LevelLayerComponent::LevelLayerComponent(int layerIdx, NLTmxMap* pTilemap, std::map<std::string, Texture*>* pTilesetTexture, RenderWindow* pWindow)
{
	m_pWindow = pWindow;
	m_iTileSize = pTilemap->tileWidth;

	NLTmxMapLayer* layer = pTilemap->layers[layerIdx];
	int size = layer->width * layer->height;

	// go over all elements in the layer
	for (int i = 0; i < size; i++)
	{
		int grid = layer->data[i];

		if (grid == 0)	continue;

		// get tileset and tileset texture
		NLTmxMapTileset* tileset = pTilemap->getTilesetForGrid(grid);
		Vector2i tileSize(pTilemap->tileWidth, pTilemap->tileHeight);
		Texture* texture = pTilesetTexture->at(tileset->name);
		assert(texture != nullptr);

		// horizontal tile count in tileset texture
		int tileCountX = texture->getSize().x / tileSize.x;

		// calcualte position of tile
		Vector2f position;
		position.x = (i % layer->width) * (float)tileSize.x;
		position.y = (i / layer->width) * (float)tileSize.y;

		// calculate 2d idx of tile in tileset texture
		int idx = grid - tileset->firstGid;
		int idxX = idx % tileCountX;
		int idxY = idx / tileCountX;

		// calculate source area of tile in tileset texture
		IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

		//create tile and put it into a layer
		Sprite* sprite = new Sprite();
		sprite->setTexture(*texture);
		sprite->setTextureRect(source);
		sprite->setPosition(position.x, position.y);

		m_pLayerSprites.push_back(sprite);
	}
}

void LevelLayerComponent::Render(GameObject* pOwner)
{
	IntRect view = IntRect();
	view.width = m_pWindow->getSize().x + 2 * m_iTileSize;
	view.height = m_pWindow->getSize().y +2 * m_iTileSize;
	view.left = m_pWindow->getView().getCenter().x - view.width / 2;
	view.top = m_pWindow->getView().getCenter().y - view.height / 2;

	for (auto sprite : m_pLayerSprites)
	{
		if (sprite->getPosition().x > view.left &&
			sprite->getPosition().x < view.left + view.width &&
			sprite->getPosition().y > view.top &&
			sprite->getPosition().y < view.top + view.height)
		{
			m_pWindow->draw(*sprite);
		}
	}
}

void LevelLayerComponent::Shutdown()
{
	for (auto sprite : m_pLayerSprites) delete sprite;
}
