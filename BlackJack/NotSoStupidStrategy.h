#include "Strategy.h"

class NotSoStupidStrategy : public Strategy {
public:
    ~NotSoStupidStrategy(){}
    int takeCard() override;
    int play(int,int) override;
private:

};

Strategy* createNotSoStupidStrategy ();
