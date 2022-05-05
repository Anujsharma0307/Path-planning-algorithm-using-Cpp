
#include "NodeList.h"
#include <iostream>



NodeList::NodeList(){
    length = 0;
}


NodeList::~NodeList(){
    for(int i = 0; i < length; i++) {
        delete nodes[i];
    }
}

NodeList::NodeList(NodeList& other){
    for(int i = 0; i < other.getLength(); i++) {
        addBack(other.get(i));
    }
}


int NodeList::getLength(){
    return length;
}


NodePtr NodeList::get(int i){
    return nodes[i];
}

void NodeList::addBack(NodePtr newNode){
    nodes[length++] = new Node( newNode->getRow(),
                                newNode->getCol(),
                                newNode->getDistanceToS());
}

bool NodeList::containsNode(NodePtr node){
    bool found = false;
    for(int i = 0; i < getLength(); i++) {
        if(node->getCol() == nodes[i]->getCol() && node->getRow() == nodes[i]->getRow()) {
            found = true;
        }
    }
    return found;
}

int NodeList::containingNodeIndex(NodePtr node){
    int index = -1;
    for(int i = 0; i < getLength(); i++) {
        if(node->getCol() == nodes[i]->getCol() && node->getRow() == nodes[i]->getRow()) {
            index = i;
        }
    }
    return index;
}

void NodeList::clear(){
    for(int i = 0; i < length; i++) {
        delete nodes[i];
    }
    length = 0;
}