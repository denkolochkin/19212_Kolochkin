#pragma once

#include "Printer.h"

#include <vector>

class Strategy {
public:
    Strategy() = default;

    virtual ~Strategy(){};

    virtual int play(int DealerCard) = 0;

    void handOut(std::vector<int> &History, int &Sum, int &CurrentCard, int DealerCard) {
        History.push_back(DealerCard);
        Sum = DealerCard;
        CurrentCard = takeCard();
        History.push_back(CurrentCard);
        Sum += CurrentCard;
        CurrentCard = takeCard();
        History.push_back(CurrentCard);
        Sum += CurrentCard;
    };

    int takeCard() {
        if (CardMode == EASY) {
            return rand() % 10 + 1;
        }
        if (CardMode == DECK) {
            std::vector<int> Deck;
            int Card = 1;
            for (int i = 0; i < 53; ++i) {
                for (int j = 0; j < 4; ++j) {
                    Deck.push_back(Card);
                }
                if (Card < 10)
                    Card++;
            }
            int index = rand() % 52 + 1;
            return Deck[index];
        }
        if (CardMode == HARD) {
            std::vector<int> Deck;
            int Card = 1;
            for (int i = 0; i < NumberOfDecks; ++i) {
                for (int j = 0; j < 53; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        Deck.push_back(Card);
                    }
                    if (Card < 10)
                        Card++;
                }
            }
            int index = rand() % (52 * NumberOfDecks) + 1;
            return Deck[index];
        }
    };

    int details(std::vector<int> History, int CurrentCard, std::string Name) {
        Printer printer(Name);
        if (printer.PrintDetails(History, CurrentCard) == QUIT) {
            return QUIT;
        }
    };

    void pass(std::string Name) {
        Printer printer(Name);
        printer.PrintPass();
    };

    void setCardMode(int CardMode_) { CardMode = CardMode_; };

    void setGameMode(int GameMode_) { GameMode = GameMode_; };

    void setNumberOfDecks(int NumberOfDecks_) { NumberOfDecks = NumberOfDecks_; };

    int getGameMode() const { return GameMode; };

private:
    int CardMode;
    int GameMode;
    int NumberOfDecks;
};

