#pragma once
#include "Behaviour.h"


class TargetBehaviour : public Behaviour
{
public:
	virtual void Enter(Agent* agent);
	virtual void Update(Agent* agent, float deltaTime);

	//UtilityAI Update 
	virtual float Evaluate(Agent* agent);
};


