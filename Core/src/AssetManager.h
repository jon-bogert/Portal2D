#pragma once
class AssetManager
{
	std::vector<std::pair<std::string, sf::Texture*>> _textures;
	std::vector<std::pair<std::string, sf::Font*>> _fonts;
	std::vector<std::pair<std::string, sf::SoundBuffer*>> _sounds;
	std::vector<std::pair<std::string, sf::Music*>> _music;

	static AssetManager& Get();
	AssetManager();

public:
	~AssetManager();
	AssetManager(const AssetManager& other) = delete;
	AssetManager& operator=(const AssetManager& other) = delete;

	static void Load();

	static sf::Texture* GetTexture(std::string key);
	static sf::Font* GetFont(std::string key);
	static sf::SoundBuffer* GetSound(std::string key);
	static sf::Music* GetMusic(std::string key);

private:
	void AddTexture(std::string path, std::string key);
	void AddFont(std::string path, std::string key);
	void AddSound(std::string path, std::string key);
	void AddMusic(std::string path, std::string key);

};

