#include "gtest/gtest.h"
#include "BlackJack.h"

namespace {
    class BlackJackTest : public ::testing::Test {};
    TEST_F(BlackJackTest, fast) {
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Base");
        Players.push_back("Trivial");
        BlackJack game(Players, EASY, 2, FAST);
        game.fast(Players[0], Players[1]);
        EXPECT_TRUE(game.WinnerName == "Base" || game.WinnerName == "Trivial");
        Players.clear();
        Players.push_back("Stupid");
        Players.push_back("Neat");
        game.fast(Players[0], Players[1]);
        EXPECT_TRUE(game.WinnerName == "Stupid" || game.WinnerName == "Neat");
        Players.clear();
        Players.push_back("Hard");
        Players.push_back("NotSoStupid");
        game.fast(Players[0], Players[1]);
        EXPECT_TRUE(game.WinnerName == "Hard" || game.WinnerName == "NotSoStupid");
    }

    TEST_F(BlackJackTest, fast_deck) {
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Base");
        Players.push_back("Trivial");
        BlackJack game(Players, DECK, 2, FAST);
        game.fast(Players[0], Players[1]);
        EXPECT_TRUE(game.WinnerName == "Base" || game.WinnerName == "Trivial");
        Players.clear();
        Players.push_back("Stupid");
        Players.push_back("Neat");
        game.fast(Players[0], Players[1]);
        EXPECT_TRUE(game.WinnerName == "Stupid" || game.WinnerName == "Neat");
        Players.clear();
        Players.push_back("Hard");
        Players.push_back("NotSoStupid");
        game.fast(Players[0], Players[1]);
        EXPECT_TRUE(game.WinnerName == "Hard" || game.WinnerName == "NotSoStupid");
    }

    TEST_F(BlackJackTest, hard) {
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Base");
        Players.push_back("Trivial");
        BlackJack game(Players, EASY, 2, HARD);
        game.fast(Players[0], Players[1]);
        EXPECT_TRUE(game.WinnerName == "Base" || game.WinnerName == "Trivial");
        Players.clear();
        Players.push_back("Stupid");
        Players.push_back("Neat");
        game.fast(Players[0], Players[1]);
        EXPECT_TRUE(game.WinnerName == "Stupid" || game.WinnerName == "Neat");
        Players.clear();
        Players.push_back("Hard");
        Players.push_back("NotSoStupid");
        game.fast(Players[0], Players[1]);
        EXPECT_TRUE(game.WinnerName == "Hard" || game.WinnerName == "NotSoStupid");
    }

    TEST_F(BlackJackTest, tournament_for_3) {
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        Players.push_back("Neat");
        BlackJack game(Players, DECK, 2, DETAILED);
        game.Tournament(Players);
        EXPECT_TRUE(game.getPlayers() == Players);
        Players.clear();
        Players.push_back("Base");
        Players.push_back("Stupid");
        Players.push_back("Hard");
        game.Tournament(Players);
        EXPECT_TRUE(game.getPlayers() == Players);
    }

    TEST_F(BlackJackTest, tournament_for_4) {
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        Players.push_back("Neat");
        Players.push_back("Stupid");
        BlackJack game(Players, TOURNAMENT, 2, DECK);
        game.Tournament(Players);
        EXPECT_TRUE(game.getPlayers() == Players);
    }

    TEST_F(BlackJackTest, fake_tournament) {
        srand(time(0));
        std::vector<std::string> Players;
        BlackJack game(Players, DECK, 2, TOURNAMENT);
        game.Tournament(Players);
        EXPECT_TRUE(game.getPlayers().size() == 0);
    }

}
