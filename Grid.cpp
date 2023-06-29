#include "grid.h"
#include <iostream>


Grid::Grid()
{
    spaceShipTexture = LoadTexture("Asset/archangel.png");
    tradePostTexture = LoadTexture("Asset/tradePost.png");
    fallenStarTexture = LoadTexture("Asset/star.png");
    narutoTexture = LoadTexture("Asset/Naruto.png");

    fallenStarTexture.width = nodeBoxSize;
    tradePostTexture.width = nodeBoxSize;
    spaceShipTexture.width = nodeBoxSize;

    fallenStarTexture.height = nodeBoxSize;
    tradePostTexture.height = nodeBoxSize;
    spaceShipTexture.height = nodeBoxSize;

    
        
    //assigning Nodes
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            int x = i * cellSize;
            int y = j * cellSize;
            GridNode tempNode;
            tempNode.position.x = x;
            tempNode.position.y = y;
            tempNode.parent = nullptr;
            tempNode.is_Visited = false;
            int b = rand() % 2;
            if (b == 1)
            {
                tempNode.is_Empty = true;
            }
            else if (b == 0)
            {
                tempNode.is_Empty = false;
            }
            nodes.push_back(tempNode);
            
            
        }
    }

    for (int x = 0; x < gridWidth; x++)
    {
        for (int y = 0; y < gridHeight; y++)
        {
            if (y > 0)
                nodes[y * gridWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * gridWidth + (x + 0)]);
            if (y < gridHeight - 1)
                nodes[y * gridWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * gridWidth + (x + 0)]);
            if (x > 0)
                nodes[y * gridWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * gridWidth + (x - 1)]);
            if (x < gridWidth - 1)
                nodes[y * gridWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * gridWidth + (x + 1)]);

            if (y > 0 && x > 0)
                    nodes[y * gridWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * gridWidth + (x - 1)]);
            if (y < gridHeight-1 && x > 0)
                nodes[y * gridWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * gridWidth + (x - 1)]);
            if (y > 0 && x < gridWidth-1)
                nodes[y * gridWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * gridWidth + (x + 1)]);
            if (y < gridHeight - 1 && x < gridWidth-1)
                    nodes[y * gridWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * gridWidth + (x + 1)]);

        }
    }
}


Grid::~Grid()
{

}

void Grid::on_render()
{

    // draw rectangles around cells
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            int x = i * cellSize;
            int y = j * cellSize;
            DrawRectangleLines(x, y, cellSize, cellSize, BLACK);
        }
    }

    //Draw connections
    for (int i = 0; i < nodes.size(); i++)
    {
        for (auto n : nodes[i].vecNeighbours)
        {
            for (int j = 0; j < nodes[i].vecNeighbours.size(); j++)
            {
                DrawLine(nodes[i].position.x + (cellSize/2), nodes[i].position.y + (cellSize / 2),
                    nodes[i].vecNeighbours[j]->position.x + (cellSize / 2), nodes[i].vecNeighbours[j]->position.y + (cellSize / 2), BLUE);
            }
        }
        
    }

    //draw grid
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].is_Empty)
        {
            DrawRectangle(nodes[i].position.x + nodeGap, nodes[i].position.y + nodeGap, nodeBoxSize, nodeBoxSize, DARKGREEN);
        }
        else if (!nodes[i].is_Empty)
        {
            DrawRectangle(nodes[i].position.x + nodeGap, nodes[i].position.y + nodeGap, nodeBoxSize, nodeBoxSize, BLACK);
        }

        if (&nodes[i] == startNode)
        {
            DrawRectangle(nodes[i].position.x + nodeGap, nodes[i].position.y + nodeGap, nodeBoxSize, nodeBoxSize, GREEN);
        }
        if (&nodes[i] == endNode)
        {
            DrawRectangle(nodes[i].position.x + nodeGap, nodes[i].position.y + nodeGap, nodeBoxSize, nodeBoxSize, RED);
        }
    }


    //draw visited line
    DrawVisitedLine(route);
    

    // draw spaceship
    DrawTextureEx(spaceShipTexture, { spaceShip->position.x + nodeGap, spaceShip->position.y + nodeGap }, 0, 1, WHITE);

    //draw tradepost
    DrawTextureEx(tradePostTexture, { tradePost->position.x + nodeGap , tradePost->position.y + nodeGap }, 0, 1, WHITE);

    //draw fallen star
    DrawTextureEx(fallenStarTexture, { fallenStar->position.x + nodeGap, fallenStar->position.y + nodeGap }, 0, 1, WHITE);

    

}

void Grid::on_update()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_SHIFT)) { // if left click on Obstacle, remove obstacle or make it an obstacle
        SetStartNode();
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_CONTROL))
    {
        SetEndNode();
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_T))
    {
        SetTradePost();
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_S))
    {
        SetSpaceship();
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        RemoveOrMakeObstacle();
    }
    if (isHoldingStar)
    {
        fallenStar = startNode;
    }
    
}

