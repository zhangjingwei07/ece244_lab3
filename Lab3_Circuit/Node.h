/* 
 * File:   Node.h
 * Author: JC and VB
 * Author: TSA
 *
 * Updated on August 24, 2016, 01:40 PM
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef NODE_H
#define NODE_H
#define MAX_RESISTORS_PER_NODE 5


extern int maxResistor;
extern int nodeid1;


class Node
{
private:
    
   int numRes=0; // number of resistors currently connected
   int resIDArray[MAX_RESISTORS_PER_NODE]; // stores the index of each resistor connected

public:
   Node(); 
   ~Node();

   // Checks to see if the resistor can be added to poistion rIndex
   // in the resistor array. Returns true if yes, otherwise false.
    bool canAddResistor(int rIndex);
    
    // Checks to see if the resistor can be added to poistion
    // in the node array. Returns true if yes, otherwise false.
    bool canAddNode();
    
   // Updates resIDArray to make the resistor in position rIndex in
   // the resistor array connected to this node.
   void addResistor (int rIndex); 

   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void print (int nodeIndex); 
   
   
};

#endif	/* NODE_H */

