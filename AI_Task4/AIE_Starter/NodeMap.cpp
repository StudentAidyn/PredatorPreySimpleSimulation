#include "NodeMap.h"

NodeMap::NodeMap() {
    //empty
}

NodeMap::~NodeMap() {
    for (int d = 0; d < (m_width * m_height); d++) {
        m_nodes[d] = nullptr;
        delete m_nodes[d]; //goes through nodes based on width and height and clears it
    }

    m_nodes = nullptr;
    delete[] m_nodes;  //clears the pointer 

    std::cout << "DELETED SUCCESSFULLY" << std::endl;
}


void NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize) {

	m_cellSize = cellSize; //sets size for squares
	const char emptySquare = '0'; 

	//this assumes all the lines are the same size
	m_height = asciiMap.size();
	m_width = asciiMap[0].size();

    //sets new pointer of nodes to be the size of width * the height
	m_nodes = new Node * [m_width * m_height];


	for (int y = 0; y < m_height; y++) { //y by height
		std::string& line = asciiMap[y];
		
        //writes to console if any lines are of different length
		if (line.size() != m_width) {
			std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << std::endl;
		}

		for (int x = 0; x < m_width; x++) { // x by width
			char tile = x < line.size() ? line[x] : emptySquare;

			m_nodes[x + m_width * y] = tile == emptySquare ? nullptr
				: new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
		}
	}

    for (int y = 0; y < m_height; y++) { //goes through x and y coordinates
        for (int x = 0; x < m_width; x++) {
            Node* node = GetNode(x, y); //grabbing them here
            if (node) {
    
                Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
                if (nodeWest)
                {
                    node->ConnectTo(nodeWest, 1);
                    nodeWest->ConnectTo(node, 1);
                }
   
                Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
                if (nodeSouth)
                {
                    node->ConnectTo(nodeSouth, 1);
                    nodeSouth->ConnectTo(node, 1);
                }
                //sets up connection based on CURRENT NODE and finding neighbouring NODES
            }
        }
    }
}


Node* NodeMap::GetClosestNode(glm::vec2 worldPos) {
    //finds closest node to location mouse position on vec2 position
    int i = (int)(worldPos.x / m_cellSize);
    if (i < 0 || i >= m_width) return nullptr;

    int j = (int)(worldPos.y / m_cellSize);
    if (j < 0 || j >= m_height) { return nullptr; }

        return GetNode(i, j);
}


Node* NodeMap::GetRandomNode() {
    Node* node = nullptr; //sets empty node
    while (node == nullptr) {
        int x = rand() % m_width;
        int y = rand() % m_height;
        node = GetNode(x, y); //gets random node and checks if node is not null
    }
    return node; //if so it returns node
}


void NodeMap::DrawMap() {
    Color cellColor;
    cellColor.a = 255;
    cellColor.r = 75;
    cellColor.g = 115;
    cellColor.b = 65;

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            Node* node = GetNode(x, y);
            //draws nodes as squares with a little bit of spacing
            if (node == nullptr) {
                DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
                    ((int)m_cellSize - 1 ), ((int)m_cellSize - 1), cellColor);
            }
            else {
                for (int i = 0; i < node->connections.size(); i++) {
                    Node* other = node->connections[i].target;
                    Vector2 StartPos;
                    StartPos.x = (x + 0.5f) * m_cellSize;
                    StartPos.y = (y + 0.5f) * m_cellSize;
                    Vector2 EndPos;
                    EndPos.x = (int)other->position.x;
                    EndPos.y = (float)other->position.y;
                    DrawLineEx(StartPos, EndPos, m_cellSize/2 + m_cellSize/4, 
                        { 250, 210, 140, 255 });
                    //using the advanced drawline function allows me to change the width of the lines, this creates a nice effect on the node map
                }
            }
        }
    }
}



//---- SmartSearch namespace -----------------------------------------------------------------------

std::vector<Node*> SmartSearch::Astar(Node* startNode, Node* endNode) {

    std::vector<Node*> Path; //sets path as an empty NODE vector

    if (startNode == nullptr || endNode == nullptr) {
        //std::cout << "ERROR: 1 OR more Nodes Used are EMPTY" << std::endl;
        return Path;
    }

    if (startNode == endNode) {
        //std::cout << "No Path, already at END" << std::endl;
        return Path;
    }

    //setup --------------------------------
    startNode->gScore = 0;
    startNode->previous = nullptr;

    std::vector<Node*> openList;
    std::vector<Node*> closedList;

    openList.push_back(startNode);
    //---------------------------------------

    //Check and sort of possible paths -----------------
    while (!openList.empty()) {
        float hold;
        for (int i = 0; i < openList.size() - 1; i++) {
            for (int j = 0; j < openList.size() - i - 1; j++) {
                if (openList[j]->fScore > openList[j + 1]->fScore) {
                    hold = openList[j + 1]->fScore;
                    openList[j + 1]->fScore = openList[j]->fScore;
                    openList[j]->fScore = hold;
                }
            }
        }
        //sorting - using simple bubble sort (probably not the most effective but it works)

        Node* currentNode = openList[0];

        if (currentNode == endNode) {
            break;
        }

        openList.erase(openList.begin());
        closedList.push_back(currentNode);

        for (auto& c : currentNode->connections) {
            if (!repeatSearch(closedList, c.target)) {
                int gScore = currentNode->gScore + c.cost;
                int hScore = heuristic(c.target, endNode);
                int fScore = gScore + hScore;

                if (!repeatSearch(openList, c.target)) {
                    c.target->gScore = gScore;
                    c.target->fScore = fScore;
                    c.target->previous = currentNode;
                    openList.push_back(c.target);
                }
                else if (gScore < c.target->gScore) {
                    c.target->gScore = gScore;
                    c.target->fScore = fScore;
                    c.target->previous = currentNode;
                }

            }
        }
        /*this compares the scores of neighboring map nodes and then assigns the best one*/
    }

    if (searchList(openList, endNode)) { //if an impossible path across a blocked off area, it will appear on the openlist so that is how it can tell when not to do a path
        Path.clear();
        return Path;
    }
    //(removing impossible paths) ----------------------------------------------------- 

    //builds path ----------------------------------------------------------------------------------------------
 
    //using current node and going back through each node using their previous variable adding it to the start of the list 
    Node* currentNode = endNode;
    while (currentNode != nullptr) {
        Path.insert(Path.begin(), currentNode);
        currentNode = currentNode->previous; //checks previous with no risk of error since if there is an impossible path it will return before this occurs
    }
    //----------------------------------------------------------------------------------------------------------

    return Path;
}


float SmartSearch::heuristic(Node* target, Node* end) {
    //basic heuristic based on current distance from the end position
    //  float heuristicV = glm::distance(target->position, end->position);

    //Manhattan Distance calculation
    float heuristicV = (end->position.x - target->position.x) + (end->position.y - target->position.y);

    return heuristicV;
}


bool SmartSearch::repeatSearch(std::vector<Node*> List, Node* searchedNode) { //returns FALSE if it finds one and returns TRUE when it doesn't
    if (std::find(List.begin(), List.end(), searchedNode) == List.end()) {
        return false;
    }
    else {
        return true;
    }
}

bool SmartSearch::searchList(std::vector<Node*> list, Node* node) { //returns TRUE if it finds one and returns FALSE when it doesn't
    if (std::find(list.begin(), list.end(), node) == list.end()) {
        return true;
    }
    else {
        return false;
    }
}