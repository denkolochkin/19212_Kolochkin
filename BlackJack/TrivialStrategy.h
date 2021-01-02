#pragma once

#include "Strategy.h"

#include <vector>

class TrivialStrategy : public Strategy {
public:
    ~TrivialStrategy(){}
    int takeCard(int CardMode, int NumberOfDecks) override;
    int play(int DealerCard, int Mode, int NumberOfDecks, int GameMode) override;
    int details(std::vector<int> History, int CurrentCard) override;
};
