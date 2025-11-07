#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>

#include "Board.h"
#include "BoardMapper.h"
#include "Direction.h"
#include "GameLogger.h"
#include "InputHandler.h"
#include "Move.h"
#include "PlayerType.h"
#include "ResultEvaluator.h"
#include "Rules.h"

class GameManager
{
    public:
        GameManager(ResultEvaluator &_evaluator, int _maxTurnLimit);
        void simulateSingleGame(const int boardSize, PlayerType &p1, PlayerType &p2);
    private:
        //Member Functions
        void AssignPlayersNecessities(PlayerType &p1, PlayerType &p2);
        void initializeBoard(char p1Piece, char p2Piece);
        void applyMove(const Move chosenMove);
        std::string CheckContinuousMoves(Move chosenMove);
        void crown(Move chosenMove);
        void swapPlayers();
        Move chooseMove(const std::vector<Move> possibleMoves);

        //Member variables
        Rules rules;
        GameLogger logger;
        ResultEvaluator *evaluator;

        Board board;
        PlayerType *players[2], *curP, *oppP;
        int curBoardSize;
        int currentIdx; // 0 -> P1, 1 -> P2
        int turnCount;

        std::string curPId;
        char curTok, oppTok;
        Direction curPDir;
};

#endif // GAMEMANAGER_H
