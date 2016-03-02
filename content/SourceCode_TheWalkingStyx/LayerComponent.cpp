#include "stdafx.h"
#include "LayerComponent.h"


bool LayerComponent::init(const std::string& filename, const Vector2f& offset)
{

	FileInputStream mapStream;
	if (!mapStream.open(filename))
	{
		err() << "loadMap: could not open file " << filename << endl;
		return false;
	}

	// convert FileInputStream to char* mapBuffer
	char* mapBuffer = new char[mapStream.getSize() + 1];
	mapStream.read(mapBuffer, mapStream.getSize());
	mapBuffer[mapStream.getSize()] = '\0';

	// now lets load a NLTmxMap
	NLTmxMap* tilemap = NLLoadTmxMap(mapBuffer);
	delete mapBuffer;

	err() << "Load tilemap with size: " << tilemap->width << ", "
		<< tilemap->height << " and tilesize: " << tilemap->tileWidth
		<< ", " << tilemap->tileHeight << std::endl;

	// load textures for every tileset
	for (auto tileset : tilemap->tilesets)
	{
		err() << "Load tileset: " << tileset->name << " width filename: "
			<< tileset->filename << " and tilesize: " << tileset->tileWidth
			<< ", " << tileset->tileHeight << std::endl;

		auto texture = make_shared<Texture>();
		if (!texture->loadFromFile(m_resourcePath + tileset->filename))
			err() << "Could not load texture " << m_resourcePath + tileset->filename << endl;
		m_tilesetTexture[tileset->name] = texture;
	}

	// go through all layers
	m_layers.resize(tilemap->layers.size());

	for (int layerIdx = 0; layerIdx < (int)tilemap->layers.size(); layerIdx++)
	{
		NLTmxMapLayer* layer = tilemap->layers[layerIdx];
		err() << "Load layer: " << layer->name << " with width: "
			<< layer->width << " and height: " << layer->height << std::endl;

		int size = layer->width * layer->height;

		// go over all elements in the layer
		for (int i = 0; i < size; i++)
		{
			int grid = layer->data[i];

			if (grid == 0)	continue;

			// get tileset and tileset texture
			NLTmxMapTileset* tileset = tilemap->getTilesetForGrid(grid);
			Vector2i tileSize(tilemap->tileWidth, tilemap->tileHeight);
			TexturePtr texture = m_tilesetTexture[tileset->name];
			assert(texture != nullptr);

			// horizontal tile count in tileset texture
			int tileCountX = texture->getSize().x / tileSize.x;

			// calcualte position of tile
			Vector2f position;
			position.x = (i % layer->width) * (float)tileSize.x;
			position.y = (i / layer->width) * (float)tileSize.y;
			position += offset;

			// calculate 2d idx of tile in tileset texture
			int idx = grid - tileset->firstGid;
			int idxX = idx % tileCountX;
			int idxY = idx / tileCountX;

			// calculate source area of tile in tileset texture
			IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

			// TODO create tile and put it into a layer
			auto sprite = make_shared<Sprite>();
			sprite->setTexture(*texture);
			sprite->setTextureRect(source);
			sprite->setPosition(position.x, position.y);

			m_layers[layerIdx].push_back(sprite);
		}
	}

	// go through all object layers
	for (auto group : tilemap->groups)
	{
		// go over all objects per layer
		for (auto object : group->objects)
		{
			Vector2f position(object->x, object->y);
			position += offset;

			FloatRect bounds(position.x, position.y, object->width, object->height);

			// TODO create object
			if (object->type == "Sprite")
			{
				auto sprite = loadSprite(object);
				m_objects[object->name] = sprite;
			}
		}
	}
	return true;
}

void LayerComponent::update(float fTime, GameObject* pOwner)
{

}

void LayerComponent::render(GameObject* pOwner)
{
	const vector<SpritePtr> &layer{};

	for (int i = 0; i < m_layers.size(); i++)
	{
		for (auto sprite : layer)
			m_pWindow->draw(*sprite);
	}
}

SpriteComponent* LayerComponent::loadSprite(NLTmxMapObject* object)
{
	SpriteComponent* pSpC{};
	Image tmpImage;
	string path;
	IntRect textureRect{};
	textureRect.width = object->width;
	textureRect.height = object->height;
	for (auto property : object->properties)
	{
		auto name = property->name;
		if (name == "Texture" &&
			!tmpImage.loadFromFile(m_resourcePath + property->value))
		{
			err() << "loadSprite: Could not load texture for sprite: " <<
				m_resourcePath + property->value << endl;
		}
		else if (name == "Texture" &&
			tmpImage.loadFromFile(m_resourcePath + property->value))
		{
			path = m_resourcePath + property->value;
			tmpImage.loadFromFile(m_resourcePath + property->value);
		}
		else if (name == "TextureRectLeft")
		{
			textureRect.left = stoi(property->value);
		}
		else if (name == "TextureRectTop")
		{
			textureRect.top = stoi(property->value);
		}
	}

	if(path.length() > 0)
	pSpC->init(path, textureRect, Vector2f(object->x, object->y));

	return pSpC;
}
