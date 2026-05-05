#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Monster.h"
#include "ActAction.h"
#include "BestiaryEntry.h"
#include <vector>
#include <map>
#include <random>

class Game {
private:
    Player* player;
    std::vector<Monster*> monsterTemplates;
    std::vector<BestiaryEntry> bestiary;
    std::map<std::string, ActAction> actCatalog;
    std::mt19937 rng;

    void mainMenu();
    void startCombat();

public:
    Game();
    ~Game();
    void run();
};

#endif
