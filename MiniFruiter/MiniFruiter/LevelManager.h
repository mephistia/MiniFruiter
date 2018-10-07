#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <string>

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void lerLevels(std::string arquivo);

private:
	int *level;
};

