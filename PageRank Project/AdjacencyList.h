#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//Joanna Mijares

//referenced class slides 8a - Graph Terminology and Implementation.pdf, slide 58
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

