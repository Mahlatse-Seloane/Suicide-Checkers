#include "Rules.h"
#include <cctype>

using namespace std;

vector<Move> Rules::getValidMoves(const vector<vector<char> > &board,const char currentToken,const char opponentToken,const Direction currentDirection)
{
    vector<Move> nonCaptureMoves(0), captureMoves(0);
    vector<char> nonCaptureTargets = {' '}, captureTargets = {opponentToken, ' '};
    const int boardSize = static_cast<int>(board.size());
    int pos = 0;

    for(int row = 0; row < boardSize; row++)
    {
        for(int col = 0; col < boardSize; col++)
        {
            if((row+col) % 2 != 0)
            {
                pos++;
                if(board[row][col] == currentToken)
                {
                    if(currentDirection == Direction::down)
                        checkCapturesDown(board,captureMoves,pos,row,col,captureTargets);
                    else if(currentDirection == Direction::up)
                        checkCapturesUp(board,captureMoves,pos,row,col,captureTargets);

                    if (captureMoves.empty())
                    {
                        if(currentDirection == Direction::down)
                            checkNonCapturesDown(board,nonCaptureMoves,pos,row,col,nonCaptureTargets);
                        else if(currentDirection == Direction::up)
                            checkNonCapturesUp(board,nonCaptureMoves,pos,row,col,nonCaptureTargets);
                    }
                }
                else if(board[row][col] == static_cast<char>(toupper(currentToken)))
                {
                    checkCapturesDown(board,captureMoves,pos,row,col,captureTargets);
                    checkCapturesUp(board,captureMoves,pos,row,col,captureTargets);
                    if(captureMoves.empty())
                    {
                        checkNonCapturesDown(board,nonCaptureMoves,pos,row,col,nonCaptureTargets);
                        checkNonCapturesUp(board,nonCaptureMoves,pos,row,col,nonCaptureTargets);
                    }
                }
            }
        }
    }

    if(!captureMoves.empty())
        return captureMoves;

    return nonCaptureMoves;
}

vector<Move> Rules::getAllowedContinuations(const vector<vector<char> > &board,const char currentToken,const char opponentToken,const int pos,const Direction currentDirection)
{
    vector<Move> captureMoves(0);
    const vector<char> captureTargets = {opponentToken, ' '};

    int row = -1, col = -1;
    BoardMapper::idToCoord(static_cast<int>(board.size()), pos, row, col);

    if(board[row][col] == currentToken)
    {
        if(currentDirection == Direction::down)
            checkCapturesDown(board,captureMoves,pos,row,col,captureTargets);
        else if(currentDirection == Direction::up)
            checkCapturesUp(board,captureMoves,pos,row,col,captureTargets);
    }
    else if(board[row][col] == static_cast<char>(toupper(currentToken)))
    {
        checkCapturesDown(board,captureMoves,pos,row,col,captureTargets);
        checkCapturesUp(board,captureMoves,pos,row,col,captureTargets);
    }

    return captureMoves;
}

void Rules::checkNonCapturesDown(const vector<vector<char> > &board,vector<Move> &moves,const int pos,const int row,const int col,const vector<char> &targets)
{
    const int boardSize = static_cast<int>(board.size());
    Move singleMove = {pos, 0, 0};

    if(checkDiagonalDownLeft(board,row,col,targets))
    {
        singleMove.moveTo = BoardMapper::stepDownLeft(pos, row, boardSize);
        moves.push_back(singleMove);
    }

    if(checkDiagonalDownRight(board,row,col,targets))
    {
        singleMove.moveTo = BoardMapper::stepDownRight(pos, row, boardSize);
        moves.push_back(singleMove);
    }
}

void Rules::checkNonCapturesUp(const vector<vector<char> > &board,vector<Move> &moves,const int pos,const int row,const int col,const vector<char> &targets)
{
    const int boardSize = static_cast<int>(board.size());
    Move singleMove = {pos, 0, 0};

    if(checkDiagonalUpLeft(board,row,col,targets))
    {
        singleMove.moveTo = BoardMapper::stepUpLeft(pos, row, boardSize);
        moves.push_back(singleMove);
    }

    if(checkDiagonalUpRight(board,row,col,targets))
    {
        singleMove.moveTo = BoardMapper::stepUpRight(pos, row, boardSize);
        moves.push_back(singleMove);
    }
}

