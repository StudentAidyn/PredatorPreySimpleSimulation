#include "FollowBehaviour.h"
#include "Agent.h"


void FollowBehaviour::Enter(Agent* agent) {
    // red when following
    agent->SetColor({ 255,0,0,255 });
    agent->Reset();
    //increases speed to induce running like behaviour
    agent->GetTarget()->SetSpeed(80);
    agent->SetSpeed(60);
}

void FollowBehaviour::Update(Agent* agent, float deltaTime) {
    targEnergy = agent->GetTarget()->GetEnergy();
    //sets the target energy so when evaluating it will evaluate whether it should continue following based on the current energy


    Agent* target = agent->GetTarget();
    //sets target to current agents target

    float dist = glm::distance(target->GetPosition(), lastTargetPosition);
    //calculates the distance between targets position and the last position the target was in

    //if position is more than the size of a node cell then the target has moved one cell over, 
    //this will reduce overrall pathfinding calculations.
    if (dist >= agent->GetNodeMap()->GetCellSize())
    {
        lastTargetPosition = target->GetPosition(); //sets last position to current position
        agent->GoTo(lastTargetPosition); //makes current agent move to the last position

        dist = glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition());
        //gets position between agent and target

        if (dist < agent->GetNodeMap()->GetCellSize()) { 
            agent->SetEnergy(agent->GetEnergy() + agent->GetTarget()->GetEnergy());
            float randVal = rand() % 100 + 50;
            agent->GetTarget()->SetEnergy(randVal);
            //if the agent is less than a cell away from the target then it will gain the targets energy, resetting it to a random number
            //this is in the if statement as otherwise it will add energy to the agent every frame causing the agent to never run out.
        }

    }
    agent->SetEnergy((agent->GetEnergy() - (deltaTime * agent->GetSpeed())));
    //reduces energy to simulate tiredness

    agent->GetTarget()->SetSpeed(80);
    /*constantly setting the speed is supposed to stop a bug from occuring
    BUG: if 2 Agents are following and 1 leaves, it will call exit and slow the target agent
    SO by applying speed in update it will make sure agent is always at the correct speed 
    and when it exits it will go back to normal meaning no agents are following */



}

void FollowBehaviour::Exit(Agent* agent) {
    //resets speed when changing Behaviour
    agent->GetTarget()->SetSpeed(40);
    agent->SetSpeed(20); 
    targEnergy = 0;
    //resets target energy to 0 so when evaluating it will only register it while following
}


//UPDATE: Using UTILITY-AI

float FollowBehaviour::Evaluate(Agent* agent)
{
    Agent* target = agent->GetTarget();
    float dist = glm::distance(target->GetPosition(), agent->GetPosition());

    float eval = 10 * agent->GetNodeMap()->GetCellSize() - dist; //the 10 relates to the max distance, and the 10 relates is the units distance.
    eval += targEnergy; //follow behaviour accounts for the targets energy but only while following, this allows for the target distance to be the only value that should be effected
    if (eval < 0)
        eval = 0;
    return eval;
}