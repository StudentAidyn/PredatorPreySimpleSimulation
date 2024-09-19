#include "WanderBehaviour.h"
#include "agent.h"

void WanderBehaviour::Enter(Agent* agent) {
	agent->SetColor({ 255,0,0,255 });//sets color to green

}

void WanderBehaviour::Update(Agent* agent, float deltaTime) {
	if (agent->PathComplete()) { //if the pathagent path vector is empty
		agent->GoTo(agent->GetNodeMap()->GetRandomNode()->position); 
		//will go to a random point selected on map
	}

    //reduce agent energy every update based on the agents current speed,
    //this is to represent the movement and the loss of energy
    agent->SetEnergy((agent->GetEnergy() - (deltaTime * agent->GetSpeed())));
    
}

// UtilityAI update
float WanderBehaviour::Evaluate(Agent* agent)
{
    float eval;
    Agent* target = agent->GetTarget();
    float dist = glm::distance(target->GetPosition(), agent->GetPosition());


    if (dist < 100) { //if distance is below 100 then eval is set to distance
         eval = dist;
    }
    else { //otherwise evaluation is capped at 100, this is to prevent awkward evaluation in other behaviours if the agent is too far away
        eval = 100;
    }
    
    if (eval < 0) //return 0 if negative
        eval = 0; 
    //evaluation score is the distance away from target
    return eval;
}