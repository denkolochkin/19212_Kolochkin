#include "NotSoStupidStrategy.h"
#include "../Factory.h"

namespace {
    Strategy *createNotSoStupidStrategy () {
        return new NotSoStupidStrategy;
    }
}

void create() {
    Factory<Strategy, std::string,Strategy*(*)()>::
    getInstance()->addCreator("NotSoStupid", createNotSoStupidStrategy);
}

int NotSoStupidStrategy::play(int DealerCard) {
    std::vector<int> History;
    int Sum = 0;
    int CurrentCard = 0;
    handOut(History, Sum, CurrentCard, DealerCard);
    Sum += CurrentCard;
    if (getGameMode() == DETAILED) {
        if(details(History, CurrentCard, getName()) == QUIT) {
            return QUIT;
        }
    }
    while (Sum <= 18) {
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
