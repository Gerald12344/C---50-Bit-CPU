#include "GPU.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <string>
#include <iostream>
#include <fstream>
#include <array>

extern int DataBus;
int screensize = 400;

void GPU::update(int opcode, int operand)
{
    if (opcode == 0b00000001)
    {
        if (operand == 0b00001011)
        {
            GPU::GENX.setValue(DataBus);
        }
        if (operand == 0b00001100)
        {
        GPU:
            GENY.setValue(DataBus);
        }
        if (operand == 0b00001101)
        {
            GPU::GENC.setValue(DataBus);
        }
    }

    if (opcode == 0b00000010)
    {
        if (operand == 0b00001011)
        {
            DataBus = GPU::GENX.getValue();
        }
        if (operand == 0b00001100)
        {

            DataBus = GPU::GENY.getValue();
        }
        if (operand == 0b00001101)
        {
            DataBus = GPU::GENC.getValue();
        }
    }

    if (opcode == 0b00010001)
    {
        if (GPU::GENX.getValue() > screensize - 1 || GPU::GENY.getValue() > screensize - 1 || GPU::GENX.getValue() < 0 || GPU::GENY.getValue() < 0)
            return;

        GPU::SCREEN[GPU::GENY.getValue()][GPU::GENX.getValue()] = GPU::GENC.getValue();
    }

    if (opcode == 0b00010011)
    {
        std::string text = "";

        for (int i = 0; i < screensize; i++)
        {
            for (int j = 0; j < screensize; j++)
            {
                text += std::to_string(GPU::SCREEN[i][j]) + ',';
            }
            text += "|";
        }

        std::ofstream MyFile("filename.txt");

        // Write to the file
        MyFile << text;

        // Close the file
        MyFile.close();
    }

    if (opcode == 0b00010010)
    {
        std::array<std::array<int, 400>, 400> NEWSCREEN;
        GPU::SCREEN = NEWSCREEN;
    }
}