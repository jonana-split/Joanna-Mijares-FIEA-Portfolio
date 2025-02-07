#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include "AdjacencyList.h"

using namespace std;

//Joanna Mijares

//referenced my own AVL project AVLTree.cpp and main.cpp files specifically for reading in and parsing the input string in testing
//From AVL Project Citations: Used the StackOverflow link below as reference for extracting a string from void function's output provided in Q14 of the Project 1 FAQ
//https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout

//basic provided test case, to explain my testing process :)
TEST_CASE("Example PageRank Output Test", "Example"){

    //establish the input string
    string input = R"(7 2
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com)";

    //establish the expected output string
    string expectedOutput = R"(facebook.com 0.20
gmail.com 0.20
google.com 0.10
maps.com 0.30
ufl.edu 0.20
)";

    //initialize a list
    AdjacencyList g;

    //used the same method as on my AVL Tree project
    //create a string stream, create a buffer to store all outputs.
    stringstream actualOutput;
    streambuf *actualOutputStream = cout.rdbuf();
    cout.rdbuf(actualOutput.rdbuf()); //everything after this is stored in the buffer

    //call parseInput function
    g.parseInput(input);

    cout.rdbuf(actualOutputStream); //stop storing stuff in the buffer

    //the output needs to be the same as the expected output
    REQUIRE(actualOutput.str() == expectedOutput);
}


//Unique Test 1
//99 lines are inputted (20 websites) to test if it can handle a large number of websites
TEST_CASE("Large number of insertions test", "Large Num"){

    string input = R"(99 3
mozilla.org facebook.com
weather.com ufl.edu
facebook.com apple.com
python.org mozilla.org
apple.com mozilla.org
getbootstrap.com zoom.us
facebook.com chase.com
microsoft.com openai.com
openai.com apple.com
disney.com apple.com
disney.com getbootstrap.com
microsoft.com python.org
weather.com getbootstrap.com
facebook.com google.com
ufl.edu samsung.com
wikipedia.org zoom.us
ufl.edu microsoft.com
weather.com instagram.com
youtube.com stackoverflow.com
openai.com roblox.com
microsoft.com samsung.com
google.com openai.com
stackoverflow.com python.org
youtube.com python.org
youtube.com facebook.com
getbootstrap.com stackoverflow.com
roblox.com ufl.edu
apple.com wikipedia.org
aman.com instagram.com
ufl.edu instagram.com
youtube.com wikipedia.org
apple.com instagram.com
zoom.us aman.com
roblox.com stackoverflow.com
ufl.edu weather.com
instagram.com weather.com
aman.com youtube.com
google.com microsoft.com
mozilla.org microsoft.com
mozilla.org chase.com
google.com youtube.com
chase.com samsung.com
wikipedia.org chase.com
mozilla.org roblox.com
instagram.com chase.com
roblox.com chase.com
openai.com youtube.com
weather.com facebook.com
mozilla.org zoom.us
roblox.com python.org
zoom.us getbootstrap.com
zoom.us microsoft.com
chase.com youtube.com
python.org zoom.us
samsung.com python.org
microsoft.com mozilla.org
apple.com aman.com
python.org weather.com
aman.com stackoverflow.com
wikipedia.org weather.com
stackoverflow.com microsoft.com
chase.com microsoft.com
apple.com ufl.edu
mozilla.org stackoverflow.com
ufl.edu mozilla.org
disney.com facebook.com
youtube.com google.com
google.com stackoverflow.com
stackoverflow.com mozilla.org
chase.com getbootstrap.com
disney.com python.org
facebook.com wikipedia.org
microsoft.com facebook.com
microsoft.com instagram.com
chase.com apple.com
zoom.us weather.com
instagram.com stackoverflow.com
ufl.edu google.com
samsung.com roblox.com
youtube.com disney.com
stackoverflow.com google.com
wikipedia.org samsung.com
aman.com samsung.com
getbootstrap.com roblox.com
openai.com aman.com
weather.com stackoverflow.com
wikipedia.org youtube.com
getbootstrap.com chase.com
wikipedia.org apple.com
google.com getbootstrap.com
ufl.edu python.org
samsung.com ufl.edu
facebook.com stackoverflow.com
weather.com wikipedia.org
mozilla.org youtube.com
python.org google.com
ufl.edu chase.com
python.org getbootstrap.com
python.org microsoft.com)";

    string expectedOutput = R"(aman.com 0.02
