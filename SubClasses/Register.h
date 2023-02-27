#include <string>

#pragma once
class Register
{
private:
    int value;
    std::string friendlyName;

public:
    Register(std::string name)
    {
        value = 0;
        friendlyName = name;
    }

    void setValue(int value);

    int getValue() { return value; }
};