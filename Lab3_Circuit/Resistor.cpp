//
//  Resistor.cpp
//  Lab3_Circuit
//
//  Created by 张经纬 on 2017/10/11.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//

#include "Node.h"
#include "Rparser.h"
#include "Resistor.h"
#include <string>
#include <iostream>

Resistor::Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]){
    resistance = resistance_;
    name = name_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    
}
Resistor::~Resistor(){
    
}
string Resistor::getName() const{
    
    return name;
}

double Resistor::getResistance() const{
    return resistance;
}

int Resistor::firstEnd() const{
    return endpointNodeIDs[0];
}
int Resistor::secondEnd() const{
    return endpointNodeIDs[1];
}

void Resistor::setResistance (double resistance_){
    resistance = resistance_;
}



void Resistor::print(){
    
 
    
    cout.width(21);
    cout << left << name;
    cout.width(8);
    cout << right << setiosflags(ios::fixed)
    << setprecision(2) << resistance
    << " Ohms "
    << endpointNodeIDs[0] << " -> "
    << endpointNodeIDs[1] << endl;
    
    
    
}
