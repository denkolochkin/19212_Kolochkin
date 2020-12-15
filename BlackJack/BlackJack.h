#include "Factory.h"
#include "Strategy.h"

#include <iostream>
#include <vector>

enum modes {
    Pass, EASY, DECK, HARD, QUIT, DETAILED, TOURNAMENT, FAST
};

class BlackJack {
public:
    BlackJack();
    ~BlackJack();
    static int ChooseWinner(int first, std::string firstName, int second, std::string secondName);

    static std::unique_ptr<Strategy>& TournamentOfTwo(
                                    std::unique_ptr<Strategy> &first, std::string firstName,
                                    std::unique_ptr<Strategy> &second, std::string secondName,
                                    int Mode, int NumberOfDecks, int GameMode
                                    );

    static void fast(std::string first, std::string second, int CardMode, int NumberOfDecks, int GameMode);

    static void Tournament(std::vector<std::string> Players, int CardMode, int NumberOfDecks, int GameMode);

};
