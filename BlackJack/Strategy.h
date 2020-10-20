#include <iostream>
#pragma once

class Strategy {
public:
    virtual int takeCard() = 0;
    virtual int play(int, int) = 0;
    virtual ~Strategy(){};
};

