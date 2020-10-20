#include "NotSoStupidStrategy.h"
#include "Factory.h"
#include <iostream>
#include <vector>

static bool g(){
    Factory<Strategy, std::string,Strategy*(*)()>::getInstance()->addCreator("NotSoStupid", createNotSoStupidStrategy);
    return true;
}

static bool b=g();

void NotSoStupidStrategy::printName() {
    std::cout<<"NotSoStupid"<<std::endl;
}

Strategy *createNotSoStupidStrategy () {
    return new NotSoStupidStrategy;
}

int NotSoStupidStrategy::TakeCard() {
    return rand() % 10 + 1;
}

int NotSoStupidStrategy::Play(int FirstCard) {
    std::vector<int> History;
    History.push_back(FirstCard);
    int Sum = FirstCard;
    int CurrentCard;
    while (Sum <= 18) {
        CurrentCard = TakeCard();
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
