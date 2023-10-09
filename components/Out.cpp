#include "Out.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <string>
#include <iostream>

extern unsigned int DataBus;

void Out::update(unsigned int opcode, unsigned int operand)
{
    if (opcode == 0b00000001)
    {
        if (operand == 0b00000111)
        {
            // Logger("Setting OUT reg to databus value");
            Out::OUT_REG.setValue(DataBus);
        }
    }

    if (opcode == 0b00010011)
    {
        // Log value as char
        printf("data: %c\n", (char)Out::OUT_REG.getValue());
    }

    if (opcode == 0b00000110)
    {
        // std::cout << Out::OUT_REG.getValue() << std::endl;

        printf("data: %d\n", Out::OUT_REG.getValue());
    }
}