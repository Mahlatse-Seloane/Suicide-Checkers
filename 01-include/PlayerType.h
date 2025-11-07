#ifndef PLAYERTYPE_H
#define PLAYERTYPE_H

#include <vector>
#include <string>

#include "Direction.h"
#include "Move.h"

class PlayerType
{
    public:
        virtual int chooseMove(const std::vector<std::vector<char> > &board,const std::vector<Move> &moves);
        void setPlayerID(std::string _playerID);
        std::string getPlayerID();
        void setToken(char _token);
        char getToken();
        void setDirection(Direction _direction);
        void setPlayerNecessities(const std::string _playerID,const char _token,const Direction _direction);
        Direction getDirection();

        void printMoves(const std::vector<Move> &moves) const;
        void PrintBoard(const std::vector<std::vector<char> > &board) const;
    private:
        //Member Functions

        //Member Variables
        char token;
        Direction direction;
        std::string playerID;
};

#endif // PLAYERTYPE_H
