#include "Strategy.h"

class StupidStrategy : public Strategy {
public:
    void printName() override;
    ~StupidStrategy(){}
    int TakeCard() override;
    int Play(int) override;
private:

};

Strategy* createStupidStrategy ();
