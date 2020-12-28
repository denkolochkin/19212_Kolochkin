#pragma once

#include <iostream>

enum modes {
    Pass, EASY, DECK, HARD, QUIT, DETAILED, TOURNAMENT, FAST
};

const int TwentyOne = 21;

class Strategy {
public:
    virtual int takeCard(int CardMode, int NumberOfDecks) = 0;
    virtual int play(int DealerCard, int Mode, int NumberOfDecks, int GameMode) = 0;
    virtual int details(std::vector<int> History, int CurrentCard) = 0;
    virtual ~Strategy(){};
};
