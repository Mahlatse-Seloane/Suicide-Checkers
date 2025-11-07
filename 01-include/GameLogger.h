#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include <iostream>
#include <fstream>

#include "Move.h"
#include "EndResults.h"

class GameLogger
{
    public:
        GameLogger(const std::string filename);
        ~GameLogger();
        void logBoardSize(int boardSize);
        void logMoves(std::string currentMove);
        void logGameResults(EndResults results);

        void logBoardSizeForDebug(int boardSize);
        void logMoveForDebug(std::string currentMove);
        void logGameResultsForDebug(EndResults results);
    private:
        std::ofstream outData;
};

#endif // GAMELOGGER_H
