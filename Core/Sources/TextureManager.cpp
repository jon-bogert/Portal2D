#include "Pch.h"
#include "TextureManager.h"

std::vector<std::pair<std::string, sf::Texture*>> textureCache;

void AddTexture(std::string path, std::string key);

void TextureManager::Load()
{
	AddTexture("Assets/Textures/test-cube.png", "test cube");
}

void TextureManager::Unload()
{
	while (!textureCache.empty())
	{
		delete textureCache[0].second;
		textureCache.erase(textureCache.begin());
	}
}

sf::Texture* TextureManager::GetTexture(const std::string& key)
{
	for (auto pair : textureCache)
	{
		if (pair.first == key)
		{
			return pair.second;
		}
	}
	Debug::LogErr("No Texture '%s' found.", key.c_str());
	return nullptr;
}

void AddTexture(std::string path, std::string key)
{
	sf::Texture* temp = new sf::Texture;
	if (!temp->loadFromFile(path))
	{
		Debug::LogWarn("Could not find texture file at path: %s", path.c_str());
		delete temp;
		return;
	}

	textureCache.push_back({ key, temp });
}
