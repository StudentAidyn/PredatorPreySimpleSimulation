#include "PathAgent.h"

using namespace SmartSearch; 
PathAgent::PathAgent() {

}


PathAgent::~PathAgent() {
	m_path.clear(); //clears m_path
}

void PathAgent::GoToNode(Node* node) {
	m_path = Astar(m_currentNode, node);
	m_currentIndex = 0;
}

void PathAgent::Update(float deltaTime) {
	if (m_path.empty()) {
		//could make it pick it's own path by selecting a random cell;
		return;
	}

	m_currentNode = (1 <= m_currentIndex) ? m_path[m_currentIndex + 1] : m_path[m_currentIndex];
	//this is set so the agent will move from it's most recent position and is set to hopefully reduce the possibility for the agent going through walls

	glm::vec2 direction = glm::normalize(m_path[m_currentIndex + 1]->position - m_position); //gets movement direction using normalisation and position of self and next node
	float distance = glm::distance(m_position, m_path[m_currentIndex + 1]->position); //distance is calculated using glm's distance function, takes 2 positions and calculates change

	float move = m_speed * deltaTime; //total move distance
	distance -= move; //distance going to move

	if (distance > 0) { //distance is more than 0 then it is moving
		m_position += move * direction;
	}
	else { //it is not moving meaning it is either past the next node or at the end
		m_currentIndex++; 

		if (m_currentIndex >= m_path.size()-1) { //if at end node stop everything and reset path
			m_position = m_path.back()->position;
			Reset();
			return;
		}
		else if (m_path[m_currentIndex]) {
			float overshot = -distance;

			direction = glm::normalize(m_path[m_currentIndex - 1]->position - m_path[m_currentIndex]->position); 
			//gets new normalised vector direction based on current and now previous node (since m_currentIndex was increased)

			m_position += overshot * direction; //change position
		}
	}
}

void PathAgent::Draw() { //this literally draws a circle and uses the position of the PATHAGENT
		DrawCircle((int)m_position.x, (int)m_position.y, 4, m_color);
}