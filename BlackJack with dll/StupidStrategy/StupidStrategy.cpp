#include "StupidStrategy.h"
#include "../Factory.h"

namespace {
    Strategy *createStupidStrategy () {
        return new StupidStrategy;
    }
}

void create() {
    Factory<Strategy, std::string,Strategy*(*)()>::
    getInstance()->addCreator("Stupid", createStupidStrategy);
}

int StupidStrategy::play(int DealerCard) {
    std::vector<int> History;
    int Sum = 0;
    int CurrentCard = 0;
    handOut(History, Sum, CurrentCard, DealerCard);
    if (getGameMode() == DETAILED) {
        if(details(History, CurrentCard, getName()) == QUIT) {
            return QUIT;
        }
    }
    if (DealerCard == 5 || Sum == 14) {
        if (getGameMode() == DETAILED) {
            pass(getName());
        }
        return Pass;
    }
    while (Sum < 21) {
        CurrentCard = takeCard();
        History.push_back(CurrentCard);
        Sum += CurrentCard;
        if (getGameMode() == DETAILED) {
            if(details(History, CurrentCard, getName()) == QUIT) {
                return QUIT;
            }
        }
    }
    return Sum;
}
