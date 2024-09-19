#pragma once
#include "Behaviour.h"

//behaviour not used in Utility AI but kept as it is important to use

class GotoPointBehaviour : public Behaviour
{
public:
	virtual void Enter(Agent* agent); 
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Exit(Agent* agent);
};
