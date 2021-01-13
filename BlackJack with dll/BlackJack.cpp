#include "BlackJack.h"
#include "Factory.h"
#include "Printer.h"

#include <filesystem>
#include <dlfcn.h>

BlackJack::BlackJack(std::vector<std::string> currentPlayers_, int CardMode_,
                     int NumberOfDecks_, int GameMode_)
                     : currentPlayers(currentPlayers_), CardMode(CardMode_),
                     NumberOfDecks(NumberOfDecks_), GameMode(GameMode_) {
    Register();
}

std::unique_ptr<Strategy>& BlackJack::TournamentOfTwo(
                                                       std::unique_ptr<Strategy>& first,
                                                       std::string firstName,
                                                       std::unique_ptr<Strategy>& second,
                                                       std::string secondName
                                                       ) {
    (*first).setCardMode(CardMode);
    (*first).setGameMode(GameMode);
    (*first).setNumberOfDecks(NumberOfDecks);
    (*second).setCardMode(CardMode);
    (*second).setGameMode(GameMode);
    (*second).setNumberOfDecks(NumberOfDecks);
    int DealerCard = first->takeCard();
    int ResultOfFirst = first->play(DealerCard);
    if (ResultOfFirst == QUIT) {
        first = nullptr;
        return first;
    }
    int ResultOfSecond = second->play(DealerCard);
    if (ResultOfSecond == QUIT) {
        second = nullptr;
        return second;
    }
    Printer printer(ResultOfFirst, ResultOfSecond, firstName, secondName);
    int ResultOfWinner = printer.PrintWinner();
    if (ResultOfWinner == ResultOfFirst) {
        return first;
    }
    if (ResultOfWinner == ResultOfSecond) {
        return second;
    }
    first = nullptr;
    second = nullptr;
    return first;
}

void BlackJack::fast(std::string Player1, std::string Player2) {
    std::unique_ptr<Strategy> FirstStrategy(
                                            Factory<Strategy, std::string, Strategy *(*)()>::
                                            getInstance()->makeStrategy(Player1)
                                            );
    std::unique_ptr<Strategy> SecondStrategy(
                                             Factory<Strategy, std::string, Strategy *(*)()>::
                                             getInstance()->makeStrategy(Player2)
                                             );
    std::unique_ptr<Strategy> &Winner = TournamentOfTwo(
                                                    FirstStrategy, Player1,
                                                    SecondStrategy, Player2
                                                       );
    if (Winner == FirstStrategy) {
        WinnerName = Player1;
    }
    else if (Winner == SecondStrategy) {
        WinnerName = Player2;
    }
    else {
        WinnerName = "No winner";
    }

}

void BlackJack::Tournament(std::vector<std::string> Players) {
    if (Players.size() == 0) {
        return;
    }
    currentPlayers = Players;
    std::string first;
    std::string second;
    for (int i = 0; i < Players.size() - 1; ++i) {
        for (int j = i + 1; j < Players.size(); ++j) {
            first = Players[i];
            second = Players[j];
            fast(first, second);
        }
    }
}

void BlackJack::Register() {
    std::string path = "/Users/deniskolockin/CLionProjects/lab2b_new/dylibs";
    for (const auto &i : std::filesystem::directory_iterator(path)) {
        void* handle;
        void (*f)();
        char* error;
        std::string i_path = i.path();
        char* tmp = const_cast<char*>(i_path.c_str());
        handle = dlopen(tmp, RTLD_LAZY);
        f = (void(*)())(dlsym(handle, "Create"));
        error = dlerror();
        if (error) {
            return;
        }
        (*f)();
    }
}
