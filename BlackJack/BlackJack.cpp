#include "BlackJack.h"
#include "Printer.h"
#include "Factory.h"

BlackJack::BlackJack() {}

BlackJack::~BlackJack() {}

BlackJack::BlackJack(BlackJack &b) {
    currentPlayers = b.currentPlayers;
    CardMode = b.CardMode;
    NumberOfDecks = b.NumberOfDecks;
    GameMode = b.GameMode;
    WinnerName = b.WinnerName;
}

BlackJack& BlackJack::operator=(BlackJack &b) {
    if (!(*this == b)) {
        currentPlayers = b.currentPlayers;
        CardMode = b.CardMode;
        NumberOfDecks = b.NumberOfDecks;
        GameMode = b.GameMode;
        WinnerName = b.WinnerName;
    }
    return *this;
}

bool BlackJack::operator==(BlackJack &b) {
    return currentPlayers == b.currentPlayers &&
           CardMode == b.CardMode &&
           NumberOfDecks == b.NumberOfDecks &&
           GameMode == b.GameMode &&
           WinnerName == b.WinnerName;
}

std::unique_ptr<Strategy>& BlackJack::TournamentOfTwo(
                                                       std::unique_ptr<Strategy>& first,
                                                       std::string firstName,
                                                       std::unique_ptr<Strategy>& second,
                                                       std::string secondName
                                                       ) {
    int DealerCard = first->takeCard(CardMode, NumberOfDecks);
    int ResultOfFirst = first->play(DealerCard, CardMode, NumberOfDecks, GameMode);
    if (ResultOfFirst == QUIT) {
        first = nullptr;
        return first;
    }
    int ResultOfSecond = second->play(DealerCard, CardMode, NumberOfDecks, GameMode);
    if (ResultOfSecond == QUIT) {
        second = nullptr;
        return second;
    }
    Printer printer;
    printer.first = ResultOfFirst;
    printer.firstName = firstName;
    printer.second = ResultOfSecond;
    printer.secondName = secondName;
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

void BlackJack::fast(std::vector<std::string> Players) {
    std::unique_ptr<Strategy> FirstStrategy(
                                            Factory<Strategy, std::string, Strategy *(*)()>::
                                            getInstance()->makeStrategy(Players[0])
                                            );
    std::unique_ptr<Strategy> SecondStrategy(
                                             Factory<Strategy, std::string, Strategy *(*)()>::
                                             getInstance()->makeStrategy(Players[1])
                                             );
    std::unique_ptr<Strategy> &Winner = TournamentOfTwo(
                                                    FirstStrategy, Players[0],
                                                    SecondStrategy, Players[1]
                                                       );
    if (FirstStrategy == nullptr) {
        WinnerName = "No winner";
    }
    if (Winner == FirstStrategy) {
        WinnerName = Players[0];
    }
    if (Winner == SecondStrategy) {
        WinnerName = Players[1];
    }

}

void BlackJack::Tournament(std::vector<std::string> Players) {
    if (Players.size() == 0) {
        return;
    }
    currentPlayers.resize(currentPlayers.size());
    currentPlayers = Players;
    std::string first;
    std::string second;
    for (int i = 0; i < Players.size() - 1; ++i) {
        for (int j = i + 1; j < Players.size(); ++j) {
            first = Players[i];
            second = Players[j];
            std::unique_ptr<Strategy> FirstStrategy (Factory<Strategy, std::string, Strategy *(*)()>::
                                                     getInstance()->makeStrategy(first));
            std::unique_ptr<Strategy> SecondStrategy (Factory<Strategy, std::string, Strategy *(*)()>::
                                                      getInstance()->makeStrategy(second));
            std::unique_ptr<Strategy> &Winner = TournamentOfTwo(FirstStrategy, first,
                                                                SecondStrategy, second
                                                                );
        }
    }
}
