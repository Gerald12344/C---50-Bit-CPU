#include "RAM.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <string>

extern int DataBus;

void RAM::update(int opcode, int operand)
{

    if (opcode == 0b00000001)
    {
        if (operand == 0b00000000)
        {
            Logger("Seting MAR to: " + std::to_string(DataBus));
            RAM::MAR.setValue(DataBus);
            RAM::MDR.setValue(RAM::RAM_INTERAL[RAM::MAR.getValue()]);
        }

        if (operand == 0b00001000)
        {
            Logger("Setting RIR to: " + std::to_string(DataBus));
            RAM::RIR.setValue(DataBus);
        }

        if (operand == 0b00001010)
        {
            Logger("Setting RAM[" + std::to_string(RAM::RAR.getValue()) + "] to: " + std::to_string(RAM::RIR.getValue()));
            RAM::RAR.setValue(DataBus);
        }
    }

    if (opcode == 0b00000010)
    {
        if (operand == 0b00000001)
        {
            Logger("Setting data bus to MDR value");
            DataBus = RAM::MDR.getValue();
        }

        if (operand == 0b00001001)
        {
            Logger("Setting data bus to ROR value");
            DataBus = RAM::ROR.getValue();
        }
    }

    if (opcode == 0b00001111)
    {
        Logger("Setting RAM value " + std::to_string(RAM::RAR.getValue()) + " to: " + std::to_string(RAM::RIR.getValue()));

        RAM::RAM_INTERAL[RAM::RAR.getValue()] = RAM::RIR.getValue();
    }

    if (opcode == 0b00010000)
    {
        Logger("Setting RAM value " + std::to_string(RAM::RAR.getValue()) + " to: " + std::to_string(RAM::RIR.getValue()));

        RAM::ROR.setValue(RAM::RAM_INTERAL[RAM::RAR.getValue()]);
    }
}