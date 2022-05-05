
#include "PathPlanner.h"

#include <iostream>


PathPlanner::PathPlanner(Env env, int rows, int cols){
    this->rows = rows;
    this->cols = cols;
    this->env = new char* [rows];
    // Construct ENV environment copy
    for(int i = 0; i < rows ; ++i) {
        this->env[i] = new char[cols];
        for(int j = 0; j < cols ; ++j) {
            this->env[i][j] = env[i][j];
        }
    }
}

PathPlanner::~PathPlanner(){

}

void PathPlanner::initialPosition(int row, int col){
    startingPos = new Node(row,col,0);
}

// Search environment for the starting position
void PathPlanner::locateInitPoint(){
    bool found = false;
    for(int i = 0; i < rows && !found; ++i) {
        for(int j = 0; j < cols && !found; ++j) {
            if(env[i][j] == SYMBOL_START) {
                initialPosition(i,j);
            }
        }
    }
}
//
bool PathPlanner::isValidPath(Env env, int row, int col){
    bool valid = true;
    if((row >= 0 && row < rows) && (col >= 0 && col < cols)){
        valid = (env[row][col] != SYMBOL_WALL);
    }
    else{
        valid = false;
    }
    return valid;
}

NodeList* PathPlanner::getReachableNodes(){
    // Open List and Closed List of Nodes
    NodeList* OpenListNode  = new NodeList();
    NodeList* CloseListNode = new NodeList();

    //Find Starting point
    locateInitPoint();

    //Define a variable p and point it to the start node in O
    NodePtr P = new Node(startingPos->getRow(),startingPos->getCol(),0);
    OpenListNode->addBack(P);

    int index = 0;
    // While open list have nodes
    while (OpenListNode->get(index) != nullptr) {
        NodePtr nodePtr = OpenListNode->get(index);
        // U node
        if (isValidPath(env,nodePtr->getRow() - 1,nodePtr->getCol()) &&
            !OpenListNode->containsNode(new Node(nodePtr->getRow() - 1,nodePtr->getCol(),0))) {
            OpenListNode->addBack(new Node(nodePtr->getRow() - 1, nodePtr->getCol(), nodePtr->getDistanceToS() + 1));
        }

        // R node
        if (isValidPath(env,nodePtr->getRow(),nodePtr->getCol()+1)&&
            !OpenListNode->containsNode(new Node(nodePtr->getRow(),nodePtr->getCol() + 1,0))) {
            OpenListNode->addBack(new Node(nodePtr->getRow(), nodePtr->getCol() + 1, nodePtr->getDistanceToS() + 1));
        }

        // D node
        if (isValidPath(env,nodePtr->getRow() + 1,nodePtr->getCol())&&
            !OpenListNode->containsNode(new Node(nodePtr->getRow() + 1,nodePtr->getCol(),0))) {
            OpenListNode->addBack(new Node(nodePtr->getRow() + 1, nodePtr->getCol(), nodePtr->getDistanceToS() + 1));
        }

        // L node
        if (isValidPath(env,nodePtr->getRow(),nodePtr->getCol()-1)&&
            !OpenListNode->containsNode(new Node(nodePtr->getRow(),nodePtr->getCol() -1,0))) {
            OpenListNode->addBack(new Node(nodePtr->getRow(), nodePtr->getCol() - 1, nodePtr->getDistanceToS() + 1));
        }

        // Added the checked node as a new node to the closed list
        CloseListNode->addBack(new Node(nodePtr->getRow(), nodePtr->getCol(), nodePtr->getDistanceToS()));
        index++;
    }
    // Set class variable for reachable node
    reachablePos = CloseListNode;
    // Return the reachable positions as a new node list
    NodeList* reachablePositions = new NodeList(*CloseListNode);
    return reachablePositions;
}

NodeList* PathPlanner::getPath()
{
    //Check if goal is even present in closed list
    bool goalReachable = false;
    NodePtr goalNode =  nullptr;
    NodeList* origPath = new NodeList();
    for (int i = 0; i < reachablePos->getLength() && !goalReachable; i++)
    {
        
        
        NodePtr currNode = reachablePos->get(i);
        if (env[currNode->getRow()][currNode->getCol()] == SYMBOL_GOAL) {
            goalReachable = true;
            goalNode = currNode;
        }
    }
    
    
    NodeList* tempPath = nullptr;
    //If the goal is reachable find path else return null  
    if(goalReachable){
        tempPath = new NodeList();
        NodePtr currPathNode = goalNode;
        bool foundCurr = false;
        
        NodePtr tempUp      = nullptr;
        NodePtr tempRight   = nullptr;
        NodePtr tempDown    = nullptr;
        NodePtr tempLeft    = nullptr;
        int tempIndex       = -1;
        
        
        //Keep iterating till we reach start node
        while(currPathNode->getDistanceToS()>0){
            foundCurr = false;
            //UP
            tempUp      = new Node(currPathNode->getRow()-1,currPathNode->getCol(),0);
            if(!foundCurr && reachablePos->containsNode(tempUp)){
                tempIndex = reachablePos->containingNodeIndex(tempUp);
                if(reachablePos->get(tempIndex)->getDistanceToS()<currPathNode->getDistanceToS()){
                    foundCurr = true;
                    tempPath->addBack(tempUp);
                    currPathNode = reachablePos->get(tempIndex);
                }
            }

            //RIGHT
            tempRight   = new Node(currPathNode->getRow(),currPathNode->getCol()+1,0);
            if(!foundCurr && reachablePos->containsNode(tempRight)){
                tempIndex = reachablePos->containingNodeIndex(tempRight);
                if(reachablePos->get(tempIndex)->getDistanceToS()<currPathNode->getDistanceToS()){
                    foundCurr = true;
                    tempPath->addBack(tempRight);
                    currPathNode = reachablePos->get(tempIndex);
                }
            }

            //DOWN
            tempDown    = new Node(currPathNode->getRow()+1,currPathNode->getCol(),0);
            if(!foundCurr && reachablePos->containsNode(tempDown)){
                tempIndex = reachablePos->containingNodeIndex(tempDown);
                if(reachablePos->get(tempIndex)->getDistanceToS()<currPathNode->getDistanceToS()){
                    foundCurr = true;
                    tempPath->addBack(tempDown);
                    currPathNode = reachablePos->get(tempIndex);
                }
            }

            //LEFT
            tempLeft    = new Node(currPathNode->getRow(),currPathNode->getCol()-1,0);
            if(!foundCurr && reachablePos->containsNode(tempLeft)){
                tempIndex = reachablePos->containingNodeIndex(tempLeft);
                if(reachablePos->get(tempIndex)->getDistanceToS()<currPathNode->getDistanceToS()){
                    foundCurr = true;
                    tempPath->addBack(tempLeft);
                    currPathNode = reachablePos->get(tempIndex);
                }
            }
        }
        tempPath->addBack(currPathNode);
        origPath = new NodeList();
        for (int i = tempPath->getLength()-1; i >= 0; i--) {
            origPath->addBack(new Node(tempPath->get(i)->getRow(),tempPath->get(i)->getCol(),tempPath->get(i)->getDistanceToS()));
        }
    } 
    return origPath;
}