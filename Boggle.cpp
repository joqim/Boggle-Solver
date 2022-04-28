
#include "Dictionary.h"
#include "Boggle.h"

// Your code here
//default constructor
Boggle::Boggle() {
    dict.LoadDictionaryFile("dictionary.txt");

    for (int i = 0; i < BOARD_SIZE; i ++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = "";
        }
    }

    for (int i = 0; i < BOARD_SIZE; i ++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            visited[i][j] = false;
        }
    }

}

//parameterized constructor
Boggle::Boggle(string filename) {
    //loading words in file into dictionary
    dict.LoadDictionaryFile(filename);

    for (int i = 0; i < BOARD_SIZE; i ++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = "";
        }
    }

    for (int i = 0; i < BOARD_SIZE; i ++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            visited[i][j] = 0;
        }
    }
}

//void Boggle::SetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
void Boggle::SetBoard(string (*board)[4]) {
    for (int i = 0; i < BOARD_SIZE; i ++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            this->board[i][j] = board[i][j];
            //this->board[i][j] = "";
        }
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    cout<<"\n Inside SolveBoard "<<printBoard;
    wordsFound.MakeEmpty();

    string word = "";
    int stepCount = 1;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            SolveBoardHelper(r, c, board, dict, wordsFound, visited, stepCount, word, printBoard, output);
        }
    }
}

//helper method for solveboard
void Boggle::SolveBoardHelper(int rowPos,
                              int colPos,
                              string board[4][4],
                              Dictionary& dict,
                              Dictionary& wordsFound,
                              int visited[4][4],
                              int stepCount,
                              string word,
                              bool printBoard,
                              ostream &output) {
    if (rowPos >= 4 || rowPos < 0 || colPos >= 4 || colPos < 0)
        return;
    if (visited[rowPos][colPos] != 0)
        return;

    word += board[rowPos][colPos];
    if (!dict.IsPrefix(word))
        return;

    visited[rowPos][colPos] = stepCount;

    if (dict.IsWord(word) && !wordsFound.IsWord(word))
    {
        wordsFound.AddWord(word);
        cout<<"\n Inside solve board helper"<<printBoard;
        if (printBoard) {
            cout<<"Inside file printing";
            output << "Word: " << word << endl;
            output << "Number of Words: " << wordsFound.WordCount() << endl;
            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    if (visited[r][c] != 0) {
                        output<< " '"<<board[r][c]<<"' ";
                    }
                    else {
                        output<<"  "<< board[r][c]<<"  ";
                    }
                }
                output << "\t";
                for (int c = 0; c < 4; c++) {
                    output << "  " << visited[r][c] << "  ";
                }
                output << endl;
            }
            output << '\n';
        } else {
            cout << "Word Count: " << wordsFound.WordCount() << " | Word: " << word << endl;
            PrintBoard(output);
            output << wordsFound.WordCount() <<"\t" << word << endl;
        }
    }
    //move in clockwise direction, recursively, to find the solution
    //north
    SolveBoardHelper(rowPos - 1, colPos, board, dict, wordsFound, visited, stepCount + 1, word, printBoard, output);
    //north-east
    SolveBoardHelper(rowPos - 1, colPos + 1, board, dict, wordsFound, visited, stepCount + 1, word, printBoard, output);
    //east
    SolveBoardHelper(rowPos, colPos + 1, board, dict, wordsFound, visited, stepCount + 1, word, printBoard, output);
    //south-east
    SolveBoardHelper(rowPos + 1, colPos + 1, board, dict, wordsFound, visited, stepCount + 1, word, printBoard, output);
    //south
    SolveBoardHelper(rowPos + 1, colPos, board, dict, wordsFound, visited, stepCount + 1, word, printBoard, output);
    //south-west
    SolveBoardHelper(rowPos + 1, colPos - 1, board, dict, wordsFound, visited, stepCount + 1, word, printBoard, output);
    //west
    SolveBoardHelper(rowPos, colPos - 1, board, dict, wordsFound, visited, stepCount + 1, word, printBoard, output);
    //north-west
    SolveBoardHelper(rowPos - 1, colPos - 1, board, dict, wordsFound, visited, stepCount + 1, word, printBoard, output);

    //Backtrack and find another solution
    visited[rowPos][colPos] = 0;
    return;
}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

//prints board matrix to terminal
void Boggle::PrintBoard(ostream &output) {
    cout<<"\n Inside PrintBoard"<<&output;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (visited[r][c] != 0) {
                cout << " '" << board[r][c] << "'";
            }
            else {
                cout << " " << board[r][c] << " ";
            }
        }
        cout << "                 ";
        for (int c = 0; c < 4; c++) {
            cout << " " << visited[r][c] << " ";
        }
        cout << endl;
    }
}



// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}



