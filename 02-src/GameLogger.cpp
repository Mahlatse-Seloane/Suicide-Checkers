#include "GameLogger.h"

using namespace std;

GameLogger::GameLogger(const string filename)
{
    outData.open(filename);
}

GameLogger::~GameLogger()
{
    if(outData.is_open())
        outData.close(); 
}

void GameLogger::logBoardSize(int boardSize)
{
    outData << boardSize << endl;
}


void GameLogger::logMoves(string currentMove)
{
    outData << currentMove << endl;
}

void GameLogger::logGameResults(EndResults results)
{
    outData << "tp1 " << results.p1TokenCount << endl;
    outData << "tp2 " << results.p2TokenCount << endl;
    outData << results.winner << endl;
    outData << endl;
}

void GameLogger::logBoardSizeForDebug(int boardSize)
{
    cout << boardSize << endl;
}

void GameLogger::logMoveForDebug(string currentMove)
{
    outData << currentMove << endl;
}

void GameLogger::logGameResultsForDebug(EndResults results)
{
    cout << endl;
    cout << "tp1 " << results.p1TokenCount << endl;
    cout << "tp2 " << results.p2TokenCount << endl;
    cout << results.winner << endl;
    cout << endl;
}
