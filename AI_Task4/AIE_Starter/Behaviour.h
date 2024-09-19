#pragma once

class Agent;

class Behaviour
{
public:
    virtual void Enter(Agent* agent) {}
    virtual void Update(Agent* agent, float deltaTime) = 0;
    virtual void Exit(Agent* agent) {}

    //update 4.0

    //used by UtilityAI an evaluation function to compare behaviours based on "importance" declared by a float
    virtual float Evaluate(Agent* agent) { return 0.0f; }
};

