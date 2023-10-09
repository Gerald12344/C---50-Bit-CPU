#include <string>
#include "../SubClasses/Logger.h"
#include "../SubClasses/Register.h"

class ALU
{
private:
    Register REG_A;
    Register REG_B;
    Register REG_C;
    Register REG_D;
    Register ACC;

    bool ZERO;
    bool NEGATIVE;

public:
    ALU(Register A, Register B, Register C, Register D, Register ALU) : REG_A(A), REG_B(B), REG_C(C), REG_D(D), ACC(ALU)
    {
        REG_A = A;
        REG_B = B;
        REG_C = C;
        REG_D = D;
        ACC = ALU;
    }

    void update(unsigned int opcode, unsigned int operand);

    void calculate();
};