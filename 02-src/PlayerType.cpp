#include "PlayerType.h"

#include <iostream>
#include <iomanip>

using namespace std;

int PlayerType::chooseMove(const std::vector<std::vector<char>>& board, const std::vector<Move>& moves)
{
    return rand() % moves.size();
}

void PlayerType::setPlayerID(string _playerID)
{
    playerID = _playerID;
}

string PlayerType::getPlayerID()
{
    return playerID;
}

void PlayerType::setToken(char _token)
{
    token = _token;
}

char PlayerType::getToken()
{
    return token;
}

void PlayerType::setDirection(Direction _direction)
{
    direction = _direction;
}

Direction PlayerType::getDirection()
{
    return direction;
}

void PlayerType::setPlayerNecessities(const string _playerID,const char _token,const Direction _direction)
{
    playerID = _playerID;
    token = _token;
    direction = _direction;
}

void PlayerType::printMoves(const vector<Move> &moves) const
{
    int noOfMoves = static_cast<int>(moves.size());
    if(noOfMoves <= 0) return;

    cout << setw(2) << " ";
    cout << "|" << setw(11) << " Move From |" << setw(9) << " Move To |" << setw(9) << " Capture |" << endl;
    for(int i =  0; i < noOfMoves; i++)
    {
        cout << setw(2) << i+1;
        cout << "|" << setw(6) << moves[i].moveFrom << setw(6);
        cout << "|" << setw(5) << moves[i].moveTo << setw(5);
        cout << "|" << setw(5) << moves[i].capture << setw(5);
        cout << "|" << endl;
    }
    cout << endl;
}

void PlayerType::PrintBoard(const vector<vector<char> > &board) const
{
    int boardSize = static_cast<int>(board.size());
    for(int i = 0; i < boardSize; i++)
    {
        cout << setfill('-') << setw((boardSize * 2) + 1) << "" << endl;
        for(int j = 0; j < boardSize; j++)
            cout << "|" << board[i][j];

        cout << "|" << endl;
    }
    cout << setw((boardSize * 2) + 1) << "" << endl << endl;
    cout << setfill(' ');
}
