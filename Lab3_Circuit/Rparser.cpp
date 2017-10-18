
#include <iostream>
using namespace std;

#include <sstream>
#include <string>
#include <iomanip>
#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
int maxNode = 0;
int maxResistor = 0;
Node** pNodeArray;
bool delete_net = false;
Resistor **pResistorArray;
int rIndex = 0;
int rCount = 0;
bool rNameFound = false;
bool endloop = false;

// The Parser function

void Rparser() {

    // Setup variables
    string line, command;
    string r_name;
    double r_value;
    int nodeid1, nodeid2 = 0;
    
    bool can_be_all;

    
    getline(cin, line); // Get a line from standard input
    cout << "> ";
    while (!cin.eof()) {
        // Put the line in a stringstream for parsing

        string test_space;
        stringstream lineStream(line);
        lineStream >> command;
        // insert a resistor
        if (command == "maxVal") {
            
            setMaxVal(lineStream);
            
        }

        else if (command == "insertR") {
            // Create a loop for break
            while (!endloop) {
            
                
            }
        }
            // to modify the value of an existing R  
        else if (command == "modifyR") {
            // Create a loop for break
            while (!endloop) {

                // Read the resistor name and check valid
                can_be_all = false;
                if (readString(lineStream, r_name, can_be_all))
                    break;

                // Read the resistor value and check valid
                if (readDouble(lineStream, r_value))
                    break;

                // Check whether the value of resistor is negative
                if (r_value < 0) {
                    cout << "Error: negative resistance" << endl;
                    break;
                }

                // Check if there are too many arguments
                if (tooManyArg(lineStream))
                    break;
                // modifyR
                for (int i = 0; i < rCount; i++) {
                    if (pResistorArray[i]->getName() == r_name) {
                        rNameFound = true;

                        cout << fixed << setprecision(2) << "Modified: resistor " << r_name << " from " << pResistorArray[i]->getResistance() << " Ohms" << " to " << r_value << " Ohms" << endl;
                        pResistorArray[i]->setResistance(r_value);
                        break;
                    }
                }


                // Output the modified result


                if (!rNameFound)
                    cout << "Error: resistor " << r_name << " not found" << endl;
                break;
            }
        }

            // print r
        else if (command == "printR") {
            // Create while loop for using break
            while (endloop != true) {

                // Read the resistor name and check valid
                can_be_all = true;
                if (readString(lineStream, r_name, can_be_all))
                    break;
                lineStream.clear();

                // Read the resistor value and check valid
                if (tooManyArg(lineStream))
                    break;

                // Check whether to print all resistors
                if (r_name != "all") {
                    for (int i = 0; i < rCount; i++) {
                        if (pResistorArray[i]->getName() == r_name) {
                            rNameFound = true;
                            cout << "Print:" << endl;
                            pResistorArray[i]->print();
                        }
                    }
                }

                else {
                    cout << "Print:" << endl;
                    for (int i = 0; i < rCount; i++) {

                        pResistorArray[i]->print();

                    }
                }
                break;
            }
        }

            // print node
        else if (command == "printNode") {
            // Create while loop for using break
            while (endloop != true) {

                // Read the node to be printed and check valid
                if (readPrintNode(lineStream, nodeid1))
                    break;

                // Check too many arguments
                if (tooManyArg(lineStream))
                    break;

                // Output the print outcome

                cout << "Print:" << endl;
                pNodeArray[nodeid1]->print(nodeid1);



                break;
            }
        }

            // delete resistor
        else if (command == "deleteR") {
            while (endloop != true) {
                can_be_all = true;
                // Read the resistor name to be deleted and check valid
                if (readString(lineStream, r_name, can_be_all))
                    break;

                lineStream.clear();
                // Check too many arguments
                if (tooManyArg(lineStream))
                    break;
                // Check whether the name is all
                if (r_name != "all")
                    cout << "Deleted: resistor " << r_name << endl;
                    // Output the outcome
                else {
                    cout << "Deleted: all resistors" << endl;
                    deleteNet();

                }

                endloop = true;
            }
        }

            // If the command is invalid
        else {
            cout << "Error: invalid command" << endl;
        }

        // Get new command
        getline(cin, line);
        endloop = false;
        cout << "> ";
    } // End input loop until EOF.

}


// The function to read string and check valid

