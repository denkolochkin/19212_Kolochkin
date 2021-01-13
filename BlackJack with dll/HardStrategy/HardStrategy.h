#pragma once

#include "../Strategy.h"

class HardStrategy : public Strategy {
public:
    HardStrategy() = default;

    ~HardStrategy() = default;

    int play(int DealerCard) override;

    std::string getName() { return Name; };

private:
    std::string Name = "Hard";
};

extern "C" {
    void create();
}


