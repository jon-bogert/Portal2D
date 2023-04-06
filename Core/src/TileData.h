#pragma once

class TileData
{
	std::vector<std::string> _data;

	static TileData& Get();
	TileData();

public:
	// Static Interfaces
	static std::string Get(const int id);
	static int Get(const std::string tag);

private:
	//Implementation of Singleton Functions
	std::string _Get(const int id) const;
	int _Get(const std::string tag) const;
};