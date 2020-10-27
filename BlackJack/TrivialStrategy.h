#include "Strategy.h"

class TrivialStrategy : public Strategy {
public:
    ~TrivialStrategy(){}
    int takeCard(int, int) override;
    int play(int, int, int, int) override;
    int details(std::vector<int> History, int CurrentCard) override;
private:

};

Strategy* createTrivialStrategy ();
