#ifndef RULES_H
#define RULES_H

#include <vector>

#include "BoardMapper.h"
#include "Direction.h"
#include "Move.h"

class Rules
{
public:
    std::vector<Move> getValidMoves(const std::vector<std::vector<char> > &board, char currentToken, char opponentToken, Direction currentDirection);
    std::vector<Move> getAllowedContinuations(const std::vector<std::vector<char> > &board,const char currentToken,const char opponentToken,const int pos,const Direction currentDirection);
    static bool checkDiagonalDownLeft(const std::vector<std::vector<char> > &board,int row,int col,const std::vector<char> &targets);
    static bool checkDiagonalDownRight(const std::vector<std::vector<char> > &board,int row,int col,const std::vector<char> &targets);
    static bool checkDiagonalUpLeft(const std::vector<std::vector<char> > &board,int row,int col,const std::vector<char> &targets);
    static bool checkDiagonalUpRight(const std::vector<std::vector<char> > &board,int row,int col,const std::vector<char> &targets);
    static bool isManOrKing(char cell, char tok);

private:
    //Helpers
    void checkCapturesDown(const std::vector<std::vector<char> > &board,std::vector<Move> &moves,const int pos,const int row,const int col,const std::vector<char> &targets);
    void checkCapturesUp(const std::vector<std::vector<char> > &board,std::vector<Move> &moves,const int pos,const int row,const int col,const std::vector<char> &targets);
    void checkNonCapturesDown(const std::vector<std::vector<char> > &board,std::vector<Move> &moves,const int pos,const int row,const int col,const std::vector<char> &targets);
    void checkNonCapturesUp(const std::vector<std::vector<char> > &board,std::vector<Move> &moves,const int pos,const int row,const int col,const std::vector<char> &targets);
    static bool matchDiagonalSequence(const std::vector<std::vector<char> > &board,int row,int col,const int dRow,const int dCol,const std::vector<char> &targets);
};

#endif // RULES_H
