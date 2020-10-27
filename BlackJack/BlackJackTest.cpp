#include "gtest/gtest.h"
#include "../main.cpp"
#define Pass -1
#define EASY 1
#define DECK 2
#define HARD 3
#define DETAILED 0
#define TOURNAMENT 1
#define FAST 4
#define QUIT -1

namespace {
    class BlackJackTest : public ::testing::Test {};

    TEST_F(BlackJackTest, fast) {
        srand(time(0));
        int CardMode = EASY;
        int GameMode = FAST;
        int NumberOfDecks = 2;
        std::string first = "Base";
        std::string second = "Trivial";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
    }

    TEST_F(BlackJackTest, fast_deck) {
        srand(time(0));
        int CardMode = DECK;
        int GameMode = DETAILED;
        int NumberOfDecks = 2;
        std::string first = "Stupid";
        std::string second = "Hard";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
    }

    TEST_F(BlackJackTest, tournament) {
        srand(time(0));
        int CardMode = HARD;
        int GameMode = TOURNAMENT;
        int NumberOfDecks = 2;
        std::vector<std::string> Players;
        std::string first = "NotSoStupid";
        std::string second = "Neat";
        std::string third = "Base";
        Players.push_back(first);
        Players.push_back(second);
        Players.push_back(third);
        Tournament(Players, CardMode, NumberOfDecks, GameMode);
    }
}
