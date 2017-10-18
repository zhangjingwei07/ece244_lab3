//
//  Node.cpp
//  Lab3_Circuit
//
//  Created by 张经纬 on 2017/10/11.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//
#include <cstdlib>
#include <iomanip>
#include <string>
#include <iostream>
#include "Node.h"
#include "Rparser.h"
#include "Resistor.h"

// The node constructor
Node::Node(){
    
    
}
// The default node destructor
Node::~Node(){
    
}


// The function to determine whether the resistor array is full
bool Node::canAddResistor(int rIndex){
    if (rIndex == maxResistor){
        cout << "Error: resistor array is full" << endl;
        return false;
    }
    
    return true;
}

// The function to determine whether the node array is full
bool Node::canAddNode(){
    if(numRes == MAX_RESISTORS_PER_NODE){
        cout << "Error: node is full" << endl;
        return false;
    }
    return true;
}

// The function to add the resistor
void Node::addResistor (int rIndex){
    
    resIDArray[numRes] = rIndex;
    numRes++;
}

// The member function to print the node connection
void Node:: print (int nodeIndex){
    if (numRes == 0)
    cout << "Connections at node "<<  nodeIndex << ": 0 resistor(s)" << endl;
    else{
        
            cout << "Connections at node " << nodeIndex <<": "  <<numRes<<" resistor(s)"<< endl;
        for(int i = 0; i< numRes ; i++){
            cout <<"  ";
            cout.width(21);
            cout << left << pResistorArray[resIDArray[i]]->getName();
            cout.width(8);
            cout << right << setiosflags(ios::fixed)
            << setprecision(2) << pResistorArray[resIDArray[i]]->getResistance()
            << " Ohms "
            << pResistorArray[resIDArray[i]]-> firstEnd()<< " -> "
            << pResistorArray[resIDArray[i]]->secondEnd() << endl;
        }
        
    }
    
}




