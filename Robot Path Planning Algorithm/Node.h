
#ifndef COSC_ASS_ONE_NODE
#define COSC_ASS_ONE_NODE

#include "Types.h"

class Node {
public:

    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // get row-co-ordinate
    int getRow();

    // get Column-co-ordinate
    int getCol();

    // getters and setters for distance to source
    int getDistanceToS();
    void setDistanceToS(int distanceToS);


    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    //Copy Constructor
    Node(Node& other);
    //getter for estimated dist to goal - need to return -> Manhatten distance + distance traveled
    int getApproxDistToGoal(Node* goal);
    //Compare and return the node closer to the goal
    Node* compareDist(Node* other, Node* goal);
    //Parameterizd Constructor
    Node(int row, int col, int distanceToS);
    //Destructor
    ~Node();


private:
    int row;
    int col;
    int distanceToS;


};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Position-Distance
typedef Node* NodePtr;

#endif // COSC_ASS_ONE_NODE
