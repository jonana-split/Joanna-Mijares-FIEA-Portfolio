#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include "AVLTree.h"
using namespace std;

//Joanna Mijares

int main() {
    MyAVLTree tree; //create an AVL tree

    //take in the number of commands
    int numCommands;
    cin >> numCommands;
    // so numCommands doesn't count as one of the commands
    cin.ignore();

    //go through all commands
    for (int i = 0; i < numCommands; ++i) {
        string line;
        getline(cin, line); //get the input line that contains the command and inputs
        tree.commandInput(line);
    }

    return 0;
}