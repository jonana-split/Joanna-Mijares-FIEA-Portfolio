/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include "AVLTree.h"
#include "AVLTree.cpp"
#include <sstream>
using namespace std;

//Joanna Mijares

// you must write 5 unique, meaningful tests for credit on the testing portion of this project!

//Citation: Used the StackOverflow link below as reference for extracting a string from void function's output provided in Q14 of the Project 1 FAQ
//https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout

TEST_CASE("Test 1: Incorrect Commands", "command_tests"){

    MyAVLTree tree; //create a tree

    SECTION("incorrect_command") {

        //testing if incorrect command outputs unsuccessful
        stringstream outputWrongInsert; //create a string stream
        streambuf *outputWrongInsertStream = cout.rdbuf(); //create a buffer to store the printed outputs
        cout.rdbuf(outputWrongInsert.rdbuf()); //the output after this point is being stored in the buffer

        tree.commandInput("inserrt \"one\" 11111111"); //incorrectly spell a command

        cout.rdbuf(outputWrongInsertStream); //output is no longer being stored in buffer

        //the output must be "unsuccessful"
        REQUIRE(outputWrongInsert.str() == "unsuccessful\n");

    }

    SECTION("incorrect_name") {

        //testing if incorrect name outputs unsuccessful
        stringstream outputWrongName;
        streambuf *outputWrongNameStream = cout.rdbuf();
        cout.rdbuf(outputWrongName.rdbuf());

        tree.commandInput("insert 123 11111111"); //insert a number rather than a name

        cout.rdbuf(outputWrongNameStream);

        //the output must be "unsuccessful"
        REQUIRE(outputWrongName.str() == "unsuccessful\n");
    }

    SECTION("incorrect_ufid") {

        //testing if incorrect ufid outputs unsuccessful
        stringstream outputWrongUfid;
        streambuf *outputWrongUfidStream = cout.rdbuf();
        cout.rdbuf(outputWrongUfid.rdbuf());


        tree.commandInput("insert \"Joanna\" \"Mijares\""); //inserting a name as the ufid instead of a number

        cout.rdbuf(outputWrongUfidStream);

        //the output must be "unsuccessful"
        REQUIRE(outputWrongUfid.str() == "unsuccessful\n");

    }

    SECTION("incorrect_search") {

        //insert "apple" to test search
        tree.insert("apple", "12345678");

        //testing if incorrect search outputs unsuccessful
        stringstream outputWrongSearch;
        streambuf *outputWrongSearchStream = cout.rdbuf();
        cout.rdbuf(outputWrongSearch.rdbuf());

        tree.commandInput("search apple"); //attempting to search for a name without quotes

        cout.rdbuf(outputWrongSearchStream);

        //the output must be "unsuccessful"
        REQUIRE(outputWrongSearch.str() == "unsuccessful\n");

    }

    SECTION("incorrect_remove") {

        //insert ufid 22222222 to test search
        tree.insert("apple", "22222222");

        //testing if incorrect remove outputs unsuccessful
        stringstream outputWrongRemove;
        streambuf *outputWrongRemoveStream = cout.rdbuf();
        cout.rdbuf(outputWrongRemove.rdbuf());

        tree.commandInput("remove \"22222222\""); //remove attempt to remove something in quotation marks

        cout.rdbuf(outputWrongRemoveStream);

        //the output must be "unsuccessful"
        REQUIRE(outputWrongRemove.str() == "unsuccessful\n");

    }

    SECTION("incorrect_name2") {

        //testing if incorrect name outputs unsuccessful
        stringstream outputWrongNameTwoRemove;
        streambuf *outputWrongNameTwoRemoveStream = cout.rdbuf();
        cout.rdbuf(outputWrongNameTwoRemove.rdbuf());

        tree.commandInput("insert \"J0anna_Mijares\" 11111111"); //insert a name with a number and underscore

        cout.rdbuf(outputWrongNameTwoRemoveStream);

        //the output must be "unsuccessful"
        REQUIRE(outputWrongNameTwoRemove.str() == "unsuccessful\n");

    }

}


