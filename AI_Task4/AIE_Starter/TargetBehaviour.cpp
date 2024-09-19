#include "TargetBehaviour.h"
#include "agent.h"

//copy of wanderbehaviour but without the reduction of energy

void TargetBehaviour::Enter(Agent* agent) {
    agent->SetColor({ 255,0,0,255 });//sets color to green

}

void TargetBehaviour::Update(Agent* agent, float deltaTime) {
    if (agent->PathComplete()) { //if the pathagent path vector is empty
        agent->GoTo(agent->GetNodeMap()->GetRandomNode()->position);
        //will go to a random point selected on map
    }
//no reduction of energy in the target behaviour
}

// UtilityAI update
float TargetBehaviour::Evaluate(Agent* agent)
{
    Agent* target = agent->GetTarget();
    float dist = glm::distance(target->GetPosition(), agent->GetPosition());

    float eval = dist;
    if (eval < 0) //return 0 if negative
        eval = 0;
    return eval;
}