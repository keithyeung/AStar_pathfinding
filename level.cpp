#include "level.h"


void Level::reset()
{
	gridsystem.OnSetUp();
	naruto.gridManager = &gridsystem;
	naruto.On_SetUp();
}

void Level::update()
{
	
	gridsystem.on_update();
	naruto.on_update();
	
}

void Level::draw()
{
	gridsystem.on_render();
	naruto.on_render();
}

Level::Level()
{
	
}

Level::~Level()
{
}
