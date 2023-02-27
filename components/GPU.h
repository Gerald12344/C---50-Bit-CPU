#include "../SubClasses/Register.h"
#include <array>
#include <iostream>

class GPU
{
private:
    Register GENX;
    Register GENY;
    Register GENC;

    std::array<std::array<int, 400>, 400> SCREEN;

public:
    GPU(Register GENX_Input, Register GENY_Input, Register GENC_Input) : GENX(GENX_Input), GENY(GENY_Input), GENC(GENC_Input)
    {
        GENX = GENX_Input;
        GENY = GENY_Input;
        GENC = GENC_Input;
    }

    void update(int opcode, int operand);

    void setScreen(std::array<std::array<int, 400>, 400> RAM_Input)
    {
        SCREEN = RAM_Input;

        /* for (int i = 100 - 1; i >= 0; i--)
             std::cout << RAM_INTERAL[i] << ", "; */
    }
};