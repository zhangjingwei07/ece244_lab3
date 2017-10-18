#ifndef rparser_h
#define rparser_h
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
using namespace std;

extern Node** pNodeArray;
extern Resistor** pResistorArray;


void Rparser();
void deleteNet();
bool readString(stringstream &lineStream, string &string_name, bool can_be_all );
bool readDouble(stringstream &lineStream, double &double_name );
bool readInt(stringstream &lineStream, int &int_name );
bool tooManyArg(stringstream &lineStream);
bool readPrintNode(stringstream &lineStream, int &nodeid1);
void setMaxVal(stringstream &lineStream);
extern int maxResistor;
extern int maxNode;
#endif
