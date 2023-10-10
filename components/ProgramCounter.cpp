#include "ProgramCounter.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <string>
#include <iostream>

extern unsigned int DataBus;
extern unsigned int PC_COUNTER;

void ProgramCounter::update(unsigned int opcode, unsigned int operand)
{

    if (opcode == 0b00001000)
    {
        unsigned int newVal = ProgramCounter::PC_REG.getValue() + 1;
        ProgramCounter::PC_REG.setValue(newVal);
        PC_COUNTER = newVal;
    }

    if (opcode == 0b00000001 && operand == 0b00000010)
    {
        ProgramCounter::PC_REG.setValue(DataBus);
        PC_COUNTER = DataBus;
    }

    if (opcode == 0b00000100)
    {
        // Logger("Incrementing PC");
        unsigned int newVal = ProgramCounter::PC_REG.getValue() + 1;
        ProgramCounter::PC_REG.setValue(newVal);
        PC_COUNTER = newVal;
    }

    if (opcode == 0b00000010)
    {
        if (operand == 0b00000010)
        {
            // Logger("Setting data bus to PC value");

            DataBus = ProgramCounter::PC_REG.getValue();
        }
    }

    if (opcode == 0b00000101)
    {
        // Logger("JUMP PC to: " + std::to_string(operand));
        ProgramCounter::PC_REG.setValue(operand);
        PC_COUNTER = operand;
    }
}