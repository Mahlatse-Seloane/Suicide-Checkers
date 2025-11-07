#ifndef SUICIDEAI_H
#define SUICIDEAI_H

#include "BoardMapper.h"
#include "Direction.h"
#include "Move.h"
#include "Option.h"
#include "PlayerType.h"
#include "Rules.h"

class SuicideAI: public PlayerType
{
public:
    SuicideAI();
    SuicideAI(std::string _playerID);
    void findOpponentToken(const std::vector<std::vector<char> > &board);
    int chooseMove(const std::vector<std::vector<char> > &board,const std::vector<Move> &moves) override;
    bool MakeWayForCaptureMoveDownLeft(const std::vector<std::vector<char> > &board,const int rowFrom,const int colFrom);
    bool MoveDownLeftToBeCaptured(const std::vector<std::vector<char> > &board,const int rowTo,const int colTo);
    bool MakeWayForCaptureMoveUpLeft(const std::vector<std::vector<char> > &board,const int rowFrom,const int colFrom);
    bool MoveUpLeftToBeCaptured(const std::vector<std::vector<char> > &board,const int rowTo,const int colTo);
    bool MakeWayForCaptureMoveDownRight(const std::vector<std::vector<char> > &board,const int rowFrom,const int colFrom);
    bool MoveDownRightToBeCaptured(const std::vector<std::vector<char> > &board,const int rowTo,const int colTo);
    bool MakeWayForCaptureMoveUpRight(const std::vector<std::vector<char> > &board,const int rowFrom,const int colFrom);
    bool MoveUpRightToBeCaptured(const std::vector<std::vector<char> > &board,const int rowTo,const int colTo);
private:
    //Member Functions
    std::vector<Move> findBestCaptureOptions(const std::vector<std::vector<char> > &board,const std::vector<Move> &moves);
    int findMove(const Move chosenMove, const std::vector<Move> &moves);
    std::vector<Move> findBestSacrificeOptions(const std::vector<std::vector<char> > &board,const std::vector<Move> &moves);

    //Member Variables
    char opponentToken;
};

#endif // SUICIDEAI_H
