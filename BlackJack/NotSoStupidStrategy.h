#include "Strategy.h"

class NotSoStupidStrategy : public Strategy {
public:
    ~NotSoStupidStrategy(){}
    int takeCard(int, int) override;
    int play(int, int, int, int) override;
    int details(std::vector<int> History, int CurrentCard) override;
private:

};

Strategy* createNotSoStupidStrategy ();
