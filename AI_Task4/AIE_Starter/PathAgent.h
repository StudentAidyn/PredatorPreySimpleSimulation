#pragma once
#include "NodeMap.h"

class PathAgent
{
private:
	//holds xy coordinates and a vector node path
	glm::vec2 m_position;
	std::vector<Node*> m_path;

	//used to calculate position
	int m_currentIndex;
	Node* m_currentNode;

	Color m_color = GREEN; //sets a default color
	
	float m_speed;

public:
	PathAgent();
	~PathAgent();

	//Functions
	void GoToNode(Node* node);
	void Update(float deltaTime);
	void Draw();

	//SET Functions - position, current node, color, speed
	void SetPosition(Node* node) { m_position = node->position; }
	void SetNode(Node* node) { m_currentNode = node; }
	void SetColor(Color color) { m_color = color; }
	void SetSpeed(float speed) { m_speed = speed; }


	//GET Functions - position, vector node path
	glm::vec2 GetPosition() { return m_position; }
	std::vector<Node*> GetPath() { return m_path; }
	float GetSpeed() { return m_speed; }
	
	//Reset
	void Reset() { m_path.clear(); }
	
};

