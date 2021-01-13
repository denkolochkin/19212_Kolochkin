#pragma once

#include "../Strategy.h"

class BaseStrategy : public Strategy {
public:
    BaseStrategy() = default;

    ~BaseStrategy() = default;

    int play(int DealerCard) override;

    std::string getName() { return Name; };

private:
    std::string Name = "Base";
};

extern "C" {
    void create();
}



