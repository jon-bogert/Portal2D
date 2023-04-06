#include "Pch.h"
#include "AssetManager.h"

AssetManager& AssetManager::Get()
{
    static AssetManager instance;
    return instance;
}

AssetManager::AssetManager()
{
    //Tetures
    AddTexture("assets/textures/test.png", "test");
    AddTexture("assets/textures/background.png", "background");
    AddTexture("assets/textures/instructions.png", "instructions");

    //Fonts
    AddFont("assets/fonts/JetBrainsMono.ttf", "default");

    //Sounds
    AddSound("assets/audio/menu-hover.wav", "menuHover");
    AddSound("assets/audio/menu-select.wav", "menuSelect");

    //Music
    //AddMusic("path", "key");
}

AssetManager::~AssetManager()
{
    for (auto texture : _textures)
        delete texture.second;

    for (auto font : _fonts)
        delete font.second;

    for (auto sound : _sounds)
        delete sound.second;
}

void AssetManager::Load()
{
    Get();
}

sf::Texture* AssetManager::GetTexture(std::string key)
{
    for (auto texture : Get()._textures)
    {
        if (texture.first == key)
            return texture.second;
    }
    return nullptr;
}

sf::Font* AssetManager::GetFont(std::string key)
{
    for (auto font : Get()._fonts)
    {
        if (font.first == key)
            return font.second;
    }
    return nullptr;
}

sf::SoundBuffer* AssetManager::GetSound(std::string key)
{
    for (auto sound : Get()._sounds)
    {
        if (sound.first == key)
            return sound.second;
    }
    return nullptr;
}

sf::Music* AssetManager::GetMusic(std::string key)
{
    for (auto music : Get()._music)
    {
        if (music.first == key)
            return music.second;
    }
    return nullptr;
}

void AssetManager::AddTexture(std::string path, std::string key)
{
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(path);
    _textures.push_back({ key, texture });
}

void AssetManager::AddFont(std::string path, std::string key)
{
    sf::Font* font = new sf::Font();
    font->loadFromFile(path);
    _fonts.push_back({ key, font });
}

void AssetManager::AddSound(std::string path, std::string key)
{
    sf::SoundBuffer* sound = new sf::SoundBuffer();
    sound->loadFromFile(path);
    _sounds.push_back({ key, sound });
}

void AssetManager::AddMusic(std::string path, std::string key)
{
    sf::Music* music = new sf::Music();
    music->openFromFile(path);
    _music.push_back({ key, music });
}
