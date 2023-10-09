#include "../SubClasses/Register.h"
#include <array>
#include <iostream>

class RAM
{
private:
    Register MAR;
    Register MDR;

    Register RIR;
    Register ROR;
    Register RAR;

    unsigned int RAM_SIZE;

    std::array<unsigned int, 42949672> RAM_INTERAL;

public:
    RAM(Register MAR_Input, Register MDR_Input, Register RIR_Input, Register ROR_Input, Register RAR_Input) : MAR(MAR_Input), MDR(MDR_Input), RIR(RIR_Input), ROR(ROR_Input), RAR(RAR_Input)
    {
        MAR = MAR_Input;
        MDR = MDR_Input;
        RIR = RIR_Input;
        ROR = ROR_Input;
        RAR = RAR_Input;
        RAM_SIZE = 42949672;
    }

    void print();

    void update(unsigned int opcode, unsigned int operand);

    void setRam(std::array<unsigned int, 42949672> RAM_Input)
    {
        RAM_INTERAL = RAM_Input;

        /* for (unsigned int i = 100 - 1; i >= 0; i--)
             std::cout << RAM_INTERAL[i] << ", "; */
    }
};