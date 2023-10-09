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
void LoggerNum(unsigned int  inputData)
{
    if (DEBUG)
    {
        std::cout << inputData << "\n";
    }
}