void Grid::DrawVisitedLine(GridNode* p_end)
{
    if (p_end != nullptr)
    {
        GridNode* tempNode = p_end;
        while (tempNode->parent != nullptr)
        {
            DrawLine(tempNode->position.x + (cellSize / 2), tempNode->position.y + (cellSize / 2),
                tempNode->parent->position.x + (cellSize / 2), tempNode->parent->position.y + (cellSize / 2), YELLOW);

            tempNode = tempNode->parent;
        }
    }
}

void Grid::MakePathList(GridNode* p_end)
{
    pathNode.clear();
    if (p_end != nullptr)
    {
        GridNode* tempNode = p_end;
        while (tempNode->parent != nullptr)
        {
            pathNode.push_back(tempNode);
            tempNode = tempNode->parent;
        }
    }
}




Vector2 Grid::GetStarPos()
{
    return fallenStar->position;
}

Vector2 Grid::GetSpaceshipPos()
{
    return spaceShip->position;
}

Vector2 Grid::GetTradePostPos()
{
    return tradePost->position;
}

void Grid::RemoveOrMakeObstacle()
{
    Vector2 mousePos = GetMousePosition();
    Rectangle tempRect;
    for (int i = 0; i < nodes.size(); i++)
    {
        tempRect.x = nodes[i].position.x + nodeGap;
        tempRect.y = nodes[i].position.y + nodeGap;
        tempRect.width = nodeBoxSize;
        tempRect.height = nodeBoxSize;
        if (CheckCollisionPointRec(mousePos, tempRect))
        {
            nodes[i].is_Empty = !nodes[i].is_Empty;
            std::cout << i << std::endl;
        }
    }
}

void Grid::SetStartNode()
{
    Vector2 mousePos = GetMousePosition();
    Rectangle tempRect;
    for (int i = 0; i < nodes.size(); i++)
    {
        tempRect.x = nodes[i].position.x+ nodeGap;
        tempRect.y = nodes[i].position.y + nodeGap;
        tempRect.width = nodeBoxSize;
        tempRect.height = nodeBoxSize;
        if (CheckCollisionPointRec(mousePos, tempRect))
        {
            if (nodes[i].is_Empty)
            {
                startNode = &nodes[i];
            }
            else
            {
                std::cout << "Cannot move to a obstacle block" << std::endl;
            }
        }
    }
}

void Grid::SetEndNode()
{
    Vector2 mousePos = GetMousePosition();
    Rectangle tempRect;
    for (int i = 0; i < nodes.size(); i++)
    {
        tempRect.x = nodes[i].position.x + nodeGap;
        tempRect.y = nodes[i].position.y + nodeGap;
        tempRect.width = nodeBoxSize;
        tempRect.height = nodeBoxSize;
        if (CheckCollisionPointRec(mousePos, tempRect))
        {
            if (nodes[i].is_Empty)
            {
                endNode = &nodes[i];
                fallenStar = endNode;
            }
            else
            {
                std::cout << "Cannot put the star on a obstacle block" << std::endl;
            }
        }
    }
}

void Grid::SetTradePost()
{
    Vector2 mousePos = GetMousePosition();
    Rectangle tempRect;
    for (int i = 0; i < nodes.size(); i++)
    {
        tempRect.x = nodes[i].position.x + nodeGap;
        tempRect.y = nodes[i].position.y + nodeGap;
        tempRect.width = nodeBoxSize;
        tempRect.height = nodeBoxSize;
        if (CheckCollisionPointRec(mousePos, tempRect))
        {
            if (nodes[i].is_Empty)
            {
                tradePost = &nodes[i];
            }
            else
            {
                std::cout << "Cannot move tradePost to a obstacle block" << std::endl;
            }
        }
    }
}

void Grid::SetSpaceship()
{
    Vector2 mousePos = GetMousePosition();
    Rectangle tempRect;
    for (int i = 0; i < nodes.size(); i++)
    {
        tempRect.x = nodes[i].position.x + nodeGap;
        tempRect.y = nodes[i].position.y + nodeGap;
        tempRect.width = nodeBoxSize;
        tempRect.height = nodeBoxSize;
        if (CheckCollisionPointRec(mousePos, tempRect))
        {
            if (nodes[i].is_Empty)
            {
                spaceShip = &nodes[i];
            }
            else
            {
                std::cout << "Cannot move spaceship to a obstacle block" << std::endl;
            }
        }
    }
}

GridNode* Grid::SpawnEntity()
{
    int randomNumber = rand() % 400;
    GridNode* temp;
    while (nodes[randomNumber].is_Empty == false)
    {
        randomNumber = rand() % 400;
    }
    temp = &nodes[randomNumber];
    return temp;
    
    

}

void Grid::OnSetUp()
{
    startNode = SpawnEntity();
    endNode = SpawnEntity();
    tradePost = SpawnEntity();
    spaceShip = SpawnEntity();

    fallenStar = endNode;
    isHoldingStar = false;

    tradePost->width = tradePostTexture.width;
    fallenStar->width = fallenStarTexture.width;
    spaceShip->width = spaceShipTexture.width;
    route = endNode;
}






