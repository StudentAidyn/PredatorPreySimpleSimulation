#include "LowEnergyBehaviour.h"
#include "Agent.h"

void LowEnergyBehaviour::Enter(Agent* agent) {
	agent->SetSpeed(5);
	agent->SetColor(GRAY);
}

void LowEnergyBehaviour::Update(Agent* agent, float deltaTime) {
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

	agent->SetEnergy((agent->GetEnergy() - (deltaTime * (agent->GetSpeed() * 2))));
	//reduces Agents energy even with 0, this is to punish the Agent as they gradually will reclaim energy once they reach a food source
	
	dist = glm::distance(selectedFood->GetPosition(), agent->GetPosition());

	if (dist <= (agent->GetNodeMap()->GetCellSize() * 2)) {
		agent->SetEnergy(agent->GetEnergy() + selectedFood->GetEnergy());
		//if Agent gets to a food source it will add energy to the player
	}

	//as bonus to the behaviour, if the target agent passes over the main Agent will gain the targets energy
	float enemyDist = glm::distance(agent->GetTarget()->GetPosition(), agent->GetPosition());

	if (enemyDist < agent->GetNodeMap()->GetCellSize()) {
		agent->SetEnergy(agent->GetTarget()->GetEnergy() * 2 );
		float randVal = rand() % 100 + 50;
		agent->GetTarget()->SetEnergy(randVal);
		//the target energy is randomised between values 50 and 150
	}

}


void LowEnergyBehaviour::Exit(Agent* agent) {
	agent->SetSpeed(20);

}

float LowEnergyBehaviour::Evaluate(Agent* agent) {
	float val = 0;
	if (agent->GetEnergy() <= 0) {
		val = 10000;
		//value is extremly high to FORCE behaviour active
	}
	return val;
}