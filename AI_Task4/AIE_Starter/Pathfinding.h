#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace AIForGames
{
    struct Node;

    struct Edge {
        Edge() { target = 0; cost = 0; }
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}
        Node* target;
        float cost; //cost which effects the GSCORE of NODE
    };

    struct Node {
        Node() { position.x = 0.0f; position.y = 0.0f;} //sets this as default constructor
        Node(float _x, float _y) : position(_x, _y){  } //constructor that takes positional values

        glm::vec2 position;
        std::vector<Edge> connections;

        float gScore;   //goal score
        Node* previous; //holds previous node location

        float hScore;   //heuristic score
        float fScore;   //final score

        void ConnectTo(Node* other, float cost) {
            connections.push_back((Edge(other, cost)));
        };  //edge connection creator
    };
}
