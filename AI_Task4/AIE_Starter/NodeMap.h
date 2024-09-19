#pragma once
#include "Pathfinding.h"
#include <iostream>
#include "raylib.h"

using namespace AIForGames;

class NodeMap {
public:
	NodeMap();
	~NodeMap();

	//Functions
	void DrawMap();
	void Initialise(std::vector<std::string> asciiMap, int cellSize);

	//returns node closest to the passed in vec2 (x and y position)
	Node* GetClosestNode(glm::vec2 worldPos);
	
	//returns node that is not a nullptr
	Node* GetRandomNode();


	//GET Functions
	Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }
	float GetCellSize() { return m_cellSize; }


private:
	//variables of map, height, width and indivisual cell size
	int m_width, m_height;
	float m_cellSize;

	Node** m_nodes; //pointer to pointers
	
};



namespace SmartSearch { 
	std::vector<Node*> Astar(Node* startNode, Node* endNode);
	float heuristic(Node* currentNode, Node* endNode);
	bool repeatSearch(std::vector<Node*> openList, Node*  searchedNode); //checks if a repeated node is in a vector list
	bool searchList(std::vector<Node*> list, Node* node); //checks for a node in a vector list
};

//namespace to make it easier to understand keeping it understandable