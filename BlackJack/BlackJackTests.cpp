#include "gtest/gtest.h"
#include "BlackJack.h"
#define Pass -2
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
        first = "Base";
        second = "Neat";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Trivial";
        second = "NotSoStupid";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
    }

    TEST_F(BlackJackTest, fast_deck) {
        srand(time(0));
        int CardMode = DECK;
        int GameMode = FAST;
        int NumberOfDecks = 2;
        std::string first = "Stupid";
        std::string second = "Hard";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Base";
        second = "Neat";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Trivial";
        second = "NotSoStupid";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
    }

    TEST_F(BlackJackTest, hard) {
        srand(time(0));
        int CardMode = HARD;
        int GameMode = FAST;
        int NumberOfDecks = 2;
        std::string first = "Stupid";
        std::string second = "Hard";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Base";
        second = "Neat";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Trivial";
        second = "NotSoStupid";
        fast(first, second, CardMode, NumberOfDecks, GameMode);
    }

    TEST_F(BlackJackTest, tournament_for_3) {
        srand(time(0));
        int CardMode = DECK;
        int GameMode = DETAILED;
        int NumberOfDecks = 2;
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        Players.push_back("Neat");
        Tournament(Players, CardMode, NumberOfDecks, GameMode);
        GameMode = DETAILED;
        Players.push_back("Base");
        Players.push_back("Stupid");
        Players.push_back("Hard");
        Tournament(Players, CardMode, NumberOfDecks, GameMode);
    }

    TEST_F(BlackJackTest, tournament_for_4) {
        srand(time(0));
        int CardMode = DECK;
        int GameMode = TOURNAMENT;
        int NumberOfDecks = 2;
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        Players.push_back("Neat");
        Players.push_back("Stupid");
        Tournament(Players, CardMode, NumberOfDecks, GameMode);
    }
}
