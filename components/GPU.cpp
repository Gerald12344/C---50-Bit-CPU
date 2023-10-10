#include "GPU.h"
#include "../SubClasses/Logger.h"
#include "../main.h"
#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <thread>

extern unsigned int DataBus;
unsigned int screensize = 400;

void UpdateScreenBuffer(std::array<std::array<int, 400>, 400> screen)
{
    std::ofstream MyFile("filename.txt");
    std::string text = "";

    for (unsigned int i = 0; i < screensize; i++)
    {
        for (unsigned int j = 0; j < screensize; j++)
        {
            text += std::to_string(screen[i][j]) + ',';
        }
        text += "|";
    }

    // Write to the file
    MyFile << text;

    // Close the file

    MyFile.close();
}

void GPU::update(unsigned int opcode, unsigned int operand)
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

        std::cout << "X: " << GPU::GENX.getValue() << " Y: " << GPU::GENY.getValue() << " C: " << GPU::GENC.getValue() << std::endl;

        GPU::SCREEN[GPU::GENY.getValue()][GPU::GENX.getValue()] = GPU::GENC.getValue();
    }

    if (opcode == 0b00010011)
    {
        UpdateScreenBuffer(GPU::SCREEN);
        // std::thread first(UpdateScreenBuffer, GPU::SCREEN);
        // first.detach();
        //  std::future<void> fut = std::async(UpdateScreenBuffer, GPU::SCREEN);
    }

    if (opcode == 0b00010010)
    {
        std::array<std::array<int, 400>, 400> NEWSCREEN;
        GPU::SCREEN = NEWSCREEN;
    }
}