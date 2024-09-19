#pragma once
#include "Behaviour.h"
#include <glm/glm.hpp>

class LowEnergyBehaviour : public Behaviour
{
public:
	virtual void Enter(Agent* agent);
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Exit(Agent* agent);

	virtual float Evaluate(Agent* agent);

private:
	Agent* selectedFood; //currently selected food/energy source
	float newFoodTime; //timer to calculate the possibly new closest food source
};


/*Low Energy Behaviour (LEB) Description 
LEB describes when the AI agent has lost all it's energy forcing it to conserve it. 
this behaviour is shown by the agent moving at slow speeds and turning grey, the agent must path to its 
closest energy source to regain energy. */