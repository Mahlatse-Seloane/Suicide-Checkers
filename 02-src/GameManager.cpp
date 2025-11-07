#include "GameManager.h"
#include <cctype>
#include <cstdlib>
#include <iomanip>

using namespace std;

GameManager::GameManager(ResultEvaluator &_evaluator, int _maxTurnLimit) : logger("results.txt")
{
    evaluator = &_evaluator;
    evaluator->setTurnLimit(_maxTurnLimit);
}

void GameManager::simulateSingleGame(const int boardSize, PlayerType &p1, PlayerType &p2)
{
    AssignPlayersNecessities(p1, p2);
    evaluator->setTokens(p1.getToken(), p2.getToken());
    curBoardSize = boardSize;

    initializeBoard(players[0]->getToken(), players[1]->getToken());

    bool isGameOver = false;

    vector<Move> validMoves(0);
    turnCount = 0;
    currentIdx = rand() % 2;
    swapPlayers();

    string moves = " ";
    int noOfValidMoves = 0;
    logger.logBoardSize(curBoardSize);
    do
    {
        //board.PrintBoard();
        //cout << curPId << endl;
        validMoves = rules.getValidMoves(board.peekBoard(),curTok,oppTok,curPDir);

        noOfValidMoves = static_cast<int>(validMoves.size());

        isGameOver = evaluator->terminal(board.peekBoard(), curTok, noOfValidMoves, turnCount);
        if(!isGameOver)
        {
            moves = curPId + " ";
            Move chosenMove = chooseMove(validMoves);
            applyMove(chosenMove);
            crown(chosenMove);

            moves += to_string(chosenMove.moveFrom) + ((chosenMove.capture == 0) ? "-" : "x") + to_string(chosenMove.moveTo);

            moves += CheckContinuousMoves(chosenMove);
            logger.logMoves(moves);

            swapPlayers();
            turnCount++;
            validMoves.clear();
        }
    }
    while(!isGameOver);

    logger.logGameResults(evaluator->getResults());
}

void GameManager::initializeBoard(char p1Piece, char p2Piece)
{
    board.clearBoard();
    board.createBoard(curBoardSize, curBoardSize);

    char curToken = ' ';
    int noOfRowsToOccupy = (curBoardSize/2) - 1;
    for(int i = 0; i < curBoardSize; i++)
    {
        for(int j = 0; j < curBoardSize; j++)
        {
            if((i + j) % 2 == 0)
                curToken = '#';
            else
                curToken = (i < noOfRowsToOccupy) ? p1Piece: ((i >= curBoardSize - noOfRowsToOccupy) ? p2Piece: ' ');

            board.setCell(i, j, curToken);
        }
    }
}

void GameManager::AssignPlayersNecessities(PlayerType &p1, PlayerType &p2)
{
    players[0] = &p1, players[1] = &p2;

    players[0]->setPlayerNecessities("p1",'x',Direction::down);
    players[1]->setPlayerNecessities("p2",'o',Direction::up);
}

Move GameManager::chooseMove(const vector<Move> possibleMoves)
{
    int index = -1;
    const int maxNoOfPosMoves = static_cast<int>(possibleMoves.size());
    while(index < 0 || index >= maxNoOfPosMoves)
        index = curP->chooseMove(board.peekBoard(), possibleMoves);

    return possibleMoves[index];
}

void GameManager::applyMove(const Move chosenMove)
{
    int row = -1, col = -1;

    BoardMapper::idToCoord(curBoardSize, chosenMove.moveFrom, row, col);
    char cell = (board.lookAt(row, col) == curTok) ? curTok: static_cast<char>(toupper(curTok));
    board.setCell(row, col, ' ');

    BoardMapper::idToCoord(curBoardSize, chosenMove.moveTo, row, col);
    board.setCell(row, col, cell);

    if(chosenMove.isCapture())
    {
        BoardMapper::idToCoord(curBoardSize, chosenMove.capture, row, col);
        board.setCell(row, col, ' ');
    }
}

string GameManager::CheckContinuousMoves(Move chosenMove)
{
    vector<Move> continuousMoves(0);
    string moves = "";

    while(chosenMove.capture != 0)
    {
        moves += "(" + to_string(chosenMove.capture) + ")";

        int movedTo = chosenMove.moveTo;
        chosenMove.resetMove();

        continuousMoves = rules.getAllowedContinuations(board.peekBoard(),curTok,oppTok,movedTo,curPDir);
        if(static_cast<int>(continuousMoves.size()) > 0)
        {
            chosenMove = chooseMove(continuousMoves);
            applyMove(chosenMove);
            crown(chosenMove);

            moves += to_string(chosenMove.moveFrom) + "x" + to_string(chosenMove.moveTo);
        }

        continuousMoves.clear();
    }

    return moves;
}

void GameManager::crown(Move chosenMove)
{
    int row = -1, col = -1;
    BoardMapper::idToCoord(curBoardSize, chosenMove.moveTo, row, col);

    if((curPDir == Direction::up && row == 0) || (curPDir == Direction::down && row == curBoardSize - 1))
        board.setCell(row, col, static_cast<char>(toupper(curTok)));
}

void GameManager::swapPlayers()
{
    currentIdx = 1 - currentIdx;
    curP = players[currentIdx], oppP = players[1 - currentIdx];
    curPId = curP->getPlayerID();
    curTok = curP->getToken(), oppTok = oppP->getToken();
    curPDir = curP->getDirection();
}
