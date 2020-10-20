#include <iostream>
#pragma once

class Strategy {
public:
    virtual void printName() = 0;
    virtual int TakeCard() = 0;
    virtual int Play(int) = 0;
    virtual ~Strategy(){};
};

