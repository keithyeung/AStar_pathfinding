#pragma once
#include "raylib.h"
#include <vector>
#include <unordered_map>
#include "Grid.h"
#include "Starchaser.h"

//class Level;
//
//class Agent
//{
//public:
//	int id           = 0;
//	Vector2 position = {};
//	bool dead        = false;
//	
//
//	virtual void sense(Level* level)  = 0;
//	virtual void decide() = 0;
//	virtual void act()    = 0;
//
//	virtual void draw(Texture p_texture)   = 0;
//
//	virtual ~Agent() = default;
//};
//
//// This is just an example
//class SillyAgent : public Agent
//{
//public:
//	void sense(Level* level) override;
//	void decide() override;
//	void act() override;
//	void draw(Texture p_texture) override;
//
//	SillyAgent();
//	virtual ~SillyAgent() = default;
//
//private:
//};
	
class Level 
{
	int last_id = 0;

	////NOTE(Filippo): Using a list here is not the best idea, ideally you should store agents in some other data structure that keeps them close to each other while being pointer-stable.
	//std::list<SillyAgent> silly_agents;
	//// @AddMoreHere

	//std::unordered_map<int, Agent*> id_to_agent;
	//std::vector<Agent*> all_agents;

	//std::vector<Agent*> pending_agents; // Agents that will be added at the beginning of the next frame

public:
	/*Agent* get_agent(int id);

	Agent* spawn_agent(SillyAgent agent);*/
	// @AddMoreHere
	Grid gridsystem;
	Starchaser naruto;

	void reset();
	void update();
	void draw();

	Level();
	~Level();

private:
	void remove_dead_and_add_pending_agents();
	// Remember, if you add more lists (see @AddMoreHere), edit this function so that dead agents are removed correctly without leaking memory

	
};