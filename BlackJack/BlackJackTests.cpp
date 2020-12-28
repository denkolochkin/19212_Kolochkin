#include "gtest/gtest.h"
#include "BlackJack.h"

namespace {

    class BlackJackTest : public ::testing::Test {};
    TEST_F(BlackJackTest, fast) {
        BlackJack game;
        srand(time(0));
        int CardMode = EASY;
        int GameMode = FAST;
        int NumberOfDecks = 2;
        std::string first = "Base";
        std::string second = "Trivial";
        game.fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Base";
        second = "Neat";
        game.fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Trivial";
        second = "NotSoStupid";
        game.fast(first, second, CardMode, NumberOfDecks, GameMode);
    }

    TEST_F(BlackJackTest, fast_deck) {
        BlackJack game;
        srand(time(0));
        int CardMode = DECK;
        int GameMode = FAST;
        int NumberOfDecks = 2;
        std::string first = "Stupid";
        std::string second = "Hard";
        game.fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Base";
        second = "Neat";
        game.fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Trivial";
        second = "NotSoStupid";
        game.fast(first, second, CardMode, NumberOfDecks, GameMode);
    }

    TEST_F(BlackJackTest, hard) {
        BlackJack game;
        srand(time(0));
        int CardMode = HARD;
        int GameMode = FAST;
        int NumberOfDecks = 2;
        std::string first = "Stupid";
        std::string second = "Hard";
        game.fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Base";
        second = "Neat";
        game.fast(first, second, CardMode, NumberOfDecks, GameMode);
        first = "Trivial";
        second = "NotSoStupid";
        game.fast(first, second, CardMode, NumberOfDecks, GameMode);
    }

    TEST_F(BlackJackTest, tournament_for_3) {
        BlackJack game;
        srand(time(0));
        int CardMode = DECK;
        int GameMode = DETAILED;
        int NumberOfDecks = 2;
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        Players.push_back("Neat");
        game.Tournament(Players, CardMode, NumberOfDecks, GameMode);
        EXPECT_TRUE(game.currentPlayers == Players);
        Players.clear();
        GameMode = DETAILED;
        Players.push_back("Base");
        Players.push_back("Stupid");
        Players.push_back("Hard");
        game.Tournament(Players, CardMode, NumberOfDecks, GameMode);
        EXPECT_TRUE(game.currentPlayers == Players);
    }

    TEST_F(BlackJackTest, tournament_for_4) {
        BlackJack game;
        srand(time(0));
        int CardMode = DECK;
        int GameMode = TOURNAMENT;
        int NumberOfDecks = 2;
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        Players.push_back("Neat");
        Players.push_back("Stupid");
        game.Tournament(Players, CardMode, NumberOfDecks, GameMode);
        EXPECT_TRUE(game.currentPlayers == Players);
    }

    TEST_F(BlackJackTest, fake_tournament) {
        BlackJack game;
        srand(time(0));
        int CardMode = DECK;
        int GameMode = TOURNAMENT;
        int NumberOfDecks = 2;
        std::vector<std::string> Players;
        game.Tournament(Players, CardMode, NumberOfDecks, GameMode);
        EXPECT_TRUE(game.currentPlayers.size() == 0);
    }

}
