#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include <string>
//update 1.0
#include "Pathfinding.h"        
#include "NodeMap.h"            
#include "PathAgent.h"          
//update 2.0
#include "GotoPointBehaviour.h" 
#include "WanderBehaviour.h"    
#include "FollowBehaviour.h"    
//update 3.0
#include "Agent.h"
//update 4.0
#include "UtilityAI.h"
//addon Update 4.5 
#include "FoodBehaviour.h"
#include "FoodGrabBehaviour.h"
#include "LowEnergyBehaviour.h"
#include "TargetBehaviour.h"


//namespace
using namespace AIForGames;
using namespace SmartSearch;

int main(int argc, char* argv[]) {

    //version 1.0

    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
 

    //Map initialization
    NodeMap nodeMap;
    
    //map builder, uses ascii char in a vector container, 0 = walls/blocks || 1 = traversaval space
    std::vector<std::string> asciiMap; 

    asciiMap.push_back("000000000000000000000000000000000000000000000000000000000000000000");
    asciiMap.push_back("010111011100011111011100111110111000111110111011001111101111011100");
    asciiMap.push_back("010101110111110101110111101011101111101011101101111010111001110110");
    asciiMap.push_back("010100000001010100000010101000000010101000000100101010000000000010");
    asciiMap.push_back("010111111101110111111110101111111011101111111111101011111111111110");
    asciiMap.push_back("010000001000011100010010100000010000111000100100101000000100010010");
    asciiMap.push_back("011111111111110001111010111111111111100011110110101111111101111010");
    asciiMap.push_back("010010000100010111000010100100001000111110000100101001000011000010");
    asciiMap.push_back("010111111100010101111110101111111001101011111111101011111101111110");
    asciiMap.push_back("010000010000110100000001100000100001001000000000011000001000000000");
    asciiMap.push_back("011100011111111101111111001111101111101011111111110011111001111110");
    asciiMap.push_back("010111010100010111011101111010111000101110111011011110101111011100");
    asciiMap.push_back("010101110111110101110100001011101111101011101101000010111001110110");
    asciiMap.push_back("010100000001010100000111001000000010101000000101110010000000000010");
    asciiMap.push_back("010111111101110111111101111111111011101111111111011111111111111110");
    asciiMap.push_back("010000001000011100010011000000010000111000100100110000000100010010");
    asciiMap.push_back("011111111111110001111110011111111111100011110111100111111101111010");
    asciiMap.push_back("010010000100010111000011000100001000101110000100110001000011000010");
    asciiMap.push_back("010111111101110101111111001111111000101011111111110011111101111110");
    asciiMap.push_back("010000010001010100000001000000100001101000000000010000001000000010");
    asciiMap.push_back("011111111111111101111111111111111111111011111111111111111111111110");
    asciiMap.push_back("000000000000000000000000000000000000000000000000000000000000000000");

    nodeMap.Initialise(asciiMap, 12); //takes vector map and cell size - map size is currently set to 12
   

    //delta time setup
    float time = (float)GetTime(); 
    float deltaTime;



    //agents setup
    Agent agent(&nodeMap, new TargetBehaviour());

    //agent Setup - Wonder Behaviour //target insect
    agent.SetPosition(nodeMap.GetRandomNode());
    agent.SetNode(nodeMap.GetClosestNode(agent.GetPosition()));
    agent.SetColor({ 0,50,200, 255 });
    agent.SetSpeed(40);


    //agent2 Setup - Uses Utility AI with 4 main behaviours
    UtilityAI* utilityAI2 = new UtilityAI();
    utilityAI2->AddBehaviour(new WanderBehaviour());
    utilityAI2->AddBehaviour(new FollowBehaviour());
    utilityAI2->AddBehaviour(new FoodGrabBehaviour());
    utilityAI2->AddBehaviour(new LowEnergyBehaviour());


    Agent agent2(&nodeMap, utilityAI2);
    agent2.SetPosition(nodeMap.GetRandomNode());
    agent2.SetNode(nodeMap.GetClosestNode(agent2.GetPosition()));
    agent2.SetTarget(&agent);
    agent2.SetColor(RED);
    agent2.SetEnergy(500);
    agent2.SetSpeed(20);
    

  

    //Agent3 Setup for Utility-AI - Uses same 4 main behaviours 
    UtilityAI* utilityAI3 = new UtilityAI();
    utilityAI3->AddBehaviour(new WanderBehaviour());
    utilityAI3->AddBehaviour(new FollowBehaviour());
    utilityAI3->AddBehaviour(new FoodGrabBehaviour());
    utilityAI3->AddBehaviour(new LowEnergyBehaviour());
    

    Agent agent3(&nodeMap, utilityAI3);
    agent3.SetPosition(nodeMap.GetRandomNode());
    agent3.SetNode(nodeMap.GetClosestNode(agent3.GetPosition()));
    agent3.SetTarget(&agent);
    agent3.SetColor(RED);
    agent3.SetEnergy(500);
    agent3.SetSpeed(20);



    //food test
    const int TOTAL_FOOD = 5;
    std::vector<Agent*> food;

    for (int i = 0; i < TOTAL_FOOD; i++) {
        Agent* fooditem = new Agent(&nodeMap, new FoodBehaviour());
        fooditem->SetPosition(nodeMap.GetRandomNode());
        fooditem->SetNode(nodeMap.GetClosestNode(fooditem->GetPosition()));
        fooditem->SetTarget(&agent3);
        fooditem->SetEnergy(500);
        fooditem->SetSpeed(0);
        food.push_back(fooditem);
        agent2.AddPST(fooditem);
        agent3.AddPST(fooditem);
    }

   
    //-------------------------------------------------------------------------------------

    // Main SIM loop **********************************************************************

    while (!WindowShouldClose()) 
    {
        // Update
        //--------------------------------------------------------------
        float fTime = (float)GetTime();                                 
        deltaTime = fTime - time;                                       
        time = fTime;                                                   
        //Delta Time Update                                             
                                                                        
        // Draw                                                         
        //--------------------------------------------------------------
        BeginDrawing();                                                 
                                                                        
        ClearBackground(BLACK);                                         
                                                                        
        //draws map                                                     
        nodeMap.DrawMap();                                              
                                                                        
        //Agent Updates + Draw                                          
        agent.Update(deltaTime);                                        
        agent.Draw();                                                   
                                                                        
        agent2.Update(deltaTime);                                       
        agent2.Draw();                                                  
                                                                        
        agent3.Update(deltaTime);                                       
        agent3.Draw();                                                  
                                                                        
        //Food Agent Updates + Draw                                     
        for (Agent* f : food) {                                         
            f->Update(deltaTime);                                       
            f->Draw();                                                  
        }                                                               
                                                                        
        EndDrawing();                                                   
        //--------------------------------------------------------------
    }

    CloseWindow();        // Close window
    //-------------------------------------------------------------------------------------

    return 0;
}