bool readString(stringstream &lineStream, string &string_name, bool can_be_all) {
    bool endloop = false;
    lineStream >> string_name;
    // Name of resistor cannot be "all"
    if (string_name == "all" && can_be_all == false) {

        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        lineStream.clear();
        return endloop = true;
    }
    // if the name is invalid
    if (lineStream.fail()) {
        lineStream.clear();
        if (lineStream.peek() > 0)
            // Actually a read string won't be invalid, just put it here for fun
            cout << "Error: invalid argument" << endl;
            // If no available char detected
        else if (lineStream.peek() < 0)
            cout << "Error: too few arguments" << endl;
        endloop = true;
    }
    lineStream.clear();
    return endloop;
}

// The function to read double and check valid

bool readDouble(stringstream &lineStream, double &double_name) {
    bool endloop = false;
    lineStream >> double_name;
    // if fail reading r value

    if (lineStream.fail()) {
        lineStream.clear();
        // Check too few or invalid argument
        if (lineStream.peek() < 0) {
            cout << "Error: too few arguments" << endl;
        } else
            cout << "Error: invalid argument" << endl;
        return endloop = true;
    }
    // If the int is followed by a invalid char
    if (lineStream.peek() != 32 && lineStream.peek() != -1) {
        cout << "Error: invalid argument" << endl;
        return endloop = true;
    }
    lineStream.clear();
    return endloop;
}

// The function to read int and check valid

bool readInt(stringstream &lineStream, int &int_name) {
    bool endloop = false;
    lineStream >> int_name;
    // If fail reading the int
    if (lineStream.fail()) {
        lineStream.clear();
        // Determine too few or invalid argument
        if (lineStream.peek() < 0)
            cout << "Error: too few arguments" << endl;
        else
            cout << "Error: invalid argument" << endl;

        return endloop = true;
    }
    // If the int is followed by a invalid char
    if (lineStream.peek() != 32 && lineStream.peek() != -1) {
        cout << "Error: invalid argument" << endl;
        return endloop = true;
    }
    lineStream.clear();
    return endloop;
}

// The function to detect too many arguments

bool tooManyArg(stringstream &lineStream) {
    bool endloop = false;
    // If a space detected after the last valid argument
    if (lineStream.peek() == 32) {
        string test_space;
        // Put the stream into a new string to see whether there are spaces or chars
        lineStream >> test_space;
        if (test_space != "") {
            cout << "Error: too many arguments" << endl;
            return endloop = true;
        }
    }
    // If the last int is followed by a invalid char
    if (lineStream.peek() != 32 && lineStream.peek() > 0) {
        cout << "Error: invalid argument" << endl;
        endloop = true;
    }
    lineStream.clear();
    return endloop;
}

// The function to check the command of printing an existing node

bool readPrintNode(stringstream &lineStream, int &nodeid1) {
    bool endloop = false;
    string node_all;
    lineStream >> nodeid1;
    // If fail reading the int
    if (lineStream.fail()) {
        lineStream.clear();
        // Argument is too few
        if (lineStream.peek() < 0) {
            cout << "Error: too few arguments" << endl;
            return endloop = true;
        }
        // Check whether the failed reading is caused by name "all"
        if (lineStream.peek() >= 0) {
            lineStream >> node_all;
            lineStream.clear();
            // If all argument detected
            if (node_all == "all") {
                if (lineStream.peek() < 0) {
                    cout << "Print:" << endl;
                    for (int i = 0; i <= maxNode ; i++) {
                        pNodeArray[i]->print(i );
                    }
                }
                if (lineStream.peek() > 0)
                    cout << "Error: too many arguments" << endl;
            }                // If other invalid argument detected
            else
                cout << "Error: invalid argument" << endl;
            endloop = true;



            return endloop;
        }
    }

    lineStream.clear();
    // Check whether the nodeid is in range
    if (nodeid1 < 0 || nodeid1 > maxNode) {
        cout << "Error: node " << nodeid1 << " is out of permitted range " << 0 << "-" << maxNode << endl;
        endloop = true;
    }



    return endloop;
}

void deleteNet(){
    for (int i = 0; i < rCount; i++) {
                        delete pResistorArray[i];
                        pResistorArray[i] = NULL;
                    }
                    delete [] pResistorArray;
                    pResistorArray = NULL;

                    for (int i = 0; i <= maxNode; i++) {
                        delete pNodeArray[i];
                        pNodeArray[i] = NULL;
                    }
                    delete [] pNodeArray;
                    pNodeArray = NULL;
                    pResistorArray = new Resistor*[maxResistor + 1];

                    pNodeArray = new Node*[maxNode + 1];

                    for (int i = 0; i <= maxNode; i++)
                        pNodeArray[i] = new Node;
                    rCount = 0;
}


