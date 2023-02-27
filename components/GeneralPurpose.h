#include <string>
#include "../SubClasses/Logger.h"
#include "../SubClasses/Register.h"

class GEN
{
private:
    Register GEN_REG;

public:
    GEN(Register GEN_Input) : GEN_REG(GEN_Input)
    {
        GEN_REG = GEN_Input;
    }

    void update(int opcode, int operand);
};