apple.com 0.04
chase.com 0.07
disney.com 0.01
facebook.com 0.04
getbootstrap.com 0.06
google.com 0.06
instagram.com 0.05
microsoft.com 0.08
mozilla.org 0.07
openai.com 0.02
python.org 0.08
roblox.com 0.04
samsung.com 0.05
stackoverflow.com 0.09
ufl.edu 0.05
weather.com 0.05
wikipedia.org 0.04
youtube.com 0.05
zoom.us 0.04
)";

    AdjacencyList g;

    stringstream actualOutput;
    streambuf *actualOutputStream = cout.rdbuf();
    cout.rdbuf(actualOutput.rdbuf());

    g.parseInput(input);

    cout.rdbuf(actualOutputStream);

    REQUIRE(actualOutput.str() == expectedOutput);
}

//Unique Test 2
//testing a small graph with one website only having 1 indegree and the other only having 1 outdegree
TEST_CASE("Small number of insertions test", "Small num"){

    string input = R"(1 10
joanna mijares)";

    string expectedOutput = R"(joanna 0.00
mijares 0.00
)";

    AdjacencyList g;

    stringstream actualOutput;
    streambuf *actualOutputStream = cout.rdbuf();
    cout.rdbuf(actualOutput.rdbuf());

    g.parseInput(input);

    cout.rdbuf(actualOutputStream);

    REQUIRE(actualOutput.str() == expectedOutput);
}

//Unique Test 3
//testing only 1 power iteration. all values should be the same since it's the initial one
TEST_CASE("Only 1 power iteration", "One Power"){

    string input = R"(10 1
openai.com disney.com
aman.com samsung.com
aman.com weather.com
weather.com microsoft.com
openai.com microsoft.com
youtube.com samsung.com
microsoft.com wikipedia.org
wikipedia.org disney.com
disney.com openai.com
openai.com samsung.com
)";

    string expectedOutput = R"(aman.com 0.12
disney.com 0.12
microsoft.com 0.12
openai.com 0.12
samsung.com 0.12
weather.com 0.12
wikipedia.org 0.12
youtube.com 0.12
)";

    AdjacencyList g;

    stringstream actualOutput;
    streambuf *actualOutputStream = cout.rdbuf();
    cout.rdbuf(actualOutput.rdbuf());

    g.parseInput(input);

    cout.rdbuf(actualOutputStream);

    REQUIRE(actualOutput.str() == expectedOutput);
}

//Unique Test 4
//testing a large number of power iterations. I test 5000 iterations just to be sure my code can handle all those calculations correctly
TEST_CASE("Large Number of Powers", "Many Powers"){

    string input = R"(7 5000
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com
)";

    string expectedOutput = R"(facebook.com 0.24
gmail.com 0.18
google.com 0.12
maps.com 0.24
ufl.edu 0.24
)";

    AdjacencyList g;

    stringstream actualOutput;
    streambuf *actualOutputStream = cout.rdbuf();
    cout.rdbuf(actualOutput.rdbuf());

    g.parseInput(input);

    cout.rdbuf(actualOutputStream);

    REQUIRE(actualOutput.str() == expectedOutput);
}


//Unique Test 5
//testing only one origin website with no indegrees and 10 outdegrees (everything should be 0)
TEST_CASE("Only one 'origin' website", "origin"){

    string input = R"(10 3
google.com gmail.com
google.com maps.com
google.com ufl.edu
google.com facebook.com
google.com meow.com
google.com joanna.com
google.com dsa.com
google.com computer.com
google.com cise.com
google.com parsnip.com
)";

    string expectedOutput = R"(cise.com 0.00
computer.com 0.00
dsa.com 0.00
facebook.com 0.00
gmail.com 0.00
google.com 0.00
joanna.com 0.00
maps.com 0.00
meow.com 0.00
parsnip.com 0.00
ufl.edu 0.00
)";

    AdjacencyList g;

    stringstream actualOutput;
    streambuf *actualOutputStream = cout.rdbuf();
    cout.rdbuf(actualOutput.rdbuf());

    g.parseInput(input);

    cout.rdbuf(actualOutputStream);

    REQUIRE(actualOutput.str() == expectedOutput);
}

//Unique Test 6
//testing only one "to" website with 10 indegrees and no outdegrees. All the other sites just have 1 in degree (everything should be 0)
TEST_CASE("Only one 'to' website", "to"){

    string input = R"(10 3
gmail.com google.com
maps.com google.com
ufl.edu google.com
facebook.com google.com
meow.com google.com
joanna.com google.com
dsa.com google.com
computer.com google.com
cise.com google.com
parsnip.com google.com
)";

    string expectedOutput = R"(cise.com 0.00
