#include "Printer.h"
#include "Strategy.h"

#include <iostream>

int Printer::PrintWinner() {
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
}