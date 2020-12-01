#include "HardStrategy.h"
#include "Factory.h"
#include <iostream>
#include <vector>
#define Pass -2
#define EASY 1
#define DECK 2
#define HARD 3
#define DETAILED 0
#define QUIT -1

static bool g(){
    Factory<Strategy, std::string,Strategy*(*)()>::getInstance()->addCreator("Hard", createHardStrategy);
    return true;
}

static bool b=g();

Strategy *createHardStrategy () {
    return new HardStrategy;
}

int HardStrategy::details(std::vector<int> History, int CurrentCard) {
    std::cout<<"Details of hard strategy:"<<std::endl;
    std::cout<<"New card - "<<CurrentCard<<std::endl;
    std::cout<<"Cards of hard strategy strategy now: ";
    for (int i = 0; i < History.size(); ++i) {
        std::cout<<History[i]<< " ";
    }
    if (getchar() == 113) {
        return QUIT;
    }
}


int HardStrategy::takeCard(int CardMode, int NumberOfDecks) {
    if (CardMode == EASY) {
        return rand() % 10 + 1;
    }
    if (CardMode == DECK) {
        std::vector<int> Deck;
        int Card = 1;
        for (int i = 0; i < 53; ++i) {
            for (int j = 0; j < 4; ++j) {
                Deck.push_back(Card);
            }
            if (Card < 10)
                Card++;
        }
        int index = rand() % 52 + 1;
        return Deck[index];
    }
    if (CardMode == HARD) {
        std::vector<int> Deck;
        int Card = 1;
        for (int i = 0; i < NumberOfDecks; ++i) {
            for (int j = 0; j < 53; ++j) {
                for (int k = 0; k < 4; ++k) {
                    Deck.push_back(Card);
                }
                if (Card < 10)
                    Card++;
            }
        }
        int index = rand() % (52 * NumberOfDecks) + 1;
        return Deck[index];
    }
}

int HardStrategy::play(int DealerCard, int Mode, int NumberOfDecks, int GameMode) {
    std::vector<int> History;
    History.push_back(DealerCard);
    int Sum = DealerCard;
    int CurrentCard = takeCard(Mode, NumberOfDecks);
    History.push_back(CurrentCard);
    Sum += CurrentCard;
    CurrentCard = takeCard(Mode, NumberOfDecks);
    History.push_back(CurrentCard);
    Sum += CurrentCard;
    if (DealerCard <= 4) {
        if (GameMode == DETAILED) {
            printf("Hard strategy - pass \n");
        }
        return Pass;
    }
    if (GameMode == DETAILED) {
        if(details(History, CurrentCard) == QUIT) {
            return QUIT;
        }
    }
    if (Sum < 15) {
        while (Sum < 17) {
            CurrentCard = takeCard(Mode, NumberOfDecks);
            History.push_back(CurrentCard);
            Sum += CurrentCard;
            if (GameMode == DETAILED) {
                if(details(History, CurrentCard) == QUIT) {
                    return QUIT;
                }
            }
        }
    }
    if (Sum < 17) {
        CurrentCard = takeCard(Mode, NumberOfDecks);
        History.push_back(CurrentCard);
        Sum += CurrentCard;
        if (GameMode == DETAILED) {
            if(details(History, CurrentCard) == QUIT) {
                return QUIT;
            }
        }
    }
    if (Sum < 20) {
        CurrentCard = takeCard(Mode, NumberOfDecks);
        History.push_back(CurrentCard);
        Sum += CurrentCard;
        if (GameMode == DETAILED) {
            if(details(History, CurrentCard) == QUIT) {
                return QUIT;
            }
        }
    }
    return Sum;
}
