#include "ResultEvaluator.h"

using namespace std;

ResultEvaluator::ResultEvaluator()
{

}

void ResultEvaluator::setTurnLimit(const int limit)
{
    maxTurnLimit = limit;
}

void ResultEvaluator::setTokens(const char _p1Token,const char _p2Token)
{
    p1Token = _p1Token, p2Token = _p2Token;
}

bool ResultEvaluator::terminal(const vector<vector<char> > &board, const char curPTok,const int noOfMoves,const int turnCount)
{
    TokenCounter(board);

    if(turnCount < maxTurnLimit && results.p1TokenCount > 0 && results.p2TokenCount > 0 && noOfMoves > 0)
        return false;

    if (turnCount > maxTurnLimit)
    {
        results.winner = "d";
        results.reason = EndReason::TurnLimit;
    }

    if (results.p1TokenCount == 0 || results.p2TokenCount == 0)
    {
        results.winner = (results.p1TokenCount == 0) ? "wp1" : "wp2";
        results.reason = EndReason::NoTokens;
    }

    if (noOfMoves == 0)
    {
        results.winner = (curPTok == p1Token) ? "wp1" : "wp2";
        results.reason = EndReason::NoMoves;
    }

    return true;
}

void ResultEvaluator::TokenCounter(const vector<vector<char> > &board)
{
    int boardSize = board.size();
    results.p1TokenCount = 0, results.p2TokenCount = 0;

    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            if(board[i][j] == p1Token || board[i][j] == toupper(p1Token))
                results.p1TokenCount++;
            if(board[i][j] == p2Token || board[i][j] == toupper(p2Token))
                results.p2TokenCount++;
        }
    }
}
