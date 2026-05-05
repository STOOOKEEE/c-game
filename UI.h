#ifndef UI_H
#define UI_H

#include "Player.h"
#include "BestiaryEntry.h"
#include <vector>

class UI {
public:
    static void showBestiary(const std::vector<BestiaryEntry>& bestiary);
    static void showStats(const Player& player);
    static void showItems(Player& player);
    static void showEnding(const Player& player);
    static void showGameOver();
    static int readChoice();
};

#endif