TEST_CASE("Test 2- Edge Cases", "edge_cases") {

    MyAVLTree tree; //create a tree

    SECTION("nonexistent_ufid") {

        //insert 3 nodes
        tree.commandInput("insert \"one\" 11111111");
        tree.commandInput("insert \"two\" 22222222");
        tree.commandInput("insert \"three\" 33333333");

        //testing if removing nonexistent ufid outputs unsuccessful
        stringstream outputRemoveNonexistent;
        streambuf *outputRemoveNonexistentStream = cout.rdbuf();
        cout.rdbuf(outputRemoveNonexistent.rdbuf());

        tree.commandInput("remove 44444444"); //remove a valid ID that doesn't exist

        cout.rdbuf(outputRemoveNonexistentStream);

        //the output must be "unsuccessful"
        REQUIRE(outputRemoveNonexistent.str() == "unsuccessful\n");

    }

    SECTION("nonexistent_search") {

        //insert 3 nodes
        tree.commandInput("insert \"one\" 11111111");
        tree.commandInput("insert \"two\" 22222222");
        tree.commandInput("insert \"three\" 33333333");

        //testing if nonexistent search outputs unsuccessful
        stringstream outputSearchNonexistent;
        streambuf *outputSearchNonexistentStream = cout.rdbuf();
        cout.rdbuf(outputSearchNonexistent.rdbuf());

        tree.commandInput("search 44444444"); //search for valid ID that doesn't exist

        cout.rdbuf(outputSearchNonexistentStream);

        //the output must be "unsuccessful"
        REQUIRE(outputSearchNonexistent.str() == "unsuccessful\n");

    }

    SECTION("nonexistent_removeInorder") {

        //insert 3 nodes
        tree.commandInput("insert \"one\" 11111111");
        tree.commandInput("insert \"two\" 22222222");
        tree.commandInput("insert \"three\" 33333333");

        //testing if nonexistent remove inorder index outputs unsuccessful
        stringstream outputIndexNonexistent;
        streambuf *outputIndexNonexistentStream = cout.rdbuf();
        cout.rdbuf(outputIndexNonexistent.rdbuf());

        tree.commandInput("removeInorder 10"); //remove an index that doesn't exist, since there are only 3 objects in the tree

        cout.rdbuf(outputIndexNonexistentStream);

        //the output must be "unsuccessful"
        REQUIRE(outputIndexNonexistent.str() == "unsuccessful\n");
    }

    SECTION("insert_duplicate") {

        //insert 3 nodes
        tree.commandInput("insert \"one\" 11111111");
        tree.commandInput("insert \"two\" 22222222");
        tree.commandInput("insert \"three\" 33333333");

        //testing if inserting duplicate outputs unsuccessful
        stringstream outputDuplicateInsert;
        streambuf *outputDuplicateInsertStream = cout.rdbuf();
        cout.rdbuf(outputDuplicateInsert.rdbuf());

        tree.commandInput("insert \"one\" 11111111"); //attempt to insert a duplicate node that is already in the tree

        cout.rdbuf(outputDuplicateInsertStream);

        //the output must be "unsuccessful"
        REQUIRE(outputDuplicateInsert.str() == "unsuccessful\n");

    }

    SECTION("remove_only_node") {

        //insert a node
        tree.commandInput("insert \"one\" 11111111");

        //testing if removing only node outputs successful
        stringstream outputDuplicateInsert;
        streambuf *outputDuplicateInsertStream = cout.rdbuf();
        cout.rdbuf(outputDuplicateInsert.rdbuf());

        tree.commandInput("remove 11111111"); //remove the one node

        cout.rdbuf(outputDuplicateInsertStream);

        //the output must be "successful"
        REQUIRE(outputDuplicateInsert.str() == "successful\n");

    }

}

