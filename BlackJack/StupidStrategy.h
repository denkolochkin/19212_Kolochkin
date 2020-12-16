#pragma once

#include "Strategy.h"

enum modes {
    Pass, EASY, DECK, HARD, QUIT, DETAILED, TOURNAMENT, FAST
};

class StupidStrategy : public Strategy {
public:
    ~StupidStrategy(){}
    int takeCard(int CardMode, int NumberOfDecks) override;
    int play(int DealerCard, int Mode, int NumberOfDecks, int GameMode) override;
    int details(std::vector<int> History, int CurrentCard) override;
};
