#include "Strategy.h"

class BaseStrategy : public Strategy {
public:
    ~BaseStrategy(){}
    int takeCard(int, int) override;
    int play(int, int, int, int) override;
    int details(std::vector<int> History, int CurrentCard) override;

};

Strategy* createBaseStrategy ();