//3.0 update

/* DevLog:
Removed start and end variables, they are no longer needed since the agents use a random position,
agents have also been updated, one takes the wander behaviour and the other takes the FSM
behaviour manager.

.cpp/.h removed: SelectorBehaviour

unneeded with the update to the FSM.
*/

//4.0 update
//Update 4.0

  /*DEV LOG 1
  New Agent added "agent3", new agent runs off new UtilityAI.
  UtilityAI has behaviours Wander and Follow added to it,
  it selects these behaviours by comparing which behaviour is weighing in at more importance
  the higher the number the more important the behaviour is. */

/* DevLog: 2
- Added Utility AI with new sections in Behaviours
- Utility AI compares returned values and picks behaviour due to highest return value
- Added Utility AI Agent
- Agent uses wander and follow AI
*/

// 4.5 update

/* DevLog:
- Removed FSM agent to only show the new Utility AI agents in the simulation
- Added new behaviours, including: Food, LowEnergy and FoodGrab +++ TargetBehaviour.
- Added a second Utility AI agent
- Added food "Object" (agent)
- Updated agents:
    + food vector list w/ get and add func
    + Energy levels w/ get and set func
- Agents both use Wander, Follow, foodGrab and lowEnergy behaviours
- Added food Agent vector list to main
- Food Agents use food behaviour.

- */

