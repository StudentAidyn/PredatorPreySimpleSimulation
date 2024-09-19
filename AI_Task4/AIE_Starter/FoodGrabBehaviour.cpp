#include "FoodGrabBehaviour.h"
#include "Agent.h"

void FoodGrabBehaviour::Enter(Agent* agent) {
	//increased speed so the Agent can get back to the other behaviours faster
	agent->SetSpeed(80);
	//change colour to resemble food colour so user will know when this behaviour occurs
	agent->SetColor(BLUE);
	//defaulting food timer
	newFoodTime = 0;
}

void FoodGrabBehaviour::Update(Agent* agent, float deltaTime) {

	//setting variables for current update
	std::vector<Agent*> targets = agent->GetPST(); //this is used to simplify the code and search for a viable food Agent
	float search = 0;
	selectedFood = targets[0];
	float dist = glm::distance(agent->GetPosition(), selectedFood->GetPosition());//gets distance between agent and current food

	//if the food timer is below or is 0 then it will activate the search algorithm
	if (newFoodTime <= 0) {
		for (Agent* a : targets) { //searches food vector for closest energy source
			search = glm::distance(agent->GetPosition(), a->GetPosition());
			//search calculated based on distance between loop Agent position and Food Agent position
			if (search < dist) {
				selectedFood = a;
				dist = search; 
				// if search is less than distance than distance = search and selectedFood (an Agent) is set to the current loop Agent
			}
		}
		agent->GoTo(selectedFood->GetPosition()); //goes to nearest food position
		newFoodTime = 5; //resets count down
	}
	else {
		newFoodTime -= deltaTime;
		//reduces timer based on deltatime
	}

	agent->SetEnergy((agent->GetEnergy() - (deltaTime * agent->GetSpeed()/4)));
	//reduces energy to simulate tiredness but does it by a quater to help the main Agent move to a food source more consistently

	dist = glm::distance(selectedFood->GetPosition(), agent->GetPosition());
	//Distance is calculated between Agent and selected food Agent
	
	if (dist <= agent->GetNodeMap()->GetCellSize()) {
		agent->SetEnergy(agent->GetEnergy() + selectedFood->GetEnergy());
		//if the distance is less than nodemap cellsize then agent gains the energy from food agent
	}
}

void FoodGrabBehaviour::Exit(Agent* agent) {
	agent->SetSpeed(20);
}

float FoodGrabBehaviour::Evaluate(Agent* agent) {
	float needs = 0;

	if (agent->GetEnergy() < 250) {
		needs =  500 - agent->GetEnergy();
		//subtracts Agent's current energy value off 500 to produce a needs value
	}
	/* this simulates hunger within the Agent, the less energy the agent has the higher the evaluation number will be,
	this works to show that the less energy the Agent has the more Hungry they will be*/

	return needs;
}
