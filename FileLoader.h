#ifndef FILELOADER_H
#define FILELOADER_H

#include "Player.h"
#include "Monster.h"
#include <string>
#include <vector>

class FileLoader {
public:
    static bool loadItems(const std::string& filename, Player& player);
    static bool loadMonsters(const std::string& filename, std::vector<Monster*>& monsterTemplates);

private:
    static std::string trim(const std::string& str);
};

#endif
