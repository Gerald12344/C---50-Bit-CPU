#include "RAM.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <string>

extern unsigned int DataBus;
extern unsigned int PC_COUNTER;

void RAM::print()
{
    for (unsigned int i = 32000000; i < 32000100; i++)
    {
        std::cout << RAM::RAM_INTERAL[i] << ", ";
    }
    std::cout << std::endl;
}

void RAM::update(unsigned int opcode, unsigned int operand)
{

    if (opcode == 0b00000001)
    {
        if (operand == 0b00000000)
        {
            // Logger("Seting MAR to: " + std::to_string(DataBus));
            RAM::MAR.setValue(DataBus);
            RAM::MDR.setValue(RAM::RAM_INTERAL[RAM::MAR.getValue()]);
        }

        if (operand == 0b00001000)
        {
            // Logger("Setting RIR to: " + std::to_string(DataBus));
            RAM::RIR.setValue(DataBus);
        }

        if (operand == 0b00001010)
        {
            // Logger("Setting RAM[" + std::to_string(RAM::RAR.getValue()) + "] to: " + std::to_string(RAM::RIR.getValue()));
            RAM::RAR.setValue(DataBus);
        }
    }

    if (opcode == 0b00001000)
    {
        if (PC_COUNTER > RAM::RAM_SIZE)
        {
            // Logger("PC is out of bounds");
            return;
        }
        DataBus = RAM::RAM_INTERAL[PC_COUNTER];
    }

    if (opcode == 0b00000010)
    {
        if (operand == 0b00000001)
        {
            // Logger("Setting data bus to MDR value");

            DataBus = RAM::MDR.getValue();
        }

        if (operand == 0b00001001)
        {
            // Logger("Setting data bus to ROR value");
            DataBus = RAM::ROR.getValue();
        }
    }

    if (opcode == 0b00001111)
    {
        // Logger("Setting RAM value " + std::to_string(RAM::RAR.getValue()) + " to: " + std::to_string(RAM::RIR.getValue()));

        RAM::RAM_INTERAL[RAM::RAR.getValue()] = RAM::RIR.getValue();
    }

    if (opcode == 0b00010000)
    {
        // Logger("Setting RAM value " + std::to_string(RAM::RAR.getValue()) + " to: " + std::to_string(RAM::RIR.getValue()));

        RAM::ROR.setValue(RAM::RAM_INTERAL[RAM::RAR.getValue()]);
    }
}