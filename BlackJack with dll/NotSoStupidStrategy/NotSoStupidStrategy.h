#pragma once

#include "../Strategy.h"

#include <vector>

class NotSoStupidStrategy : public Strategy {
public:
    NotSoStupidStrategy() = default;

    ~NotSoStupidStrategy() = default;

    int play(int DealerCard) override;

    std::string getName() { return Name; };

private:
    std::string Name = "NotSoStupid";
};

extern "C" {
    void create();
}
