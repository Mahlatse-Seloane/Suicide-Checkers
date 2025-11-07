#ifndef ENDRESULTS_H
#define ENDRESULTS_H

#include <string>

enum class EndReason { None, NoMoves, NoTokens, TurnLimit };

struct EndResults
{
    int p1TokenCount{};
    int p2TokenCount{};
    std::string winner;  // "wp1", "wp2", "d"
    EndReason reason{EndReason::None};
};
#endif // ENDRESULTS_H
