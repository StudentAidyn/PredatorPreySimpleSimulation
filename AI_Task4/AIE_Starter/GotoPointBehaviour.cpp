#include "GotoPointBehaviour.h"
#include "Agent.h"  //since behaviour is forward declared, Agent.h has to be included here

void GotoPointBehaviour::Enter(Agent* agent) {
	agent->SetColor(YELLOW);
	agent->Reset();
	//calls on agent to reset it's path
	agent->SetSpeed(100);
}

void GotoPointBehaviour::Update(Agent* agent, float deltaTime) {
	//while in this behaviour, 
	//if mouse button is clicked then it will try and go to that point the mouse clicked.
	if (IsMouseButtonPressed(0)) {
		Vector2 mousePos = GetMousePosition();
		agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
	}

	if (IsMouseButtonPressed(1)) {
		Vector2 mousePos = GetMousePosition();
		if (agent->GetNodeMap()->GetClosestNode(glm::vec2(mousePos.x, mousePos.y)) != nullptr) {
			agent->SetPosition(agent->GetNodeMap()->GetClosestNode(glm::vec2(mousePos.x, mousePos.y)));
			agent->SetNode(agent->GetNodeMap()->GetClosestNode(agent->GetPosition()));
		}
		
	}
}

void GotoPointBehaviour::Exit(Agent* agent) {
	agent->SetSpeed(20);
}