#include "Strategy.h"

class StupidStrategy : public Strategy {
public:
    ~StupidStrategy(){}
    int takeCard(int, int) override;
    int play(int, int, int, int) override;
    int details(std::vector<int> History, int CurrentCard) override;
private:

};

Strategy* createStupidStrategy ();
