#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "Direction.h"
#include "PlayerType.h"

#include "Move.h"
#include <vector>
#include <string>

class RandomAI: public PlayerType
{
    public:
        RandomAI();
        RandomAI(std::string _playerID);
    private:

};

#endif // RANDOMAI_H
