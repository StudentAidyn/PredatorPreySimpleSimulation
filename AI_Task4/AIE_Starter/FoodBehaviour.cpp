#include "FoodBehaviour.h"
#include "Agent.h"

//empty behaviour as this behaviour is used just as a still object
void FoodBehaviour::Enter(Agent* agent) {
	agent->SetColor(BLUE);
}

void FoodBehaviour::Update(Agent* agent, float deltaTime) {

}

void FoodBehaviour::Exit(Agent* agent) {

}
