#include <iostream>
#include "Factory.h"
#include "Strategy.h"
#include <vector>
#define Pass -1
#define EASY 1
#define DECK 2
#define HARD 3
#define DETAILED 0
#define TOURNAMENT 1
#define FAST 4
#define QUIT -1

int ChooseWinner (int first, std::string firstName, int second, std::string secondName);

std::unique_ptr<Strategy>& TournamentOfTwo (std::unique_ptr<Strategy>& first, std::string firstName, std::unique_ptr<Strategy>& second,std::string secondName, int Mode, int NumberOfDecks, int GameMode);

void fast (std::string first, std::string second, int CardMode, int NumberOfDecks, int GameMode);

void Tournament(std::vector<std::string> Players , int CardMode, int NumberOfDecks, int GameMode);
