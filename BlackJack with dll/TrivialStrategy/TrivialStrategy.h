#pragma once

#include "../Strategy.h"

class TrivialStrategy : public Strategy {
public:
    TrivialStrategy() = default;

    ~TrivialStrategy() = default;

    int play(int DealerCard) override;

    std::string getName() { return Name; };

private:
    std::string Name = "Trivial";
};

extern "C" {
    void create();
}
