#include "BoardMapper.h"

void BoardMapper::idToCoord(int boardSize, int pos, int &row, int &col)
{
    if(!assertSquareIdInRange(pos, boardSize))
        return;

    int counter = 0;
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            counter += ((i + j) % 2 != 0);
            if(counter == pos)
            {
                row = i, col = j;
                return;
            }
        }
    }
}

int BoardMapper::coordToId(int boardSize, int row, int col)
{
    int counter = 0;
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            counter += ((i + j) % 2 != 0);
            if(i == row && j == col)
                return counter;
        }
    }

    return 0;
}

int BoardMapper::stepDownLeft(int pos,int row,int boardSize)
{
    return pos + ((boardSize/2) - ((row+1)%2 == 0));
}

int BoardMapper::captureDownLeft(int pos,int row,int boardSize)
{
    return pos + (boardSize - 1);
}

int BoardMapper::stepDownRight(int pos,int row,int boardSize)
{
    return pos + ((boardSize/2) + ((row+1)%2 != 0));
}

int BoardMapper::captureDownRight(int pos,int row,int boardSize)
{
    return pos + (boardSize + 1);
}

int BoardMapper::stepUpLeft(int pos,int row,int boardSize)
{
    return  pos - ((boardSize/2) + ((row-1)%2 == 0));
}

int BoardMapper::captureUpLeft(int pos,int row,int boardSize)
{
    return pos - (boardSize + 1);
}

int BoardMapper::stepUpRight(int pos,int row,int boardSize)
{
    return pos - ((boardSize/2) - ((row-1)%2 != 0));
}

int BoardMapper::captureUpRight(int pos,int row,int boardSize)
{
    return pos - (boardSize - 1);
}

bool BoardMapper::assertSquareIdInRange(int id, int boardSize)
{
    int maxId = (boardSize * boardSize) / 2;
    return (id >= 1 && id <= maxId);
}
