#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int NUM_CHARS = 26;

class DictionaryError{
public:
    explicit DictionaryError(string msg) {
        this->msg = msg;
    }
    string Msg(){
        return msg;  // returns king of flavor
    }
private:
    string msg;
};

class Dictionary
{

public:
    //Function: Default constructor
    //Pre: -
    //Post: Initialising root node and setting numWords variable to 0.
    Dictionary();

    //Function: Destructor
    ~Dictionary();  // I will not require this

    //Function: Copy constructor
    //Pre: otherDict parameter must be valid
    //Post: Clones the dictionary from otherDict into current dictionary
    Dictionary(const Dictionary& otherDict);    // copy constructor


    //Function: Parameterized constructor
    //Pre: Filename must be valid
    //Post: Loads words from file into dictionary
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.

    //Function: Operator overloading of "equal to" sign
    //Pre: CopyOther function must be defined
    //Post: Uses copy other function to copy all contents of otherDict to this.
    Dictionary& operator=(const Dictionary& otherDict);

    //Function: Loads all words in filename to dictionary
    //Pre: Dictionary must be initialized, filename must be valid
    //Post: Adds all words in file to dictionary
    void LoadDictionaryFile(string filename);

    //Function: Writes words in dictionary to file
    //Pre: Dictionary must be initialized, filename must be valid
    //Post: Uses the SaveDictionary helper method to write words in dictionary to file
    void SaveDictionaryFile(string filename);

    //Function: Adds a word to the dictionary
    //Pre: Word must be valid and dictionary must be initialized
    //Post: The given word is added into the dictionary
    void AddWord(string word);

    //Function: Destroys all nodes in the tree
    //Pre: Dict should be valid
    //Post:Uses destroyHelper method and deletes all nodes in the tree
    void MakeEmpty();

    //Function: Checks if given word is a word
    //Pre: Word should be valid
    //Post: Returns true if IsWord at the last letter of the word is true
    bool IsWord(string word);

    //Function: Checks if given word is prefix
    //Pre: Word should be valid
    //Post: Returns true if isWord at last letter of the given word is false
    bool IsPrefix(string word);

    //Function: Returns the count of number of words in the dictionary
    //Pre: Dictionary must be valid
    //Post: Returns the value of numWords
    int WordCount();

private:

    class Node {
    public:
        // Your node structure here.
        // You can also use a struct if you like.

        // It is strongly recommended you create a constructor
        // to set default values
        struct Node *children[NUM_CHARS]; //each index represents a character
        bool isWord;
        //create object of Node
        Node(){
            isWord=false;
            for(int i=0;i<NUM_CHARS;++i){ //Make all nodes to null
                children[i]=NULL;
            }
        }
    };

    Node* root;
    int numWords;

    // This function is used by the
    // copy constructor and the assignment operator.
    void copyOther(const Dictionary& otherDict);

    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.
    //helper method for MakeEmpty
    void destroyHelper(Node* thisTree);

    //helper method for copy constructor
    void copyHelper(Node*& thisTree, Node* otherTree);

    //helper method for save dictionary
    void SaveDictionaryHelper(Node* curr, int iterator, string currPrefix, ofstream& outFile);
};

#endif
