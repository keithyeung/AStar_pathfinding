#pragma once
#include "raylib.h"
#include <vector>
#include <unordered_map>
#include "Grid.h"
#include "Starchaser.h"

	
class Level 
{
	int last_id = 0;

public:
	Grid gridsystem;
	Starchaser naruto;

	void reset();
	void update();
	void draw();

	Level();
	~Level();

private:
	void remove_dead_and_add_pending_agents();
};
