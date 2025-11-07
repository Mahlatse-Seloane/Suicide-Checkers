#include "InputHandler.h"

using namespace std;

vector<int> InputHandler::FileReader(const string filename)
{
    ifstream inData;
    inData.open(filename);

    vector<int> validSizes(0);
    int tempInput = 0, counter = 0;
    if (inData)
    {
        vector<int> sizesFromInput = loadAllSizes(inData);
        validSizes = parseAndFilter(sizesFromInput, 6, 12);
    }

    inData.close();
    return validSizes;
}

vector<int> InputHandler::loadAllSizes(ifstream &inData)
{
    vector<int> validSizes(0);

    string line;
    while (getline(inData, line))
    {
        istringstream iss(line);
        int tempInput;
        if (iss >> tempInput && iss.eof())
            validSizes.push_back(tempInput);
        else
            continue;
    }

    return validSizes;
}

vector<int> InputHandler::parseAndFilter(vector<int> boardSizes, int minRange, int maxRange)
{
    vector<int> validBoardSizes;
    for(int i = 0; i < boardSizes.size(); i++)
    {
        if((boardSizes[i] >= minRange && boardSizes[i] <= maxRange) && boardSizes[i] % 2 == 0)
            validBoardSizes.push_back(boardSizes[i]);
    }

    return validBoardSizes;
}
