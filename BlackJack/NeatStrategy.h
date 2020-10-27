#include "Strategy.h"

class NeatStrategy : public Strategy {
public:
    ~NeatStrategy(){}
    int takeCard(int, int) override;
    int play(int, int, int, int) override;
    int details(std::vector<int> History, int CurrentCard) override;

};

Strategy* createNeatStrategy ();
