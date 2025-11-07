#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
    public:
        //Member Functions
        void clearBoard();
        void createBoard(int noOfRows, int noOfCols);
        char lookAt(int row, int col) const;
        void setCell(int row, int col, char ch);
        const std::vector<std::vector<char> > &peekBoard() const;
        void PrintBoard() const;

    private:
        //Member Variables
        std::vector<std::vector<char> > board;
};

#endif // Board_H
