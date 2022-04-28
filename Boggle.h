#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:

    //Function: Default constructor
    //Pre: Dictionary is initially empty
    //Post: Loaded words from dictionary file into dict and initialising board and visited matrix
    Boggle();  // load "dictionary.txt" into dict

    //Function: Parameterized constructor, loads words from filename into dictionary
    //Pre: Dictionary is initially empty
    //Post: Loaded words from the file and initialising board and visited matrix
    explicit Boggle(string filename);  // load filename into dict

    //Function: Sets the values global variable board matrix
    //Pre: board variable values is initially empty strings
    //Post: board variable values are updated
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

    //Function: Solves the board using recursive backtracking approach
    //Pre: board is initialized
    //Post: Traverses the entire board and adds words to the wordsFound dictionary. Prints into terminal or writes to file depending on ostream parameter
    void SolveBoard(bool printBoard, ostream& output);

    //Function: Calls the SaveDictionary method in the wordsFound dictionary
    //Pre: The file initially doesn't contain the words
    //Post: Uses a SaveDictionaryHelper method which iterates through the board and converts the index values into character
    void SaveSolve(string filename);   // Saves all the words from the last solve.

    Dictionary GetDictionary();
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    //Prints the board
    void PrintBoard(ostream& output);

    //Used by SolveBoard for recursive backtracking approach
    void SolveBoardHelper(int rowPos, int colPos, string board[4][4], Dictionary& dict, Dictionary& wordsFound, int steps[4][4], int stepCount, string word, bool printBoard, ostream &output);
};

#endif
