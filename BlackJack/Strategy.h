#include <iostream>
#pragma once

class Strategy {
public:
    virtual int details(std::vector<int>, int) = 0;
    virtual int takeCard(int, int) = 0;
    virtual int play(int, int, int, int) = 0;
    virtual ~Strategy(){};
};
