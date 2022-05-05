#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
Env readEnvStdin(Env env, int rows, int cols);

/* 
* Print out a Environment to standard output with path.
* To be implemented for Milestone 3
*/ 
void printPath(Env env, NodeList* solution, int rows, int cols);

/* The solution employed in Milestone 3 was is in accordance to the descripton.
 * We check for the presence of the goal in reachable nodes
 * If found we traverse back till we are able to find the start node
 * Once the list is created we reverse it so we get start to goal and not otherwise.
 * I encoutered some issue when printing cause I forgot to reverse the nodelist altough I figured it out on first glance.

 * For milestone 4 I made a few changes in ENV type.
 * Initialized the ENV dynamically
 * Had the read function read from file to test it
 * Added row and column dimensions to the type.h so it can create the dynamic sized ENV from the file
 */

int main(int argc, char** argv){
  
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    //std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    //testNode();
    //testNodeList();
    //std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment
    Env env = nullptr;

    //
    int row = 0;
    int col = 0;
 
    std::string input;
    std::ifstream stream;
    stream.open(ENV_FILE);
    while(getline(stream,input)){
        row++;
        col = input.length();
    }
    
    int envRow = row;
    int envCol = col;
    
    env = readEnvStdin(env, envRow, envCol);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathPlanner* pathPlanner = new PathPlanner(env, envRow, envCol);
    NodeList* reachablePositions = nullptr;
    pathPlanner->getReachableNodes();
    
    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathPlanner->getPath();
    
    //print the path
    printPath(env, solution, envRow, envCol);

    delete pathPlanner;
    delete reachablePositions;
    delete solution;

}

Env readEnvStdin(Env env, int rows, int cols){
    //TODO
    //Static Size

    // char p1[ENV_DIM];
    // int row = 0;
    // while (!std::cin.eof()) {
    //     std::cin >> p1;
    //     for (int col = 0; col < ENV_DIM; ++col) {
    //         //assign environment element to char at matching index position of char string
    //         env[row][col] = p1[col];
    //     }
    //     ++row;
    // }

    //Dynamic Size
    std::string input;
    std::ifstream stream;
    stream.open(ENV_FILE);
    
    // stream.close();
    //stream.open(ENV_FILE);
    
    env = nullptr;


    if (rows >= 0 && cols >= 0) {
        env = new char* [rows];
        for (int i = 0; i < rows; i++) {
            getline (stream, input);
            env[i] = new char[cols];
            for (int j = 0; j < cols; j++) {
                env[i][j] = input[j];
            }
        }
    }
    return env;
}

/*
 * This function is to help you delete a
 * dynamically allocated 2D Environment.
 */
void delete_env(Env env, int rows, int cols) {
    if (rows >= 0 && cols >= 0) {
        for (int i = 0; i < rows; i++) {
            delete env[i];
        }
        delete env;
    }
    return;
}

void printPath(Env env, NodeList* solution, int rows, int cols) {
    Node* pos = nullptr;
    Node* nextPos = nullptr;

    const int LEFT = -1, RIGHT = 1, UP = -1, DOWN = 1;

    //We update our environment with our directional characters
    for (int i = 1; i < solution->getLength() - 1; i++) {
        pos = solution->get(i);
        nextPos = solution->get(i + 1);

        int colDiff = nextPos->getCol() - pos->getCol();
        int rowDiff = nextPos->getRow() - pos->getRow();

        if(colDiff == RIGHT) {
            env[nextPos->getRow()][nextPos->getCol()] = '>';
        } else if (colDiff == LEFT) {
            env[nextPos->getRow()][nextPos->getCol()] = '<';
        } else if (rowDiff == DOWN) {
            env[nextPos->getRow()][nextPos->getCol()] = 'v';
        } else if (rowDiff == UP) {
            env[nextPos->getRow()][nextPos->getCol()] = '^';
        }
    }
    //We print our environment
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            std::cout << env[row][col];
        }
        std::cout << std::endl;
    }
}



void printReachablePositions(Env env, NodeList* reachablePositions){
    std::cout<<"All Reachable Nodes"<<std::endl;
    for (int i = 0; i < reachablePositions->getLength(); i++)
    {
        std::cout<<reachablePositions->get(i)<<std::endl;   
    }
    
}


void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}