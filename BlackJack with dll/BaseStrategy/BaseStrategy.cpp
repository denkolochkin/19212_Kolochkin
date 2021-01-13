#include "BaseStrategy.h"
#include "../Factory.h"

namespace {
    Strategy *createBaseStrategy () {
        return new BaseStrategy;
    }
}

void create() {
    Factory<Strategy, std::string,Strategy*(*)()>::
    getInstance()->addCreator("Base", createBaseStrategy);
}

int BaseStrategy::play(int DealerCard) {
    std::vector<int> History;
    int Sum = 0;
    int CurrentCard  = 0;
    handOut(History, Sum, CurrentCard, DealerCard);
    if (getGameMode() == DETAILED) {
        if(details(History, CurrentCard, getName()) == QUIT) {
            return QUIT;
        }
    }
    if (Sum - DealerCard < 12 && DealerCard < 10) {
        while (Sum < 20) {
            CurrentCard = takeCard();
            History.push_back(CurrentCard);
            Sum += CurrentCard;
            if (getGameMode() == DETAILED) {
                if(details(History, CurrentCard, getName()) == QUIT) {
                    return QUIT;
                }
            }
        }
    }
    if (Sum < 17) {
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
