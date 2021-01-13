#include "BlackJack.h"

int main (int argc, char *argv[]) {
    srand(time(0));
    if (argv[1][0] == 'd') {
        std::vector<std::string> Players;
        for (int i = 2; i <= argc - 1; ++i) {
            Players.push_back(argv[i]);
        }
        BlackJack game(Players, EASY, 2, DETAILED);
        game.Tournament(Players);
    }
    if (argv[1][0] == 't') {
        std::vector<std::string> Players;
        for (int i = 2; i <= argc - 1; ++i) {
            Players.push_back(argv[i]);
        }
        BlackJack game(Players, EASY, 2, TOURNAMENT);
        game.Tournament(Players);
    }
    if (argv[1][0] == 'f') {
        std::vector<std::string> Players;
        Players.push_back(argv[2]);
        Players.push_back(argv[3]);
        BlackJack game(Players, EASY, 2, FAST);
        game.fast(Players[0], Players[1]);
    }
    return 0;
}
