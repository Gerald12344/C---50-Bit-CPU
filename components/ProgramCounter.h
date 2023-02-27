#include <string>
#include "../SubClasses/Logger.h"
#include "../SubClasses/Register.h"

class ProgramCounter
{
private:
    Register PC_REG;

public:
    ProgramCounter(Register PC_Input) : PC_REG(PC_Input)
    {
        PC_REG = PC_Input;
    }

    void update(int opcode, int operand);
};