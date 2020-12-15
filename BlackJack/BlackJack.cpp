#include "BlackJack.h"

#include <iostream>
#include <vector>

int BlackJack::ChooseWinner(int first, std::string firstName, int second, std::string secondName) {
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

std::unique_ptr<Strategy>& BlackJack::TournamentOfTwo(
                                                       std::unique_ptr<Strategy>& first,
                                                       std::string firstName,
                                                       std::unique_ptr<Strategy>& second,
                                                       std::string secondName,
                                                       int Mode, int NumberOfDecks, int GameMode
                                                       ) {
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

void BlackJack::fast (std::string first, std::string second, int CardMode, int NumberOfDecks, int GameMode) {
    std::unique_ptr<Strategy> FirstStrategy(
                                            Factory<Strategy, std::string, Strategy *(*)()>::
                                            getInstance()->makeStrategy(first)
                                            );
    std::unique_ptr<Strategy> SecondStrategy(
                                             Factory<Strategy, std::string, Strategy *(*)()>::
                                             getInstance()->makeStrategy(second)
                                             );
    std::unique_ptr<Strategy> &Winner = TournamentOfTwo(
                                                    FirstStrategy, first,
                                                    SecondStrategy, second,
                                                        CardMode, NumberOfDecks, GameMode
                                                       );
}

void BlackJack::Tournament(std::vector<std::string> Players , int CardMode, int NumberOfDecks, int GameMode) {
    std::string first;
    std::string second;
    for (int i = 0; i < Players.size() - 1; ++i) {
        for (int j = i + 1; j < Players.size(); ++j) {
            first = Players[i];
            second = Players[j];
            std::unique_ptr<Strategy> FirstStrategy (Factory<Strategy, std::string, Strategy *(*)()>::
                                                     getInstance()->makeStrategy(first));
            std::unique_ptr<Strategy> SecondStrategy (Factory<Strategy, std::string, Strategy *(*)()>::
                                                      getInstance()->makeStrategy(second));
            std::unique_ptr<Strategy> &Winner = TournamentOfTwo(FirstStrategy, first,
                                                                SecondStrategy, second,
                                                                    CardMode, NumberOfDecks, GameMode);
        }
    }
}
