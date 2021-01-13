#include "HardStrategy.h"
#include "../Factory.h"

namespace {
    Strategy *createHardStrategy () {
        return new HardStrategy;
    }
}

void create() {
    Factory<Strategy, std::string,Strategy*(*)()>::
    getInstance()->addCreator("Hard", createHardStrategy);
}

int HardStrategy::play(int DealerCard) {
    std::vector<int> History;
    int Sum = 0;
    int CurrentCard = 0;
    handOut(History, Sum, CurrentCard, DealerCard);
    if (DealerCard <= 4) {
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
    if (Sum < 15) {
        while (Sum < 17) {
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
    if (Sum < 20) {
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
