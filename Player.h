#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Item.h"
#include <vector>

class Player : public Entity {
private:
    std::vector<Item> inventory;
    int kills;
    int spares;
    int victories;

public:
    Player(const std::string& name);

    // Accesseurs
    int getKills() const;
    int getSpares() const;
    int getVictories() const;
    std::vector<Item>& getInventory();

    // Modificateurs
    void addKill();
    void addSpare();
    void addVictory();
    void addItem(const Item& item);

    // Implementation de la methode virtuelle pure
    void displayStats() const override;
};

#endif