void setMaxVal(stringstream &lineStream){
    
        
        int tempNode = maxNode;
        int tempResistor = maxResistor;
        if (readInt(lineStream, maxNode)) {
            maxNode = tempNode;
            return;
        }
        if (readInt(lineStream, maxResistor)) {
            maxResistor = tempResistor;
            return;
        }
        if (maxNode == 0 || maxResistor == 0) {
            cout << "Error: maxVal arguments must be greater than 0" << endl;
            maxNode = tempNode;
            maxResistor = tempResistor;
            return;
        }
        // delete
        if (delete_net) {
            for (int i = 0; i < rCount; i++) {
                delete pResistorArray[i];
                pResistorArray[i] = NULL;
            }
            delete [] pResistorArray;
            
            pResistorArray = NULL;
            
            for (int i = 0; i <= tempNode ; i++) {
                delete pNodeArray[i];
                pNodeArray[i] = NULL;
            }
            delete [] pNodeArray;
            pNodeArray = NULL;
            
            
            rCount = 0;
            
            
        }
        pResistorArray = NULL;
        pNodeArray = NULL;
        pResistorArray = new Resistor*[maxResistor + 1];
        pNodeArray = new Node*[maxNode + 1];
        for (int i = 0; i <= maxNode ; i++)
            pNodeArray[i] = new Node;
        
        cout << "New network: max node number is " << maxNode << "; max resistors is " << maxResistor << endl;
        endloop = true;
        delete_net = true;
    
}

void insertR(stringstream &lineStream, bool can_be_all){
    string r_name;
    double r_value;
    int nodeid1, nodeid2 = 0;
    // Read the resistor name and determine if the name is valid
    can_be_all = false;
    if (readString(lineStream, r_name, can_be_all))
        return;
    
    lineStream.clear();
    
    // Read the resistor value and determine if the value is valid
    if (readDouble(lineStream, r_value))
        return;
    
    if (r_value < 0) {
        cout << "Error: negative resistance" << endl;
        return;
    }
    
    lineStream.clear();
    
    // Read the value for nodeid1 and check valid
    if (readInt(lineStream, nodeid1))
        return;
    // Determine whether nodeid1 is in range
    if (nodeid1 > maxNode || nodeid1 < 0) {
        cout << "Error: node " << nodeid1 << " is out of permitted range " << 0 << "-" << maxNode << endl;
        return;
    }
    
    lineStream.clear();
    
    // Read nodeid2 and check valid
    if (readInt(lineStream, nodeid2))
        return;
    
    
    // Determine whether nodeid 2 is in range
    if (nodeid2 > maxNode || nodeid2 < 0) {
        cout << "Error: node " << nodeid2 << " is out of permitted range " << 0 << "-" << maxNode << endl;
        return;
    }
    
    
    // Nodeid1 and nodeid2 cannot be equal
    if (nodeid1 == nodeid2) {
        
        cout << "Error: both terminals of resistor connect to node " << nodeid1 << endl;
        return;
    }
    
    // Detect too many argument and int followed by other syntax
    if (tooManyArg(lineStream))
        return;
    
    
    
    int node[2];
    node[0] = nodeid1;
    node[1] = nodeid2;
    
    // insertR into array
    for (int i = 0; i < rCount; i++) {
        if (pResistorArray[i]->getName() == r_name) {
            endloop = true;
            cout << "Error: resistor " << r_name << " already exists" << endl;
        }
    }
    if (endloop)
        return;
    
    
    
    if (pNodeArray[nodeid1]->canAddResistor(rCount) && pNodeArray[nodeid1]->canAddNode()
        && pNodeArray[nodeid2]->canAddNode()) {
        pResistorArray[rCount] = new Resistor(rCount, r_name, r_value, node);
    }
    else
        return;
    
    
    // Output the inserting outcome
    cout << fixed << setprecision(2) << "Inserted: resistor " << r_name << " " << r_value << " Ohms " << nodeid1 << " -> " << nodeid2 << endl;
    
    pNodeArray[nodeid1]->addResistor(rCount);
    pNodeArray[nodeid2]->addResistor(rCount);
    
    
    rCount = rCount + 1;
    endloop = true;
}









