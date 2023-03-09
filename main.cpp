#include "main.h"
#include <iostream>
#include <bitset>
#include <array>
#include <cmath>
#include "SubClasses/Register.h"
#include "SubClasses/Logger.h"
#include "components/ALU.h"
#include "components/GeneralPurpose.h"
#include "components/ProgramCounter.h"
#include "components/Out.h"
#include "components/RAM.h"
#include "components/GPU.h"
#include <sys/time.h>
#include <future>

using namespace std;

// ----------CONFIG----------
int BIT_WIDTH = 50;
bool DEBUG = true;
int PC_COUNTER = 0;

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
    switch (opcode)
    {
    case 0b00000001:
        ALU_COMP.update(opcode, operand);
        GEN_COMP.update(opcode, operand);
        OUT_COMP.update(opcode, operand);
        RAM_COMP.update(opcode, operand);
        break;
    case 0b00000010:
        ALU_COMP.update(opcode, operand);
        GEN_COMP.update(opcode, operand);
        RAM_COMP.update(opcode, operand);
        GPU_COMP.update(opcode, operand);
        PC_COMP.update(opcode, operand);
        break;
    case 0b00000100:
        PC_COMP.update(opcode, operand);
        break;
    case 0b00000101:
        PC_COMP.update(opcode, operand);
        break;
    case 0b00000110:
        OUT_COMP.update(opcode, operand);
        break;
    case 0b00001000:
        RAM_COMP.update(opcode, operand);
        PC_COMP.update(opcode, operand);
        break;
    case 0b00001001:
        GEN_COMP.update(opcode, operand);
        break;
    case 0b00001011:
        GEN_COMP.update(opcode, operand);
        break;
    case 0b00001100:
        GEN_COMP.update(opcode, operand);
        break;
    case 0b00001101:
        ALU_COMP.update(opcode, operand);
        break;
    case 0b00001110:
        ALU_COMP.update(opcode, operand);
        break;
    case 0b00001111:
        RAM_COMP.update(opcode, operand);
        break;
    case 0b00010000:
        RAM_COMP.update(opcode, operand);
        break;
    case 0b00010001:
        GEN_COMP.update(opcode, operand);
        break;
    case 0b00010010:
        GEN_COMP.update(opcode, operand);
        break;
    }
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

    switch (data)
    {
    case 0b00000000:
        ADD = true;
        break;
    case 0b00000001:
        SUB = true;
        break;
    case 0b00000010:
        MUL = true;
        break;
    case 0b00000011:
        DIV = true;
        break;
    case 0b00000100:
        MOD = true;
        break;
    case 0b00000101:
        COMP = true;
        break;
    case 0b00000110:
        AND = true;
        break;
    default:
        break;
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

    // Logger("Opcode: " + std::to_string(opcode));
    // Logger("Operand: " + std::to_string(operand));
    // Logger("Databus:" + std::to_string(DataBus));

    // Increment PC
    updateComponents(0b00000100, 0, "N/A");

    // -----Decode----- \\


    // -----Execute----- \\

    updateComponents(opcode, operand, "N/A");

    cout << "Opcode: " << opcode << endl;

    if (opcode == 0)
    {
        HLT = true;
        // Logger("PROGRAM HALTED");
    }

    if (opcode == 0b00000111)
    {
        flagHandler(operand);
    }

    // Logger("----------------");
}

void fasterPulse()
{
    updateComponents(0b00001000, 0, "N/A");

    // Data Bus --> Control Unit
    int opcode = DataBus >> (BIT_WIDTH / 2);
    int operand = DataBus & (int)std::pow(2, BIT_WIDTH / 2) - 1;

    // -----Decode----- \\


    // -----Execute----- \\

    updateComponents(opcode, operand, "N/A");

    switch (opcode)
    {
    case 0b00000111:
        flagHandler(operand);
        break;
    case 0:
        HLT = true;
        // Logger("PROGRAM HALTED");
        break;
    }
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
    std::array<int, 100000> RAM_INTERAL = {301989988, 402653194, 100663296, 301992788, 402653192, 503316480, 100663296, 536870912,
                                           369098761, 402653187, 100663296, 301989889, 402653188, 100663296, 234881025, 100663296,
                                           536870912, 369098761, 402653187, 369098757, 402653192, 402653191, 201326592, 436207642,
                                           503316480, 167772176, 0};
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
            cout << "Time Taken: " << diff << "ms and operated at " << (intClicks / seconds) / pow(10, 6) << "MHz with a total of " << clicks << " clock cycles and the time per cycle is " << (seconds / intClicks) * pow(10, 9) << " nano seconds" << endl;
            intClicks = 0;
            tempStart = getMS();
        }
        fasterPulse();
    }

    long int end = getMS();

    cout << "Program Ended" << endl;
    int diff = end - start;
    float seconds = diff / 1000.0;

    cout << "Time Taken: " << end - start << "ms and operated at " << (clicks / seconds) / pow(10, 6) << "MHz with a total of " << clicks << " clock cycles and each cycle took " << (seconds / clicks) * pow(10, 9) << " nano seconds" << endl;

    return 0;
}