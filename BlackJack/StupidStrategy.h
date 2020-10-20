#include "Strategy.h"

class StupidStrategy : public Strategy {
public:
    ~StupidStrategy(){}
    int takeCard() override;
    int play(int, int) override;
private:

};

Strategy* createStupidStrategy ();
