#include "Strategy.h"


class NotSoStupidStrategy : public Strategy {
public:
    void printName() override;
    ~NotSoStupidStrategy(){}
    int TakeCard() override;
    int Play(int) override;
private:

};

Strategy* createNotSoStupidStrategy ();
