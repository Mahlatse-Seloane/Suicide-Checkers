#ifndef BOARDMAPPER_H
#define BOARDMAPPER_H

#include <cassert>

class BoardMapper
{
private:
    BoardMapper();
    static bool assertSquareIdInRange(int id, int boardSize);

public:
    static void idToCoord(int boardSize, int pos, int &row, int &col);
    static int coordToId(int boardSize, int row, int col);

    static int stepDownLeft(int pos, int row, int boardSize);
    static int captureDownLeft(int pos, int row, int boardSize);

    static int stepDownRight(int pos, int row, int boardSize);
    static int captureDownRight(int pos, int row, int boardSize);

    static int stepUpLeft(int pos,int row,int boardSize);
    static int captureUpLeft(int pos,int row,int boardSize);

    static int stepUpRight(int pos,int row,int boardSize);
    static int captureUpRight(int pos,int row,int boardSize);
};

#endif // BOARDMAPPER_H
