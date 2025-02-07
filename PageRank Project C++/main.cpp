#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "AdjacencyList.h"

using namespace std;

//Joanna Mijares

int main() {
    int no_of_lines;
    int power_iterations;
    string from;
    string to;

    //initialize your list
    AdjacencyList adjacencyList;

    //take in the number of lines and num of power iterations
    cin >> no_of_lines >> power_iterations;

    //iterate for the number of lines
    for (int i = 0; i < no_of_lines; i++) {
        //take in the "from" and "to" values
        cin >> from >> to;
        //insert the websites
        adjacencyList.insertWebsite(from, to);
    }

    //take the page rank, and it's done :)
    adjacencyList.PageRank(power_iterations);

}
