#include "gtest/gtest.h"
#include "BlackJack.h"

namespace {
    class BlackJackTest : public ::testing::Test {};
    
    TEST_F(BlackJackTest, fast) {
        BlackJack game;
        game.GameMode = FAST;
        game.NumberOfDecks = 2;
        game.CardMode = EASY;
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Base");
        Players.push_back("Trivial");
        game.fast(Players);
        EXPECT_TRUE(game.WinnerName == "Base" || game.WinnerName == "Trivial");
        Players.clear();
        Players.push_back("Stupid");
        Players.push_back("Neat");
        game.fast(Players);
        EXPECT_TRUE(game.WinnerName == "Stupid" || game.WinnerName == "Neat");
        Players.clear();
        Players.push_back("Hard");
        Players.push_back("NotSoStupid");
        game.fast(Players);
        EXPECT_TRUE(game.WinnerName == "Hard" || game.WinnerName == "NotSoStupid");
    }

    TEST_F(BlackJackTest, fast_deck) {
        BlackJack game;
        game.GameMode = FAST;
        game.NumberOfDecks = 2;
        game.CardMode = DECK;
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Base");
        Players.push_back("Trivial");
        game.fast(Players);
        EXPECT_TRUE(game.WinnerName == "Base" || game.WinnerName == "Trivial");
        Players.clear();
        Players.push_back("Stupid");
        Players.push_back("Neat");
        game.fast(Players);
        EXPECT_TRUE(game.WinnerName == "Stupid" || game.WinnerName == "Neat");
        Players.clear();
        Players.push_back("Hard");
        Players.push_back("NotSoStupid");
        game.fast(Players);
        EXPECT_TRUE(game.WinnerName == "Hard" || game.WinnerName == "NotSoStupid");
    }

    TEST_F(BlackJackTest, hard) {
        BlackJack game;
        game.GameMode = HARD;
        game.NumberOfDecks = 2;
        game.CardMode = EASY;
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Base");
        Players.push_back("Trivial");
        game.fast(Players);
        EXPECT_TRUE(game.WinnerName == "Base" || game.WinnerName == "Trivial");
        Players.clear();
        Players.push_back("Stupid");
        Players.push_back("Neat");
        game.fast(Players);
        EXPECT_TRUE(game.WinnerName == "Stupid" || game.WinnerName == "Neat");
        Players.clear();
        Players.push_back("Hard");
        Players.push_back("NotSoStupid");
        game.fast(Players);
        EXPECT_TRUE(game.WinnerName == "Hard" || game.WinnerName == "NotSoStupid");
    }

    TEST_F(BlackJackTest, tournament_for_3) {
        BlackJack game;
        game.GameMode = DETAILED;
        game.CardMode = DECK;
        game.NumberOfDecks = 2;
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        Players.push_back("Neat");
        game.Tournament(Players);
        EXPECT_TRUE(game.currentPlayers == Players);
        Players.clear();
        Players.push_back("Base");
        Players.push_back("Stupid");
        Players.push_back("Hard");
        game.Tournament(Players);
        EXPECT_TRUE(game.currentPlayers == Players);
    }

    TEST_F(BlackJackTest, tournament_for_4) {
        BlackJack game;
        game.GameMode = TOURNAMENT;
        game.CardMode = DECK;
        game.NumberOfDecks = 2;
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        Players.push_back("Neat");
        Players.push_back("Stupid");
        game.Tournament(Players);
        EXPECT_TRUE(game.currentPlayers == Players);
    }

    TEST_F(BlackJackTest, fake_tournament) {
        BlackJack game;
        game.GameMode = TOURNAMENT;
        game.CardMode = DECK;
        game.NumberOfDecks = 2;
        srand(time(0));
        std::vector<std::string> Players;
        game.Tournament(Players);
        EXPECT_TRUE(game.currentPlayers.size() == 0);
    }

    TEST_F(BlackJackTest, BlackJack_equal) {
        BlackJack game;
        BlackJack new_game;
        game.GameMode = TOURNAMENT;
        game.CardMode = DECK;
        game.NumberOfDecks = 2;
        srand(time(0));
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        game = new_game;
        new_game.Tournament(Players);
        EXPECT_TRUE(new_game.currentPlayers == Players);
    }

    TEST_F(BlackJackTest, BlackJack_operator) {
        BlackJack game;
        BlackJack new_game;
        game.GameMode = TOURNAMENT;
        game.CardMode = DECK;
        game.NumberOfDecks = 2;
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        game = new_game;
        EXPECT_TRUE(game == new_game);
    }

    TEST_F(BlackJackTest, BlackJack_other_operator) {
        BlackJack game;
        BlackJack new_game;
        game.GameMode = TOURNAMENT;
        game.CardMode = DECK;
        game.NumberOfDecks = 2;
        std::vector<std::string> Players1;
        Players1.push_back("Trivial");
        Players1.push_back("NotSoStupid");
        game.currentPlayers = Players1;
        new_game.GameMode = TOURNAMENT;
        new_game.CardMode = DECK;
        new_game.NumberOfDecks = 3;
        std::vector<std::string> Players2;
        Players2.push_back("Base");
        Players2.push_back("Stupid");
        new_game.currentPlayers = Players2;
        EXPECT_FALSE(game == new_game);
    }

    TEST_F(BlackJackTest, BlackJack_copy_ctor) {
        BlackJack game;
        game.GameMode = TOURNAMENT;
        game.CardMode = DECK;
        game.NumberOfDecks = 2;
        std::vector<std::string> Players;
        Players.push_back("Trivial");
        Players.push_back("NotSoStupid");
        game.currentPlayers = Players;
        BlackJack new_game(game);
        EXPECT_TRUE(game == new_game);
    }
    
}
