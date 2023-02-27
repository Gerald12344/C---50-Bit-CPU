#include "GeneralPurpose.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <iostream>
#include <string>

extern int DataBus;

void GEN::update(int opcode, int operand)
{
    if (opcode == 0b00001011)
    {

        Logger("Setting data bus to GP value");
        updateComponents(0b00000010, operand, "GEN");

        GEN::GEN_REG.setValue(DataBus);
    }
    if (opcode == 0b00001100)
    {

        Logger("Setting data bus to GP value");
        DataBus = GEN::GEN_REG.getValue();
        updateComponents(0b0000001, operand, "GEN");
    }
    if (opcode == 0b00001001)
    {
        Logger("Setting GP value to: " + std::to_string(operand));
        GEN::GEN_REG.setValue(operand);
    }
}