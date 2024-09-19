#pragma once
#include "Behaviour.h"
#include <glm/glm.hpp>
#include <vector>

class FoodGrabBehaviour : public Behaviour
{
public:
	virtual void Enter(Agent* agent);
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Exit(Agent* agent);

	//UtilityAI Update 
	virtual float Evaluate(Agent* agent);

private:
	glm::vec2 lastTargetPosition;
	Agent* selectedFood;
	float newFoodTime;
};

