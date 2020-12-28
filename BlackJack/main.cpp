#include "BlackJack.h"

int main (int argc, char *argv[]) {
    int CardMode = EASY;
    int NumberOfDecks = 2;
    int GameMode = 0;
    srand(time(0));
    if (argv[1][0] == 100) {
        GameMode = DETAILED;
        std::vector<std::string> Players;
        for (int i = 2; i <= argc - 1; ++i) {
            Players.push_back(argv[i]);
        }
        Tournament(Players, CardMode, NumberOfDecks, GameMode);
    }
    if (argv[1][0] == 116) {
        GameMode = TOURNAMENT;
        std::vector<std::string> Players;
        std::string first;
        std::string second;
        for (int i = 2; i <= argc - 1; ++i) {
            Players.push_back(argv[i]);
        }
        Tournament(Players, CardMode, NumberOfDecks, GameMode);
    }
    if (argv[1][0] == 102) {
        GameMode = FAST;
        std::string first = argv[2];
        std::string second = argv[3];
        fast(first, second, CardMode, NumberOfDecks, GameMode);
    }
    return 0;
}
