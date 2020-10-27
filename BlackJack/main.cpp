#include <iostream>
#include "Factory.h"
#include "Strategy.h"
#include <vector>
#define Pass -1
#define EASY 1
#define DECK 2
#define HARD 3
#define DETAILED 0
#define TOURNAMENT 1
#define FAST 4
#define QUIT -1

int ChooseWinner (int first, std::string firstName, int second, std::string secondName) {
    std::cout<<"***Results of tournament***"<<std::endl;
    if (first == Pass) {
        if (second <= 21) {
            std::cout<<secondName<<" win with result: "<<second<<std::endl;
            std::cout<<firstName<<" lose - pass"<<std::endl;
            printf("\n");
            return 0;
        }
        else {
            std::cout<<firstName<<" vs "<<secondName<<" - no winner"<<std::endl;
            printf("\n");
            return 0;
        }
    }
    if (second == Pass) {
        if (first <= 21) {
            std::cout<<firstName<<" win with result: "<<first<<std::endl;
            std::cout<<secondName<<" lose - pass"<<std::endl;
            printf("\n");
            return first;
        }
        else {
            std::cout<<firstName<<" vs "<<secondName<<" - no winner"<< std::endl;
            printf("\n");
            return 0;
        }
    }
    if (first == 21) {
        std::cout<<firstName<<" - BlackJack"<<std::endl;
        std::cout<<secondName<<" - "<<second<<std::endl;
        printf("\n");
        return first;
    }
    if (second == 21) {
        std::cout<<secondName<<" - BlackJack"<<std::endl;
        std::cout<<firstName<<" - "<<second<<std::endl;
        printf("\n");
        return second;
    }
    if (first > 21) {
        if (second < 21) {
            std::cout<<secondName<<" win with result: "<<second<<std::endl;
            std::cout<<firstName<<" lose with result: "<<first<<std::endl;
            printf("\n");
            return second;
        }
        std::cout<<firstName<<" vs "<<secondName<<" - no winner"<< std::endl;
        printf("\n");
        return 0;
    }
    if (second > 21) {
        if (first < 21) {
            std::cout<<firstName<<" win with result: "<<first<<std::endl;
            std::cout<<secondName<<" lose with result: "<<second<<std::endl;
            printf("\n");
            return first;
        }
        std::cout<<firstName<<" vs "<<secondName<<" - no winner"<< std::endl;
        printf("\n");
        return 0;
    }
    if (first <= 21 && second <= 21) {
        if (first < second) {
            std::cout<<secondName<<" win with result: "<<second<<std::endl;
            std::cout<<firstName<<" lose with result: "<<first<<std::endl;
            printf("\n");
            return second;
        }
        if (first > second) {
            std::cout<<firstName<<" win with result: "<<first<<std::endl;
            std::cout<<secondName<<" lose with result: "<<second<<std::endl;
            printf("\n");
            return first;
        }
    }
}

std::unique_ptr<Strategy>& TournamentOfTwo (std::unique_ptr<Strategy>& first, std::string firstName, std::unique_ptr<Strategy>& second,std::string secondName, int Mode, int NumberOfDecks, int GameMode) {
    int DealerCard = first->takeCard(Mode, NumberOfDecks);
    int ResultOfFirst = first->play(DealerCard, Mode, NumberOfDecks, GameMode);
    if (ResultOfFirst == QUIT) {
        first = nullptr;
        return first;
    }
    int ResultOfSecond = second->play(DealerCard, Mode, NumberOfDecks, GameMode);
    if (ResultOfSecond == QUIT) {
        second = nullptr;
        return second;
    }
    int ResultOfWinner =  ChooseWinner(ResultOfFirst, firstName, ResultOfSecond, secondName);
    if (ResultOfWinner == ResultOfFirst) {
        return first;
    }
    else {
        return second;
    }
}

void fast (std::string first, std::string second, int CardMode, int NumberOfDecks, int GameMode) {
    std::unique_ptr<Strategy> FirstStrategy(Factory<Strategy, std::string, Strategy *(*)()>::getInstance()->makeStrategy(first));
    std::unique_ptr<Strategy> SecondStrategy(Factory<Strategy, std::string, Strategy *(*)()>::getInstance()->makeStrategy(second));
    std::unique_ptr<Strategy> &Winner = TournamentOfTwo(FirstStrategy, first, SecondStrategy, second, CardMode, NumberOfDecks, GameMode);
}

void Tournament(std::vector<std::string> Players , int CardMode, int NumberOfDecks, int GameMode) {
    std::string first;
    std::string second;
    for (int i = 0; i < Players.size() - 1; ++i) {
        for (int j = i + 1; j < Players.size(); ++j) {
            first = Players[i];
            second = Players[j];
            std::unique_ptr<Strategy> FirstStrategy (Factory<Strategy, std::string, Strategy *(*)()>::getInstance()->makeStrategy(first));
            std::unique_ptr<Strategy> SecondStrategy (Factory<Strategy, std::string, Strategy *(*)()>::getInstance()->makeStrategy(second));
            std::unique_ptr<Strategy> &Winner = TournamentOfTwo(FirstStrategy, first, SecondStrategy, second, CardMode, NumberOfDecks, GameMode);
        }
    }
}

int main (int argc, char *argv[]) {
    int CardMode = EASY;
    int NumberOfDecks = 2;
    int GameMode = 0;

    if (argv[1][0] == 100) {
        GameMode = DETAILED;
    }
    if (argv[1][0] == 116) {
        GameMode = TOURNAMENT;
    }
    if (argv[1][0] == 102) {
        GameMode = FAST;
    }

    srand(time(0));

    if (GameMode == FAST) {
        std::string first = argv[2];
        std::string second = argv[3];
        fast(first, second, CardMode, NumberOfDecks, GameMode);
    }

    if (GameMode == TOURNAMENT) {
        std::vector<std::string> Players;
        std::string first;
        std::string second;
        for (int i = 2; i <= argc - 1; ++i) {
            Players.push_back(argv[i]);
        }
        Tournament(Players, CardMode, NumberOfDecks, GameMode);
    }

    if (GameMode == DETAILED) {
        std::vector<std::string> Players;
        for (int i = 2; i <= argc - 1; ++i) {
            Players.push_back(argv[i]);
        }
        Tournament(Players, CardMode, NumberOfDecks, GameMode);
    }

    return 0;
}
