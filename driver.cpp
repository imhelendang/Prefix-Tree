#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// =======================================================================================================================================================
// = Programmed by: Nika Douri and Jade Tran
// = Assingment:    Problem Set 2: String Data Structures - Problem 1: An old Google interview question
// = Class:         CS1D
// = Section:       TTh - 11:30am - 1:50pm
// = Due date:      Nov 11 2021
// =======================================================================================================================================================
// = Problem:       You are given a collection of strings w₁, w₂, ..., wₖ whose combined total length is n. 
// =                Design an O(n) - time algorithm that determines whether any of these strings 
// =                    are prefixes of one another. 
// =                As usual, argue that your algorithm is correct and meets this runtime bound.
// =======================================================================================================================================================
// = Algorithm:     The approach for this problem is using TRIE. The tree will contain 26 elements (including root) as 26 alphabet characters
// =                    and a boolean variable which will be marked 'true' when the current character is in leaf node (end of word).
// = To compile:    g++ -o driver driver.cpp  
// = To run:        ./run
// =======================================================================================================================================================
// = Sample output:
//                  = Welcome! This program is an implementation of An Old Google Interview Question..
//                  = The given strings are: cat, catnip, catnap, catch, catcher, cater, caterpillar, catfish, catfish!
//                  = (cat) is a prefix of the other words!
// =======================================================================================================================================================
// = REFERENCE:     geeksforgeeks - Trie | (Insert and Search) by Venkateswara Rao Sanaka
// =                https://www.geeksforgeeks.org/trie-insert-and-search/
// =======================================================================================================================================================

// GLOBAL CONSTANT variable
const int ALPHA = 26;
 
// Data structure for TRIE node
struct pref_tree {

    // an array of pointers type struct point to next level trie nodes.
    struct pref_tree *link[ALPHA];
 
    // is_word is true if the node represents a complete word (works as the notation of $)
    // use to denote a leaf node
    bool is_word;
};
 
// Base case: the node is empty
// Create a new node and initialize to NULL, is_word is false (not a word)
struct pref_tree *new_node()
{
    pref_tree *node =  new pref_tree;

    for (int i = 0; i < ALPHA; i++)
        node->link[i] = NULL;
 
    node->is_word = false;      
    return node;
}
 
// If the 'letter' doesn't exist in the tree, inserts key into trie
void add(pref_tree *root, string newWord) {

    pref_tree *node = root;
    for (int i = 0; i < newWord.length(); i++) {

        int index = newWord[i] - 'a';               // Find index for the new character of "key" in children[]
        if (node->link[index] == NULL) {                   // If the node is empty -> create a new node
            node->link[index] = new_node();
        }
        node = node->link[index];
    }

    // mark $ - the leaf node --> end of word
    node->is_word = true;
    return;
}

// Deallocate all the nodes
void delete_trie(pref_tree* root){
   
   for(int i=0; i < ALPHA; i++) {
    if(root->link[i]!=NULL)
     delete_trie(root->link[i]);
   }

   delete root;
   root = NULL;
}

 

// Driver
int main() {

    cout << "= Welcome! This program is an implementation of An Old Google Interview Question..\n";
    // List of strings
    string list[] = {"cat", "catnip", "catnap", "catch", "catcher", "cater", "caterpillar", "catfish"};
    int k = sizeof(list)/sizeof(list[0]); // k here is number of elements in array

    // Output all the strings nicelty
    cout << "= The given strings are:";
    for (int i = 0; i < k; i++) {

        cout << list[i] << ", ";
        if( i == k-1 )
            cout << list[i] << "!\n";
    }
 
    struct pref_tree *root = new_node(); // Create a new node as the TRIE is currently empty
 
    // Construct the prefix TRIE
    // Conditions: if the current string is prefix of the following string, then add to the prefix tree
    //             other wise, move on to the next pair.
    for (int i = 0; i < k - 1; i++) {

        // can't be a prefix if the length of the current string is equal or grater than the other string
        if(list[i].length() < list[i+1].length()) {  
            if(list[i+1].rfind(list[i], 0) == 0) {
                add(root, list[i]);
                cout << "= (" << list[i] << ") is a prefix of one or more strings in the array!\n";
            }
        }        
    }

    // Clean up
    delete_trie(root); 

    // Terminating the program
    return 0;
}


