#pragma once
namespace sf
{
	class Texture;
}

namespace TextureManager
{
	void Load();
	void Unload();

	sf::Texture* GetTexture(const std::string& key);
};

