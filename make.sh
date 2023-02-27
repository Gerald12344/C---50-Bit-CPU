#!/bin/bash

g++ main.cpp ControlUnit.cpp SubClasses/Register.cpp SubClasses/Logger.cpp components/ALU.cpp components/GeneralPurpose.cpp components/ProgramCounter.cpp components/Out.cpp components/RAM.cpp components/GPU.cpp
./a.out