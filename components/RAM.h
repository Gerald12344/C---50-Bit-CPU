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

    std::array<int, 100000> RAM_INTERAL;

public:
    RAM(Register MAR_Input, Register MDR_Input, Register RIR_Input, Register ROR_Input, Register RAR_Input) : MAR(MAR_Input), MDR(MDR_Input), RIR(RIR_Input), ROR(ROR_Input), RAR(RAR_Input)
    {
        MAR = MAR_Input;
        MDR = MDR_Input;
        RIR = RIR_Input;
        ROR = ROR_Input;
        RAR = RAR_Input;
    }

    void update(int opcode, int operand);

    void setRam(std::array<int, 100000> RAM_Input)
    {
        RAM_INTERAL = RAM_Input;

        /* for (int i = 100 - 1; i >= 0; i--)
             std::cout << RAM_INTERAL[i] << ", "; */
    }
};