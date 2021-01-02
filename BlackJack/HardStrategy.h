#pragma once

#include "Strategy.h"

#include <vector>

class HardStrategy : public Strategy {
public:
    ~HardStrategy(){}
    int takeCard(int CardMode, int NumberOfDecks) override;
    int play(int DealerCard, int Mode, int NumberOfDecks, int GameMode) override;
    int details(std::vector<int> History, int CurrentCard) override;
};
