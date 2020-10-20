#include <iostream>
#include "Factory.h"
#include "Strategy.h"

void ChooseWinner (int first, int second) {
    if (first == 21) {
        std::cout << "Stupid strategy - BlackJack" << std::endl;
        return;
    }
    if (second == 21) {
        std::cout << "Not so stupid strategy - BlackJack" << std::endl;
        return;
    }
    if (first > 21) {
        if (second < 21) {
            std::cout << "Not so stupid strategy win with result: " << second << std::endl;
            std::cout << "Stupid strategy lose with result: " << first << std::endl;
            return;
        }
        std::cout << "No winner"<< std::endl;
        return;
    }
    if (second > 21) {
        if (first < 21) {
            std::cout << "Stupid strategy win with result: " << first << std::endl;
            std::cout << "Not so stupid strategy lose  with result: " << second << std::endl;
            return;
        }
        std::cout << "No winner"<< std::endl;
        return;
    }
}


int main (int argc, char *argv[]) {
    std::string Stupid = "Stupid";
    std::string NotSoStupid = "NotSoStupid";

    std::unique_ptr<Strategy> StupidStrategy (Factory<Strategy,std::string,Strategy*(*)()>::getInstance()->makeStrategy(Stupid));
    std::unique_ptr<Strategy> NotSoStupidStrategy (Factory<Strategy,std::string,Strategy*(*)()>::getInstance()->makeStrategy(NotSoStupid));

    srand(time(0));
    int FirstCard = StupidStrategy->TakeCard();
    int ResultOfStupidStrategy = StupidStrategy->Play(FirstCard);
    int ResultOfNotSoStupidStrategy = NotSoStupidStrategy->Play(StupidStrategy->TakeCard());

   ChooseWinner(ResultOfStupidStrategy, ResultOfNotSoStupidStrategy);

   return 0;
}