void Rules::checkCapturesDown(const vector<vector<char> > &board,vector<Move> &moves,const int pos,const int row,const int col,const vector<char> &targets)
{
    const int boardSize = static_cast<int>(board.size());
    Move singleMove = {pos, 0, 0};

    if(checkDiagonalDownLeft(board,row,col,targets))
    {
        singleMove.capture = BoardMapper::stepDownLeft(pos, row, boardSize);
        singleMove.moveTo = BoardMapper::captureDownLeft(pos, row, boardSize);
        moves.push_back(singleMove);
    }

    if(checkDiagonalDownRight(board,row,col,targets))
    {
        singleMove.capture = BoardMapper::stepDownRight(pos, row, boardSize);
        singleMove.moveTo = BoardMapper::captureDownRight(pos, row, boardSize);
        moves.push_back(singleMove);
    }
}

void Rules::checkCapturesUp(const vector<vector<char> > &board,vector<Move> &moves,const int pos,const int row,const int col,const vector<char> &targets)
{
    const int boardSize = static_cast<int>(board.size());
    Move singleMove = {pos, 0, 0};

    if(checkDiagonalUpLeft(board,row,col,targets))
    {
        singleMove.capture = BoardMapper::stepUpLeft(pos, row, boardSize);
        singleMove.moveTo = BoardMapper::captureUpLeft(pos, row, boardSize);
        moves.push_back(singleMove);
    }

    if(checkDiagonalUpRight(board,row,col,targets))
    {
        singleMove.capture = BoardMapper::stepUpRight(pos, row, boardSize);
        singleMove.moveTo = BoardMapper::captureUpRight(pos, row, boardSize);
        moves.push_back(singleMove);
    }
}

// Starts one step down-right from (row, col) and checks each square along the diagonal against the characters in 'targets'.
bool Rules::checkDiagonalDownRight(const vector<vector<char> > &board,int row,int col,const vector<char> &targets)
{
    const int dRow = 1, dCol = 1;
    return matchDiagonalSequence(board,row,col,dRow,dCol,targets);
}

// Starts one step down-left from (row, col) and checks each square along the diagonal against the characters in 'targets'.
bool Rules::checkDiagonalDownLeft(const vector<vector<char> > &board,int row,int col,const vector<char> &targets)
{
    const int dRow = 1, dCol = -1;
    return matchDiagonalSequence(board,row,col,dRow,dCol,targets);
}

// Starts one step up-right from (row, col) and checks each square along the diagonal against the characters in 'targets'.
bool Rules::checkDiagonalUpRight(const vector<vector<char> > &board,int row,int col,const vector<char> &targets)
{
    const int dRow = -1, dCol = 1;
    return matchDiagonalSequence(board,row,col,dRow,dCol,targets);
}

// Starts one step up-left from (row, col) and checks each square along the diagonal against the characters in 'targets'.
bool Rules::checkDiagonalUpLeft(const vector<vector<char> > &board,int row,int col,const vector<char> &targets)
{
    const int dRow = -1, dCol = -1;
    return matchDiagonalSequence(board,row,col,dRow,dCol,targets);
}

bool Rules::matchDiagonalSequence(const vector<vector<char> > &board,int row,int col,const int dRow,const int dCol,const vector<char> &targets)
{
    const int noOfTargets = static_cast<int>(targets.size());
    const int boardSize = static_cast<int>(board.size());
    const int maxVerticalSteps = (dRow < 0) ? row: ((boardSize - 1) - row);
    const int maxHorizontalSteps = (dCol < 0) ? col: ((boardSize - 1) - col);
    const int availableSteps = (maxVerticalSteps < maxHorizontalSteps) ? maxVerticalSteps : maxHorizontalSteps;

    if (noOfTargets > availableSteps)
        return false;

    for(int i = 0; i < noOfTargets; i++)
    {
        row += dRow, col += dCol;
        const char want = targets[i];
        const char cell = board[row][col];

        if ((want == ' ' && cell != ' ') || (want != ' ' && !isManOrKing(cell, want)))
            return false;
    }

    return true;
}

bool Rules::isManOrKing(char cell, char tok)
{
    return cell == tok || cell == static_cast<char>(toupper(static_cast<unsigned char>(tok)));
}
