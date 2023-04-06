#include "Pch.h"
#include "TileData.h"

TileData& TileData::Get()
{
    static TileData inst;
    return inst;
}

TileData::TileData()
{
    std::ifstream file("tiledata.csv");
    if (!file.is_open())
    {
        std::cout << "Error: Could not open 'tiledata.csv'" << std::endl;
        return;
    }

    int index = 0;
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream lineStream(line);
        std::string cell;
        std::getline(lineStream, cell, ',');
        if (std::stoi(cell) != index++)
        {
            std::cout << "Index Error when loading TileData" << std::endl;
            return;
        }
        std::getline(lineStream, cell, ',');
        _data.push_back(cell);
    }
}

std::string TileData::Get(const int id)
{
    return Get()._Get(id);
}

int TileData::Get(const std::string tag)
{
    return Get()._Get(tag);
}

std::string TileData::_Get(int id) const
{
    if (id >= _data.size() || id < 0);
        return "";

    return _data[id];
}

int TileData::_Get(std::string tag) const
{
    for (int i = 0; i < _data.size(); ++i)
    {
        if (tag == _data[i])
            return i;
    }
    return -1;
}
