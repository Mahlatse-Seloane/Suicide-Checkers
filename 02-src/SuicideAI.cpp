#include "SuicideAI.h"

using namespace std;

SuicideAI::SuicideAI()
{
    setPlayerID("p1");
}

SuicideAI::SuicideAI(string _playerID)
{
    setPlayerID(_playerID);
}

int SuicideAI::chooseMove(const vector<vector<char> > &board,const vector<Move> &moves)
{
    //printMoves(moves);
    findOpponentToken(board);
    int index = -1;

    vector<Move> bestCaptureOptions = findBestCaptureOptions(board,moves);
    if(bestCaptureOptions.size() > 0)
    {
        //cout << "best capture options" << endl;
        int noOfCaptureOptions = static_cast<int>(bestCaptureOptions.size());
        index = rand() % noOfCaptureOptions;
        return findMove(bestCaptureOptions[index],moves);
    }

    vector<Move> bestSacrificeOptions = findBestSacrificeOptions(board,moves);
    if(bestSacrificeOptions.size() > 0)
    {
        //cout << "best sacriface options" << endl;
        int noOfSacrifaceOptions = static_cast<int>(bestSacrificeOptions.size());
        index = rand() % noOfSacrifaceOptions;
        return findMove(bestSacrificeOptions[index],moves);
    }

    return rand() % moves.size();
}

vector<Move> SuicideAI::findBestCaptureOptions(const vector<vector<char> > &board,const vector<Move> &moves)
{
    vector<Move> bestOptions(0);
    vector<char> targets = {opponentToken, ' '};
    int rowFrom = -1, colFrom = -1, rowTo = -1, colTo = -1;
    int boardSize = static_cast<int>(board.size()), noOfMoves = static_cast<int>(moves.size());

    for(int i = 0; i < noOfMoves; i++)
    {
        if(moves[i].isCapture())
        {
            BoardMapper::idToCoord(boardSize, moves[i].moveFrom, rowFrom, colFrom);
            BoardMapper::idToCoord(boardSize, moves[i].moveTo, rowTo, colTo);

            bool capturesDown = !(Rules::checkDiagonalDownLeft(board,rowTo,colTo,targets) || Rules::checkDiagonalDownRight(board,rowTo,colTo,targets));
            bool capturesUp = !(Rules::checkDiagonalUpLeft(board,rowTo,colTo,targets) || Rules::checkDiagonalUpRight(board,rowTo,colTo,targets));

            if(board[rowFrom][colFrom] == getToken())
            {
                if((getDirection() == Direction::down && capturesDown) || (getDirection() == Direction::up && capturesUp))
                    bestOptions.push_back(moves[i]);
            }
            else if(board[rowFrom][colFrom] == toupper(getToken()))
            {
                if(capturesDown && capturesUp)
                    bestOptions.push_back(moves[i]);
            }
        }
    }

    return bestOptions;
}

vector<Move> SuicideAI::findBestSacrificeOptions(const vector<vector<char> > &board,const vector<Move> &moves)
{
    vector<Move> bestOptions(0);
    int rowFrom = -1, colFrom = -1, rowTo = -1, colTo = -1;
    int boardSize = static_cast<int>(board.size()), noOfMoves = static_cast<int>(moves.size());

    for(int i = 0; i < noOfMoves; i++)
    {
        if(!moves[i].isCapture())
        {
            BoardMapper::idToCoord(boardSize, moves[i].moveFrom, rowFrom, colFrom);
            BoardMapper::idToCoord(boardSize, moves[i].moveTo, rowTo, colTo);

            bool downLeftCheck = false, downRightCheck = false,upLeftCheck = false, upRightCheck = false;

            int horizontalDir = colFrom - colTo;
            if(horizontalDir > 0)
            {
                downLeftCheck = Rules::checkDiagonalDownLeft(board,rowFrom,colFrom, {' ',opponentToken});
                downLeftCheck = downLeftCheck || MakeWayForCaptureMoveDownLeft(board,rowFrom,colFrom)|| MoveDownLeftToBeCaptured(board,rowTo,colTo);

                upLeftCheck = Rules::checkDiagonalUpLeft(board,rowFrom,colFrom, {' ',opponentToken});
                upLeftCheck = upLeftCheck || MakeWayForCaptureMoveUpLeft(board,rowFrom,colFrom)|| MoveDownLeftToBeCaptured(board,rowTo,colTo);
            }
            else if(horizontalDir < 0)
            {
                downRightCheck = Rules::checkDiagonalDownRight(board,rowFrom,colFrom, {' ',opponentToken});
                downRightCheck = downRightCheck || MakeWayForCaptureMoveDownRight(board,rowFrom,colFrom)|| MoveDownRightToBeCaptured(board,rowTo,colTo);

                upRightCheck = Rules::checkDiagonalUpRight(board,rowFrom,colFrom, {' ', opponentToken});
                upRightCheck = upRightCheck || MakeWayForCaptureMoveUpRight(board,rowFrom,colFrom)|| MoveDownRightToBeCaptured(board,rowTo,colTo);
            }

            if(board[rowFrom][colFrom] == getToken())
            {
                if(getDirection() == Direction::down && (downLeftCheck || downRightCheck))
                    bestOptions.push_back(moves[i]);
                else if(getDirection() == Direction::up && (upLeftCheck || upRightCheck))
                    bestOptions.push_back(moves[i]);
            }
            else if(board[rowFrom][colFrom] == toupper(getToken()))
            {
                if(downLeftCheck || upLeftCheck || downRightCheck || upRightCheck)
                    bestOptions.push_back(moves[i]);
            }
        }
    }

    return bestOptions;
}

