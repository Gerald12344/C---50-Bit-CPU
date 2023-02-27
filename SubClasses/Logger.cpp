#include <iostream>
#include <string>

extern bool DEBUG;

void Logger(std::string inputData)
{
    if (DEBUG)
    {
        std::cout << inputData << "\n";
    }
}
void LoggerNum(int inputData)
{
    if (DEBUG)
    {
        std::cout << inputData << "\n";
    }
}