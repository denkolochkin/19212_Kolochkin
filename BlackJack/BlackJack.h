#pragma once

#include "Factory.h"
#include "Strategy.h"

#include <iostream>
#include <vector>

class BlackJack {
public:
    BlackJack();
    ~BlackJack();
    int ChooseWinner(int first, std::string firstName, int second, std::string secondName);

    std::unique_ptr<Strategy>& TournamentOfTwo(
                                    std::unique_ptr<Strategy> &first, std::string firstName,
                                    std::unique_ptr<Strategy> &second, std::string secondName,
                                    int Mode, int NumberOfDecks, int GameMode
                                    );

    void fast(std::string first, std::string second, int CardMode, int NumberOfDecks, int GameMode);

    void Tournament(std::vector<std::string> Players, int CardMode, int NumberOfDecks, int GameMode);

    std::vector<std::string> currentPlayers; //for test
};
