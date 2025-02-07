#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include "AVLTree.h"
using namespace std;

//Joanna Mijares

//Citation: Used Stepik Module5_Solution.PDF as reference and guide

//Height Function recursively finds the longest path from root to leaf. The height of each subtree is calculated and the
//largest one is selected until eventually the last and greatest node is reached. Then 1 is added to it to account for the node itself
int MyAVLTree::height(Node* node) const {
    if (node == nullptr)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

//Citation: Used Discussion Slides Discussion 5 - Balanced Trees Slide 18 as reference and guide

//The Balance Factor is the height of a node's left child minus the height of a node's right child
int MyAVLTree::balanceFactor(Node* node){
    if(node == nullptr){
        return 0;
    }
    return (height(node->left)-height(node->right));
}

//prints the height of the tree, aka level count
void MyAVLTree::levelCountHelper(Node* node) const{
    if(node == nullptr){
        cout<<0<<endl;
    }else {
        cout << height(node) << endl;
    }
}

//prints the level count
void MyAVLTree::printLevelCount() {
    levelCountHelper(root);
}

//Citation: Referenced 3 - Trees.pdf Slide 69 for inspiration and reference

//Finds the total number of nodes in a tree.
int MyAVLTree::treeSizeHelper(Node* node) const{
    if(node == nullptr){
        return 0;
    }

    int totalNumNodes = 1; //count the root here

    //recursively find the total number of nodes in each subtree and add it to the total
    totalNumNodes += treeSizeHelper(node->left);
    totalNumNodes += treeSizeHelper(node->right);

    return totalNumNodes;
}

//prints and returns the tree size
int MyAVLTree::treeSize() const{
    cout<< treeSizeHelper(root)<<endl;
    return treeSizeHelper(root);
}

//Citation: Class Presentation 4-Balanced Trees Slides #12-14

//Rotates the node to the left
Node* MyAVLTree::rotateLeft(Node *node) {
    //in a right-heavy tree...
    //the grandchild is the left child of the right child of the original node
    Node* grandchild = node->right->left;
    Node* replaceParent = node->right;  //what will replace the node is the node's right child
    replaceParent ->left = node; //the left node of replaceParent becomes the original node
    node->right = grandchild; //the right child of the original node is now the grandchild

    height(node); //update the height

    return replaceParent; //return the new head node
}

//Citation: Class Presentation 4-Balanced Trees Slides #12-14

//Rotates node to the right
Node* MyAVLTree::rotateRight(Node *node) {
    //in a left-heavy tree...
    //the grandchild is the right child of the left child of the original node
    Node* grandchild = node->left->right;
    Node* replaceParent = node->left; //what will replace the node is the node's left child
    replaceParent ->right = node; //the right node of replaceParent becomes the original node
    node->left = grandchild; //the left child of the original node is now the grandchild

    height(node); //update height

    return replaceParent; //return the new head node
}

//Citation: Used Stepik Module5_Solution.PDF as reference and guide

//Inorder function prints the values in the tree in numerical order, printing all left nodes first, then the node itself, then all right nodes.
void MyAVLTree::inorderHelper(Node* node, vector<string>& results) const{
    //if no node is found
    if(node==nullptr){
        return;
    }

    //Inorder: left, node, right

    inorderHelper(node->left, results); //recursively traverse left subtree, outputting out smallest numbers

    //commas placed in front of nodes as long as not the first item
    if(results.size()>0){
        results.push_back(", ");
    }

    results.push_back(node->name); //push current node into vector

    inorderHelper(node->right, results); //recursively traverse right subtree, outputting largest numbers in order

}

//extra function used in removeInorder and insert
void MyAVLTree::inorderIDHelper(Node* node, vector<string>& ufidResults) const{
    //if no node is found
    if(node==nullptr){
        return;
    }

    //same as inorder, but without the commas

    inorderIDHelper(node->left, ufidResults);

    ufidResults.push_back(node->ufid);

    inorderIDHelper(node->right, ufidResults);

}

void MyAVLTree::printInorder() const{
    //if no node is found
    if(root == nullptr){
        cout<<""<<endl;
        return;
    }

    //print out each value in the inorder vector
    vector<string> results;
    inorderHelper(root,results);
    for(int i=0; i<results.size(); i++){
        cout<<results[i];
        if(i == results.size()-1){
            cout<<endl; //end line on last value
        }
    }
}

//Citation: Used Stepik Module5_Solution.PDF as reference and guide

//Preorder function prints the node itself first, then recursively prints the left subtree, then recursively prints the right subtree
void MyAVLTree::preorderHelper(Node* node, vector<string>& results) const{
    //if no node is found
    if(node==nullptr){
        return;
    }

    //Preorder: node, left, right (good for testing rotations)

    //commas placed in front as long as not the first item
    if(results.size()>0){
        results.push_back(", ");
    }

    results.push_back(node->name); //push current node into vector

    preorderHelper(node->left,results); //recursively traverse left subtree

    preorderHelper(node->right, results); //recursively traverse right subtree
}

void MyAVLTree::printPreorder() const{
    //if no node is found
    if(root == nullptr){
        cout<<""<<endl;
        return;
    }

    //print out each value in the preorder vector
    vector<string> results;
    preorderHelper(root, results);
    for(int i=0; i<results.size(); i++){
        cout<<results[i];
        if(i == results.size()-1){
            cout<<endl; //end line on last value
        }
    }
}

//Citation: Used Stepik Module5_Solution.PDF as reference and guide

//Postorder function recursively prints the left subtree, then recursively prints the right subtree, then prints the node itself
void MyAVLTree::postorderHelper(Node* node, vector<string>& results) const{
    //if no node is found
    if(node==nullptr){
        return;
    }

    //Postorder: left, right, node

    postorderHelper(node->left, results); //recursively traverse left subtree

    postorderHelper(node->right, results); //recursively traverse right subtree

    //commas placed in front as long as not the first item
    if(results.size()>0){
        results.push_back(", ");
    }

    results.push_back(node->name); //push current node into vector
}

void MyAVLTree::printPostorder() const{
    //if no node is found
    if(root == nullptr){
        cout<<""<<endl;
        return;
    }

    //print out each value in the preorder vector
    vector<string> results;
    postorderHelper(root, results);
    for(int i=0; i<results.size(); i++){
        cout<<results[i];
        if(i == results.size()-1){
            cout<<endl; //end line on last value
        }
    }
}

//SearchID outputs name associated with ID
Node* MyAVLTree::searchIDHelper(Node* node, string targetUfid, vector<string>& nameList){

    //if no id is found
    if(node == nullptr){
        cout<<"unsuccessful"<<endl;
        return nullptr;
    }

    //if length of inputted id is less than 8
    if(targetUfid.length()!=8){
        cout<<"unsuccessful"<<endl;
        return nullptr;
    }

    //convert targetUfid and current ufid to integer to compare all ufids in the tree
    int targetNum = stoi(targetUfid);
    int nodeNum = stoi(node->ufid);

    //if matching id is found, push out corresponding name. otherwise, keep recursively searching the left and right of the tree
    if (targetNum == nodeNum) {
        nameList.push_back(node->name);
    }else if (nodeNum > targetNum) {
        node->left = searchIDHelper(node->left, targetUfid, nameList);
    }else if (nodeNum < targetNum) {
        node->right = searchIDHelper(node->right, targetUfid, nameList);
    }

    return node;
}

void MyAVLTree::searchID(string ufid){
    vector<string> nameList;
    searchIDHelper(root, ufid, nameList);

    //after searching, print out the name with corresponding ID.
    // will only be one value due to checks in insert.
    if(!nameList.empty()) {
        cout << nameList[0] << endl;
    }

}

//SearchName outputs IDs associated with name
void MyAVLTree::searchNameHelper(Node* node, string targetName, vector<string>& ufidList){

    //if no node is found
    if(node == nullptr){
        return;
    }

    //use same traversal method as preorder to push names into list
    //if target name is equal to current node's name, push current node in first, then recursively traverse left and right subtrees for more names
    if(targetName == node->name) {
        ufidList.push_back(node->ufid);
    }
        searchNameHelper(node->left, targetName, ufidList);
        searchNameHelper(node->right, targetName, ufidList);
}

void MyAVLTree::searchName(string name){
    vector<string> ufidList;
    searchNameHelper(root, name, ufidList);
    if(ufidList.empty()){
        cout<<"unsuccessful"<<endl; //if no names are found
        return;
    }
    //push back all ids onto new lines
    for(int i=0; i<ufidList.size(); i++){
        cout<<ufidList[i]<<endl;
    }
}

//Citation: Referenced and used Class Slides 4-Balanced Trees.pdf slides 79-81
//Citation: for Structure and Pseudocode, referenced and used Class Slides 3- Trees.pdf slide 38

//Remove function deletes a node with a given ID
Node* MyAVLTree::removeHelper(Node *node, string targetUfid){

    //if no node is found
    if(root == nullptr || node == nullptr){
        cout<<"unsuccessful"<<endl;
        return node;
    }

    bool success = false;

    //convert current node and targetUFID into integers to traverse tree
    int targetNum = stoi(targetUfid);
    int nodeNum = stoi(node->ufid);

    //Citation: inspiration from Project 1 Breakdown slide 15
    
    //recursively search left or right subtrees for node to remove
    if (nodeNum > targetNum) {
        node->left = removeHelper(node->left, targetUfid);
    }else if (nodeNum < targetNum) {
        node->right = removeHelper(node->right, targetUfid);
    }

    //separate remove function for the root with special rules.
    // unsure if this is necessary, but it worked best for me in the end :(
    else if(node == root) {
        Node* treeHead = root; //pointer to the root of the tree
        if(node->left == nullptr){ //if there is no left child
            root = root->right; //new root is the root's right child
            delete treeHead; //delete the old root
            success = true;
        }else if(node->right == nullptr){ //if there is no right child
            root = root->left; //new root is the root's left child
            delete treeHead; //delete the old root
            success = true;
        }else{
            //find leftmost child of right root

            //in the right subtree of the root
            Node* successor = node->right;

            //while there are still left children...
            while(successor->left != nullptr){
                successor = successor->left;
            }

            //replace node with inorder successor's ufid and name
            node->ufid = successor->ufid;
            node->name = successor->name;

            //delete successor by recursively calling on remove function again inside the right subtree
            //this will delete the successor no matter where it is in the subtree
            node->right = removeHelper(node->right, successor->ufid);

        }
        //removal of any other node that isn't the root
    }else {
        //the node we will be deleting. we will be reassigning 'node'
        Node* tempReplace = node;

            //if there are 0 children of the node
           if(node->left == nullptr && node->right == nullptr) {
               node = nullptr; //just make node nullptr and delete it in memory
               delete tempReplace;
               success = true;
           }else if(node->left == nullptr){ //if only one right child
               node = node->right; //new node is the node's right child
               delete tempReplace; //delete old node
               success = true;
           }else if(node->right == nullptr){ //if only one left child
               node = node->left; //new node is the node's left child
               delete tempReplace; //delete old node
               success = true;
           }else if(node->left != nullptr && node->right != nullptr){

                //find leftmost child of right root
                Node* successor = node->right;

               //while there are still left children...
               while(successor->left != nullptr){
                       successor = successor->left;
                   }

                   //replace node with inorder successor's ufid and name
                   node->ufid = successor->ufid;
                   node->name = successor->name;

                   //delete successor by calling on remove function again
                   node->right = removeHelper(node->right, successor->ufid);
               }

       }

    //reestablish the height and balance factors of the tree
    //rotations aren't necessary but these should be updated
    height(node);
    balanceFactor(node);

    //if success bool is true output successful
    if(success){
        cout<<"successful"<<endl;
    }

    return node;

}

//returns removeHelper
Node* MyAVLTree::remove(string ufid){
    return removeHelper(root, ufid);
}

//RemoveInorder function removes a node at the index n after the tree has been sorted inorder
void MyAVLTree::removeInorderHelper(Node *node, int& n) {

    //if no node is found
    if(root == nullptr || node == nullptr){
        cout<<"unsuccessful"<<endl;
        return;
    }

    //assign the nodes to a vector with inorderIdHelper
    vector<string> results;
    inorderIDHelper(node, results);

    string ID = results[n]; //individual ID

    if(n<results.size()){ //if n is a valid index
        //"successful" will print inside removeHelper
        //remove the target id at the given index
        removeHelper(node, ID);
    }else{
        cout<<"unsuccessful"<<endl;
    }
}

//returns removeInorderHelper
void MyAVLTree::removeInorder(int n) {
    return removeInorderHelper(root, n);
}

//Citation: followed example from AVL Project Breakdown/Q&A Session video

Node* MyAVLTree::insert(string name, string ufid){
    this -> root = insertHelper(this -> root, name, ufid);
    return root;
}

//Citation: Class Slides 4-Balanced Trees slide 28

//inserts and creates a new node
Node* MyAVLTree::insertHelper(Node* node, string name, string newUfid)
{

    //creates an inorder vector of all nodes
    vector<string> IDResults;
    inorderIDHelper(node, IDResults);

    //if id we want to insert is equal to any existing IDs, output unsuccessful
    for(int i = 0; i<IDResults.size(); i++){
        if(IDResults[i] == newUfid){
            cout<<"unsuccessful"<<endl;
            return node;
        }
    }

    int newID = stoi(newUfid);

    //whenever we create a new node that doesn't exist yet output successful and create it
    if (node == nullptr) {
        cout<<"successful"<<endl;
        return new Node(name, newUfid);
    }else {
        int nodeID = stoi(node->ufid);
        //recursively go through left and right subtrees searching for empty location to place node.
        if (newID < nodeID) {
            node->left = insertHelper(node->left, name, newUfid);
        }
        else {
            node->right = insertHelper(node->right, name, newUfid);
        }
    }
    // Update height of the current node
    height(node);

    //if right heavy...
    if(balanceFactor(node)<-1) {
        //if tree's right subtree is left heavy...
        if (balanceFactor(node->right) > 0) {
            //Perform Right Left rotation
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
            //Just perform Left rotation
            return rotateLeft(node);
    }

    //if left heavy
    else if(balanceFactor(node)>1) {
        //if tree's left subtree is right heavy...
        if (balanceFactor(node->left) < 0) {
            //Perform Left Right rotation
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        } else {
            //Just perform Right rotation
            return rotateRight(node);
        }

    }

    return node;
}

//CommandInput helps with interpreting and using commands
void MyAVLTree::commandInput(string line) {

    // Read the input line
    istringstream in(line);

    //first thing in input line is always command
        string command;
        in >> command;

        //if command is insert...
        if (command == "insert") {

            string name;
            string ufid;
            string space;
            char quote;

            //get rid of the quote
            in >> quote;

            //read in name here
            getline(in, name, '"');

            //read in ufid here
            in >> ufid;

            //name and id requirements with regex!
            //names are only letters and spaces.
            //IDs are only 8 numbers
            regex nameRequirements("^[a-zA-Z ]+$");
            regex idRequirements("^[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]$");

            if (!regex_match(name, nameRequirements)) {
                cout << "unsuccessful" << endl;
                return;
            }

            if (!regex_match(ufid, idRequirements)) {
                cout << "unsuccessful" << endl;
                return;
            }

            //insert the name and id
            insert(name, ufid);

            //for print commands just call their corresponding function
        } else if (command == "printInorder") {
            printInorder();
        } else if (command == "printPreorder") {
            printPreorder();
        } else if (command == "printPostorder") {
            printPostorder();
        }
        //if command is remove...
        else if (command == "remove") {
            string ufid;

            //read in UFID
            in >> ufid;

            //make sure the ID follows the requirements of being 8 digits long
            regex idRequirements("^[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]$");

            if (!regex_match(ufid, idRequirements)) {
                cout << "unsuccessful" << endl;
                return;
            }

            //call remove
            remove(ufid);

        } else if (command == "printLevelCount") { //prints level count
            printLevelCount();
        } else if (command == "search") {
            string ufid;
            string name;
            string input;

            //read in input (ambiguous because it could be id or name)
            in >> input;

            //make sure the ID follows the requirements of being 8 digits long
            regex idRequirements("^[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]$");

            //if the input equals the id requirements, then it is considered a number and you can call searchID
            if (regex_match(input, idRequirements)) {
                ufid = input;
                searchID(ufid);
            }else{
                //otherwise, we consider it a name!
                name = input;

                //BUT if the first character of this "name" is not a quotation mark, it is invalid input and therefore unsuccessful
                if(name[0] != '"'){
                    cout<<"unsuccessful"<<endl;
                    return;
                }

                //get rid of the quotation marks at the start and end of the name. then call searchName
                name.erase(0,1);
                name.erase(name.length()-1, 1);
                searchName(name);
            }

        } else if (command == "removeInorder") {
            int n;

            //read in n here
            in >> n;

            removeInorder(n); //call removeInorder
        }else{
            //any other commands will not work
            cout<<"unsuccessful"<<endl;
            return;
        }


}

//my destructor calls destructorHelper
MyAVLTree::~MyAVLTree() {
    destructorHelper(root);
}

void MyAVLTree::destructorHelper(Node *node) {

    //when the tree is empty, stop removing
    if(node==nullptr) {
        return;
    }

    //continue removing nodes recursively from left subtree
    if(node->left != nullptr){
        destructorHelper(node->left);
    }

    //continue removing nodes recursively from right subtree
    if(node->right != nullptr){
        destructorHelper(node->right);
    }

    //delete the leftover node
    delete node;

}

//thank you for reading!
