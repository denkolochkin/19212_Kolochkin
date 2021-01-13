#pragma once

#include "../Strategy.h"

class NeatStrategy : public Strategy {
public:
    NeatStrategy() = default;

    ~NeatStrategy() = default;

    int play(int DealerCard) override;

    std::string getName() { return Name; }
private:
    std::string Name = "Neat";
};

extern "C" {
    void create();
}

