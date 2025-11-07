#include "Board.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Board::clearBoard()
{
    board.clear();
}

void Board::createBoard(int noOfRows, int noOfCols)
{
    for(int i = 0; i < noOfRows; i++)
    {
        vector<char> temp(noOfCols, ' ');
        board.push_back(temp);
    }
}

char Board::lookAt(int row, int col) const
{
    return board[row][col];
}

void Board::setCell(int row, int col, char ch)
{
    board[row][col] = ch;
}

const vector<vector<char> > &Board::peekBoard() const
{
    return board;
}

void Board::PrintBoard() const
{
    int boardSize = static_cast<int>(board.size());
    for(int i = 0; i < boardSize; i++)
    {
        cout << setfill('-') << setw((boardSize * 2) + 1) << "" << endl;
        for(int j = 0; j < boardSize; j++)
            cout << "|" << board[i][j];

        cout << "|" << endl;
    }
    cout << setw((boardSize * 2) + 1) << "" << endl << endl;
    cout << setfill(' ');
}
