#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include "AdjacencyList.h"

using namespace std;

//Joanna Mijares

//referenced my own AVL project AVLTree.cpp and main.cpp files specifically for reading in and parsing the input string in testing
//Citation: Used the StackOverflow link below as reference for extracting a string from void function's output provided in Q14 of the Project 1 FAQ
//https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout

void AdjacencyList::parseInput(string str) {

    //this function acts like my main.cpp but for testing

    AdjacencyList adjacencyList; //create a list

    istringstream in(str); //

    int no_of_lines;
    int power_iterations;

    //the first 2 items in the stringstream are the number of lines and the num of power iterations
    in >> no_of_lines >> power_iterations;

    string from;
    string to;

    //iterate through all the lines and take in the "from" and "to" values for each website
    for (int i = 0; i < no_of_lines; i++) {
        in >> from >> to;
        adjacencyList.insertWebsite(from, to); //insert website on the list
    }

    //calculate pagerank
    adjacencyList.PageRank(power_iterations);

}

//Citation: referenced some functions/ structure from my Programming Assignment 8
//Citation: referenced class slides 8a - Graph Terminology and Implementation.pdf, slides 58, 56
void AdjacencyList::PageRank(int n){

    float rank = 0;

    //the initial rank when there's only 1 power iteration is just 1/number of sites
    //add it to the ranks map
    for(int i=0; i<websites.size(); i++) {
        rank = 1.0f/numSites;
        ranks[websites[i]] = rank;
    }

    //if there's more than 1 power iteration...
    if(n>1){
        //for the number of power iterations over 1...
        for(int i=1; i<n; i++){
            //create a temporary rank map to hold the ranks so that the initial values don't affect calculations
            map<string, float> ranksTemp = ranks;
            //for all the vertices in the adjacency list...
            for(auto it = adjList.begin(); it != adjList.end(); it++){
                //set the temporary rank of the site we're looking at to 0 so the calculations don't get messed up
                ranksTemp[it->first] = 0;
                //for all vectors/ values associated with the website key we're looking at
                for(auto iter = it->second.begin(); iter != it->second.end(); iter++) {
                    if(outDegrees[iter->first] == 0){
                        //if there's no outdegrees the rank stays 0
                        ranksTemp[it->first] = 0;
                    }else {
                        //otherwise, the rank is equal to the sum of the ranks pointing to the key divided by the outdegree of the website pointing to the key
                        ranksTemp[it->first] += ranks[iter->first] / outDegrees[iter->first];
                    }
                }
            }
            //transfer ranksTemp info to ranks
            ranks = ranksTemp;
        }
    }

    //print out all the websites and ranks, up to 2 decimal points
    for(int i=0; i<websites.size(); i++){
        cout << websites[i] << " " << fixed <<setprecision(2)<< ranks[websites[i]] <<"\n";
    }
}

//referenced class slides 8a - Graph Terminology and Implementation.pdf, slide 56
void AdjacencyList::insertWebsite(string from, string to){

    //push all websites to a vector for easy access later
    if(find(websites.begin(), websites.end(), from) == websites.end()){
        websites.push_back(from);
    }
    if(find(websites.begin(), websites.end(), to) == websites.end()){
        websites.push_back(to);
    }

    //sort the vector so it prints in order later
    sort(websites.begin(), websites.end());

    //easy way to get the total number of websites
    numSites = websites.size();

    //call getOutdegree to calculate the outdegree of the "from" website
    int out = getOutdegree(from);

    //if from is not in the "to" keys, make it a key with an empty vector associated
    //this was a big roadblock for me! I got it in the end though :)
    if (adjList.find(from) == adjList.end()) {
        vector<pair<string, float>> empty;
        adjList[from] = empty;
    }

    //create a new pair out of the "from" value and 1/the outdegree of the "from" value
    //to be quite honest I probably could have just used a vector of strings instead of a vector of pairs, but I just kept going with what I was working with from the start
    pair<string, float> newPair = {from, 1.0f/out};

    //push back the "to" key and "from" value to the adjacency list
    adjList[to].push_back(newPair);
}

//calculate the outDegree of a website
float AdjacencyList::getOutdegree(string from){
    //initial outdegree is 0
    int out = 0;
    //if outdegree is found in the outDegrees list associated with the "from" value then the existing outDegree is updated
    if (outDegrees.find(from) != outDegrees.end()) {
        out = outDegrees[from];
    }
    //add 1 to the outdegree
    out += 1;
    //update the outdegree map
    outDegrees[from] = out;
    return out;
}



