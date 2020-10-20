#include "StupidStrategy.h"
#include "Factory.h"
#include <iostream>
#include <vector>

static bool g(){
    Factory<Strategy, std::string,Strategy*(*)()>::getInstance()->addCreator("Stupid", createStupidStrategy);
    return true;
}

static bool b=g();



Strategy *createStupidStrategy () {
    return new StupidStrategy;
}

int StupidStrategy::takeCard() {
    return rand() % 10 + 1;
}

int StupidStrategy::play(int FirstCard, int FirstCardOfOpponent) {
    std::vector<int> History;
    History.push_back(FirstCard);
    int Sum = FirstCard;
    int CurrentCard;
    while (Sum < 21) {
        CurrentCard = takeCard();
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