TEST_CASE("Test 3- Rotations", "rotations") {

    MyAVLTree tree; //create a tree
    //printing preorder with a 3 node tree helps see if tree was properly rotated

    SECTION("right") {

        //left-heavy tree
        tree.commandInput("insert \"six\" 66666666");
        tree.commandInput("insert \"four\" 44444444");
        tree.commandInput("insert \"two\" 22222222");

        //testing right-right rotation
        stringstream outputRightRight;
        streambuf *outputRightRightStream = cout.rdbuf();
        cout.rdbuf(outputRightRight.rdbuf());

        tree.commandInput("printPreorder");
        //printing preorder will make it easier to visualize the rotated tree

        cout.rdbuf(outputRightRightStream);

        REQUIRE(outputRightRight.str() == "four, two, six\n"); //expected balanced tree

    }
    SECTION("left") {

    //create right-heavy tree
        tree.commandInput("insert \"two\" 22222222");
        tree.commandInput("insert \"four\" 44444444");
        tree.commandInput("insert \"six\" 66666666");

        //testing left-left rotation
        stringstream outputLeftLeft;
        streambuf* outputLeftLeftStream  = cout.rdbuf();
        cout.rdbuf(outputLeftLeft.rdbuf());

        tree.commandInput("printPreorder");

        cout.rdbuf(outputLeftLeftStream);

        REQUIRE(outputLeftLeft.str() == "four, two, six\n"); //expected balanced tree
    }

    SECTION("left_right") {

        //create tree that goes left then right
        tree.commandInput("insert \"four\" 44444444");
        tree.commandInput("insert \"two\" 22222222");
        tree.commandInput("insert \"three\" 33333333");

        //testing left-right rotation
        stringstream outputLeftRight;
        streambuf *outputLeftRightStream = cout.rdbuf();
        cout.rdbuf(outputLeftRight.rdbuf());

        tree.commandInput("printPreorder");

        cout.rdbuf(outputLeftRightStream);

        REQUIRE(outputLeftRight.str() == "three, two, four\n"); //expected balanced tree
    }

    SECTION("right_left") {

        //create tree that goes right then left
        tree.commandInput("insert \"two\" 22222222");
        tree.commandInput("insert \"four\" 44444444");
        tree.commandInput("insert \"three\" 33333333");

        //testing right-left rotation
        stringstream outputRightLeft;
        streambuf *outputRightLeftStream = cout.rdbuf();
        cout.rdbuf(outputRightLeft.rdbuf());

        tree.commandInput("printPreorder");

        cout.rdbuf(outputRightLeftStream);

        REQUIRE(outputRightLeft.str() == "three, two, four\n"); //expected balanced tree

    }
}

TEST_CASE("Test 4- Root Deletion", "deletion_cases") {

    MyAVLTree tree; //create a tree

    tree.commandInput("insert \"one\" 11111111");
    tree.commandInput("insert \"two\" 22222222");
    tree.commandInput("insert \"three\" 33333333");
    tree.commandInput("insert \"four\" 44444444");
    tree.commandInput("insert \"five\" 55555555");
    tree.commandInput("insert \"six\" 66666666");
    tree.commandInput("insert \"seven\" 77777777");
    tree.commandInput("insert \"eight\" 88888888");

    //testing two-node ROOT deletion
    stringstream outputRightLeft;
    streambuf* outputRightLeftStream  = cout.rdbuf();
    cout.rdbuf(outputRightLeft.rdbuf());

    tree.commandInput("remove 44444444"); //remove the node of this large tree

    cout.rdbuf(outputRightLeftStream);

    REQUIRE(outputRightLeft.str() == "successful\n"); //the tree should successfully be able to delete its node

}

