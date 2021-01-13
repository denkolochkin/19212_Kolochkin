#include "TrivialStrategy.h"
#include "../Factory.h"

namespace {
    Strategy *createTrivialStrategy () {
        return new TrivialStrategy;
    }
}

void create() {
    Factory<Strategy, std::string,Strategy*(*)()>::
    getInstance()->addCreator("Trivial", createTrivialStrategy);
}

int TrivialStrategy::play(int DealerCard) {
    std::vector<int> History;
    int Sum = 0;
    int CurrentCard = 0;
    handOut(History, Sum, CurrentCard, DealerCard);
    if (getGameMode() == DETAILED) {
        if(details(History, CurrentCard, getName()) == QUIT) {
            return QUIT;
        }
    }
    if (DealerCard == 10 || Sum == 12) {
        if (getGameMode() == DETAILED) {
            pass(getName());
        }
        return Pass;
    }
    if (Sum < 15) {
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
    }
    return Sum;
}
