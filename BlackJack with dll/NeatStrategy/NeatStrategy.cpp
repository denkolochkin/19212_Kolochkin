#include "NeatStrategy.h"
#include "../Factory.h"

namespace {
    Strategy *createNeatStrategy () {
        return new NeatStrategy;
    }
}

void create() {
    Factory<Strategy, std::string,Strategy*(*)()>::
    getInstance()->addCreator("Neat", createNeatStrategy);
}

int NeatStrategy::play(int DealerCard) {
    std::vector<int> History;
    int Sum = 0;
    int CurrentCard = 0;
    handOut(History, Sum, CurrentCard, DealerCard);
    if (DealerCard <= 5) {
        if (getGameMode() == DETAILED) {
            pass(getName());
        }
        return Pass;
    }
    if (getGameMode() == DETAILED) {
        if(details(History, CurrentCard, getName()) == QUIT) {
            return QUIT;
        }
    }
    if (Sum > 10 && Sum < 15) {
        CurrentCard = takeCard();
        History.push_back(CurrentCard);
        Sum += CurrentCard;
        if (getGameMode() == DETAILED) {
            if(details(History, CurrentCard, getName()) == QUIT) {
                return QUIT;
            }
        }
    }
    if (Sum > 14 && Sum < 17) {
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
