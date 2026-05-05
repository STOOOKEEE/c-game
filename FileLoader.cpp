#include "FileLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string FileLoader::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}

bool FileLoader::loadItems(const std::string& filename, Player& player) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string name, type, valStr, qtyStr;
        if (!std::getline(ss, name, ';')) continue;
        if (!std::getline(ss, type, ';')) continue;
        if (!std::getline(ss, valStr, ';')) continue;
        if (!std::getline(ss, qtyStr, ';') && !std::getline(ss, qtyStr)) continue;

        name = trim(name);
        type = trim(type);
        valStr = trim(valStr);
        qtyStr = trim(qtyStr);

        try {
            int value = std::stoi(valStr);
            int qty = std::stoi(qtyStr);
            player.addItem(Item(name, type, value, qty));
        } catch (...) {
            std::cerr << "Warning: malformed line in " << filename << ": " << line << std::endl;
        }
    }
    return true;
}

bool FileLoader::loadMonsters(const std::string& filename, std::vector<Monster*>& monsterTemplates) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string catStr, name, hpStr, atkStr, defStr, mercyStr;
        std::string act1, act2, act3, act4;

        if (!std::getline(ss, catStr, ';')) continue;
        if (!std::getline(ss, name, ';')) continue;
        if (!std::getline(ss, hpStr, ';')) continue;
        if (!std::getline(ss, atkStr, ';')) continue;
        if (!std::getline(ss, defStr, ';')) continue;
        if (!std::getline(ss, mercyStr, ';')) continue;
        std::getline(ss, act1, ';');
        std::getline(ss, act2, ';');
        std::getline(ss, act3, ';');
        std::getline(ss, act4);

        catStr = trim(catStr);
        name = trim(name);
        act1 = trim(act1); act2 = trim(act2);
        act3 = trim(act3); act4 = trim(act4);

        try {
            int hp = std::stoi(trim(hpStr));
            int atk = std::stoi(trim(atkStr));
            int def = std::stoi(trim(defStr));
            int mercyGoal = std::stoi(trim(mercyStr));

            MonsterCategory cat;
            if (catStr == "NORMAL") cat = MonsterCategory::NORMAL;
            else if (catStr == "MINIBOSS") cat = MonsterCategory::MINIBOSS;
            else if (catStr == "BOSS") cat = MonsterCategory::BOSS;
            else continue;

            std::vector<std::string> acts;
            if (act1 != "-" && !act1.empty()) acts.push_back(act1);
            if (act2 != "-" && !act2.empty()) acts.push_back(act2);
            if (act3 != "-" && !act3.empty()) acts.push_back(act3);
            if (act4 != "-" && !act4.empty()) acts.push_back(act4);

            Monster* m = nullptr;
            switch (cat) {
                case MonsterCategory::NORMAL:
                    m = new NormalMonster(name, hp, atk, def, cat, mercyGoal, acts);
                    break;
                case MonsterCategory::MINIBOSS:
                    m = new MiniBossMonster(name, hp, atk, def, cat, mercyGoal, acts);
                    break;
                case MonsterCategory::BOSS:
                    m = new BossMonster(name, hp, atk, def, cat, mercyGoal, acts);
                    break;
            }
            if (m) monsterTemplates.push_back(m);
        } catch (...) {
            std::cerr << "Warning: malformed line in " << filename << ": " << line << std::endl;
        }
    }
    return !monsterTemplates.empty();
}
