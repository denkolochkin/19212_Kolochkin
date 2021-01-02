#include "BlackJack.h"
#include <vector>

int main (int argc, char *argv[]) {
    BlackJack game;
    game.CardMode = EASY;
    game.GameMode = 0;
    game.NumberOfDecks = 2;
    srand(time(0));
    if (argv[1][0] == 100) {
        game.GameMode = DETAILED;
        std::vector<std::string> Players;
        for (int i = 2; i <= argc - 1; ++i) {
            Players.push_back(argv[i]);
        }
        game.Tournament(Players);
    }
    if (argv[1][0] == 116) {
        game.GameMode = TOURNAMENT;
        std::vector<std::string> Players;
        for (int i = 2; i <= argc - 1; ++i) {
            Players.push_back(argv[i]);
        }
        game.Tournament(Players);
    }
    if (argv[1][0] == 102) {
        game.GameMode = FAST;
        std::vector<std::string> Players;
        Players.push_back(argv[2]);
        Players.push_back(argv[3]);
        game.fast(Players);
    }
    return 0;
}
