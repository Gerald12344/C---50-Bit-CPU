#!/bin/bash
g++ main.cpp ControlUnit.cpp SubClasses/Register.cpp SubClasses/Logger.cpp components/ALU.cpp components/GeneralPurpose.cpp components/ProgramCounter.cpp components/Out.cpp components/RAM.cpp components/GPU.cpp -O3 

#/opt/intel/oneapi/compiler/latest/mac/bin/intel64/icc main.cpp ControlUnit.cpp SubClasses/Register.cpp SubClasses/Logger.cpp components/ALU.cpp components/GeneralPurpose.cpp components/ProgramCounter.cpp components/Out.cpp components/RAM.cpp components/GPU.cpp -O3 -o a.out
./a.out