computer.com 0.00
dsa.com 0.00
facebook.com 0.00
gmail.com 0.00
google.com 0.00
joanna.com 0.00
maps.com 0.00
meow.com 0.00
parsnip.com 0.00
ufl.edu 0.00
)";

    AdjacencyList g;

    stringstream actualOutput;
    streambuf *actualOutputStream = cout.rdbuf();
    cout.rdbuf(actualOutput.rdbuf());

    g.parseInput(input);

    cout.rdbuf(actualOutputStream);

    REQUIRE(actualOutput.str() == expectedOutput);
}

//Unique Test 7
//just testing a randomly generated set from the test generator website we were provided
TEST_CASE("Random Test 1", "random"){

    string input = R"(9 7
python.org instagram.com
aman.com getbootstrap.com
zoom.us pcbuildinguf.com
microsoft.com twitter.com
openai.com python.org
aman.com instagram.com
zoom.us roblox.com
instagram.com roblox.com
pcbuildinguf.com getbootstrap.com
)";

    string expectedOutput = R"(aman.com 0.00
getbootstrap.com 0.00
instagram.com 0.00
microsoft.com 0.00
openai.com 0.00
pcbuildinguf.com 0.00
python.org 0.00
roblox.com 0.00
twitter.com 0.00
zoom.us 0.00
)";

    AdjacencyList g;

    stringstream actualOutput;
    streambuf *actualOutputStream = cout.rdbuf();
    cout.rdbuf(actualOutput.rdbuf());

    g.parseInput(input);

    cout.rdbuf(actualOutputStream);

    REQUIRE(actualOutput.str() == expectedOutput);
}

//Unique Test 7
//just testing a randomly generated set from the test generator website we were provided
TEST_CASE("Random Test 2", "random"){

    string input = R"(68 16
pcbuildinguf.com wikipedia.org
samsung.com google.com
instagram.com openai.com
ufl.edu roblox.com
google.com pcbuildinguf.com
stackoverflow.com roblox.com
disney.com samsung.com
zoom.us chase.com
instagram.com facebook.com
pcbuildinguf.com samsung.com
pcbuildinguf.com weather.com
chase.com wikipedia.org
ufl.edu weather.com
zoom.us weather.com
wikipedia.org youtube.com
youtube.com microsoft.com
stackoverflow.com pcbuildinguf.com
instagram.com disney.com
pcbuildinguf.com microsoft.com
roblox.com openai.com
wikipedia.org stackoverflow.com
instagram.com roblox.com
google.com disney.com
roblox.com wikipedia.org
ufl.edu google.com
openai.com wikipedia.org
wikipedia.org weather.com
openai.com google.com
stackoverflow.com zoom.us
aman.com microsoft.com
pcbuildinguf.com python.org
ufl.edu chase.com
disney.com openai.com
stackoverflow.com google.com
google.com chase.com
weather.com facebook.com
samsung.com python.org
instagram.com google.com
roblox.com stackoverflow.com
roblox.com python.org
chase.com zoom.us
roblox.com chase.com
google.com ufl.edu
microsoft.com youtube.com
python.org pcbuildinguf.com
python.org stackoverflow.com
chase.com pcbuildinguf.com
microsoft.com stackoverflow.com
samsung.com disney.com
facebook.com microsoft.com
google.com microsoft.com
facebook.com chase.com
microsoft.com zoom.us
stackoverflow.com facebook.com
microsoft.com samsung.com
youtube.com wikipedia.org
samsung.com facebook.com
aman.com google.com
disney.com microsoft.com
weather.com wikipedia.org
disney.com ufl.edu
ufl.edu microsoft.com
openai.com weather.com
disney.com weather.com
weather.com ufl.edu
wikipedia.org roblox.com
ufl.edu stackoverflow.com
instagram.com ufl.edu
)";

    string expectedOutput = R"(aman.com 0.00
chase.com 0.09
disney.com 0.02
facebook.com 0.06
google.com 0.04
instagram.com 0.00
microsoft.com 0.09
openai.com 0.01
pcbuildinguf.com 0.07
python.org 0.04
roblox.com 0.06
samsung.com 0.04
stackoverflow.com 0.09
ufl.edu 0.04
weather.com 0.10
wikipedia.org 0.12
youtube.com 0.05
zoom.us 0.07
)";

    AdjacencyList g;

    stringstream actualOutput;
    streambuf *actualOutputStream = cout.rdbuf();
    cout.rdbuf(actualOutput.rdbuf());

    g.parseInput(input);

    cout.rdbuf(actualOutputStream);

    REQUIRE(actualOutput.str() == expectedOutput);
}
