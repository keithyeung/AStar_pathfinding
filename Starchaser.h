#pragma once
#include <raylib.h>
#include "Grid.h"

class Starchaser
{

public:	
	void on_update();
	void on_render();
	void On_SetUp();

	Starchaser();
	~Starchaser();

	Grid* gridManager;
	GridNode naruto;
private:
	Texture m_texture;
	int m_width, m_height;
	int timer;
	int stamina;
	const int max_stamina = 5;
	
	enum FSM
	{
		FindStar,
		FindTradePost,
		NeedABreak,
	}fsm_mode;


private:
	void FiniteStateMachine();
	float Distance(GridNode* p_start, GridNode* p_end);
	float Heuristic(GridNode* p_start, GridNode* p_end);

	void AStar(GridNode* p_start, GridNode* p_end);
};