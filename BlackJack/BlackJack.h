#pragma once

#include "Strategy.h"

#include <vector>

class BlackJack {
public:
    BlackJack();
    ~BlackJack();

    std::unique_ptr<Strategy>& TournamentOfTwo(
                                    std::unique_ptr<Strategy> &first, std::string firstName,
                                    std::unique_ptr<Strategy> &second, std::string secondName
                                    );

    void fast(std::vector<std::string> Players);

    void Tournament(std::vector<std::string> Players);

    std::vector<std::string> currentPlayers;
    int CardMode;
    int NumberOfDecks;
    int GameMode;
    std::string WinnerName;
};
