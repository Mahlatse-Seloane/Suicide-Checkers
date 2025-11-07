#include <iostream>
#include <fstream>
#include <limits>
#include <ctime>

#include "GameManager.h"
#include "InputHandler.h"
#include "SuicideAI.h"
#include "RandomAI.h"
#include "ResultEvaluator.h"

using namespace std;

int main()
{
    srand(time(NULL));
    vector<int> boardSizesFromInputFile = InputHandler::FileReader("input.txt");

    bool anyValidBoardSizes = (boardSizesFromInputFile.size() > 0);
    if(anyValidBoardSizes)
    {
        ResultEvaluator evaluator;
        SuicideAI suicidalAI;
        RandomAI randomAI;

        GameManager manager(evaluator, 1000);

        const int noOfBoardSizes = static_cast<int>(boardSizesFromInputFile.size());
        for(int i = 0; i < noOfBoardSizes; i++)
        {
            const int curBoardSize = boardSizesFromInputFile[i];
            manager.simulateSingleGame(curBoardSize, suicidalAI, randomAI);
        }
    }

    return 0;
}
