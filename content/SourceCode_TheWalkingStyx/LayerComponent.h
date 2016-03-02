#pragma once
#include "stdafx.h"

class LayerComponent : public IRenderComponent
{
public:
	typedef shared_ptr<Texture> TexturePtr;
	typedef shared_ptr<Sprite> SpritePtr;
	typedef shared_ptr<GameObject> GameObjectPtr;

	const string m_resourcePath = "../assets/";

	LayerComponent(RenderWindow* pWindow) : IRenderComponent(pWindow) { }
	~LayerComponent() {}
	bool init(const std::string& filename, const Vector2f& offset);
	void update(float fTime, GameObject* pOwner);
	void render(GameObject* pOwner);

private:
	std::unordered_map<std::string, TexturePtr> m_tilesetTexture;
	
	vector<vector<SpritePtr>> m_layers;
	unordered_map<string, SpriteComponent*> m_objects;

	SpriteComponent* loadSprite(NLTmxMapObject* object);
};
