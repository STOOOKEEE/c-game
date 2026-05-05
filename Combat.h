#ifndef COMBAT_H
#define COMBAT_H

#include "Player.h"
#include "Monster.h"
#include "ActAction.h"
#include "BestiaryEntry.h"
#include <vector>
#include <map>
#include <random>

class Combat {
private:
    Player& player;
    std::map<std::string, ActAction>& actCatalog;
    std::vector<BestiaryEntry>& bestiary;
    std::mt19937& rng;

    int randomDamage(int hpMaxDefender);
    void playerFight(Monster* enemy);
    void playerAct(Monster* enemy);
    void playerItem();
    bool playerMercy(Monster* enemy);
    void monsterTurn(Monster* enemy);

public:
    Combat(Player& player, std::map<std::string, ActAction>& actCatalog,
           std::vector<BestiaryEntry>& bestiary, std::mt19937& rng);

    void start(Monster* enemy);
};

#endif
