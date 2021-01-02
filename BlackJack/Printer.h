#pragma once

#include <string>

class Printer {
public:
    Printer(){};
    ~Printer(){};
    int PrintWinner();
    int first;
    int second;
    std::string firstName;
    std::string secondName;
};

