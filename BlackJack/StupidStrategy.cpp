#include "StupidStrategy.h"
#include "Factory.h"
#include <iostream>
#include <vector>

static bool g(){
    Factory<Strategy, std::string,Strategy*(*)()>::getInstance()->addCreator("Stupid", createStupidStrategy);
    return true;
}

static bool b=g();

void StupidStrategy::printName() {
    std::cout<<"Stupid"<<std::endl;
}

Strategy *createStupidStrategy () {
    return new StupidStrategy;
}

int StupidStrategy::TakeCard() {
    return rand() % 10 + 1;
}

int StupidStrategy::Play(int FirstCard) {
    std::vector<int> History;
    History.push_back(FirstCard);
    int Sum = FirstCard;
    int CurrentCard;
    while (Sum < 21) {
        CurrentCard = TakeCard();
        History.push_back(CurrentCard);
        Sum += CurrentCard;
    }
    std::cout<<"History of stupid strategy: ";
    for (int i = 0; i < History.size(); ++i) {
        std::cout<<History[i]<< " ";
    }
    std::cout<<std::endl;
    return Sum;
}
