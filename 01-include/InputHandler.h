#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H


#include <sstream>
#include <vector>
#include <fstream>

class InputHandler
{
private:
    static std::vector<int> loadAllSizes(std::ifstream &inData);
    static std::vector<int> parseAndFilter(std::vector<int> boardSizes, int minRange, int maxRange);
public:
    static std::vector<int> FileReader(const std::string filename);
};

#endif // INPUTHANDLER_H
