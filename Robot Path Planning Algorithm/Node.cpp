
#include "Node.h"

//Parameterized Constructor
Node::Node(int row, int col, int distanceToS){
    //TODO
    this->row = row;
    this->col = col;
    this->distanceToS = distanceToS;
}

//Destructor
Node::~Node(){
}

//Getter/Setter Function
int Node::getRow(){
    return row;
}

//
int Node::getCol(){
    return col;
}

int Node::getDistanceToS(){
    return distanceToS;
}

void Node::setDistanceToS(int distanceToS){
    this->distanceToS = distanceToS;
}

/*
 * Calculate Manhattan-Distance
 * Add already travelled distance to it
 * Return total approximated distance
 */
int Node::getApproxDistToGoal(Node* goal){
    int manhattan = abs(col - goal->getCol()) + abs(row - goal->getRow());
    return distanceToS + manhattan;
}

/*
 * Find the approximated distance of 'current' node to the goal
 * Find the approximated distance of 'other' node to the goal
 * Return the one that's closer to the goal.
 */
Node* Node::compareDist(Node* other, Node* goal) {
    Node* target = this;
    if(other->getApproxDistToGoal(goal) < getApproxDistToGoal(goal)) {
        target = other;
    }
    return target;
}
