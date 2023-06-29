#pragma once
#include<raylib.h>
#include <vector>
#include <deque>

struct GridNode
{
	bool is_Empty = true;					// is this node empty?	
	bool is_Visited = false;				// is this node already visited
	Vector2 position{};						// Nodes position in 2D space.
	float globalGoal;						// distance to end goal
	float localGoal;						// distance to goal if we took alternative path.
	int width{};
	int height{};
	std::vector<GridNode*> vecNeighbours;
	GridNode *parent;

};


class Grid {
public:

	const int cellSize = 50; // size of each cell in pixels
	const int gridWidth = 20; // number of cells horizontally
	const int gridHeight = 20; // number of cells vertically

	const int nodeBoxSize = 30;
	const int nodeGap = 10;

	bool isHoldingStar;


	Grid();
	~Grid();

	void on_render();
	void on_update();
	void OnSetUp();


	void MakePathList(GridNode* p_end);
	void DrawVisitedLine(GridNode* p_end);

	
	std::deque<GridNode> nodes;
	std::vector<GridNode*> pathNode;


	GridNode* startNode = nullptr;
	GridNode* endNode = nullptr;

	GridNode* spaceShip;
	GridNode* tradePost;
	GridNode* fallenStar;
	GridNode* route;

	Texture2D narutoTexture;
public:
	Vector2 GetStarPos();
	Vector2 GetSpaceshipPos();
	Vector2 GetTradePostPos();
private:

	Texture2D spaceShipTexture;

	Texture2D tradePostTexture;

	Texture2D fallenStarTexture;


private:
	//User Control things
	void RemoveOrMakeObstacle();
	void SetStartNode();
	void SetEndNode();
	void SetTradePost();
	void SetSpaceship();
	GridNode* SpawnEntity();
};
