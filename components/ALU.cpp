#include "ALU.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <iostream>
#include <string>

extern unsigned int DataBus;

extern bool HLT;
extern bool ADD;
extern bool SUB;
extern bool MUL;
extern bool DIV;
extern bool MOD;
extern bool COMP;
extern bool AND;

extern bool Zero;
extern bool Negative;

void ALU::update(unsigned int opcode, unsigned int operand)
{
    if (opcode == 0b00000001)
    {
        if (operand == 0b00000011)
        {
            // Logger("Setting REG_A to: " + std::to_string(DataBus));
            ALU::REG_A.setValue(DataBus);
            ALU::calculate();
        }
        if (operand == 0b00000100)
        {
            // Logger("Setting REG_B to: " + std::to_string(DataBus));
            ALU::REG_B.setValue(DataBus);
            ALU::calculate();
        }

        if (operand == 0b00001110)
        {
            // Logger("Setting REG_C to: " + std::to_string(DataBus));
            ALU::REG_C.setValue(DataBus);
        }
        if (operand == 0b00001111)
        {
            // Logger("Setting REG_C to: " + std::to_string(DataBus));
            ALU::REG_D.setValue(DataBus);
        }
    }

    if (opcode == 0b00001101)
    {

        if (Zero == true)
        {
            // Logger("Jumping to: " + std::to_string(operand));

            updateComponents(0b00000101, operand, "ALU");
        }
    }

    if (opcode == 0b00000010)
    {
        // Logger("Setting data bus to ACC value " + std::to_string(ALU::ACC.getValue()));
        if (operand == 0b00000101)
        {
            DataBus = ALU::ACC.getValue();
        }
        else if (operand == 0b00001110)
        {

            DataBus = ALU::REG_C.getValue();
        }
        else if (operand == 0b00001111)
        {

            DataBus = ALU::REG_D.getValue();
        }
    }
}

void ALU::calculate()
{
    unsigned int a = ALU::REG_A.getValue();
    unsigned int b = ALU::REG_B.getValue();

    unsigned int result;
    if (SUB)
    {
        result = a - b;
    }
    else if (MUL)
    {
        result = a * b;
    }
    else if (DIV)
    {
        result = a / b;
    }
    else if (MOD)
    {
        result = a % b;
    }
    else if (COMP)
    {
        result = a == b;
    }
    else if (AND)
    {
        result = a & b;
    }
    else
    {
        result = a + b;
    }

    result == 0 ? Zero = true : Zero = false;
    result < 0 ? Negative = true : Negative = false;

    ACC.setValue(result);
}
