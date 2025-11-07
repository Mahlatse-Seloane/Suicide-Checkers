#ifndef RESULTEVALUATOR_H
#define RESULTEVALUATOR_H

#include <iostream>
#include <vector>

#include "EndResults.h"

class ResultEvaluator
{
    public:
        ResultEvaluator();
        void setTurnLimit(const int limit);
        void setTokens(const char _p1Token,const char _p2Token);
        bool terminal(const std::vector<std::vector<char> > &board,const char currentPlayerToken,const int noOfMoves,const int turnCount);
        EndResults getResults(){return results;};
    private:
        //Member Functions
        void TokenCounter(const std::vector<std::vector<char> > &board);

        //Member Variables
        int maxTurnLimit;
        char p1Token, p2Token;
        EndResults results;
};

#endif // RESULTEVALUATOR_H
