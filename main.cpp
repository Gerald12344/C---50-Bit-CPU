#include "main.h"
#include <iostream>
#include <bitset>
#include <array>
#include <cmath>
#include "SubClasses/Register.h"
#include "SubClasses/Logger.h"
#include "ControlUnit.h"
#include "components/ALU.h"
#include "components/GeneralPurpose.h"
#include "components/ProgramCounter.h"
#include "components/Out.h"
#include "components/RAM.h"
#include "components/GPU.h"
#include <sys/time.h>

using namespace std;

// ----------CONFIG----------
int BIT_WIDTH = 50;
bool DEBUG = false;

// ----------FLAGS-----------
bool HLT = false;
bool ADD = true;
bool SUB = false;
bool MUL = false;
bool DIV = false;
bool MOD = false;
bool COMP = false;
bool AND = false;

bool Zero = false;
bool Negative = false;

// --------COMPONENTS--------

// Registers
Register MAR("MAR");
Register MDR("MDR");
Register PC("PC");
Register REG_A("RegA");
Register REG_B("RegB");
Register ACC("ACC");
Register GENR("GEN");
Register OUTR("OUT");
Register RIR("RIR");
Register ROR("ROR");
Register RAR("RAR");
Register GPX("GPUX");
Register GPY("GPUY");
Register GPC("GPC");

// Buses
int DataBus = 0;
int ControlBus = 0;

// MainComps
ALU ALU_COMP(REG_A, REG_B, ACC);
GEN GEN_COMP(GENR);
ProgramCounter PC_COMP(PC);
Out OUT_COMP(OUTR);
RAM RAM_COMP(MAR, MDR, RIR, ROR, RAR);
GPU GPU_COMP(GPX, GPY, GPC);

void updateComponents(int opcode, int operand, std::string info)
{

    ALU_COMP.update(opcode, operand);
    GEN_COMP.update(opcode, operand);
    PC_COMP.update(opcode, operand);
    OUT_COMP.update(opcode, operand);
    RAM_COMP.update(opcode, operand);
    GPU_COMP.update(opcode, operand);
}

void flagHandler(int data)
{
    ADD = false;
    SUB = false;
    MUL = false;
    DIV = false;
    MOD = false;
    COMP = false;
    AND = false;

    if (data == 0b00000000)
    {
        ADD = true;
    }
    else if (data == 0b00000001)
    {
        SUB = true;
    }
    else if (data == 0b00000010)
    {
        MUL = true;
    }
    else if (data == 0b00000011)
    {
        DIV = true;
    }
    else if (data == 0b00000100)
    {
        MOD = true;
    }
    else if (data == 0b00000101)
    {
        COMP = true;
    }
    else if (data == 0b00000110)
    {
        AND = true;
    }

    ALU_COMP.calculate();
}

void clockPulse()
{
    // -----FETCH----- \\

    // PC -> Bus
    updateComponents(0b00000010, 0b00000010, "N/A");
    // Bus --> MAR
    updateComponents(0b00000001, 0b00000000, "N/A");
    // MDR --> Data Bus
    updateComponents(0b00000010, 0b00000001, "N/A");
    // Data Bus --> Control Unit
    int opcode = DataBus >> (BIT_WIDTH / 2);
    int operand = DataBus & (int)std::pow(2, BIT_WIDTH / 2) - 1;

    Logger("Opcode: " + std::to_string(opcode));
    Logger("Operand: " + std::to_string(operand));
    Logger("Databus:" + std::to_string(DataBus));

    // Increment PC
    updateComponents(0b00000100, 0, "N/A");

    // -----Decode----- \\


    // -----Execute----- \\

    updateComponents(opcode, operand, "N/A");

    if (opcode == 0)
    {
        HLT = true;
        Logger("PROGRAM HALTED");
    }

    if (opcode == 0b00000111)
    {
        flagHandler(operand);
    }

    Logger("----------------");
}

long int getMS()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    return ms;
}

int main()
{
    std::array<int, 100000> RAM_INTERAL = {301989990, 402653194, 301990288, 402653192, 503316480, 536870912, 369098761, 402653187,
                                           301989889, 402653188, 234881025, 536870912, 369098761, 402653187, 369098757, 402653192,
                                           402653191, 503316480, 402653195, 369098765, 402653187, 301989889, 402653188, 234881024,
                                           369098757, 402653191, 402653197, 570425344, 536870912, 369098761, 234881024, 402653187,
                                           301989888, 402653188, 436207652, 167772165, 369098764, 402653187, 234881024, 301989889,
                                           402653188, 369098757, 402653196, 637534208, 167772160, 0};
    RAM_COMP.setRam(RAM_INTERAL);

    cout << "Starting Program" << endl;
    long int start = getMS();
    int clicks = 0;
    int intClicks = 0;

    long int tempStart = getMS();

    while (HLT == false)
    {
        clicks++;
        intClicks++;
        if (intClicks % 10000000 == 0)
        {
            int diff = getMS() - tempStart;
            float seconds = diff / 1000.0;
            cout << "Time Taken: " << diff << "ms and operated at " << (intClicks / seconds) / pow(10, 6) << "MHz with a total of " << clicks << " clock cycles" << endl;
            intClicks = 0;
            tempStart = getMS();
        }
        clockPulse();
    }

    long int end = getMS();

    cout << "Program Ended" << endl;
    int diff = end - start;
    float seconds = diff / 1000.0;

    cout << "Time Taken: " << end - start << "ms and operated at " << (clicks / seconds) / pow(10, 6) << "MHz with a total of " << clicks << " clock cycles" << endl;

    return 0;
}