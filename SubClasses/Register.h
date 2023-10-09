#include <string>

#pragma once
class Register
{
private:
    unsigned int  value;
    std::string friendlyName;

public:
    Register(std::string name)
    {
        value = 0;
        friendlyName = name;
    }

    void setValue(unsigned int  value);

    unsigned int  getValue() { return value; }
};