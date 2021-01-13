#pragma once

#include "Strategy.h"

#include <string>

class BlackJack {
public:
    BlackJack(std::vector<std::string> currentPlayers_, int CardMode_,
              int NumberOfDecks_, int GameMode_
              );

    ~BlackJack() = default;

    BlackJack(BlackJack& b) = delete;

    BlackJack& operator=(BlackJack& b) = delete;

    std::unique_ptr<Strategy>& TournamentOfTwo(
                                    std::unique_ptr<Strategy> &first, std::string firstName,
                                    std::unique_ptr<Strategy> &second, std::string secondName
                                    );

    void fast(std::string Player1, std::string Player2);

    void Tournament(std::vector<std::string> Players);
    //for tests
    std::vector<std::string> getPlayers() { return currentPlayers; };
    //for dll
    void Register();

    std::string WinnerName;

private:
    std::vector<std::string> currentPlayers;
    int CardMode;
    int NumberOfDecks;
    int GameMode;
};