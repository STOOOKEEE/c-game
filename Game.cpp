#include "Game.h"
#include "FileLoader.h"
#include "UI.h"
#include "Combat.h"
#include <iostream>

Game::Game() : player(nullptr), rng(std::random_device{}()) {
    actCatalog = createActCatalog();
}

Game::~Game() {
    delete player;
    for (auto* m : monsterTemplates) delete m;
}

void Game::run() {
    std::cout << "========================================" << std::endl;
    std::cout << "         Welcome to ALTERDUNE" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter your character name: ";
    std::string name;
    std::getline(std::cin, name);
    if (name.empty()) name = "Hero";

    player = new Player(name);

    if (!FileLoader::loadItems("items.csv", *player)) return;
    if (!FileLoader::loadMonsters("monsters.csv", monsterTemplates)) return;

    std::cout << std::endl;
    std::cout << "=== Game Start ===" << std::endl;
    std::cout << "Player: " << player->getName() << std::endl;
    std::cout << "HP: " << player->getHp() << "/" << player->getHpMax() << std::endl;
    std::cout << "Items:" << std::endl;
    for (auto& item : player->getInventory()) {
        std::cout << "  - " << item.getName() << " x" << item.getQuantity()
                  << " (heals " << item.getValue() << " HP)" << std::endl;
    }
    std::cout << std::endl;

    mainMenu();
}

void Game::mainMenu() {
    while (true) {
        if (player->getVictories() >= 10) {
            UI::showEnding(*player);
            return;
        }
        if (!player->isAlive()) {
            UI::showGameOver();
            return;
        }

        std::cout << "========================================" << std::endl;
        std::cout << "           MAIN MENU" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "  1. Bestiary" << std::endl;
        std::cout << "  2. Start Combat" << std::endl;
        std::cout << "  3. Character Stats" << std::endl;
        std::cout << "  4. Items" << std::endl;
        std::cout << "  5. Quit" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Choice: ";

        int choice = UI::readChoice();
        if (choice == -1) continue;

        switch (choice) {
            case 1: UI::showBestiary(bestiary); break;
            case 2: startCombat(); break;
            case 3: UI::showStats(*player); break;
            case 4: UI::showItems(*player); break;
            case 5:
                std::cout << "Goodbye!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}

void Game::startCombat() {
    if (monsterTemplates.empty()) {
        std::cout << "No monsters available!" << std::endl;
        return;
    }
    std::uniform_int_distribution<int> dist(0, (int)monsterTemplates.size() - 1);
    int idx = dist(rng);
    Monster* enemy = monsterTemplates[idx]->clone();

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  A wild " << enemy->getName() << " [" << enemy->getCategoryStr() << "] appears!" << std::endl;
    std::cout << "========================================" << std::endl;

    Combat combat(*player, actCatalog, bestiary, rng);
    combat.start(enemy);
    delete enemy;
}
