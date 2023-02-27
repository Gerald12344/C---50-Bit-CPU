#include <string>
#include "../SubClasses/Logger.h"
#include "../SubClasses/Register.h"

class ALU
{
private:
    Register REG_A;
    Register REG_B;
    Register ACC;

    bool ZERO;
    bool NEGATIVE;

public:
    ALU(Register A, Register B, Register ALU) : REG_A(A), REG_B(B), ACC(ALU)
    {
        REG_A = A;
        REG_B = B;
        ACC = ALU;
    }

    void update(int opcode, int operand);

    void calculate();
};