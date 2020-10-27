#include "Strategy.h"

class HardStrategy : public Strategy {
public:
    ~HardStrategy(){}
    int takeCard(int, int) override;
    int play(int, int, int, int) override;
    int details(std::vector<int> History, int CurrentCard) override;
};

Strategy* createHardStrategy ();
