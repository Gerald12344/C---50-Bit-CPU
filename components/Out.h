#include <string>
#include "../SubClasses/Logger.h"
#include "../SubClasses/Register.h"

class Out
{
private:
    Register OUT_REG;

public:
    Out(Register OUT_Input) : OUT_REG(OUT_Input)
    {
        OUT_REG = OUT_Input;
    }

    void update(int opcode, int operand);
};