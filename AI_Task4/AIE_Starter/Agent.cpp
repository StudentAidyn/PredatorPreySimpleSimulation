#include "Agent.h"
#include "Behaviour.h"

Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : 
	m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 0, 255 }) { //def constr
	m_current->Enter(this);
}

void Agent::Update(float deltaTime) {
	if (m_current) {
		m_current->Update(this, deltaTime);
	}
	m_pathAgent.Update(deltaTime);
}

void Agent::GoTo(glm::vec2 point) {
	Node* end = m_nodeMap->GetClosestNode(point);
	m_pathAgent.GoToNode(end);
}

void Agent::SetNode(Node* node) {
	m_pathAgent.SetNode(node);
}

void Agent::Draw() {
	m_pathAgent.Draw();
}

bool Agent::PathComplete() {
	return m_pathAgent.GetPath().empty();
}

void Agent::Reset() {
	m_pathAgent.Reset();
}