bool SuicideAI::MakeWayForCaptureMoveDownLeft(const vector<vector<char> > &board,const int rowFrom,const int colFrom)
{
    return (Rules::checkDiagonalDownRight(board,rowFrom,colFrom, {getToken(),opponentToken}) && Rules::checkDiagonalDownLeft(board,rowFrom,colFrom, {' '}));
}

bool SuicideAI::MakeWayForCaptureMoveDownRight(const vector<vector<char> > &board,const int rowFrom,const int colFrom)
{
    return (Rules::checkDiagonalDownLeft(board,rowFrom,colFrom, {getToken(),opponentToken}) && Rules::checkDiagonalDownRight(board,rowFrom,colFrom, {' '}));
}

bool SuicideAI::MakeWayForCaptureMoveUpLeft(const vector<vector<char> > &board,const int rowFrom,const int colFrom)
{
    return (Rules::checkDiagonalUpRight(board,rowFrom,colFrom, {getToken(),opponentToken}) && Rules::checkDiagonalUpLeft(board,rowFrom,colFrom, {' '}));
}

bool SuicideAI::MakeWayForCaptureMoveUpRight(const vector<vector<char> > &board,const int rowFrom,const int colFrom)
{
    return (Rules::checkDiagonalUpLeft(board,rowFrom,colFrom, {getToken(),opponentToken}) && Rules::checkDiagonalUpRight(board,rowFrom,colFrom, {' '}));
}

bool SuicideAI::MoveDownLeftToBeCaptured(const vector<vector<char> > &board,const int rowTo,const int colTo)
{
    return (Rules::checkDiagonalDownRight(board,rowTo,colTo, {opponentToken}) && Rules::checkDiagonalUpLeft(board,rowTo,colTo, {' '}));
}

bool SuicideAI::MoveDownRightToBeCaptured(const vector<vector<char> > &board,const int rowTo,const int colTo)
{
    return (Rules::checkDiagonalDownLeft(board,rowTo,colTo, {opponentToken}) && Rules::checkDiagonalUpRight(board,rowTo,colTo, {' '}));
}

bool SuicideAI::MoveUpLeftToBeCaptured(const vector<vector<char> > &board,const int rowTo,const int colTo)
{
    return (Rules::checkDiagonalUpRight(board,rowTo,colTo, {opponentToken}) && Rules::checkDiagonalDownLeft(board,rowTo,colTo, {' '}));
}

bool SuicideAI::MoveUpRightToBeCaptured(const vector<vector<char> > &board,const int rowTo,const int colTo)
{
    return (Rules::checkDiagonalUpLeft(board,rowTo,colTo, {opponentToken}) && Rules::checkDiagonalDownRight(board,rowTo,colTo, {' '}));
}

void SuicideAI::findOpponentToken(const vector<vector<char> > &board)
{
    const int boardSize = static_cast<int>(board.size());
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            if(board[i][j] != '#' && board[i][j] != ' ' && board[i][j] != getToken())
            {
                opponentToken = board[i][j];
                return;
            }
        }
    }
}

int SuicideAI::findMove(const Move chosenMove,const vector<Move> &moves)
{
    const int noOfAllAvailableMoves = static_cast<int>(moves.size());
    for(int i = 0; i < noOfAllAvailableMoves; i++)
    {
        if(chosenMove.checkEquality(moves[i]))
            return i;
    }

    return 0;
}
