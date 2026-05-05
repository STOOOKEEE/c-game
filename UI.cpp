#include "UI.h"
#include <iostream>
#include <limits>

int UI::readChoice() {
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

void UI::showBestiary(const std::vector<BestiaryEntry>& bestiary) {
    std::cout << std::endl;
    std::cout << "=== BESTIARY ===" << std::endl;
    if (bestiary.empty()) {
        std::cout << "No monsters defeated yet." << std::endl;
    } else {
        for (size_t i = 0; i < bestiary.size(); i++) {
            auto& e = bestiary[i];
            std::cout << i + 1 << ". " << e.getName() << " [" << e.getCategory() << "]"
                      << " | HP: " << e.getHpMax()
                      << " ATK: " << e.getAtk()
                      << " DEF: " << e.getDef()
                      << " | " << (e.wasKilled() ? "KILLED" : "SPARED") << std::endl;
        }
    }
    std::cout << std::endl;
}

void UI::showStats(const Player& player) {
    std::cout << std::endl;
    player.displayStats();
    std::cout << std::endl;
}

void UI::showItems(Player& player) {
    std::cout << std::endl;
    std::cout << "=== ITEMS ===" << std::endl;
    auto& inv = player.getInventory();
    bool hasItems = false;
    for (size_t i = 0; i < inv.size(); i++) {
        if (inv[i].getQuantity() > 0) {
            std::cout << "  " << i + 1 << ". " << inv[i].getName()
                      << " x" << inv[i].getQuantity()
                      << " (heals " << inv[i].getValue() << " HP)" << std::endl;
            hasItems = true;
        }
    }
    if (!hasItems) {
        std::cout << "  No items available." << std::endl;
        std::cout << std::endl;
        return;
    }
    std::cout << "  0. Back" << std::endl;
    std::cout << "Use item (0 to cancel): ";

    int choice = readChoice();
    if (choice <= 0) return;

    int index = choice - 1;
    if (index < 0 || index >= (int)inv.size()) {
        std::cout << "Invalid item." << std::endl;
        return;
    }
    if (inv[index].getQuantity() <= 0) {
        std::cout << "No more " << inv[index].getName() << " left!" << std::endl;
        return;
    }
    if (player.getHp() == player.getHpMax()) {
        std::cout << "HP is already full!" << std::endl;
        return;
    }
    inv[index].use();
    int healAmount = inv[index].getValue();
    player.heal(healAmount);
    std::cout << "Used " << inv[index].getName() << "! Healed " << healAmount
              << " HP. (HP: " << player.getHp() << "/" << player.getHpMax() << ")" << std::endl;
    std::cout << std::endl;
}

void UI::showEnding(const Player& player) {
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "       10 VICTORIES ACHIEVED!" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    int kills = player.getKills();
    int spares = player.getSpares();

    if (spares == 0 && kills > 0) {
        std::cout << "  === GENOCIDE ENDING ===" << std::endl;
        std::cout << "  You killed every monster you faced." << std::endl;
        std::cout << "  The world trembles in your wake..." << std::endl;
    } else if (kills == 0 && spares > 0) {
        std::cout << "  === PACIFIST ENDING ===" << std::endl;
        std::cout << "  You spared every monster you met." << std::endl;
        std::cout << "  Peace reigns across ALTERDUNE!" << std::endl;
    } else {
        std::cout << "  === NEUTRAL ENDING ===" << std::endl;
        std::cout << "  You killed " << kills << " and spared " << spares << " monsters." << std::endl;
        std::cout << "  The world remembers your choices..." << std::endl;
    }

    std::cout << std::endl;
    std::cout << "  Killed: " << kills << " | Spared: " << spares << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "         Thanks for playing!" << std::endl;
    std::cout << "========================================" << std::endl;
}

void UI::showGameOver() {
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "           YOU HAVE FALLEN..." << std::endl;
    std::cout << "            GAME OVER" << std::endl;
    std::cout << "========================================" << std::endl;
}
