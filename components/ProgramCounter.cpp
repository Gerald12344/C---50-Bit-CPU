#include "ProgramCounter.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <string>
#include <iostream>

extern int DataBus;
extern int PC_COUNTER;

void ProgramCounter::update(int opcode, int operand)
{

    if (opcode == 0b00001000)
    {
        int newVal = ProgramCounter::PC_REG.getValue() + 1;
        ProgramCounter::PC_REG.setValue(newVal);
        PC_COUNTER = newVal;
    }

    if (opcode == 0b00000100)
    {
        // Logger("Incrementing PC");
        int newVal = ProgramCounter::PC_REG.getValue() + 1;
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