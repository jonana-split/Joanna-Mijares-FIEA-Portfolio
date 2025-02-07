#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//Joanna Mijares

class AdjacencyList {
private:
    map<string, vector<pair<string,float>>> adjList;
    map<string, int> outDegrees;
    vector<string> websites;
    map<string, float> ranks;
    float numSites = 0;


public:
    void PageRank(int n);
    void parseInput(string str);
    void insertWebsite(string from, string to);
    float getOutdegree(string from);
};

