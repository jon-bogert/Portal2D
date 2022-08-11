#include "Pch.h"
#include "TestChamber.h"

TestChamber::TestChamber(std::string path)
	: filePath(path)
{
}

TestChamber::~TestChamber()
{
}

void TestChamber::Start()
{
    LoadFromFile();
    Reset();
}

void TestChamber::Update(const float& deltaTime)
{
}

void TestChamber::Draw()
{
}

void TestChamber::OnDestroy()
{
}

void TestChamber::Reset()
{
    tileMapCurrent = tileMapOriginal;
}

void TestChamber::LoadFromFile()
{
    tileMapOriginal.clear();
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        Debug::LogErr("Could not open tilemap '%s'.", filePath.c_str());
        return;
    }

    std::string line;
    std::string data;
    bool isFirstLine = true;
    while (std::getline(file, line))
    {
        if (isFirstLine)
        {
            bool isHeight{};
            for (char c : line)
            {
                if (!isHeight && c != ' ')
                    data.push_back(c);
                else if (!isHeight)
                {
                    dimensions.x = atoi(data.c_str());
                    data.clear();
                }
                else if (isHeight && c != '\n')
                    data.push_back(c);
                else
                {
                    dimensions.y = atoi(data.c_str());
                    data.clear();
                }
            }
        }
        else
        {
            for (char c : line)
            {
                if (c != ' ' && c != '\n')
                    data.push_back(c);
                else
                {
                    tileMapOriginal.push_back(atoi(data.c_str()));
                    data.clear();
                }
            }
        }
    }

    file.close();
}


