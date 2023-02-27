#include "Out.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <string>
#include <iostream>

extern int DataBus;

void Out::update(int opcode, int operand)
{
    if (opcode == 0b00000001)
    {
        if (operand == 0b00000111)
        {
            Logger("Setting OUT reg to databus value");
            Out::OUT_REG.setValue(DataBus);
        }
    }

    if (opcode == 0b00000110)
    {
        std::cout << Out::OUT_REG.getValue() << std::endl;
    }
}