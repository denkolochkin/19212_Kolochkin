#include <iostream>
#include "Factory.h"
#include "Strategy.h"
#define NotCard 0
#define Pass -1

void ChooseWinner (int first, int second) {
    if (first == Pass) {
        if (second <= 21) {
            std::cout << "Not so stupid strategy win with result: " << second << std::endl;
            return;
        }
        else {
            std::cout << "No winner"<< std::endl;
            std::cout<<"Not so stupid strategy lose - pass"<<std::endl;
            return;
        }
    }
    if (second == Pass) {
        if (first <= 21) {
            std::cout << "Stupid strategy win with result: " << first << std::endl;
            std::cout<<"Not so stupid strategy lose - pass"<<std::endl;
            return;
        }
        else {
            std::cout << "No winner"<< std::endl;
            return;
        }
    }
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

void TournamentOfTwo (std::unique_ptr<Strategy>& first, std::unique_ptr<Strategy>& second) {
    int FirstCard = first->takeCard();
    int ResultOfStupidStrategy = first->play(FirstCard, NotCard);
    int ResultOfNotSoStupidStrategy = second->play(second->takeCard(), FirstCard);
    ChooseWinner(ResultOfStupidStrategy, ResultOfNotSoStupidStrategy);
}


int main (int argc, char *argv[]) {
    std::string Stupid = "Stupid";
    std::string NotSoStupid = "NotSoStupid";

    std::unique_ptr<Strategy> StupidStrategy (Factory<Strategy,std::string,Strategy*(*)()>::getInstance()->makeStrategy(Stupid));
    std::unique_ptr<Strategy> NotSoStupidStrategy (Factory<Strategy,std::string,Strategy*(*)()>::getInstance()->makeStrategy(NotSoStupid));

    srand(time(0));

    TournamentOfTwo(StupidStrategy, NotSoStupidStrategy);

    return 0;
}
