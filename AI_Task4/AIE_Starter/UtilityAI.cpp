#include "UtilityAI.h"

UtilityAI::~UtilityAI() {
    //delete m_behaviours since the pointers are owned by UtilityAI
	for (Behaviour* b : m_behaviours) {
		delete b;
	}
}

void UtilityAI::Update(Agent* agent, float deltaTime)
{
    //cB = currentBehaviour
    //nB = newBehaviour

    float bestEval = 0; //sets base value
    Behaviour* newBehaviour = nullptr; //new empty behaviour pointer
    for (Behaviour* b : m_behaviours) //comparing pointer evaluations
    {
        float eval = b->Evaluate(agent);
        if (eval > bestEval) //sets bestEval as eval value if bestEval is less than returned evaluation value
        {
            bestEval = eval;
            newBehaviour = b; //and assigns new behaviour the current behaviour in the for loop
        }
    }

    if (newBehaviour != nullptr 
        && newBehaviour != currentBehaviour) //if nB has been assigned a behaviour AND newBehaviour is not the same as currentBehaviour's behaviour
    {
        if (currentBehaviour)
            currentBehaviour->Exit(agent); //if there is a behaviour set to currentBehaviour then EXIT is called
        currentBehaviour = newBehaviour;
        currentBehaviour->Enter(agent);
        //sets cB to nB and call ENTER for cB 
    }

    currentBehaviour->Update(agent, deltaTime); 
}