TEST_CASE("Test 5- Deletion Cases", "deletion_cases") {

    MyAVLTree tree; //create a tree

    SECTION("2NodeDelete") {

            tree.commandInput("insert \"one\" 11111111");
            tree.commandInput("insert \"two\" 22222222");
            tree.commandInput("insert \"three\" 33333333");
            tree.commandInput("insert \"four\" 44444444");
            tree.commandInput("insert \"five\" 55555555");
            tree.commandInput("insert \"six\" 66666666");
            tree.commandInput("insert \"seven\" 77777777");
            tree.commandInput("insert \"eight\" 88888888");

            //testing two-node root deletion
            stringstream outputTwoNode;
            streambuf *outputTwoNodeStream = cout.rdbuf();
            cout.rdbuf(outputTwoNode.rdbuf());

            tree.commandInput("remove 22222222"); //2 should have 2 children

            cout.rdbuf(outputTwoNodeStream);

            REQUIRE(outputTwoNode.str() == "successful\n"); //this should be a successful deletion
        }

        SECTION("1NodeDelete") {

            tree.commandInput("insert \"one\" 11111111");
            tree.commandInput("insert \"two\" 22222222");
            tree.commandInput("insert \"three\" 33333333");
            tree.commandInput("insert \"four\" 44444444");
            tree.commandInput("insert \"five\" 55555555");
            tree.commandInput("insert \"six\" 66666666");
            tree.commandInput("insert \"seven\" 77777777");
            tree.commandInput("insert \"eight\" 88888888");

            //testing one-node root deletion
            stringstream outputOneNode;
            streambuf *outputOneNodeStream = cout.rdbuf();
            cout.rdbuf(outputOneNode.rdbuf());

            tree.commandInput("remove 77777777"); //7 should have 1 child

            cout.rdbuf(outputOneNodeStream);

            REQUIRE(outputOneNode.str() == "successful\n"); //this should be a successful deletion
        }

        SECTION("0NodeDelete") {

            tree.commandInput("insert \"one\" 11111111");
            tree.commandInput("insert \"two\" 22222222");
            tree.commandInput("insert \"three\" 33333333");
            tree.commandInput("insert \"four\" 44444444");
            tree.commandInput("insert \"five\" 55555555");
            tree.commandInput("insert \"six\" 66666666");
            tree.commandInput("insert \"seven\" 77777777");
            tree.commandInput("insert \"eight\" 88888888");

            //testing zero-node root deletion
            stringstream outputNoNode;
            streambuf *outputNoNodeStream = cout.rdbuf();
            cout.rdbuf(outputNoNode.rdbuf());

            tree.commandInput("remove 33333333"); //3 should have 0 children

            cout.rdbuf(outputNoNodeStream);

            REQUIRE(outputNoNode.str() == "successful\n"); //this should be a successful deletion
        }


}

//credit to provided link of Catch Test Examples onlinegdb for help and reference
//https://www.onlinegdb.com/Ih4XEhD80w
TEST_CASE("Test 6- 100 insertions and 10 removals", "insertion_and_removal_cases") {

    MyAVLTree tree;
    //std::vector<int> expectedOutput, actualOutput;

    std::vector<string> outputPreDeletion, outputAfterDeletion;

    string ufid;

    //for 100 inputs...
    for(int i = 0; i < 100; i++){

        //get a random 8 digit number
            int input = rand() % 60000000 + 20000000;

            //convert integer to string since my UFIDs are strings
            ufid = to_string(input);

            //insert the ufid
            tree.insert("Joanna", ufid);

            //for debugging
            cout<<ufid<<endl;

            outputPreDeletion.push_back(ufid);

    }

    REQUIRE(outputPreDeletion.size() == 100);

    //make sure remove works for 10 removals
    for(int i = 0; i < 10; i++) {

        //remove a random index 1-70 (does not have to be 70 I just did it this way)
        int index = rand() % 70 + 1;
        cout<<index<<endl;

        tree.remove(outputPreDeletion[index]); //remove the ufid at the specified index in the vector
        outputPreDeletion.erase(outputPreDeletion.begin() + index); //erase the object in the vector at the index's position

    }

    //use treeSize function to check the size of the tree after removal
    int treeSizeCheck = tree.treeSize();
    outputAfterDeletion = outputPreDeletion;
    //the size of the tree should match the new vector size after removals from both
    REQUIRE(treeSizeCheck == outputAfterDeletion.size());
    REQUIRE(treeSizeCheck == 90); //make sure 10 nodes were removed

}
 
*/