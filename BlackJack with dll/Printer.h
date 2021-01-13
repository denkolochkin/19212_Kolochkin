#pragma once

#include <iostream>
#include <vector>
#include <string>

enum modes {
    Pass, EASY, DECK, HARD, QUIT, DETAILED, TOURNAMENT, FAST
};

const int TwentyOne = 21;

class Printer {
public:
    Printer(int first_, int second_, std::string firstName_, std::string secondName_)
                    : first(first_), second(second_),
                     firstName(firstName_), secondName(secondName_){};

    Printer(std::string detailsName_)
            : detailsName(detailsName_){};

    ~Printer() = default;

    int PrintWinner() {
        std::cout<<"***Results of tournament***"<<std::endl;
        if (first == Pass) {
            if (second <= TwentyOne) {
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
            if (first <= TwentyOne) {
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
        if (first == TwentyOne) {
            std::cout<<firstName<<" - BlackJack"<<std::endl;
            std::cout<<secondName<<" - "<<second<<std::endl;
            printf("\n");
            return first;
        }
        if (second == TwentyOne) {
            std::cout<<secondName<<" - BlackJack"<<std::endl;
            std::cout<<firstName<<" - "<<second<<std::endl;
            printf("\n");
            return second;
        }
        if (first > TwentyOne) {
            if (second < TwentyOne) {
                std::cout<<secondName<<" win with result: "<<second<<std::endl;
                std::cout<<firstName<<" lose with result: "<<first<<std::endl;
                printf("\n");
                return second;
            }
            std::cout<<firstName<<" vs "<<secondName<<" - no winner"<< std::endl;
            printf("\n");
            return 0;
        }
        if (second > TwentyOne) {
            if (first < TwentyOne) {
                std::cout<<firstName<<" win with result: "<<first<<std::endl;
                std::cout<<secondName<<" lose with result: "<<second<<std::endl;
                printf("\n");
                return first;
            }
            std::cout<<firstName<<" vs "<<secondName<<" - no winner"<< std::endl;
            printf("\n");
            return 0;
        }
        if (first <= TwentyOne && second <= TwentyOne) {
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
    };

    int PrintDetails(std::vector<int> History, int CurrentCard) {
        std::cout<<"Details of "<<detailsName<<" strategy:"<<std::endl;
        std::cout<<"New card - "<<CurrentCard<<std::endl;
        std::cout<<"Cards of "<<detailsName<<" strategy strategy now: ";
        for (int i = 0; i < History.size(); ++i) {
            std::cout<<History[i]<< " ";
        }
        if (getchar() == 113) {
            return QUIT;
        }
    };

    void PrintPass() {
        std::cout<<detailsName<<" strategy - pass"<<std::endl;
    };

private:
    int first;
    int second;
    std::string firstName;
    std::string secondName;
    std::string detailsName;
};

