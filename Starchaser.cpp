#include"Starchaser.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <raylib.h>
#include <list>

Starchaser::Starchaser()
{
	
}

Starchaser::~Starchaser()
{
	
}

void Starchaser::on_update()
{

	timer++;
	naruto = *gridManager->startNode;
	FiniteStateMachine();
}

void Starchaser::on_render()
{
	DrawTextureEx(m_texture, naruto.position, 0, 1, WHITE);
	
}

void Starchaser::On_SetUp()
{
	m_width = gridManager->cellSize;
	m_height = gridManager->cellSize;
	m_texture = LoadTexture("Asset/Naruto.png");
	naruto = *gridManager->startNode;
	timer = 0;
	stamina = max_stamina;
	fsm_mode = FindStar;
}



void Starchaser::FiniteStateMachine()
{
	switch (fsm_mode)
	{
	case(FindStar):
		AStar(gridManager->startNode, gridManager->endNode);
		gridManager->MakePathList(gridManager->endNode);
		gridManager->route = gridManager->endNode;
		
		if (!gridManager->pathNode.empty())
		{
			if (timer >= 30)
			{
				gridManager->startNode = gridManager->pathNode.back();
				gridManager->pathNode.pop_back();
				timer = 0;
			}
		}
		if (gridManager->pathNode.empty() && gridManager->startNode == gridManager->endNode)
		{
			gridManager->isHoldingStar = true;

			fsm_mode = FindTradePost;
		}
		
		break;
	case(FindTradePost):
		AStar(gridManager->startNode, gridManager->tradePost);
		gridManager->MakePathList(gridManager->tradePost);
		gridManager->route = gridManager->tradePost;
		if (!gridManager->pathNode.empty())
		{
			if (timer >= 30)
			{
				gridManager->startNode = gridManager->pathNode.back();
				gridManager->pathNode.pop_back();
				timer = 0;
				stamina--;
			}
		}
		if (gridManager->startNode == gridManager->tradePost)
		{
			std::cout << "We have sold the star" << std::endl;
			break;
		}
		if (stamina <= 0)
		{
			gridManager->pathNode.clear();
			fsm_mode = NeedABreak;
		}
		
		if (IsKeyPressed(KEY_B))
		{
			fsm_mode = FindStar;
		}
		break;
	case(NeedABreak):
		gridManager->isHoldingStar = false;
		gridManager->endNode = gridManager->fallenStar;
		AStar(gridManager->startNode, gridManager->spaceShip);
		gridManager->MakePathList(gridManager->spaceShip);
		gridManager->route = gridManager->spaceShip;
		
		if (!gridManager->pathNode.empty())
		{
			if (timer >= 30)
			{
				gridManager->startNode = gridManager->pathNode.back();
				gridManager->pathNode.pop_back();
				timer = 0;
			}
		}
		if (gridManager->pathNode.empty() && gridManager->startNode == gridManager->spaceShip)
		{
			stamina = max_stamina;
			fsm_mode = FindStar;
		}
		if (IsKeyPressed(KEY_B))
		{
			fsm_mode = FindStar;
		}
		break;
	default:
		break;
	}
}

float Starchaser::Distance(GridNode* p_start, GridNode* p_end)
{
	return sqrt((float)pow(p_end->position.x - p_start->position.x, 2) + pow(p_end->position.y - p_start->position.y, 2));
}

float Starchaser::Heuristic(GridNode* p_start, GridNode* p_end)
{
	return Distance(p_start, p_end);
}

void Starchaser::AStar(GridNode* p_start, GridNode* p_end)
{
	for (int i = 0; i < gridManager->nodes.size(); i++)
	{
		gridManager->nodes[i].is_Visited = false;
		gridManager->nodes[i].globalGoal = INFINITY;
		gridManager->nodes[i].localGoal = INFINITY;
		gridManager->nodes[i].parent = nullptr;
	}
	//setting up the starting point
	GridNode *current = p_start;
	p_start->localGoal = 0.0f;
	p_start->globalGoal = Heuristic(p_start,p_end);
	
	std::list<GridNode*> openList; //openlist = not tested list.
	openList.push_back(p_start);

	while (!openList.empty() && current != p_end) {
		openList.sort([](const GridNode* lhs, const GridNode* rhs) {return lhs->globalGoal < rhs->globalGoal; });
		//sort the nodes by global so that the lowest global value is in the front

		while (!openList.empty() && openList.front()->is_Visited)
		{
			openList.pop_front();
		}

		if (openList.empty())
		{
			break;
		}

		current = openList.front();
		current->is_Visited = true;

		for (auto neighborNode : current->vecNeighbours)
		{
			if (!neighborNode->is_Visited && neighborNode->is_Empty)
			{
				openList.push_back(neighborNode);
			}
			float lowestGoal = current->localGoal + Distance(current, neighborNode); //cal if the neighbour has lower distance
			if (lowestGoal < neighborNode->localGoal)
			{
				neighborNode->parent = current;
				neighborNode->localGoal = lowestGoal;
				neighborNode->globalGoal = neighborNode->localGoal + Heuristic(neighborNode, p_end);
			}
		}
	}
}

