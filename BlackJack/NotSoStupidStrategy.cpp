#include "NotSoStupidStrategy.h"
#include "Factory.h"
#include <iostream>
#include <vector>
#define Pass -1

static bool g(){
    Factory<Strategy, std::string,Strategy*(*)()>::getInstance()->addCreator("NotSoStupid", createNotSoStupidStrategy);
    return true;
}

static bool b=g();

Strategy *createNotSoStupidStrategy () {
    return new NotSoStupidStrategy;
}

int NotSoStupidStrategy::takeCard() {
    return rand() % 10 + 1;
}

int NotSoStupidStrategy::play(int FirstCard, int FirstCardOfOpponent) {
    std::vector<int> History;
    History.push_back(FirstCard);
    int Sum = FirstCard;
    if (FirstCardOfOpponent == 10) {
        for (int i = 0; i < History.size(); ++i) {
            std::cout<<"History of not so stupid strategy: ";
            std::cout<<History[i]<< " ";
            std::cout<<std::endl;
        }
        return Pass;
    }
    int CurrentCard;
    while (Sum <= 18) {
        CurrentCard = takeCard();
        History.push_back(CurrentCard);
        Sum += CurrentCard;
    }
    std::cout<<"History of not so stupid strategy: ";
    for (int i = 0; i < History.size(); ++i) {
        std::cout<<History[i]<< " ";
    }
    std::cout<<std::endl;
    return Sum;
}