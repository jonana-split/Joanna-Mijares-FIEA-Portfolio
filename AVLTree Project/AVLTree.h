#ifndef PROJECT1_AVLTREE_H
#define PROJECT1_AVLTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

//Joanna Mijares

//Citation: CREDIT TO PWPT SLIDES 4-Balanced Trees slide 26

//Creating node struct
struct Node {
public:
    string name;
    string ufid;
    int n;
    Node *left;
    Node *right;
    Node* root;
    Node(string name, string ufid) : name(name), ufid(ufid), left(nullptr), right(nullptr) {}
};

//My AVL Tree class, creates AVL trees and all of the functions needed for this assignment
//anything that deals directly with the root or nodes is kept private
class MyAVLTree {
private:
    Node* root;
    Node* insertHelper(Node* root, string name, string ufid);
    Node* removeHelper(Node*root, string ufid);
    Node* searchIDHelper(Node* root, string ufid, vector<string>& nameList);
    void searchNameHelper(Node* root, string name, vector<string>& ufidList);
    void removeInorderHelper(Node* root, int& n);
    void inorderIDHelper(Node* node, vector<string>& ufidResults) const;
    void inorderHelper(Node* node, vector<string>& results) const;
    void preorderHelper(Node* node, vector<string>& results) const;
    void postorderHelper(Node* node, vector<string>& results) const;
    void levelCountHelper(Node* node) const;
    int height(Node* root) const;
    int treeSizeHelper(Node* root) const;
    int balanceFactor(Node* root);
    Node* rotateRight(Node* root);
    Node* rotateLeft(Node* root);
    void destructorHelper(Node* node);

public:
    Node* insert(string name, string ufid);
    Node* remove(string ufid);
    int treeSize() const;
    void searchID(string ufid);
    void searchName(string name);
    void removeInorder(int n);
    void printLevelCount();
    void printInorder() const;
    void printPreorder() const;
    void printPostorder() const;
    void commandInput(string command);
    MyAVLTree() : root(nullptr) {}
    ~MyAVLTree();


};

#endif //PROJECT1_AVLTREE_H


