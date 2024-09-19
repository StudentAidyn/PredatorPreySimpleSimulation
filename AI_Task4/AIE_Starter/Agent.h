#pragma once
#include "PathAgent.h"

class Behaviour;

class Agent
{
public:
    Agent() {}
    Agent(NodeMap* _nodeMap, Behaviour* _behaviour); //def constr - takes NodeMap and a Behaviour
    ~Agent() { delete m_current; }


    //Functions - these just call on PathAgent's Functions
    void Update(float deltaTime);
    void Draw();
    void GoTo(glm::vec2 point);
    void Reset();

    bool PathComplete();


    //SET Functions
    void SetPosition(Node* node) { m_pathAgent.SetPosition(node); }
    void SetNode(Node* node);
    void SetColor(Color color) { m_pathAgent.SetColor(color); }
    void SetSpeed(float speed) { m_pathAgent.SetSpeed(speed); }
    void SetTarget(Agent* target) { m_target = target; }
    void SetEnergy(float energy) { m_energy = energy; }


    //GET Functions
    glm::vec2 GetPosition() { return m_pathAgent.GetPosition(); }
    std::vector<Node*> GetPath() { return m_pathAgent.GetPath(); }
    NodeMap* GetNodeMap() { return m_nodeMap; }
    Agent* GetTarget() { return m_target; }
    std::vector<Agent*> GetPST() { return m_powerSourceTarget; } //PST = power source target
    float GetEnergy() { return m_energy; }
    float GetSpeed() { return m_pathAgent.GetSpeed(); }


    void AddPST(Agent* PST) { m_powerSourceTarget.push_back(PST); }
  

private:
    float m_energy = 100; // stamina OR health

    Agent* m_target; 
    //target can be set to a vector, this mean it would be able to hold multiple targets at once.
    //BUT this also means a new heuristic would have to exist, it would have to seach for the closest target or some other base heuristic.
    std::vector<Agent*> m_powerSourceTarget;

    PathAgent m_pathAgent;
    Behaviour* m_current;
    NodeMap* m_nodeMap;
    Color m_color;
};

