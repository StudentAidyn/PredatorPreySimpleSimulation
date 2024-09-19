#pragma once
#include "Behaviour.h"
#include <glm/glm.hpp>

class FollowBehaviour : public Behaviour
{
public:
	virtual void Enter(Agent* agent);
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Exit(Agent* agent);
	
	//UtilityAI Update
	virtual float Evaluate(Agent* agent);

private:
	glm::vec2 lastTargetPosition; 
	//needs to hold the last available position of a target

	float targEnergy = 0; //used to help evaluate whether Agent should continue to follow or not
	//but only if it is already following. defaulting prevents crash

};

