#pragma once

#include "../Strategy.h"

class StupidStrategy : public Strategy {
public:
    StupidStrategy() = default;

    ~StupidStrategy() = default;

    int play(int DealerCard) override;

    std::string getName() { return Name; };

private:
    std::string Name = "Stupid";
};

extern "C" {
    void create();
}
