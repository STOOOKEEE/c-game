#include "Combat.h"
#include "UI.h"
#include <iostream>

Combat::Combat(Player& player, std::map<std::string, ActAction>& actCatalog,
               std::vector<BestiaryEntry>& bestiary, std::mt19937& rng)
    : player(player), actCatalog(actCatalog), bestiary(bestiary), rng(rng) {}

int Combat::randomDamage(int hpMaxDefender) {
    std::uniform_int_distribution<int> dist(0, hpMaxDefender);
    return dist(rng);
}

void Combat::start(Monster* enemy) {
    while (player.isAlive() && enemy->isAlive()) {
        std::cout << std::endl;
        std::cout << "--- " << player.getName() << " HP: " << player.getHp() << "/" << player.getHpMax()
                  << " | " << enemy->getName() << " HP: " << enemy->getHp() << "/" << enemy->getHpMax()
                  << " | Mercy: " << enemy->getMercy() << "/" << enemy->getMercyGoal() << " ---" << std::endl;
        std::cout << std::endl;
        std::cout << "  FIGHT    ACT    ITEM    MERCY" << std::endl;
        std::cout << "   (1)     (2)     (3)     (4)" << std::endl;
        std::cout << "Choice: ";

        int choice = UI::readChoice();
        if (choice == -1) continue;

        bool turnUsed = false;
        switch (choice) {
            case 1:
                playerFight(enemy);
                turnUsed = true;
                break;
            case 2:
                playerAct(enemy);
                turnUsed = true;
                break;
            case 3:
                playerItem();
                turnUsed = true;
                break;
            case 4:
                if (playerMercy(enemy)) return;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
                continue;
        }

        if (!turnUsed) continue;

        if (enemy->isAlive()) {
            monsterTurn(enemy);
            if (!player.isAlive()) {
                UI::showGameOver();
                return;
            }
        }

        if (!enemy->isAlive()) {
            std::cout << std::endl;
            std::cout << "* " << enemy->getName() << " has been defeated!" << std::endl;
            enemy->setKilled(true);
            player.addKill();
            player.addVictory();
            bestiary.push_back({enemy->getName(), enemy->getCategoryStr(),
                               enemy->getHpMax(), enemy->getAtk(), enemy->getDef(), true});
            std::cout << "Victory! (" << player.getVictories() << "/10)" << std::endl;

            return;
        }
    }
}

void Combat::playerFight(Monster* enemy) {
    int dmg = randomDamage(enemy->getHpMax());
    if (dmg == 0) {
        std::cout << "* You attack but miss!" << std::endl;
    } else {
        enemy->takeDamage(dmg);
        std::cout << "* You attack " << enemy->getName() << " for " << dmg << " damage!" << std::endl;
    }
}

void Combat::playerAct(Monster* enemy) {
    const auto& acts = enemy->getActIds();
    int maxActs = enemy->getMaxActs();

    std::cout << "Choose an action:" << std::endl;
    for (int i = 0; i < maxActs && i < (int)acts.size(); i++) {
        auto it = actCatalog.find(acts[i]);
        if (it != actCatalog.end()) {
            std::string impact;
            if (it->second.mercyImpact > 0) impact = " [+Mercy]";
            else if (it->second.mercyImpact < 0) impact = " [-Mercy]";
            else impact = " [=]";
            std::cout << "  " << i + 1 << ". " << acts[i] << impact << std::endl;
        }
    }
    std::cout << "Choice: ";

    int choice = UI::readChoice();
    if (choice == -1) return;

    choice--;
    if (choice < 0 || choice >= maxActs || choice >= (int)acts.size()) {
        std::cout << "Invalid action." << std::endl;
        return;
    }

    auto it = actCatalog.find(acts[choice]);
    if (it == actCatalog.end()) {
        std::cout << "Unknown action." << std::endl;
        return;
    }

    std::cout << it->second.text << std::endl;
    enemy->modifyMercy(it->second.mercyImpact);
    std::cout << "  [Mercy: " << enemy->getMercy() << "/" << enemy->getMercyGoal() << "]" << std::endl;
}

void Combat::playerItem() {
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
        std::cout << "No items available!" << std::endl;
        return;
    }
    std::cout << "Choice: ";

    int choice = UI::readChoice();
    if (choice == -1) return;

    choice--;
    if (choice < 0 || choice >= (int)inv.size() || inv[choice].getQuantity() <= 0) {
        std::cout << "Invalid item." << std::endl;
        return;
    }

    int healAmount = inv[choice].getValue();
    inv[choice].use();
    player.heal(healAmount);
    std::cout << "* Used " << inv[choice].getName() << "! HP: "
              << player.getHp() << "/" << player.getHpMax() << std::endl;
}

bool Combat::playerMercy(Monster* enemy) {
    if (enemy->getMercy() >= enemy->getMercyGoal()) {
        std::cout << std::endl;
        std::cout << "* You spared " << enemy->getName() << "." << std::endl;
        std::cout << "* " << enemy->getName() << " walks away peacefully." << std::endl;
        enemy->setSpared(true);
        player.addSpare();
        player.addVictory();
        bestiary.push_back({enemy->getName(), enemy->getCategoryStr(),
                           enemy->getHpMax(), enemy->getAtk(), enemy->getDef(), false});
        std::cout << "Victory! (" << player.getVictories() << "/10)" << std::endl;

        return true;
    } else {
        std::cout << "* " << enemy->getName() << " is not ready to be spared yet. (Mercy: "
                  << enemy->getMercy() << "/" << enemy->getMercyGoal() << ")" << std::endl;
        return false;
    }
}

void Combat::monsterTurn(Monster* enemy) {
    int dmg = randomDamage(player.getHpMax());
    if (dmg == 0) {
        std::cout << "* " << enemy->getName() << " attacks but misses!" << std::endl;
    } else {
        player.takeDamage(dmg);
        std::cout << "* " << enemy->getName() << " attacks you for " << dmg
                  << " damage! (HP: " << player.getHp() << "/" << player.getHpMax() << ")" << std::endl;
    }
}
