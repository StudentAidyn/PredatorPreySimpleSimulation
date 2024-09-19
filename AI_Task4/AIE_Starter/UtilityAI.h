#pragma once
#include "Behaviour.h"
#include <vector>

class UtilityAI : public Behaviour
{
private:
    std::vector<Behaviour*> m_behaviours;
    Behaviour* currentBehaviour;

public:
    ~UtilityAI();
    virtual void Update(Agent* agent, float deltaTime);

    void AddBehaviour(Behaviour* behaviour) { m_behaviours.push_back(behaviour); }
};

